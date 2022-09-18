/************/
/* Wait.cpp */
/************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"
#include <sys/wait.h> // add this line to use waitpid()

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a specific process to be done");
    parser().registerPositional("PID's ID", "Wait for process with given ID to be done");
}

/* Destructor */
Wait::~Wait() {}

Wait::Result Wait::exec()
{
    // verify valid existing pid ID from terminal
    int pid = 0; // parse from terminal
    //int *status = 0; // where to get this status?

    cout << pid


    // calling waitpid() function to wait for that pid
    //waitpid(pid, status, 0);



    // Done
    return Success;
}
