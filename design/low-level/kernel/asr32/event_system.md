# the asr32 event system

The asr32 event system is very simple and let's processes create, subscribe to, fire, unsubscribe from and delete events.
An event holds the following information:
* the event ID
* the process which owns the event
* the relevant process group ID for the event
* the permissions* of the event
* the list of processes subscribed and the address of the handler function

*: permissions are: Subscribe,Fire,Recieve and Delete for owner process, specified process group and everyone else
