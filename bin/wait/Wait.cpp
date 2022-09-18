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
    parser().registerPositional("PID", "Wait for process with given ID to be done");
}

/* Destructor */
Wait::~Wait() {}

Wait::Result Wait::exec()
{
    // Initialize variables
    int pid = 0;
    int status;
    
    // Convert Pid string from arg to int
    pid = atoi(arguments().get("PID"));

    // DEBUG
    //printf("Pid = %d\n", pid);

    // calling waitpid() function to wait for that pid
    waitpid(pid, &status, 0);

    // Done
    return Success;
}
