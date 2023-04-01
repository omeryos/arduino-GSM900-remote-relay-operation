/*
 * Complete Project Details https://randomnerdtutorials.com
 */

// Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>

// Configure software serial port
SoftwareSerial SIM900(7, 8);

// Variable to store text message
String textMessage;


// Relay connected to pin 12
const int relay = 12;

void setup() {

   // Set relay as OUTPUT
  pinMode(relay, OUTPUT);

  // By default the relay is off
  digitalWrite(relay, HIGH);
  
  // Initializing serial commmunication
  Serial.begin(19200); 
  SIM900.begin(19200);

  // Give time to your GSM module log on to network
  delay(20000);
  Serial.print("SIM900 ready...");

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void loop(){
  if(SIM900.available()>0){
    textMessage = SIM900.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
  if(textMessage.indexOf("1960")>=0){
    // Turn on relay and save current state
    digitalWrite(relay, LOW);
    Serial.println("Relay set to ON");  
    textMessage = ""; 
    delay(1200);
    digitalWrite(relay, HIGH); 
    Serial.println("Relay set to LOW");

  }
}  
