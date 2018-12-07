/*
 * Copyright (C) 2018 dimercur
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * 
 * \brief Class holding tasks et realtime objects (semaphors, mutex ...)
 *
 */

#include <iostream>

#include "tasks.h"
#include "control.h"

#include <stdexcept>
#include <string>

#define PRIORITY_TH_COMMUNICATION 50
#define PRIORITY_TH_ASSERVISSEMENT 81
#define PRIORITY_TH_AFFICHAGE 70
#define PRIORITY_TH_BATTERIE 73
#define PRIORITY_TH_PRESENCEUSER 75
#define PRIORITY_TH_ENVOYER 90
#define PRIORITY_TH_ARRET_URGENCE 95

#define SERVER_PORT 2345

using namespace std;

void Tasks::Init() {
    int err;
    int status;

    /**************************************************************************************/
    /* 	Mutex creation                                                                    */
    /**************************************************************************************/
    if (err = rt_mutex_create(&mutexStm32Write, "mutexAngleBeta"))
        throw std::runtime_error{"Error creating mutexAngleBeta " + string(strerror(-err))};

    cout << "Mutexes created successfully" << endl;

    /**************************************************************************************/
    /* 	Semaphors creation       							  */
    /**************************************************************************************/
    if (err = rt_sem_create(&semSendGui, "semSendGui", 0, TM_INFINITE))
        throw std::runtime_error{"Error creating semSendGui " + string(strerror(-err))};

    cout << "Semaphors created successfully" << endl;

    /**************************************************************************************/
    /* Tasks creation                                                                     */
    /**************************************************************************************/
    if (err = rt_task_create(&taskStm32Handler, "taskStm32", 0, PRIORITY_TH_COMMUNICATION, 0)) 
        throw std::runtime_error{"Error creating taskStm32 " + string(strerror(-err))};

    if (err = rt_task_create(&taskSystemControlHandler, "taskSystemControlHandler", 0, PRIORITY_TH_ASSERVISSEMENT, 0)) 
        throw std::runtime_error{"Error creating taskSystemControlHandler " + string(strerror(-err))};

    if (err = rt_task_create(&taskGuiHandler, "taskGui", 0, PRIORITY_TH_AFFICHAGE, 0)) 
        throw std::runtime_error{"Error creating taskGui " + string(strerror(-err))};

    cout << "Tasks created successfully" << endl;

    /**************************************************************************************/
    /* Message queues creation                                                            */
    /**************************************************************************************/
    err = rt_queue_create(&queueFromStm32, "queueFromStm32", sizeof (Message*)*50, Q_UNLIMITED, Q_FIFO);
    
    if (err < 0) {
        switch (err) {
            case (-EINVAL):
                throw std::runtime_error{"rt_queue_create error: invalid mode or poolsize is 0"};
                break;
            case (-ENOMEM):
                throw std::runtime_error{"rt_queue_create error: system fails to get memory"};
                break;
            case (-EEXIST):
                throw std::runtime_error{"rt_queue_create error: name conflict"};
                break;
            case (-EPERM):
                throw std::runtime_error{"rt_queue_create error: called by asynchronous context"};
                break;
        }
    } else 
        cout << "Queues created successfully" << endl << endl;

    /* Open com port with STM32 */
    cout << "Open STM32 com (";
    status = this->comStm32->Open();
    cout << status;
    cout << ")" << endl;

    if (status >= 0) {
        // Open server

        status = this->comGui->Open(SERVER_PORT);
        cout << "Open server on port " << SERVER_PORT << " (" << status << ")" << endl;

        if (status < 0) throw std::runtime_error {
            "Unable to start server on port " +std::to_string(SERVER_PORT)
        };
    } else 
        throw std::runtime_error {"Unable to open serial port /dev/ttyS0 "};
}

void Tasks::StartTasks() {
    int err;

    if (err = rt_task_start(&taskStm32Handler, (void (*)(void*))&Tasks::TaskStm32Reception, this))
        throw std::runtime_error{"Error when starting taskStm32 : " + string(strerror(-err))};

    if (err = rt_task_start(&taskGuiHandler,(void (*)(void*))&Tasks::TaskGui, this))
        throw std::runtime_error{"Error when starting taskStm32 : " + string(strerror(-err))};
}

void Tasks::DeleteTasks() {
    rt_task_delete(&this->taskGuiHandler);
    rt_task_delete(&this->taskStm32Handler);
}

