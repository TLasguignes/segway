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

//#include "trace.h"
//#include "comstm32.h"
//#include "comgui.h"

using namespace std;

int arret;
int etat_com;
int etat_reception;
int presence_user;

/*Angles etat_angle;
Battery batterie;
Consigne consigne_couple;
Beta beta ;*/

/*
 * 
 */
int main(int argc, char** argv) {
    Message *a;
    MessageFloat *f;
    MessageString *s;
    MessageBool *b;
    
    a = new Message();
    cout << "Message " << a->ToString() << endl;
    
    f = new MessageFloat(MESSAGE_ANGLE_POSITION, 10.5);
    cout << "MessageFloat " << f->ToString() << endl;
    
    s = new MessageString(MESSAGE_LOG, "Should crash here");
    cout << "MessageString " << s->ToString() << endl;
    
    b = new MessageBool(MESSAGE_USER_PRESENCE, true);
    cout << "MessageString " << b->ToString() << endl;
    
    delete (a);
    a=(Message*)f;
    cout << "Message " << a->ToString() << endl;
    
    return 0;
}

