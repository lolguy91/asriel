# Asr32 syscalls
## Definitions
`int` is a number that can be stored in a single register on the target architecture</br>

`ptr` is a pointer to some memory</br>

there can be `6` arguments maximum
## syscall list
0. exit(`int` status) </br>
stops the process with status code `status`

1. open(`ptr` URL, `int` flags, `int` mode) -> od(`int`) </br>
opens an object at location `URL` with flags `flags` and mode `mode`, returns an object descriptor.
2. close(`int` od) </br>
closes the object descriptor `od`
4. new_event(int permissions, int relevant_pgid) -> od(`int`) </br>
creates a new event
5. new_socket(**I have no fucking clue what to put here**) -> od(`int`) </br>
creates a new socket
3. act(`int` od, `int` action,`ptr` buffer, `int` size, *action specific 1*,*action specific 2*) -> status(`int`) </br>
does an action on an object descriptor `od` and returns a status code