void Tasks::UpdateParameters(Message *msg) {
    int id;
    string *str;

    if (msg != NULL) {
        id = msg->GetID();

        switch (id) {
            case MESSAGE_ANGLE_POSITION:
                parameters->SetAngularPosition(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_ANGULAR_SPEED:
                parameters->SetAngularSpeed(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_BATTERY:
                parameters->SetBattery(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_BETA:
                parameters->SetBeta(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_LINEAR_SPEED:
                parameters->SetLinearSpeed(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_TORQUE:
                parameters->SetTorque(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_EMERGENCY_STOP:
                parameters->SetEmergencyStop(((MessageBool*) msg)->GetState());
                break;
            case MESSAGE_USER_PRESENCE:
                parameters->SetUserPresence(((MessageBool*) msg)->GetState());
                break;
            case MESSAGE_EMPTY:
            case MESSAGE_LOG:
            default:
                /* nothing to do, yet !*/
                break;
        }
    }
}

/* La tâche ComSTM32Task est chargée de mettre en place la communication avec le STM32,
 *  à la réception d'un mesage du STM, elle décripte la trame et met à jour les informations
 *  des variables partagées.
 * fonctions : init_serial, read_from_serial, printf_trame
 * variables : etat_com, etat_reception */
void Tasks::TaskStm32Reception(void *arg) {
    //    int uart0_filestream = -1;
    //    int i;
    //    int com = 0;
    //    int etat_rep = 0;
    //    unsigned char tx_buffer[20];
    //    unsigned char *p_tx_buffer;
    //    message_serial *m;
    //
    //    rt_printf("Thread Communication : Debut de l'éxecution de periodique à 50 Hz\n");
    //    rt_task_set_periodic(NULL, TM_NOW, 20000000);
    //
    //    log_task_entered();
    //
    //    while (1) {
    //
    //        rt_task_wait_period(NULL);
    //
    //        uart0_filestream = init_serial(); // Initialise la connexion avec l'UART
    //
    //        if (uart0_filestream == -1) {
    //            rt_printf("Can't Use the UART\n");
    //        } else {
    //            m = (message_serial*) malloc(5 * sizeof (message_serial));
    //            m = read_from_serial();
    //            write_trame_to_data(m);
    //        }
    //    }
    Message *msg;

    cout << "Start ComSTM32Task task" << endl;

    while (1) {
        //Read incoming command from stm32
        msg = this->comStm32->Read();
        this->UpdateParameters(msg);
    }
}

/*  La tâche Affichage communique à l'interface graphique (GUI) (qui s'éxécute dans le noyau Linux) à travers un socket, 
 *  les valeurs des variables partagées du programme de temps réel
 *  cette fonction n'a pas à être modifiée, à part modification du GUI et ajout d'informations à envoyer 
 * fonctions : add_info_float, send_trame
 * variables : etat_angle, vitesse_lin, consigne_couple, batterie, presence_user, etat_com, arret */
void Tasks::TaskGui(void *arg) {

    //    unsigned char *str;
    //    int indice = 0;
    //    int bat, user, stop, com;
    //    float tamp1 = 0.0f, tamp2 = 0.0f, tamp3 = 0.0f, tamp4 = 0.0f;
    //    int sckt_gui;
    //
    //    sckt_gui = init_socket(PORT_GUI);
    //
    //    rt_printf("Thread Affichage : Debut de l'éxecution de periodique à 10 Hz\n");
    //    rt_task_set_periodic(NULL, TM_NOW, 100000000);
    //
    //    log_task_entered();
    //
    //    while (1) {
    //
    //        rt_task_wait_period(NULL);
    //
    //        str = (unsigned char*) malloc(56 * sizeof (unsigned char)); // 56 = (n * 7 ) avec n nombre de fonctions "add_info"
    //
    //        rt_mutex_acquire(&mutexAnglePosition, TM_INFINITE);
    //        log_mutex_acquired(&mutexAnglePosition);
    //
    //        tamp1 = etat_angle.angle();
    //        tamp2 = etat_angle.vitesse_ang();
    //
    //        rt_mutex_release(&mutexAnglePosition);
    //        log_mutex_released(&mutexAnglePosition);
    //
    //        rt_mutex_acquire(&mutexAngleBeta, TM_INFINITE);
    //        log_mutex_acquired(&mutexAngleBeta);
    //
    //        tamp3 = beta.beta();
    //
    //        rt_mutex_release(&mutexAngleBeta);
    //        log_mutex_released(&mutexAngleBeta);
    //
    //        rt_mutex_acquire(&mutexTorque, TM_INFINITE);
    //        log_mutex_acquired(&mutexTorque);
    //
    //        tamp4 = consigne_couple.consigne();
    //
    //        rt_mutex_release(&mutexTorque);
    //        log_mutex_released(&mutexTorque);
    //
    //        rt_mutex_acquire(&mutexBattery, TM_INFINITE);
    //        log_mutex_acquired(&mutexBattery);
    //
    //        bat = batterie.level();
    //
    //        rt_mutex_release(&mutexBattery);
    //        log_mutex_released(&mutexBattery);
    //
    //        rt_mutex_acquire(&mutexUserPresence, TM_INFINITE);
    //        log_mutex_acquired(&mutexUserPresence);
    //
    //        user = presence_user;
    //
    //        rt_mutex_release(&mutexUserPresence);
    //        log_mutex_released(&mutexUserPresence);
    //
    //        rt_mutex_acquire(&mutexComState, TM_INFINITE);
    //        log_mutex_acquired(&mutexComState);
    //
    //        com = etat_com;
    //
    //        rt_mutex_release(&mutexComState);
    //        log_mutex_released(&mutexComState);
    //
    //        rt_mutex_acquire(&mutexEmergencyStop, TM_INFINITE);
    //        log_mutex_acquired(&mutexEmergencyStop);
    //
    //        stop = arret;
    //
    //        rt_mutex_release(&mutexEmergencyStop);
    //        log_mutex_released(&mutexEmergencyStop);
    //
    //        add_info_float(str, 'p', tamp1, &indice);
    //        add_info_float(str, 's', tamp2, &indice);
    //        add_info_float(str, 'v', tamp3, &indice);
    //        add_info_float(str, 'c', tamp4, &indice);
    //
    //        add_info_float(str, 'b', bat, &indice);
    //        add_info_float(str, 'u', user, &indice);
    //        add_info_float(str, 'e', com, &indice);
    //        add_info_float(str, 'a', stop, &indice);
    //
    //        send_trame(sckt_gui, str, &indice);
    //    }

    Message *msg;
    float torque;

    cout << "Start GUITask task" << endl;

    rt_task_set_periodic(NULL, TM_NOW, 10000000);

    while (1) {
        rt_task_wait_period(NULL);

        if ((this->parameters->UserPresence() == false) || (this->parameters->Battery() < 10.0)) {
            if (this->parameters->EmergencyStop() == false) cout << "Raise emergency signal" << endl;
            this->parameters->SetEmergencyStop(true);

            msg = new MessageBool(MESSAGE_EMERGENCY_STOP, this->parameters->EmergencyStop());
            this->comStm32->Write(msg);

            torque = 0.0;
        } else {
            if (this->parameters->EmergencyStop() == true) cout << "Drop emergency signal" << endl;

            this->parameters->SetEmergencyStop(false);
            torque = Control::ComputeTorque(this->parameters->AngularPosition(), this->parameters->AngularSpeed());
        }

        this->parameters->SetTorque(torque);
        msg = new MessageFloat(MESSAGE_TORQUE, this->parameters->Torque());
        this->comStm32->Write(msg);

        this->comGui->Write(new MessageFloat(MESSAGE_ANGLE_POSITION, this->parameters->AngularPosition()));
        this->comGui->Write(new MessageFloat(MESSAGE_BATTERY, this->parameters->Battery()));
        this->comGui->Write(new MessageFloat(MESSAGE_BETA, this->parameters->Beta()));
        this->comGui->Write(new MessageBool(MESSAGE_USER_PRESENCE, this->parameters->UserPresence()));
        this->comGui->Write(new MessageFloat(MESSAGE_TORQUE, this->parameters->Torque()));
        this->comGui->Write(new MessageFloat(MESSAGE_ANGULAR_SPEED, this->parameters->AngularSpeed()));
        this->comGui->Write(new MessageFloat(MESSAGE_LINEAR_SPEED, this->parameters->LinearSpeed()));
        this->comGui->Write(new MessageBool(MESSAGE_EMERGENCY_STOP, this->parameters->EmergencyStop()));
    }
}