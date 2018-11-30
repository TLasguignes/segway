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
 * \brief Déclaration de la classe Control.
 * \author INSA Toulouse
 * \version 1.0
 * \date 25 Juillet 2017
 */

#ifndef __CONTROL_H__
#define __CONTROL_H__

class Control {
public:
    static float ComputeTorque(float AnglePosition, float AngularSpeed);
    
private:
    Control();
    ~Control();
};

#endif /* __CONTROL_H__ */
