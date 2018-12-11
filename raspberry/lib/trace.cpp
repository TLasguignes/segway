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

#include "trace.h"
#include <string>
#include <exception>
#include <stdexcept>

#ifndef __WITH_PTHREAD__

using namespace std;

typedef enum {
    SEM, MUTEX, TASK, TASK_DELETE
} message_type;

///**
// * \fn int write_in_queue(RT_QUEUE *msg_queue, void * buf, int size) 
// * \brief 	Writes a message into a queue
// * \param RT_QUEUE *msg_queue : the address of the queue
// * \param void * data : the address of message
// * \param int size : the size of the data
// * \return the error code return by the rt_queue
// */
//int write_in_queue(RT_QUEUE *msg_queue, void * buf, int size) {
//    int err = 0;
//
//    err = rt_queue_write(msg_queue, buf, size, Q_NORMAL);
//    if (err < 0) {
//        switch (err) {
//            case (-ENOMEM):
//                rt_printf("rt_queue_send1 error limit exceeded %d\n", err);
//                break;
//            case (-EINVAL):
//                rt_printf("rt_queue_send1 error: first argument is not a message queue descriptor or invalid mode or buf is NULL %d\n", err);
//                break;
//        }
//    }
//    return err;
//}

/**
 * Get the time between the start of recording and when it is called
 * @return Time in milliseconds
 */
int Trace::GetTimeMs() {
    RTIME time = (rt_timer_ticks2ns(rt_timer_read()) - this->beginTime) / 1000000;
    return (int) time;
}

/**
 * Get the time between the start of recording and when it is called
 * @return Time in microseconds
 */
int Trace::GetTimeUs() {
    RTIME time = (rt_timer_ticks2ns(rt_timer_read()) - this->beginTime) / 1000;
    return (int) time;
}

/**
 * \fn void init_message(message_log * m, message_type type, int time, const char * task_name, const char * event, const char * sarg0, const char * sarg1, const char * sarg2, int iarg0, int iarg1)
 * \brief 		Builds a message to be sent to the queue
 * \param    message_log * m : address of the message
 * \param    int time : time of the creation (in ms)
 * \param    char * task_name : name of the task
 * \param    char * event : the event that created that message
 * \param    char * sarg0 : generic string
 * \param    char * sarg1 : generic string
 * \param    char * sarg2 : generic string
 * \param    int iarg0 : generic integer
 * \param   int iarg1 : generic integer
 */

//void init_message(message_log * m, message_type type, int time, const char * task_name, const char * event, const char * sarg0, const char * sarg1, const char * sarg2, int iarg0, int iarg1) {
//
//    m->type = type;
//    m->time = time;
//    m->iarg0 = iarg0;
//    m->iarg1 = iarg1;
//    if (sarg0 != NULL) {
//        memcpy(m->sarg0, sarg0, SARG_SIZE);
//    }
//    if (sarg1 != NULL) {
//        memcpy(m->sarg1, sarg1, SARG_SIZE);
//    }
//    if (sarg2 != NULL) {
//        memcpy(m->sarg2, sarg2, SARG_SIZE);
//    }
//    if (task_name != NULL) {
//        memcpy(m->task_name, task_name, SARG_SIZE);
//    }
//    if (event != NULL) {
//        memcpy(m->event, event, SARG_SIZE);
//    }
//}

/**
 * Generic method to log en event regarding a mutex
 * @param mut Reference to the mutex
 * @param event Type of event regarding mutex
 * @return A string message containing information about mutex
 */
Message* Trace::MutexGeneric(RT_MUTEX* mut, string event) {
    MessageString* msg = new MessageString();
    msg->SetID(MESSAGE_LOG);

    RT_TASK_INFO task_info;
    RT_MUTEX_INFO mut_info;
    rt_task_inquire(NULL, &task_info);
    rt_mutex_inquire(mut, &mut_info);

    msg->SetString("[" + to_string(this->GetTimeMs()) + "] Mutex " + mut_info.name + "(" + task_info.name + "): " + event);

    return msg;
}

/**
 * Logs when the task waits for a mutex, it must be written just before the rt_mutex_acquire();
 * @param mut Reference to the mutex
 */
Message* Trace::WaitForMutex(RT_MUTEX* mut) {
    return this->MutexGeneric(mut, "waiting");
}

/**
 * Logs when the task has acquired a mutex, it must be written just after the rt_mutex_acquire();
 * @param mut Reference to the mutex
 */
Message* Trace::MutexAcquired(RT_MUTEX* mut) {
    return this->MutexGeneric(mut, "acquired");
}

