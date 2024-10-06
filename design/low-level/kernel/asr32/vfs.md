# The SOUL VFS
The SOUL VFS doesn't only manage files and directories but also all resources accessable via a URL.

URL format: `scheme:[//]url`
the scheme can be a mounted disk by name(like `A` or `DRIVE`), an unmounted disk by id(like `sda1` or `nvme0`), a network protocol(like `https` or `gopher`), or a resource(like `proc` or `dev`).

all backslashes should be treated as a slash.

