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

#include "angles.h"
#include "battery.h"
#include "beta.h"
#include "consigne.h"
#include "lib_monitor.h"
#include "lib_serial.h"
#include "lib_msg_GUI.h"

using namespace std;

int arret;
int etat_com;
int etat_reception;
int presence_user;

Angles etat_angle;
Battery batterie;
Consigne consigne_couple;
Beta beta ;
/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}

