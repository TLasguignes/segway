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
 * 
 * \brief Class holding tasks et realtime objects (semaphors, mutex ...)
 *
 */

#ifndef __TASKS_H__
#define __TASKS_H__

#include <alchemy/task.h>
#include <alchemy/mutex.h>
#include <alchemy/sem.h>
#include <alchemy/timer.h>
#include <alchemy/queue.h>

#include "comgui.h"
#include "comstm32.h"
#include "messages.h"
#include "parameters.h"

using namespace std;

/**
 *\brief Static class Tasks
 */
class Tasks {
public:
    static void Init();
    static void StartTasks();
    static void DeleteTasks();
    static void UpdateParameters(Message *msg);
    
    /* TASKS ***********************************/
    static void ComSTM32Task(void * arg);
    static void GUITask(void * arg);

    /* MUTEX ***********************************/
    static RT_MUTEX mutexAngleBeta;
    static RT_MUTEX mutexComState;
    static RT_MUTEX mutexAnglePosition;
    static RT_MUTEX mutexTorque;
    static RT_MUTEX mutexBattery;
    static RT_MUTEX mutexUserPresence;
    static RT_MUTEX mutexReceptionState;
    static RT_MUTEX mutexEmergencyStop;
    static RT_MUTEX mutexWatchdog;

    /* SEMAPHORES ******************************/
    static RT_SEM semEmergencyStop;
    static RT_SEM semSend;

    /* MESSAGES QUEUES ************************/
    static RT_QUEUE queueFromStm32; // File de messages destinés au STM32
    static RT_QUEUE queue_Msg2GUI; // File de messages destinés au GUI
    
    /* TASKS HANDLERS **********************************/
    static RT_TASK taskStm32;
    static RT_TASK taskControl;
    static RT_TASK taskGui;
    static RT_TASK taskSend;

    /* Others objects (communication, parameters storage) */
    static ComGui* comGui;
    static ComStm32* comStm32;
    static Parameters parameters;
    
private:
    // static class: will not make use of constructor and destructor
    Tasks() {
    }

    virtual ~Tasks() {
    }
};

#endif /* __TASKS_H__ */

