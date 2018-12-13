/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dimercur
 *
 * Created on 14 novembre 2018, 15:56
 */

#include <cstdlib>
#include <iostream>
#include <thread>

#include "parameters.h"
#include "messages.h"
#include "comstm32.h"

#include <time.h>
#include "comgui.h"
#include "control.h"

using namespace std;

int arret;
int etat_com;
int etat_reception;
int presence_user;
bool sysTick = false;

ComStm32 *com = new ComStm32();
ComGui *comGui = new ComGui();
Parameters parameters;

std::thread *threadTimer;
std::thread *threadCom;

void DecodeMessage(Message *msg) {
    int id;
    string *str;

    if (msg != NULL) {
        id = msg->GetID();

        switch (id) {
            case MESSAGE_ANGLE_POSITION:
                parameters.SetAngle(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_ANGULAR_SPEED:
                parameters.SetAngularSpeed(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_BATTERY:
                parameters.SetBattery(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_BETA:
                parameters.SetBeta(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_LINEAR_SPEED:
                parameters.SetLinearSpeed(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_TORQUE:
                parameters.SetTorque(((MessageFloat*) msg)->GetValue());
                break;
            case MESSAGE_EMERGENCY_STOP:
                parameters.SetEmergencyStop(((MessageBool*) msg)->GetState());
                break;
            case MESSAGE_USER_PRESENCE:
                parameters.SetUserPresence(((MessageBool*) msg)->GetState());
                break;
            case MESSAGE_EMPTY:
            case MESSAGE_LOG:
            default:

                break;
        }
    }
}

void ThreadCom(void) {
    Message *msg;

    while (1) {
        //Read incoming command from stm32
        msg = com->Read();
        DecodeMessage(msg);
    }
}

void ThreadTimer(void) {
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 10000000;
    int cnt = 0;

    while (1) {
        //std::this_thread::sleep_for(std::chrono::seconds )
        //sleep(1);
        if (nanosleep(&tim, &tim2) < 0) {
            printf("Nano sleep system call failed \n");
            return;
        }

        cnt++;

        if (cnt >= 1) {
            sysTick = true;
            cnt = 0;
        }
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    Message *a;
    MessageFloat *f;

    int status;
    int counter = 0;

    float torque;

    cout << "Open STM32 com (";
    status = com->Open();
    cout << status;
    cout << ")" << endl;

    if (status >= 0) {

        // open Server and wait for Client
        status = comGui->Open(2345);
        cout << "Open server on port 2345 (" << status << ")" << endl;

        // Wait client to connect
        status = comGui->AcceptClient();
        if (status >= 0) {

            cout << "Client connected, rock'n'roll baby !" << endl;
            threadTimer = new std::thread(ThreadTimer);
            threadCom = new std::thread(ThreadCom);

            while (1) {
                if (sysTick == true) {
                    sysTick = false;

                    if ((parameters.UserPresence() == false) || (parameters.Battery() < 10.0)) {
                        
                        if (parameters.EmergencyStop()==false) cout << "Raise emergency signal" << endl;
                        parameters.SetEmergencyStop(true);
                        
                        a = new MessageBool(MESSAGE_EMERGENCY_STOP, parameters.EmergencyStop());
                        com->Write(a);
                        
                        torque = 0.0;
                    }
                    else
                    {
                        if (parameters.EmergencyStop()==true) cout << "Drop emergency signal" << endl;
                        
                        parameters.SetEmergencyStop(false);
                        torque = Control::ComputeTorque(parameters.Angle(), parameters.AngularSpeed());
                    }
                    
                    parameters.SetTorque(torque);
                    f = new MessageFloat(MESSAGE_TORQUE, parameters.Torque());
                    com->Write(f);
                    
                    comGui->Write(new MessageFloat(MESSAGE_ANGLE_POSITION, parameters.Angle()));
                    comGui->Write(new MessageFloat(MESSAGE_BATTERY, parameters.Battery()));
                    comGui->Write(new MessageFloat(MESSAGE_BETA, parameters.Beta()));
                    comGui->Write(new MessageBool(MESSAGE_USER_PRESENCE, parameters.UserPresence()));
                    comGui->Write(new MessageFloat(MESSAGE_TORQUE, parameters.Torque()));
                    comGui->Write(new MessageFloat(MESSAGE_ANGULAR_SPEED, parameters.AngularSpeed()));
                    comGui->Write(new MessageFloat(MESSAGE_LINEAR_SPEED, parameters.LinearSpeed()));
                    comGui->Write(new MessageBool(MESSAGE_EMERGENCY_STOP, parameters.EmergencyStop()));
                }
            }
        }

        com->Close();

    } else return -1;

    return 0;
}

