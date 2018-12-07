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

#include "parameters.h"

/*! \def BATTERY_WARNING_UNKNOWN
    \brief Valeur décrivant un état inconnu de la batterie
 */
#define BATTERY_WARNING_UNKNOWN             (-1.0)

/*! \def VITESSE_ANG_INITIAL
    \brief Valeur décrivant la valeur initial des consignes de commandes 
 */
#define CONSIGNE_INITIAL                    (0.0)

/*! \def ANGLE_INITIAL
    \brief Valeur décrivant la valeur initial de angle
 */
#define ANGLE_INITIAL                       (0.0)

/*! \def VITESSE_ANG_INITIAL
    \brief Valeur décrivant la valeur initial de vitesse angulaire
 */
#define VITESSE_ANG_INITIAL                 (0.0)

/*! \def DIRECTION_INITIAL
    \brief Valeur décrivant la valeur initial de angle de direction
 */
#define DIRECTION_INITIAL                   (0.0)

/*! \def BETA_INITIAL    
    \brief Valeur décrivant la valeur initial de beta
 */
#define BETA_INITIAL                        (0.0)

/**
 * \fn Constructeur de classe
 * \brief Constructeur de l'objet Angles.
 */
Parameters::Parameters() {
    angularPosition = ANGLE_INITIAL;
    angularSpeed = VITESSE_ANG_INITIAL;
    linearSpeed = 0.0;
    battery = BATTERY_LEVEL_UNKNOWN;
    beta = BETA_INITIAL;
    torque = CONSIGNE_INITIAL;
    userPresence = false;
    emergencyStop = false;
}

/**
 * \fn Destructeur de classe
 * \brief Destructeur de l'objet Angles.
 */
Parameters::~Parameters(void) {
}

// Getters

/**
 * \fn float angle()
 * \brief Accesseur de la valeur _angle  de l'objet Angles.
 * \return _angle
 */
float Parameters::AngularPosition() {
    return this->angularPosition;
}

/**
 * \fn float vitesse_ang()
 * \brief Accesseur de la valeur _vitesse_ang  de l'objet Angles.
 * \return _vitesse_ang
 */
float Parameters::AngularSpeed() {
    return this->angularSpeed;
}

float Parameters::LinearSpeed() {
    return this->linearSpeed;
}

float Parameters::Battery() {
    return this->battery;
}

float Parameters::Torque() {
    return this->torque;
}

float Parameters::Beta() {
    return this->beta;
}

bool Parameters::UserPresence() {
    return this->userPresence;
}

bool Parameters::EmergencyStop() {
    return this->emergencyStop;
}


/**
 * \fn void set_angle(float theta)
 * \brief Mise à jour de l'angle de l'objet Angles.
 * \param theta Nouvelle valeur de l'angle (entre -20.0 et 20.0)
 */
void Parameters::SetAngularPosition(float angle) {
    this->angularPosition = angle;
}

/**
 * \fn void set_vitesse_ang(float thetap)
 * \brief Mise à jour de la vitesse angulaire de l'objet Angles.
 * \param theta Nouvelle valeur de la vitesse angulaire
 */
void Parameters::SetAngularSpeed(float angularSpeed) {
    this->angularSpeed = angularSpeed;
}

void Parameters::SetLinearSpeed(float linearSpeed) {
    this->linearSpeed = linearSpeed;
}

void Parameters::SetBattery(float battery) {
    this->battery = battery;
}

void Parameters::SetTorque(float torque) {
    this->torque = torque;
}

void Parameters::SetBeta(float beta) {
    this->beta = beta;
}

void Parameters::SetUserPresence(bool state) {
    this->userPresence = state;
}

void Parameters::SetEmergencyStop(bool state) {
    this->emergencyStop = state;
}

