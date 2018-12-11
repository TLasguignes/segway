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

/**
 * @brief Initial torque value
 */
#define INITIAL_TORQUE              (0.0)

/**
 * @brief Initial angular position
 */
#define INITIAL_ANGLE_POSITION      (0.0)

/**
 * @brief Initial angular speed
 * 
 */
#define INITIAL_ANGULAR_SPEED       (0.0)

/**   
 * @brief Initial beta angle
 */
#define INITIAL_BETA                (0.0)

/**
 * Create new Parameter object, with parameters initialized to default value
 */
Parameters::Parameters() {
    angularPosition = INITIAL_ANGLE_POSITION;
    angularSpeed = INITIAL_ANGULAR_SPEED;
    linearSpeed = 0.0;
    battery = BATTERY_LEVEL_UNKNOWN;
    beta = INITIAL_BETA;
    torque = INITIAL_TORQUE;
    userPresence = false;
    emergencyStop = false;
}

/**
 * Destroy Parameter object
 */
Parameters::~Parameters(void) {
}

// Getters

/**
 * Get current angular position
 * @return Current angular position (segway)
 */
float Parameters::AngularPosition() {
    return this->angularPosition;
}

/**
 * Get current angular speed
 * @return Current angular speed
 */
float Parameters::AngularSpeed() {
    return this->angularSpeed;
}

/**
 * Get current linear speed
 * @return Current linear speed
 */
float Parameters::LinearSpeed() {
    return this->linearSpeed;
}

/**
 * Get current battery level
 * @return Current battery level
 */
float Parameters::Battery() {
    return this->battery;
}

/**
 * Get current torque (as provided by STM32)
 * @return Current torque
 */
float Parameters::Torque() {
    return this->torque;
}

/**
 * Get current beta angle 
 * @return Current beta angle
 */
float Parameters::Beta() {
    return this->beta;
}

/**
 * Get user presence
 * @return true if user is present, false otherwise
 */
bool Parameters::UserPresence() {
    return this->userPresence;
}

/**
 * Get emergency state
 * @return True if emergency signal must be raised, false otherwise
 */
bool Parameters::EmergencyStop() {
    return this->emergencyStop;
}

/**
 * Set angular position
 * @param angle Float value for current angular position
 */
void Parameters::SetAngularPosition(float angle) {
    this->angularPosition = angle;
}

/**
 * Set angular speed
 * @param angularSpeed Float value for current angular speed
 */
void Parameters::SetAngularSpeed(float angularSpeed) {
    this->angularSpeed = angularSpeed;
}

/**
 * Set linear speed
 * @param linearSpeed Float value for current linear speed
 */
void Parameters::SetLinearSpeed(float linearSpeed) {
    this->linearSpeed = linearSpeed;
}

/**
 * Set battery level
 * @param battery Float value for current battery level
 */
void Parameters::SetBattery(float battery) {
    this->battery = battery;
}

/**
 * Set torque
 * @param torque Float value for current torque
 */
void Parameters::SetTorque(float torque) {
    this->torque = torque;
}

/**
 * Set beta angle
 * @param beta Float value for current beta angle
 */
void Parameters::SetBeta(float beta) {
    this->beta = beta;
}

/**
 * Set user presence
 * @param state Boolean representation of user presence
 */
void Parameters::SetUserPresence(bool state) {
    this->userPresence = state;
}

/**
 * Set emergency state
 * @param state boolean representing emergency state
 */
void Parameters::SetEmergencyStop(bool state) {
    this->emergencyStop = state;
}

