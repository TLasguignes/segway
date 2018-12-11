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



#include <iostream>

#include "tasks.h"
#include "control.h"

#include <stdexcept>
#include <string>

/**
 * @brief priority level for tasks
 */
#define PRIORITY_TH_COMMUNICATION 50
#define PRIORITY_TH_ASSERVISSEMENT 81
#define PRIORITY_TH_AFFICHAGE 70
#define PRIORITY_TH_BATTERIE 73
#define PRIORITY_TH_PRESENCEUSER 75
#define PRIORITY_TH_ENVOYER 90
#define PRIORITY_TH_ARRET_URGENCE 95

/**
 * @brief Server port: can be changed, in case of trouble (port already used=
 */
#define SERVER_PORT 2345

using namespace std;

/**
 * Initialize communication (open ports and server) and reset parameters
 * Create RT objects (semaphores / mutex/ queues / tasks)
 */

void Tasks::Init() {
    int err;
    int status;

    /**************************************************************************************/
    /* 	Mutex creation                                                                    */
    /**************************************************************************************/
    if (err = rt_mutex_create(&mutexStm32Write, "mutexAngleBeta"))
        throw std::runtime_error {
        "Error creating mutexAngleBeta " + string(strerror(-err))
    };

    cout << "Mutexes created successfully" << endl;

    /**************************************************************************************/
    /* 	Semaphors creation       							  */
    /**************************************************************************************/
    if (err = rt_sem_create(&semSendGui, "semSendGui", 0, TM_INFINITE))
        throw std::runtime_error {
        "Error creating semSendGui " + string(strerror(-err))
    };

    cout << "Semaphors created successfully" << endl;

    /**************************************************************************************/
    /* Tasks creation                                                                     */
    /**************************************************************************************/
    if (err = rt_task_create(&taskStm32Handler, "taskStm32", 0, PRIORITY_TH_COMMUNICATION, 0))
        throw std::runtime_error {
        "Error creating taskStm32 " + string(strerror(-err))
    };

    if (err = rt_task_create(&taskSystemControlHandler, "taskSystemControlHandler", 0, PRIORITY_TH_ASSERVISSEMENT, 0))
        throw std::runtime_error {
        "Error creating taskSystemControlHandler " + string(strerror(-err))
    };

    if (err = rt_task_create(&taskGuiHandler, "taskGui", 0, PRIORITY_TH_AFFICHAGE, 0))
        throw std::runtime_error {
        "Error creating taskGui " + string(strerror(-err))
    };

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
            "Unable to start server on port " + std::to_string(SERVER_PORT)
        };
    } else
        throw std::runtime_error {
        "Unable to open serial port /dev/ttyS0 "
    };
}

/**
 * Launch tasks, realtime system starts here
 */
void Tasks::StartTasks() {
    int err;

    if (err = rt_task_start(&taskStm32Handler, (void (*)(void*)) & Tasks::TaskStm32Reception, this))
        throw std::runtime_error {
        "Error when starting taskStm32 : " + string(strerror(-err))
    };

    if (err = rt_task_start(&taskGuiHandler, (void (*)(void*)) & Tasks::TaskGui, this))
        throw std::runtime_error {
        "Error when starting taskStm32 : " + string(strerror(-err))
    };
}

/**
 * Clean destruction of tasks, realtime system stops here
 */
void Tasks::DeleteTasks() {
    rt_task_delete(&this->taskGuiHandler);
    rt_task_delete(&this->taskStm32Handler);
}

/**
 * Helper function for storing parameter value in correct parameter objetc
 * @param msg Message to store value into parameters object
 */
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

/**
 * Task use for reception of data from STM32
 * @param arg In the case of a member of a class, this parameter holds a reference to surrounding object (this, normaly)
 */
void Tasks::TaskStm32Reception(void *arg) {
    Message *msg;

    cout << "Start ComSTM32Task task" << endl;

    while (1) {
        //Read incoming command from stm32
        msg = this->comStm32->Read();
        this->UpdateParameters(msg);
    }
}

/**
 * Task use to send data to user interface (through server)
 * @param arg In the case of a member of a class, this parameter holds a reference to surrounding object (this, normaly)
 */
void Tasks::TaskGui(void *arg) {
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

/**
 * Task use to process control loop
 * @param arg In the case of a member of a class, this parameter holds a reference to surrounding object (this, normaly)
 */
void TaskSystemControl(void * arg) {

}