/**
 * Logs when the task releases a mutex, it must be written just after the rt_mutex_release();
 * @param mut Reference to the mutex
 */
Message* Trace::MutexReleased(RT_MUTEX* mut) {
    return this->MutexGeneric(mut, "released");
}

/**
 * Generic method to log en event regarding a semaphore
 * @param sem Reference to the semaphore
 * @param event Type of event regarding semaphore
 */
Message* Trace::SemGeneric(RT_SEM* sem, string event) {
    MessageString* msg = new MessageString();
    msg->SetID(MESSAGE_LOG);

    RT_TASK_INFO task_info;
    RT_SEM_INFO sem_info;
    int err = rt_task_inquire(NULL, &task_info);
    rt_sem_inquire(sem, &sem_info);

    if (err == 0) {
        msg->SetString("[" + to_string(this->GetTimeMs()) + "] Semaphore " + sem_info.name + "(" + task_info.name + ") (Waiters " + to_string(sem_info.nwaiters) + "): " + event);
    } else {
        msg->SetString("[" + to_string(this->GetTimeMs()) + "] Error when retrieving semaphore state");
    }

    return msg;
}

/**
 * Logs when the task is waiting at a semaphore, it must be written just before the rt_sem_p();
 * @param sem Reference to the semaphore
 */
Message* Trace::WaitForSem(RT_SEM* sem) {
    return this->SemGeneric(sem, "waiting");
}

/**
 * Logs when the task has entered a semaphore, it must be written just after the rt_sem_p()
 * @param sem Reference to the semaphore
 */
Message* Trace::SemEntered(RT_SEM* sem) {
    return this->SemGeneric(sem, "entered");
}

/**
 * Logs when the task signals a semaphore, it must be written just before the rt_sem_v()
 * @param sem Reference to the semaphore
 */
Message* Trace::SemSignaled(RT_SEM* sem) {
    return this->SemGeneric(sem, "signaled");
}

/**
 * Generic method to log en event regarding a task
 * @param task Reference to the task 
 * @param string event type of event 
 * @return A string message 
 */
Message* Trace::TaskGeneric(RT_TASK* task, string event) {
    MessageString* msg = new MessageString();
    msg->SetID(MESSAGE_LOG);

    RT_TASK_INFO self_task_info;
    int err = rt_task_inquire(task, &self_task_info);

    if (err == 0) {
        msg->SetString("[" + to_string(this->GetTimeMs()) + "] Task " + self_task_info.name + " (Prio " + to_string(self_task_info.prio) + "): " + event);
    } else {
        msg->SetString("[" + to_string(this->GetTimeMs()) + "] Error when retrieving task information");
    }

    return msg;
}

/**
        logs when a task begins, it must be called at the begining of the function
        no need to give a reference to the task
 */

/**
 * Logs when a task begins, it must be called at the begining of the function
 * @return A string message 
 */
Message* Trace::TaskEntered() {
    return this->TaskGeneric(NULL, "entered");
}

/**
 * Logs when a task begins a new iteration, it must be called after the beginning of the function's loop
 * @return A string message 
 */
Message* Trace::TaskNewIteration() {
    return this->TaskGeneric(NULL, "new iteration");
}

/**
 * Logs when a task ends, it must be called at the end of the function
 * @return A string message 
 */
Message* Trace::TaskEnded() {
    return this->TaskGeneric(NULL, "ended");
}

/**
 * Logs when a task is deleted, it must be called at before the rt_delete_task()
 * @param task Reference to the task that is deleted
 * @return A string message 
 */
Message* Trace::TaskDeleted(RT_TASK * task) {
    MessageString* msg = new MessageString();
    msg->SetID(MESSAGE_LOG);

    RT_TASK_INFO self_task_info;
    RT_TASK_INFO param_task_info;
    int err_self = rt_task_inquire(NULL, &self_task_info);

    if (err_self == 0) {
        int err_param = rt_task_inquire(task, &param_task_info);

        if (err_param == 0) {
            msg->SetString("[" + to_string(this->GetTimeMs()) + "] Task " + param_task_info.name + " (Prio " + to_string(param_task_info.prio) + "): deleted");
        } else {
            msg->SetString("[" + to_string(this->GetTimeMs()) + "] Error when retrieving task information");
        }
    } else {
        msg->SetString("[" + to_string(this->GetTimeMs()) + "] Error when retrieving own task information");
    }

    return msg;
}

#endif /* #ifndef __WITH_PTHREAD__ */