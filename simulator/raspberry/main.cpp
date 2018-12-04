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
 * \brief Main part of segway supervisor program
 *
 */

#include <sys/mman.h>
#include <iostream>
#include <unistd.h>

//#include "tasks.h"
#include "tasks.h"

/**
 * \fn Main function of segway supervisor program
 */
int main(void) {
    int status;
    Tasks *tasks;
    
    /* disable memory swap */
    mlockall(MCL_CURRENT | MCL_FUTURE);
    //init_recording();		// Initialisation de l'enregistrement des évènements par le log

    cout << "Segway Supervisor" << endl << endl;
    tasks = new Tasks();
    tasks->Init(); // Création des tâches, mutex, sémaphores, files de messages, ouverture des ports
    //Tasks::Init();
    
    // Wait client to connect
    cout << "Waiting for client (GUI) to connect ..." << endl;
    status = tasks->WaitForClient();
    //status = Tasks::comGui->AcceptClient();

    if (status >= 0) {
        cout << "Client connected (" << status << "), rock'n'roll baby !" << endl << endl;

        tasks->StartTasks(); // Démarre toutes les tâches
        //Tasks::StartTasks();

        pause();
        tasks->DeleteTasks();
        //Tasks::DeleteTasks();
    }

    //stop_recording();
    return 0;
}
