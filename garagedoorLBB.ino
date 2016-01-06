/*
  ColorsExample
  For use with the "Handy BLE" iPhone app by Paul Shelley and
  the LightBlue Bean by Punchthrough Design.
  This sketch receives Serial data with a simple packet format
  of '#' for a start character and ';' as an end character. Start
  and end characters can be changed easily. Simple error checking
  is also included. 
  
  Handy BLE - https://pdshelley.com
  LightBlueBean - https://punchthrough.com
  This example code is in the public domain.
  Created 9 June 2015
  by Paul Shelley
*/

String command;
boolean commandStarted = false;

#define RELAY 1  // Pin triggering relay

void setup() {
    pinMode(RELAY, OUTPUT);
    
  Serial.begin(57600);
}

void loop() {
    
    getCommand();
    
    Bean.sleep(50);    
}

/*
This function reads the serial port and checks for the start character '#'
if the start character if found it will add all received characters to the command buffer until it receives the end command ';' When the end command is received the commandCompleted() function is called.
if a second start character is found before an end character then the buffer is cleared and the process starts over. 
*/
void getCommand() {
   while (Serial.available()) {
    char newChar = (char)Serial.read();
    if (newChar == '#') {
      commandStarted = true;
      command = "\0";
    } else if (newChar == ';') {
      commandStarted = false;
      commandCompleted();
      command = "\0";
    } else if (commandStarted == true) {
      command += newChar;
    }
  }
}

/*
This function takes the completed command and checks it against a list
of available commands and executes the appropriate code.  Add extra 'if' 
statements to add commands with the code you want to execute when that 
command is received. It is recommended to create a function for a command
if there are more than a few lines of code for as in the 'off' example.
*/
void commandCompleted() {
  if (command =="garageopen") {
    digitalWrite (RELAY,HIGH);
    }
  if (command == "off") {
    off();
    digitalWrite (RELAY,LOW);
  }
}

/*
Use a separate function like this when there are more than just a few
lines of code.  This will help maintain clean easy to read code.
*/
void off() {
  Bean.setLed( 0, 0, 0 );
}

