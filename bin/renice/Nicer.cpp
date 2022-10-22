/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Types.h>
#include <Macros.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include <errno.h>
#include "Nicer.h"


Nicer::Nicer(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Output system process list");
    parser().registerFlag('n', "priority", "Tell process to run at given priority");
    parser().registerPositional("PRIO", "The priority of the process");
    parser().registerPositional("PID", "The PID of the process we want to change");
}

/**VanComment: based on ProcessList.cpp, I think this should be 
 * Nicer::Result getPrio(int pid, int* p)
 */
Nicer::getPrio(int pid, int* p)
{
    errno = 0;
    //Checks priority of pid and returns error if invalid
    *p = getPriority(pid);
    if (*p == -1 && errno)
    {
        WARNING("Failed to get priority");
        return -errno;
    }
    return 0;
}

//Checks to see if priortiy need to be changed
Nicer::doNice(int pid, int priority)
{
    //old and new priority
    int oldp, newp;

    //If getPriority does not return an error then we set priority
    if (getPrio(pid, &oldp) != 0)
        return 1;

    //Sets priority and checks for error
    if (setPriorty(pid, priority) < 0)
        return 1;

    // Is set priority was successful, check again for error
    if (getPrio(pid, &newp) !=0)
        return 1;

    //Program was successful to change priority
    out << "Priority set. \n";
    return 0;
}

Nicer::Result Nicer::exec()
{
    const ProcessClient process;

    int p = 0, pid = 0, errs = 0;

    p = atoi(arguments().get("PRIO"));
    pid = atoi(arguments().get("PID"));

    if (p > 5 || p < 1)
    {
        ERROR("Invalid priority level")
        return InvalidArgument;
    }

    if (!arguments().get("priority"))
    {
        ERROR("No valid flag found");
        return InvalidArgument;
    }

    errs |= doNice(pid, p);
    return errs != 0 ? Error : Success;
}
