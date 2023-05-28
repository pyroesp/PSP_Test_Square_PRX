# Draw square plugin
Draw a red square on screen with a plugin.  
This is a sample code for creating a plugin that draws something on screen.  


## Controls
No controls used, just displays a square.  


## Compile
Use the latest PSPDEV docker image.  
- On windows, go to the folder containing the source code.  
- Execute `docker run -it --rm -v ${PWD}:/home/code pspdev/pspdev:latest` in powershell.  
- Navigate to `/home/code` with `cd`.  
- Execute `make` to compile and `make clean` to cleanup.  


## Credits
Everyone on the [pspdev github](https://github.com/pspdev) and [discord community](https://discord.gg/bePrj9W) for continued [pspsdk](https://github.com/pspdev/pspsdk) support and help.  
Special thanks to [krazynez](https://github.com/krazynez) for helping debug a crash.  


## License
All code, except cJSON, is under Creative Commons [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/). 
