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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    // return m_queue.count();
    Size size;
    size = m_queue_min.count() + m_queue_default.count() + m_queue_max.count();
    return size;
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    // m_queue.push(proc);
    // return Success;
    int priority = proc->getPriority(); 
    Scheduler::Result result; 
    switch (priority)
    {
        case 1: m_queue_min.push(proc);     result = Success; break;
        case 2: m_queue_lower.push(proc);   result = Success; break;
        case 3: m_queue_default.push(proc); result = Success; break;
        case 4: m_queue_higher.push(proc);  result = Success; break;
        case 5: m_queue_max.push(proc);     result = Success; break;
        // Else, just exit the switch block
    }
    return result;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    Size count = m_queue.count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = m_queue.pop();

        if (p == proc)
            return Success;
        else
            m_queue.push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    Process *p; 

    /**
     * ML Algorithm explaination:
     * - separate queue of processes at different priority levels N (1-lowest to 5-highest in this case)
     * - within each level, processes are scheduled using RR (round-robin algorithm)
     * - process at head of highest priority level (N==5) is selected for execution
     * - Processes at given level can run only if all queues at higher levels are empty
     * -- Example: a process at level N == 3 only after processes at level 5 and 4 terminate
    */
    if(m_queue_max.count() > 0){
        p = m_queue_max.pop();
        m_queue_max.push(p);
        return p; 
    }else if(m_queue_higher.count() > 0){
        p = m_queue_higher.pop(); 
        m_queue_higher.push(p);
        return p; 
    }else if(m_queue_default.count() > 0){
        p = m_queue_default.pop(); 
        m_queue_default.push(p);
        return p; 
    }else if(m_queue_lower.count() > 0){
        p = m_queue_lower.pop(); 
        m_queue_lower.push(p);
        return p; 
    }else if(m_queue_min.count() > 0 ){
        p = m_queue_min.pop(); 
        m_queue_min.push(p);
        return p; 
    }
    return (Process *) NULL;
}
