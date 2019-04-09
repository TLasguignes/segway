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

#ifndef __TRACE_H__
#define __TRACE_H__

#ifndef __WITH_PTHREAD__

#include <alchemy/task.h>
#include <alchemy/mutex.h>
#include <alchemy/sem.h>
#include <alchemy/timer.h>
#include <alchemy/queue.h>

#include "messages.h"

/**
 * Trace class, provide log functionnalities for troubleshooting mutex, semaphores and task pb
 * @brief Trace class, provide log functionnalities for troubleshooting mutex, semaphores and task pb
 */
class Trace {
public:
    /**
     * Constructor, initialize start time
     * 
     */
    Trace() {
         this->beginTime = rt_timer_ticks2ns(rt_timer_read());
    }

    /**
     * Destructor
     */
    ~Trace() {}

    /**
     * Get the time between the start of recording and when it is called
     * @return Time in milliseconds
     */
    int GetTimeUs();

    /**
     * Get the time between the start of recording and when it is called
     * @return Time in microseconds
     */
    int GetTimeMs();

    /**
     * Logs when the task waits for a mutex, it must be written just before the rt_mutex_acquire();
     * @param mut Reference to the mutex
     */
    Message* WaitForMutex(RT_MUTEX* mut);

    /**
     * Logs when the task has acquired a mutex, it must be written just after the rt_mutex_acquire();
     * @param mut Reference to the mutex
     */
    Message* MutexAcquired(RT_MUTEX* mut);

    /**
     * Logs when the task releases a mutex, it must be written just after the rt_mutex_release();
     * @param mut Reference to the mutex
     */
    Message* MutexReleased(RT_MUTEX* mut);

    /**
     * Logs when the task is waiting at a semaphore, it must be written just before the rt_sem_p();
     * @param sem Reference to the semaphore
     */
    Message* WaitForSem(RT_SEM* sem);

    /**
     * Logs when the task has entered a semaphore, it must be written just after the rt_sem_p()
     * @param sem Reference to the semaphore
     */
    Message* SemEntered(RT_SEM* sem);

    /**
     * Logs when the task signals a semaphore, it must be written just before the rt_sem_v()
     * @param sem Reference to the semaphore
     */
    Message* SemSignaled(RT_SEM* sem);

    /**
     * Logs when a task begins, it must be called at the begining of the function
     * @return A string message 
     */
    Message* TaskEntered();

    /**
     * Logs when a task begins a new iteration, it must be called after the beginning of the function's loop
     * @return A string message 
     */
    Message* TaskNewIteration();

    /**
     * Logs when a task ends, it must be called at the end of the function
     * @return A string message 
     */
    Message* TaskEnded();

    /**
     * Logs when a task is deleted, it must be called at before the rt_delete_task()
     * @param task Reference to the task that is deleted
     * @return A string message 
     */
    Message* TaskDeleted(RT_TASK* task);

private:
    /**
     * Keep initial time 
     * 
     */
    RTIME beginTime;

    /**
     * Generic method to log en event regarding a mutex
     * @paramB mut Reference to the mutex
     * @param event Type of event regarding mutex
     * @return A string message containing information about mutex
     */
    Message* MutexGeneric(RT_MUTEX* mut, string event);

    /**
     * Generic method to log en event regarding a task
     * @param task Reference to the task 
     * @param string event type of event 
     * @return A string message 
     */
    Message* TaskGeneric(RT_TASK* task, string event);

    /**
     * Generic method to log en event regarding a semaphore
     * @param sem Reference to the semaphore
     * @param event Type of event regarding semaphore
     */
    Message* SemGeneric(RT_SEM* sem, string event);
};

#endif /* __WITH_PTHREAD__ */
#endif
