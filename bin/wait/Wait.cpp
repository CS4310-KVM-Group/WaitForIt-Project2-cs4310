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
    int sec = 0;

    // Convert input to seconds
    if ((sec = atoi(arguments().get("SECONDS"))) <= 0)
    {
        ERROR("invalid Wait time `" << arguments().get("SECONDS") << "'");
        return InvalidArgument;
    }

    // Wait now
    if (wait(sec) != 0)
    {
        ERROR("failed to Wait: " << strerror(errno));
        return IOError;
    }

    // Done
    return Success;
}
