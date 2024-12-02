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
int countdown = 3, seconds = 3, minutes = 0, hours = 0;
int reset_time = 0, time = 0, time_passed = 0, previous_time = 0;
bool angry = false;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
int light_value;
bool isDown = true;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  myservo.attach(serPin);
}

void wave() {
  lcd.setCursor(2, 0);
  lcd.print("DRINK WATER!");

  for (pos = 45; pos <= 135; pos +=1) {
    myservo.write(pos);
    delay(7);
  }
  for (pos = 135; pos >= 45; pos -= 1) {
    myservo.write(pos);
    delay(7);
  }

  delay(300); //Small delay
}

String getDisplay() {
  lcd.setCursor(2, 0);
  lcd.print("DRINK  TIMER");
  lcd.setCursor(4, 1);
  String display = "";
  if (hours < 10) {
    display += "0";
  }
  display += hours;
  display += ":";
  if (minutes < 10) {
    display += "0";
  }
  display += minutes;
  display += ":";
  if (seconds < 10) {
    display += "0";
  }
  display += seconds;
  return display;
}

//
void resetBuddy() {
  //to reset, reset the variables
  countdown = 3;
  seconds = 3;
  minutes = 0;
  hours = 0;
  reset_time = time;
  time_passed = 0;
  previous_time = 0;
  int pos = myservo.read();
  for (int i = pos; i >= 45; i--) {
    myservo.write(i);
    delay(10);
  }
  lcd.setCursor(2, 0);
  lcd.print("DRINK  TIMER");
  angry = false;
}

void loop() {
  //runtime loop:
  //get sensor data and time since started
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  time = millis() / 1000;
  time_passed = time - reset_time;
  light_value = analogRead(pResistor);

  Serial.println(light_value);

  if (light_value < 50) {
    //cup is down
    isDown = true;
  }
  else {
    isDown = false;
  }

  //check if angry
  if (angry) {
    //arduino is mad that you're not drinking water
    wave();
    if (!isDown) {
      resetBuddy();
    }
  }
  else {
    //arduino is counting down
    if (previous_time != time_passed) {
      //a second has passed
      countdown--;
      if (seconds == 0) {
        seconds = 59;
        if (minutes == 0) {
          minutes = 59;
          hours--;
        }
        else {
          minutes--;
        }
      }
      else {
        seconds--;
      }
      previous_time = time_passed;
    }
    
    if (countdown == 0) {
      //countdown is done
      angry = true;
    }

    String display = getDisplay();

    //display the timer
    lcd.print(display);

    //now check if the water bottle is lifted
    if (!isDown) {
      //waterbottle was lifted, reset
      resetBuddy();
    }
  }
}