/**
 * Simple-ESP-Discord-Bot by ThatLolaSnail
 * https://github.com/ThatLolaSnail/Simple-ESP-Discord-Bot
*/

const char* host = "discordapp.com";
const int port = 443; //ssl port

/**
   Make a request to discord via HTTP GET.
   
   Example for getting a specific message:
   String message = discord("/channels/1023648136712962100/messages/1027626699774500905");

   Example for getting the last 15 messages:
   String messages = discord("/channels/" + channel + "/messages?limit=15&after=" + lastMessageID);
   
   This is needed for receiving messages.
   String command - the api endpoint
   returns - the data from discord, usually this is json.
*/
String discord(String command) {
  WiFiClientSecure client;
  client.setNoDelay(1); //Don't combine messages
  client.setInsecure(); //Only Encryption, no SSL certificate verification
  if (!client.connect(host, port)) return "";
  client.print(
    "GET /api/v8" + command + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Accept: */*\r\n" +
    "Authorization:Bot " + token + "\r\n" +
    "User-Agend:DiscrdBot (https://snailmath.github.io/, v0.1)\r\n" +
    "Content-Type: application/json\r\n" +
    "Connection: close\r\n\r\n"
  );
  String line = "";
  while (client.connected() && line[0] != '0' && line[0] != '{' && line[0] != '[') {
    line = client.readStringUntil((char)(10));
    //Serial.println("-> \"" + line + "\"");
  }
  return line;
}


/**
   Make a request to discord via HTTP POST.
   This is needed for sending messages.
   Example:
   discordSend("/channels/1023648136712962100/messages", message("Hello, World!"));
   String command - the api endpoint
   String content - the content
   returns - the data from discord
*/
String discordSend(String command, String content) {
  WiFiClientSecure client;
  client.setNoDelay(1); //Don't combine messages
  client.setInsecure(); //Only Encryption, no SSL certificate verification
  if (!client.connect(host, port)) return "";
  client.print(
    "POST /api/v8" + command + " HTTP/1.1\r\n" + //1.1
    "Host: " + host + "\r\n" +
    "Authorization:Bot " + token + "\r\n" +
    "User-Agend:DiscrdBot (https://snailmath.github.io/, v0.1)\r\n" +
    "Content-Type: application/json\r\n" +
    "Content-Length: " + String(content.length(), DEC) + "\r\n" +
    "Connection: close\r\n\r\n" +
    content +
    "\r\n\r\n"
  );
  //String received = "";
  String line = "";
  while (client.connected() && line[0] != '0' && line[0] != '{' && line[0] != '[') {
    line = client.readStringUntil((char)(10));
    //Serial.println("-> \"" + line + "\"");
  }
  return line;
}

/**
   Simple function to add the json stuff, 
   so it is a valid discord message ready to be send.
   I don't use the json library, because this is much simpler.
*/
String message(String& text) {
  text.replace("\"", "\\\"");
  return "{\"content\":\"" + text + "\",\"tts\":false}";
}
