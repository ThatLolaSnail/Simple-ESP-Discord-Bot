# Simple-ESP-Discord-Bot
The simplest possible discord bot for the ESP8266, it can SEND and RECEIVE messages, 
and it runs probably on every arduino with wifi (ESP8266, ESP32) with slight modifications.

## Usage

Open the .ino file in the Arduino IDE,
add your wifi credentials, your bot Token, and the channel ID of an existing discord channel to the file `settings.h` 
and upload the arduino sketch to the ESP8266. 

Now you can connect using a serial terminal and you can read and write messages. If you send something, it gets send immediately to the discord channel, 
if someone else sends something it can take up to 5 seconds for the message to show up, because I'm just polling every 5 seconds instead of having an open connection to discord all the time, 
just because I was lazy while programming.

Enjoy!

You can use this in your own projects, just mention that you got it from here.

`https://github.com/ThatLolaSnail/Simple-ESP-Discord-Bot`
