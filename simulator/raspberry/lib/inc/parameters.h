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
 * \brief Déclaration de la classe Parameters.
 * \author INSA Toulouse
 * \version 1.0
 * \date 25 Juillet 2017
 */

#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

//#ifdef __cplusplus
//extern "C" {
//#endif

/*! \def BATTERY_LEVEL_UNKNOWN
    \brief Valeur décrivant un niveau inconnu de la batterie
 */
#define BATTERY_LEVEL_UNKNOWN               (-1.0)

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

/*********** etat_com **************/

/*! \def CONNECTE
    \brief Valeur décrivant la valeur de etat_com lorsque la communication fonctionne
 */
#define CONNECTE              (1)

/*! \def NON_CONNECTE
    \brief Valeur décrivant la valeur de etat_com lorsque la communication est rompue
 */
#define NON_CONNECTE              (0)

class Parameters {
private:
    float angle;
    float angularSpeed;
    float linearSpeed;
    float battery;
    float torque;
    float beta;
    bool userPresence;
    bool emergencyStop;
    bool communicationState;

public:
    Parameters();
    ~Parameters();
    
    // getters
    float Angle();
    float AngularSpeed();
    float LinearSpeed();
    float Battery();
    float Torque();
    float Beta();
    bool UserPresence();
    bool EmergencyStop();
    bool CommunicationState();
    
    // setters                
    void SetAngle(float angle);
    void SetAngularSpeed(float angularSpeed);
    void SetLinearSpeed(float linearSpeed);
    void SetBattery(float battery);
    void SetTorque(float torque);
    void SetBeta(float beta);
    void SetUserPresence(bool state);
    void SetEmergencyStop(bool state);
    void CommunicationState(bool state);
};

//#ifdef __cplusplus
//}
//#endif
#endif /* __PARAMETERS_H__ */
