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

#include <sys/mman.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>

#include "tasks.h"

// global tasks to access it in the interruption handler
Tasks *tasks = nullptr;

/**
 * Handler for the interrupting signal: to force clean quit.
 * @param s
 */
void kbInterruptHandler(int s){
    cout << "Interrupting code" << endl;
    tasks->DeleteTasks();
    tasks->Close();
    exit(-1);
}
/**
 * @brief Main function of segway supervisor program
 */
int main(void) {
    int status;
    
    struct sigaction kbIntAction;
    
    /* disable memory swap */
    mlockall(MCL_CURRENT | MCL_FUTURE);
    //init_recording();		// Initialisation de l'enregistrement des évènements par le log

    cout << "Segway Supervisor" << endl << endl;
    tasks = new Tasks();
    tasks->Init(); // Création des tâches, mutex, sémaphores, files de messages, ouverture des ports
    
    // Wait client to connect
    cout << "Waiting for client (GUI) to connect ..." << endl;
    status = tasks->WaitForClient();

    kbIntAction.sa_handler = kbInterruptHandler;
    sigemptyset(&kbIntAction.sa_mask);
    kbIntAction.sa_flags = 0;

    sigaction(SIGINT, &kbIntAction, NULL);

    if (status >= 0) {
        cout << "Client connected (" << status << "), rock'n'roll baby !" << endl << endl;

        tasks->StartTasks(); // Démarre toutes les tâches

        pause();
        tasks->DeleteTasks();
    }

    //stop_recording();
    return 0;
}
