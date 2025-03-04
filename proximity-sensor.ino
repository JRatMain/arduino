/*
This project creates a small proximity sensor. If an object is 50 cm or less from the ultrasonic sensor module, a buzzer will
sound and an LCD will update. When the power button is pressed on the IR remote, the alarm will reset, the LCD will 
update to confirm the alarm reset, and the buzzer will stop making sound.

By: Matthew Vrbka
3/3/3035

Some code was copied from previous projects (i.e. handling IR input)

ChatGPT link (I asked it for some ideas and a bit of advice):
https://chatgpt.com/share/67c63189-a89c-800e-bf64-0d46131e21db 

*/


#include <LiquidCrystal.h> //library for the screen
#include "IRremote.h" // library for the IR sensor
#include "SR04.h" // library for the SR04 (ultrasonic sensor)

int TRIG_PIN = 5;
int ECHO_PIN  = 6;
int BUZZ_PIN = 2;
int receiver = 3;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
bool alarmActive;

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

IRrecv irrecv(receiver);
decode_results results;

void translateIR() {
  switch(results.value) {
    case 0xFFA25D: //power button
    lcd.setCursor(0, 1);
    lcd.print("Alarm Reset...");
    alarmActive = false;
     break;

    default: // all other buttons
    lcd.print("Invalid Command");
    break;
  }
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16 , 2);
  pinMode(BUZZ_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver for alarm resets
  

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
if (sr04.Distance() <= 50) { // 50cm or less
  alarmActive = true;
  lcd.print("Alarm triggered");
  lcd.setCursor(0, 1);
  lcd.print("buzzer active...");
    }
if (alarmActive)
 {
    digitalWrite(BUZZ_PIN, HIGH);
   
    if (irrecv.decode(&results)) { //once we get a signal
    translateIR(); 
    irrecv.resume(); // receive the next value
    }


  
 }
if (!alarmActive) {
  digitalWrite(BUZZ_PIN, LOW);
    }
}

