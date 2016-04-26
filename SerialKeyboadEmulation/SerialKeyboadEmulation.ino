/*
Last Build Notes for v1.0.0.2.

UNO

MEGA2560:
Sketch uses 6,400 bytes (2%) of program storage space. Maximum is 253,952 bytes.

Global variables use 430 bytes (5%) of dynamic memory, leaving 7,762 bytes for local variables. Maximum is 8,192 bytes.



  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
// Assign INPUT PIN NAMEs If you need more input names seperate them with a comma.
char* InputNames[5] = {"BTN_LEFT", "BTN_RIGHT", "BTN_CONFIRM", "BTN_DOWN", "BTN_UP"};
int totalnames = 5;

// Assign INPUT PINS If you need more input pins seperate them with a comma.
const int InputPin[5] = {7, 6, 10, 8, 9};
int totalins = 5;
int clicked = 0;

// Assign OUTPUT PINS
int outpin[1] = {13};
int totalouts = 1;


//Sketch CODE - Do not edit beond this point ------------------------------------
int lastinput = 0;
int lastclicked = 0;
const long sketchversion = 1.0;
int btnnum = 0;
int reading = LOW;
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
char* active = "";
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
int uniticks = 10;

//int tickEvent = t.every(1000, updateTime);
int val = 0;
byte index = 0;
#define TIMER_US 100                         // 100mS set timer duration in microseconds 
#define TICK_COUNTS 15                          // 2S worth of timer ticks
volatile long tick_count = TICK_COUNTS;         // Counter for 2S
volatile bool in_long_isr = false;

#include <TimerOne.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(12, 11); // RX, TX

void setup()
{
  int i = 0;

  while (i < totalins) {
    pinMode(InputPin[i], INPUT);

    i = i + 1;
  }
  i = 0;

  while (i < totalouts) {
    pinMode(outpin[i], OUTPUT);

    i = i + 1;
  }


  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  //}

  Serial.println("Connect. " + '\n');

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  mySerial.println("Connected..." + '\n');
  Timer1.initialize(1000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

}

void loop() // run over and over
{
  if (mySerial.available()) {
    //Serial.println(mySerial.read());
    if (Serial.available())
      mySerial.println(Serial.read());
  }
  //checkButtons();
}
void checkButtons() {
  int i = 0;

  while (i < totalins) {

    if (digitalRead(InputPin[i]) == HIGH) {
      reading = digitalRead(InputPin[i]);
      digitalWrite(outpin[1], HIGH);
      active = InputNames[i];
    }
    if (lastButtonState == LOW ) {
    if (digitalRead(InputPin[i]) == LOW) {
      reading = digitalRead(InputPin[i]);
      digitalWrite(outpin[1], LOW);
      active = InputNames[i];
    }
    }

    i = i + 1;
  }
  i = 1;



  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH),  and you've waited
  // long enough since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  i = 0;

  while (i < totalins) {

if (reading == buttonState) {
    if (digitalRead(InputPin[i]) == HIGH) {
      buttonClicked(InputPin[i]);
      lastButtonState == reading;
      lastinput = i;
    }
}
   if (reading == buttonState) {
   if ((digitalRead(InputPin[i]) == LOW) && (lastinput == i)) {
      buttonClicked(InputPin[i]);
      lastButtonState == reading;
    }
   }
    i = i + 1;
  }

  // set the LED:
  //digitalWrite(pin, ledState);
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
}
void timerIsr()
{
  digitalWrite( outpin[1], 0 );   // Toggle LED 0
  if (!(--tick_count))                             // Count to 2S
  {
    tick_count = TICK_COUNTS;                      // Reload
    tick_2s_isr();                                 // Call the 2S routine
  }
}
// --------------------------
// tick_2s_isr() 2 second routine
// Called every time the count gets to 2S
// --------------------------
void tick_2s_isr()
{
  if (in_long_isr)                                // Prevent reentering this code
  {
    return;  
  }
  in_long_isr = true;                             // Indicates we are in the long isr
  volatile long i;
  interrupts();                                   // Enable interrupts
  checkButtons();

  tick_count = TICK_COUNTS;
  digitalWrite(outpin[1], HIGH); // Toggle LED 1

  for (i = 0; i < 400000; i++)                   // Delay because delay() will not work here
  {
  }
  noInterrupts();                                 // Disable interrupts
  in_long_isr = false;                            // Indicates exit of the long isr
}
void buttonClicked(int btn) {
  btnnum = btn;
  int i = 0;

  while (i < totalins) {
    if (btn == InputPin[i] && digitalRead(InputPin[i]) == HIGH) {

      //Serial.print(InputPin[i]);
    
      Serial.print(InputPin[i]);
      Serial.println("H");
    }
    if (btn == InputPin[i] && digitalRead(InputPin[i]) == LOW) {

   if (lastButtonState == HIGH) {
  if (digitalRead(InputPin[i]) == LOW) {

      //Serial.print(InputPin[i]);

      
      Serial.print(InputPin[i]);
      Serial.println("L");
    

    }
    }
    }
    
    
    i = i + 1;
  }

  digitalWrite(outpin[1], LOW);
}


