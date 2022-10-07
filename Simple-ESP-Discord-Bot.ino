/**
 * Simple-ESP-Discord-Bot by ThatLolaSnail
 * https://github.com/ThatLolaSnail/Simple-ESP-Discord-Bot
*/

#include "settings.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "simple_discord.h"
#include "wacky_spaces.h"

StaticJsonDocument<200> filter;
String lastMessageID = "";

void setup() {
  //set up hardware
  Serial.begin(115200);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);

  // set up json filter
  filter[0]["id"] = true;
  filter[0]["content"] = true;
  filter[0]["author"]["username"] = true;
  //filter[0]["author"]["discriminator"] = true;

  //set up wifi
  Serial.println("Connecting To " + ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH); //LED off
    delay (500);
    digitalWrite(LED_BUILTIN, LOW); //LED on
  }
  Serial.print("\nConnected! \nIP address: ");
  Serial.println(WiFi.localIP());


  //Just as a demonstration: get a specific message
  String response = discord("/channels/" + channel + "/messages/1023651405174673440");
  DynamicJsonDocument message(1000);
  DeserializationError err = deserializeJson(message, response);
  if (err) Serial.println(String("error: ") + err.c_str());
  Serial.println(message["content"].as<String>());


  //get last 15 messages (before the last possible discord timestamp)
  String messages = discord("/channels/" + channel + "/messages?limit=15&before=9223372036854775807");
  
  //Parse the response
  DynamicJsonDocument msgs(10000);
  DeserializationError error = deserializeJson(msgs, messages, DeserializationOption::Filter(filter));
  if (error) Serial.println(String("error: ") + error.c_str());
  //serializeJson(msgs, Serial); Serial.println(msgs.memoryUsage());
  
  //iterate over the messages from back to front (so in chronological order)
  int msgsElements = msgs.size();
  for (int i = msgsElements - 1; i >= 0; i--) {
    String username = msgs[i]["author"]["username"].as<String>();
      Serial.println( //pad the username with spaces
        padWithSpaces(20 - username.length()) + 
        username + ": " + msgs[i]["content"].as<String>()
      );
    lastMessageID = (msgs[i]["id"]).as<String>();
  }
}

long lastTime = 0;

void loop() {
  //Check for new messages every 5 seconds (max 2 requests per second are allowed)
  if (millis() - lastTime > 5000) {
    //Get list with messags from Discord
    String messages = discord("/channels/" + channel + "/messages?limit=15&after=" + lastMessageID);

    //Parse the response
    DynamicJsonDocument msgs(10000);
    DeserializationError error = deserializeJson(msgs, messages, DeserializationOption::Filter(filter));
    if (error) Serial.println(String("error: ") + error.c_str());
    //serializeJson(msgs, Serial); Serial.println(msgs.memoryUsage());

    //iterate over the messages from back to front (so in chronological order)
    int msgsElements = msgs.size();
    for (int i = msgsElements - 1; i >= 0; i--) {
      String username = msgs[i]["author"]["username"].as<String>();
      //print it to the serial terminal
      Serial.println( //pad the username with spaces
        padWithSpaces(20 - username.length()) + 
        username + ": " + msgs[i]["content"].as<String>()
      );
      lastMessageID = (msgs[i]["id"]).as<String>();
    };
    msgs.clear();
    lastTime = millis();
  }

  //if we got text over serial, send it over discord.
  if (Serial.available()) {
    String text = Serial.readStringUntil('\n');
    discordSend("/channels/" + channel + "/messages", message(text));
  }
}
