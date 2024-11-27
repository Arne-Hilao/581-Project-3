/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
Servo myservo;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int serPin = 9;
int pos = 0;
int seconds_countdown = 0, minutes_countdown = 1, hour_countdown;
int seconds_passed;
int minutes_passed;
int hours_passed;
int reset_time = 0;
int time = 0;
int current_time = 0;
bool angry = false;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
int value;
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  myservo.attach(serPin);
}

void servo() {
  for (pos = 0; pos <= 180; pos +=1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }

  delay(500); //Small delay
}

String getDisplay() {

}

//
void resetBuddy() {

}



void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);

  //runtime loop:

  //get time since started
  time = millis() / 1000;

  value = analogRead(pResistor);
  Serial.println(value);
  if (value < 25){
    lcd.print("Low Light");
  }
  else{
    lcd.print("High Light");
  }

  if (!angry) {
    //the buddy isn't angry at you
    //countdown
    seconds_passed ++;

    if (seconds_passed == 59) {
        seconds_passed = 0;
        minutes_passed ++;
    }

    if (minutes_passed == 59) {
        hours_passed ++;
    }

    //check if countdown is down

    if (hours_passed == hour_countdown && minutes_passed == minutes_countdown && seconds_passed == seconds_countdown) {
        //countdown is done
        angry = true;
    }

    //if countdown is down, get attention
    angry = true;

    //reset the servo and timer
    //lcd.print(current_time);
}
else {
    //you need to drink some water
    //lcd.print("((•̀'ω'•́))");

    //check if water is drank
    
    //if so, set flag

    //if flag is set, and angry, check if water is put back.

    //if so, stop being angryangry = false;

    //reset servo

    myservo.write(0);
}

  servo();
  //lcd.print(current_time);
}