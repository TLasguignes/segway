# Presentation
Segway_supervisor is used for controlling segway process. It is a based on
Xenomai libraries for realtime capabilities and is written in plain C++. 
A library written in C++ provide access to serial link, server, control function
and some helper function

## Building the project
The prefered way for building project is using Netbeans IDE. A project is already 
defined, all you have to do is adding your target as remote compilation target in order
to build remotely the project.

If you prefere *root* approach, project can also be built by command line.

* For compiling program:
> make

* Built program is normally found under ./dist/Debug/GNU-Linux/segway_supervisor. To run it, use:
> sudo  ./dist/Debug/GNU-Linux/segway_supervisor

* For cleaning project:
> make clean

* For building documentation (on PC):
> doxygen doxyfile.cfg

## Provided files
Project contains following files, provided to user for help him building final project:

* main.cpp:
  Create task object and launch task. Probably nothing to do here.

* tasks.cpp/tasks.h:
  The files you probably will update the most. Contains, in fact, all your program, mutex, semaphores, task and so on.
  Initial program is just here to show you how to use mutex, semaphore, message queue, create and run task. 
  Don't be fooled by stuff already created, you can change everything.
    
* control.cpp/control.h:
  Static class with just one method, needed for computing control torque

* parameters.cpp/parameters.h:
  Class containing all system attributes (variable)

lib/inc and lib/src directories contain following useful files:

* lib/inc contains library headers:

* lib/src contains source:
  - comStm32.cpp:
    Class for communicating with STM32
  - comGui.cpp:
    Class for spawning a server and communicate through it with GUI.
  - messages.cpp:
    Classes for defining messages objects.
  - trace.cpp:
    Class for tracing realtime objects use
	
