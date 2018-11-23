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
  * \date 20 Juillet 2017
  */

#ifndef __LIB_MSG_GUI_H__
#define __LIB_MSG_GUI_H__

#define PORT_GUI 8000 /* server's port */
#define PORT_LOG 8001

using namespace std;
        
int init_socket(int port);
void add_info_float(unsigned char * str, char label, float data,int *indice);
void add_info_int(unsigned char * str, char label, int data,int *indice);
void send_trame(int sock, unsigned char * msg,int* indice);

#endif /* __LIB_MSG_GUI_H__ */
