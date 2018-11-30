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
 * \brief Source de la classe Consigne
 * \author INSA Toulouse
 * \version 1.0
 * \date 25 Juillet 2017
 *
 * Implémentation de la classe Consigne
 *
 */

#include "control.h"

#define k1 -25.8598f		/* Coefficients de l'asservissement */
#define k2 -6.5593f

float Control::ComputeTorque(float AnglePosition, float AngularSpeed)
{
    float torque;
    
    torque = -1.0*(k1 * AnglePosition + k2 * AngularSpeed);
    return torque;
}
