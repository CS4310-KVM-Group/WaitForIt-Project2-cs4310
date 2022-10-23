# Project 3: Prioritize it...

## 1. Group VKSos

### Team members:

- Van Huynh
- Selenya Vargas
- Kenny Santanu

### Demo Video Link: [Click Here](https://www.youtube.com)

### Repo Link: [Click Here](https://github.com/CS4310-KVM-Group/WaitForIt-Project2-cs4310/tree/priority/bin/renice)

<br>

### File structure

```
App Level   |ProcessList class (ps command)
            |   - handle/validate valid -l flag
            |   - create ProcessClient object - retrieve process info
            |   - display outputs
            |Renice class (renice command)
            |   - handle/validate process ID and Priority level value from user input
            |   - call setPriority() with ProcessClient object
            |   - annouce success/fail depends on result from setPriority()
            |        |
            |        |
Lib Level   |        ProcessClient class:
            |            - call to perform setter/getter from ProcessCtl class
            |            - 
            |                |
            |                |
Sys/Kernel  |                ProcessCtl class 
            |                - Process point w/ default value 0 (involve Process Class)
            |                - ProcessInfo struct pointer (involve ProcessInfo)
            |                - ProcessManager pointer  (involve ProcessManager)
            |                - case "Spawn"
            |                - Spawn is in shell (which is in POSIXAPP)
            |                        |
            |                        |
            |                        Process class
            |                        - setPriority() function
            |                        - getPriority() function

Scheduler class (harder approach)
```

## 2. Background

in FreeNos...

```
# sc 360 &    #this gives your around 1-minute running time.
```
```
# sc 300 &   #this gives your around 0.5-minute running time.
```
```
# ps –l #suppose the output has PID 17 for “sc 300”
```
```
# renice –n 2 17 #tell Process 17 to be run at priority 2
```
```
# ps –l # make sure the priority changes for “sc 300”
```
```
# # wait to see that “sc 360” finish before “sc 300”
```

## 3. Approach

- add -l flag for ps command to show priority of all current processes
- add renice commands, given a specific process id (PID) --> change priority of specific process
- implement priority queue of process
    + setter function to change priority of process within a queue
    + getter function to return priority of process
    


## Resources

- [FreeNOS doxygen Kernel module](http://www.freenos.org/doxygen/group__kernel.html)
- [FreeNOS doxygen Scheduler class](http://www.freenos.org/doxygen/classScheduler.html)
- [FreeNOS doxygen Kernel  class](http://www.freenos.org/doxygen/classKernel.html#details)
- [FreeNOS doxygen Process Manager  class](http://www.freenos.org/doxygen/classProcessManager.html)