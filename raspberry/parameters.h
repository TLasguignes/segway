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

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

/**
 * @brief Constant for unknown battery value
 */
#define BATTERY_LEVEL_UNKNOWN               (-1.0)

/**
 * Class containing all system parameters (variables)
 * 
 * @brief Class containing all system parameters (variables)
 * 
 */
class Parameters {
private:
    /**
     * Angle between segway platform and ground (from -20° to 20°, around -PI/8 to PI/8)
     */
    float angularPosition;

    /**
     * Angular Speed of wheel (from -xxx to +xxx)
     */
    float angularSpeed;

    /**
     * Linear Speed of segway (from -xxx to +xxx)
     */
    float linearSpeed;

    /**
     * Battery level (from 0.0 to 100.0, -1.0 if unknown)
     */
    float battery;

    /**
     * Torque provided to wheel (output of process control)
     */
    float torque;

    /**
     * Angle between user and platform (from -20° to 20°, around -PI/8 to PI/8)
     */
    float beta;

    /**
     * Indicate if user is present (true) or not (false)
     */
    bool userPresence;

    /**
     * Signal to send to STM32 in case of emergency (low bat or user missing)
     */
    bool emergencyStop;

public:
    /**
     * Create new Parameter object, with parameters initialized to default value
     */
    Parameters();

    /**
     * Destroy Parameter object
     */
    ~Parameters();

    /**
     * Get current angular position
     * @return Current angular position (segway)
     */
    float AngularPosition();

    /**
     * Get current angular speed
     * @return Current angular speed
     */
    float AngularSpeed();

    /**
     * Get current linear speed
     * @return Current linear speed
     */
    float LinearSpeed();

    /**
     * Get current battery level
     * @return Current battery level
     */
    float Battery();

    /**
     * Get current torque (as provided by STM32)
     * @return Current torque
     */
    float Torque();

    /**
     * Get current beta angle 
     * @return Current beta angle
     */
    float Beta();

    /**
     * Get user presence
     * @return true if user is present, false otherwise
     */
    bool UserPresence();

    /**
     * Get emergency state
     * @return True if emergency signal must be raised, false otherwise
     */
    bool EmergencyStop();

    /**
     * Set angular position
     * @param angle Float value for current angular position
     */
    void SetAngularPosition(float angle);

    /**
     * Set angular speed
     * @param angularSpeed Float value for current angular speed
     */
    void SetAngularSpeed(float angularSpeed);

    /**
     * Set linear speed
     * @param linearSpeed Float value for current linear speed
     */
    void SetLinearSpeed(float linearSpeed);

    /**
     * Set battery level
     * @param battery Float value for current battery level
     */
    void SetBattery(float battery);

    /**
     * Set torque
     * @param torque Float value for current torque
     */
    void SetTorque(float torque);

    /**
     * Set beta angle
     * @param beta Float value for current beta angle
     */
    void SetBeta(float beta);

    /**
     * Set user presence
     * @param state Boolean representation of user presence
     */
    void SetUserPresence(bool state);

    /**
     * Set emergency state
     * @param state boolean representing emergency state
     */
    void SetEmergencyStop(bool state);
};

#endif /* __PARAMETERS_H__ */
