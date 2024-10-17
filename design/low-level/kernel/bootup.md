# the SOUL bootup process
1. the kernel gains execution
2. the kernel initializes the HAL
3. the kernel initializes the object manager
4. the kernel loads all drivers and firmware from the driver ramfs
5. the kernel initializes all drivers
6. the kernel initializes the scheduler
7. the kernel sets up the asr32 startup code
8. the kernel starts the scheduler
9. asr32 starts all startup processes from the registery