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
    int pid = 0;
    int status;
    
    // Convert Pid string from arg to int 
    // And avoiding folders default processes from 1-16
    if( (pid = atoi(arguments().get("PID"))) < 17)
    {
        ERROR("failed to wait: Invalid argument" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

    // calling waitpid() function to wait for that pid
    // And if PID is not successful (status is not changing) throws error msg
    if(waitpid(pid, &status, 0) == -1)
    {
        ERROR("failed to wait: " << sterror(error));
        return IOError;
    }

    // Done
    return Success;
}
