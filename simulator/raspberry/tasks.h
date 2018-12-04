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
    // static class: will not make use of constructor and destructor
    Tasks() {
        comGui = new ComGui();
        comStm32 = new ComStm32();
        parameters = new Parameters();
    }

    virtual ~Tasks() {
        delete(comGui);
        delete(comStm32);
        delete(parameters);
    }
    
    void Init();
    void StartTasks();
    void DeleteTasks();
    void UpdateParameters(Message *msg);
    int WaitForClient() {
        return comGui->AcceptClient();
    }
    
    /* TASKS ***********************************/
    void TaskStm32Reception(void * arg);
    void TaskGui(void * arg);
    
private:
    /* MUTEX ***********************************/
    RT_MUTEX mutexAngleBeta;

    /* SEMAPHORES ******************************/
    RT_SEM semSendGui;

    /* MESSAGES QUEUES ************************/
    RT_QUEUE queueFromStm32; // File de messages destinés au STM32
    
    /* TASKS HANDLERS **********************************/
    RT_TASK taskStm32Handler;
    RT_TASK taskSystemControlHandler;
    RT_TASK taskGuiHandler;

    /* Others objects (communication, parameters storage) */
    ComGui* comGui;
    ComStm32* comStm32;
    Parameters* parameters;
};

#endif /* __TASKS_H__ */

