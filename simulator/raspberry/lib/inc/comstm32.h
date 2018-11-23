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
 * \date 20 Mai 2017
 */

#ifndef LIB_SERIAL_H
#define LIB_SERIAL_H

#include "../../includes.h"

#define MESSAGE_SERIAL_LENGTH 37
#define MESSAGE_TIMEOUT_NS 2000

typedef struct
{
  char label;
  float value;
} message_serial;

typedef struct
{
	char label;
	float fval;
	int ival;
} message_stm;

extern int lost_com;

#ifdef	__cplusplus
extern "C" {
#endif

  int init_serial();
  message_serial* read_from_serial();
  int send_float_to_serial(float fl_value, char label);
  int send_int_to_serial(int int_value, char label);
  int bytes_to_array_of_message(unsigned char * mesg, message_serial *m);
  float bytes_to_float(unsigned char * bytes);
  int close_serial();

  void write_trame_to_data(message_serial *m);
  
#ifdef	__cplusplus
}
#endif

#endif
