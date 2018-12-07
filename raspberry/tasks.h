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
 * Class holding tasks et realtime objects (semaphors, mutex ...)
 * @brief Class holding tasks et realtime objects (semaphors, mutex ...)
 *
 */
class Tasks {
public:
    /**
     * Constructor, initialize global objects (communication and parameters)
     */
    Tasks() {
        comGui = new ComGui();
        comStm32 = new ComStm32();
        parameters = new Parameters();
    }

    /**
     * Destructor, clean removal of global objects
     */
    virtual ~Tasks() {
        delete(comGui);
        delete(comStm32);
        delete(parameters);
    }
    
    /**
     * Initialize communication (open ports and server) and reset parameters
     * Create RT objects (semaphores / mutex/ queues / tasks)
     */
    void Init();
    
    /**
     * Launch tasks, realtime system starts here
     */
    void StartTasks();
    
    /**
     * Clean destruction of tasks, realtime system stops here
     */
    void DeleteTasks();
    
    /**
     * Helper function for storing parameter value in correct parameter objetc
     * @param msg Message to store value into parameters object
     */
    void UpdateParameters(Message *msg);
    
    /**
     * Wait for a client to connect to server
     * @return Client id
     */
    int WaitForClient() {
        return comGui->AcceptClient();
    }
    
    /*
     Add your tasks here
     */
    
    /**
     * Task use for reception of data from STM32
     * @param arg In the case of a member of a class, this parameter holds a reference to surrounding object (this, normaly)
     */
    void TaskStm32Reception(void * arg);
    
    /**
     * Task use to send data to user interface (through server)
     * @param arg In the case of a member of a class, this parameter holds a reference to surrounding object (this, normaly)
     */
    void TaskGui(void * arg);
    
    /**
     * Task use to process control loop
     * @param arg In the case of a member of a class, this parameter holds a reference to surrounding object (this, normaly)
     */
    void TaskSystemControl(void * arg);
    
private:
    /**
     * Mutex for protecting writes to stm32
     */
    RT_MUTEX mutexStm32Write;

    /**
     * Semaphore for synchronizing message sent to user interface
     */
    RT_SEM semSendGui;

    /**
     * Message queue used for message communication between taskStm32Handler and taskSystemControlHandler
     */
    RT_QUEUE queueFromStm32; // File de messages destinés au STM32
    
    /**
     * Task handler of TaskStm32Reception
     */
    RT_TASK taskStm32Handler;
    
    /**
     * Task handler of TaskSystemControl
     */
    RT_TASK taskSystemControlHandler;
    
    /**
     * Task handler of TaskGui
     */
    RT_TASK taskGuiHandler;

    /**
     * Server and communication object to user interface 
     */
    ComGui* comGui;
    
    /**
     * Server and communication object from and to stm32
     */
    ComStm32* comStm32;
    
    /**
     * Object holding all system parameters (angle, speed, torque, ...)
     */
    Parameters* parameters;
};

#endif /* __TASKS_H__ */

