# rat

This is an educational C++ Remote Administration Tool.
The project currently supports Windows only.

## What's in the box

- [x] Remote Command Execution (RCE) using reverse shell. There is support for launching any process and listening for its output (`cmd.exe` `powershell.exe`, etc). Launching a custom process without listening to its output is possible too.

- [x] Keylogger. Each key event will be sent to the server, along with a timestamp and the name of the focused window.

- [ ] Screenshot

## Commands