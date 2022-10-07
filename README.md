# Simple-ESP-Discord-Bot
The simplest possible discord bot for the ESP8266, it can SEND and RECEIVE messages, 
and it runs probably on every arduino with wifi (ESP8266, ESP32) with slight modifications.

```
Connecting To [redacted]
.......
Connected! 
IP address: 192.168.178.57
> Welcome to the Simple-ESP-Discord-Bot project! 
> This is a simple discord bot for the ESP written in Arduino, 
> my initial goal was to make it possible to send discord messages 
> from a calculator connected to an ESP.
             ESP8266: Hi!
       ThatLolaSnail: Hiii
       ThatLolaSnail: Dudisfahskdhccij
       ThatLolaSnail: Shshdjjdjdjsjshd
       ThatLolaSnail: Tyyy
       ThatLolaSnail: Ggfdf
             ESP8266: Hi.
       ThatLolaSnail: 👀
             ESP8266: :eyes:
       ThatLolaSnail: Wait, in discord, \:eyes\: and the eyes emoji are 2 different messages, but displayed just the same...
       ThatLolaSnail: when the ESP starts, it loads the last 15 messages, and then every 5 seconds it gets up to 15 newer messages.
             ESP8266: Hi.
       ThatLolaSnail: Hi!
       ThatLolaSnail: 
             ESP8266: Hi? I think this works now. I'm gonna upload it to https://github.com/ThatLolaSnail/Simple-ESP-Discord-Bot
```

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
