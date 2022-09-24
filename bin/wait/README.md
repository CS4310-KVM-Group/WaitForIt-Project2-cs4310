# Project 2: Wait for it...

## 1. Group VKSos

### Team members:

- Van Huynh
- Selenya Vargas
- Kenny Santanu

### Demo Video Link: [Click Here](https://www.youtube.com/watch?v=xCxUk0Qo38c)

<br>

## 2. Background
in Linux:
```
$ sleep 30   (the kernel will suspend for 30 sec, can't do anything during this time)
```
```
$ sleep 30 & (a single process is sleeping in the background)
[1] 17

$ wait 17 (wait the process with ID 17 to be done sleeping)
```

## 3. Approach

- parsing command line input
- validate inputs
    + validate valid user input from terminal
    + validate existing PIDs
- utilize waitpid() to wait for a PID
    + require a process ID
    


## Resources

- [Linux waitpid()](https://stackoverflow.com/questions/21248840/example-of-waitpid-in-use)
- [FreeNos's waitpid() code](../../lib/libposix/sys/wait/waitpid.cpp)
- [FreeNos's sleep() code](../../lib/libposix/unistd/sleep.cpp)