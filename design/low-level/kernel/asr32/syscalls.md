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
3. newobj(`int` type, `ptr` URL, `int` specific 1, `int` specific 2) -> od(`int`) </br>
creates a new object of type  `type` at location `URL`
4. act(`int` od, `int` action,`ptr` buffer, `int` size, *action specific 1*,*action specific 2*) -> status(`int`) </br>
does an action on an object descriptor `od` and returns a status code
