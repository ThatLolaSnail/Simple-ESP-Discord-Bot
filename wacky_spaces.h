/**
 * Simple-ESP-Discord-Bot by ThatLolaSnail
 * https://github.com/ThatLolaSnail/Simple-ESP-Discord-Bot
*/


/**
   return a c_string with 0 to 32 spaces...
   if we want  0 spaces, we remove the first 32 characters, 
   if we want 32 spaces, we remove 0 characters.
   the amount is constrained to 0-32.
*/
const char* spaces = "                                "; //32 spaces
char* padWithSpaces(int amount){
  return (char*)((int)spaces + constrain(32-amount, 0, 32));
}
