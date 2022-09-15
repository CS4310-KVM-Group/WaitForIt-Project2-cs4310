# Documentation

## Background
in Linux:
```
$ sleep 30   (the kernel will suspend for 30 sec, can't do anything during this time)
```
```
$ sleep 30 & (a single process is sleeping in the background)
[1] 17

$ wait 17 (wait the process with ID 17 to be done sleeping)
```

## Approach

- parsing command line input
- utilize waitpid() to wait for a PID
    + require a process ID
- utilize sleep function??? (perhaps not since waitpid() is waiting for current sleeping pid already)


## Resources

- [Linux waitpid()](https://stackoverflow.com/questions/21248840/example-of-waitpid-in-use)
- [FreeNos's waitpid() code](../../lib/libposix/sys/wait/waitpid.cpp)
- [FreeNos's sleep() code](../../lib/libposix/unistd/sleep.cpp)