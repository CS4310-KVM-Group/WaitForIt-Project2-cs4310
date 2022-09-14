#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a given number of time before continuing operations.")
    parser().registerPositional("SECONDS", "Wait for a given number of time before continuing operations.")
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    int sec = 0;

    // Convert input to seconds
    if((sec = atoi(arguments().get("SECONDS"))) <=0)
    {
        ERROR("invalid wait time `" << arguments().get("SECONDS") << "'");
        return InvalidArgument;
    }

    //Wait now
    if (wait(sec) != 0)
    {
        ERROR("failed to wait: " << strerror(errno));
        return IOError;
    }

    //Done
    return Success;
}