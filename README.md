# rat

This is a C++ Remote Administration Tool.
The project currently supports Windows only.

## Disclaimer
THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. YOU MAY USE THIS SOFTWARE AT YOUR OWN RISK. THE USE IS COMPLETE RESPONSIBILITY OF THE END-USER. THE DEVELOPERS ASSUME NO LIABILITY AND ARE NOT RESPONSIBLE FOR ANY MISUSE OR DAMAGE CAUSED BY THIS PROGRAM.

## What's in the box

- [x] Remote Command Execution (RCE) using reverse shell. There is support for launching any process and listening for its output (`cmd.exe` `powershell.exe`, etc). Launching a custom process without listening to its output is possible too.

- [x] Keylogger. Each key event will be sent to the server, along with a timestamp and the name of the focused window.

- [x] Screenshot. Receive a screenshot of the screen.

## Commands

| Command                	| Description                                                    	|
|------------------------	|----------------------------------------------------------------	|
| `l`, `list`            	| List the connected clients                                     	|
| `s`, `select`          	| Select a client for which the commands will operate            	|
| `c`, `chat`            	| Sends a text message                                           	|
| `p`, `process`         	| Open a process remotely                                        	|
| `r`, `reverse`         	| Reverse shell, open a process remotely and attach to it        	|
| `sc`, `screenshot`     	| Screenshot the clients' screen, download the image and open it 	|
| `ks`, `startkeylogger` 	| Begin receiving logs of the clients' key presses               	|
| `kk`, `stopkeylogger`  	| Stop receiving logs of the key presses                         	|