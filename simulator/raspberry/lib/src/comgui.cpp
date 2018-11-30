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
 * \author INSA Toulouse
 * \version 1.0
 * \date 20 Juillet 2017
 */

#include "comgui.h"
#include <iostream>
#include <sys/socket.h>

#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <algorithm>

const string LABEL_GUI_ANGULAR_POSITION = "AngularPosition";
const string LABEL_GUI_ANGULAR_SPEED = "AngularSpeed";
const string LABEL_GUI_BATTERY_LEVEL = "Battery";
const string LABEL_GUI_LINEAR_SPEED = "LinearSpeed";
const string LABEL_GUI_USER_PRESENCE = "User";
const string LABEL_GUI_BETA_ANGLE = "Beta";
const string LABEL_GUI_TORQUE = "Torque";
const string LABEL_GUI_EMERGENCY_STOP = "Emergency";
const string LABEL_GUI_LOG = "Log";

/**
        Fonction utilisée par le thread affichage pour initialisation de socket
 */

int ComGui::Open(int port) {
    struct sockaddr_in server;

    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        perror("Can not create socket");
        exit(-1);
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (bind(socketFD, (struct sockaddr *) &server, sizeof (server)) < 0) {
        perror("Can not bind socket");
        exit(-1);
    }

    listen(socketFD, 1);

    return socketFD;
}

void ComGui::Close() {
    close(socketFD);

    socketFD = -1;
}

int ComGui::AcceptClient() {
    struct sockaddr_in client;
    int c = sizeof (struct sockaddr_in);

    clientID = accept(socketFD, (struct sockaddr *) &client, (socklen_t*) & c);

    if (clientID < 0) {
        perror("Accept failed in AcceptClient");
        exit(-1);
    }

    return clientID;
}

/**
        Envoie une trame vers l'affichage
        @params int sock : numéro de socket
        @params char * msg : tableau de caractères à envoyer, maximum 256 caractères
 */
void ComGui::Write(Message* msg) {
    string *str;
    
    // Call user method before Write
    Write_Pre();
    
    /* Convert message to string to send to GUI */
    str = MessageToString(msg);
    
    //cout << "Message sent to GUI: " << str->c_str() << endl;
    write(clientID, str->c_str(), str->length());
    
    delete(str);
    
    // Call user method after write
    Write_Post();
}

string *ComGui::MessageToString(Message *msg)
{
    int id;
    string *str;
    
    if (msg != NULL) {
        id = msg->GetID();
        
        switch (id)
        {
            case MESSAGE_ANGLE_POSITION:
                str = new string(LABEL_GUI_ANGULAR_POSITION+"="+to_string(((MessageFloat*)msg)->GetValue())+"\n");
                replace(str->begin(), str->end(), '.', ','); // Mono C# require float to have a , instead of a .
                break;
            case MESSAGE_ANGULAR_SPEED:
                str = new string(LABEL_GUI_ANGULAR_SPEED+"="+to_string(((MessageFloat*)msg)->GetValue())+"\n");
                replace(str->begin(), str->end(), '.', ','); // Mono C# require float to have a , instead of a .
                break;
            case MESSAGE_BATTERY:
                str = new string(LABEL_GUI_BATTERY_LEVEL+"="+to_string(((MessageFloat*)msg)->GetValue())+"\n");
                replace(str->begin(), str->end(), '.', ','); // Mono C# require float to have a , instead of a .
                break;
            case MESSAGE_BETA:
                str = new string(LABEL_GUI_BETA_ANGLE+"="+to_string(((MessageFloat*)msg)->GetValue())+"\n");
                replace(str->begin(), str->end(), '.', ','); // Mono C# require float to have a , instead of a .
                break;
            case MESSAGE_LINEAR_SPEED:
                str = new string(LABEL_GUI_LINEAR_SPEED+"="+to_string(((MessageFloat*)msg)->GetValue())+"\n");
                replace(str->begin(), str->end(), '.', ','); // Mono C# require float to have a , instead of a .
                break;
            case MESSAGE_TORQUE:
                str = new string(LABEL_GUI_TORQUE+"="+to_string(((MessageFloat*)msg)->GetValue())+"\n");
                replace(str->begin(), str->end(), '.', ','); // Mono C# require float to have a , instead of a .
                break;
            case MESSAGE_EMERGENCY_STOP:
                str = new string(LABEL_GUI_EMERGENCY_STOP+"=");
                if (((MessageBool*)msg)->GetState())
                    str->append("True\n");
                else
                    str->append("False\n");
                break;
            case MESSAGE_USER_PRESENCE:
                str = new string(LABEL_GUI_USER_PRESENCE+"=");
                if (((MessageBool*)msg)->GetState())
                    str->append("True\n");
                else
                    str->append("False\n");
                break;
            case MESSAGE_EMPTY:
                str = new string(""); //empty string
                break;
            case MESSAGE_LOG:
                str = new string(LABEL_GUI_LOG+"="+((MessageString*)msg)->GetString()+"\n");
                break;
            default:
                str = new string(""); //empty string
                break;
        }
    }
    
    return str;
}
