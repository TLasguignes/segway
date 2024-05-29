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

#ifndef __CONTROL_H__
#define __CONTROL_H__

/**
 * Namespace for control algorithms
 * 
 * @brief Process control algorithms
 * 
 */
namespace Control {
    /**
     * Algorithm for computing control torque needed to bring user angle (beta) to 0
     * @param anglePosition Angle between segway and ground
     * @param angularSpeed Angular speed of wheel
     * @return Torque to provide to STM32 for bring back Beta angle to zero
     */
    static float ComputeTorque(float anglePosition, float angularSpeed);
}

#endif /* __CONTROL_H__ */
