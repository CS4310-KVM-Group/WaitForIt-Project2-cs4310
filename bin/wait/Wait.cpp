#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h> 
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a specific process to be done.")
    parser().registerPositional("PID", "Wait for process with given ID to be done.")
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int pid = 0
    int *status = 0;

    pid = atoi(arguments().get("PID"));

    waitpid(pid, status, 0);

    //Done
    return Success;
}