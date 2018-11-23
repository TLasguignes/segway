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

#ifndef LIB_MONITOR_H
#define LIB_MONITOR_H

#ifndef __WITH_PTHREAD__
#include "../../includes.h"

#define SARG_SIZE 20

typedef enum {SEM, MUTEX, TASK, TASK_DELETE} message_type;

typedef struct
{
  message_type type;
  int time;
  char task_name[SARG_SIZE];
  char event[SARG_SIZE];
  char sarg0[SARG_SIZE];
  char sarg1[SARG_SIZE];
  char sarg2[SARG_SIZE];
  int iarg0;
  int iarg1;
} message_log;

#ifdef	__cplusplus
extern "C" {
#endif
  int get_time_us();
  int get_time_ms();
  void stop_recording();
  int init_recording();
  void log_wait_for_mutex(RT_MUTEX  * mut);
  void log_mutex_acquired(RT_MUTEX * mut);
  void log_mutex_released(RT_MUTEX * mut);
  void log_sem_waiting(RT_SEM * sem);
  void log_sem_entered(RT_SEM * sem);
  void log_sem_signaled(RT_SEM * sem);
  void log_task_entered();
  void log_task_new_iteration();
  void log_task_ended();
  void log_task_deleted(RT_TASK * task);

#ifdef	__cplusplus
}
#endif

#endif /* __WITH_PTHREAD__ */
#endif
