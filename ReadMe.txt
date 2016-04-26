Arduino Serial Keyboard Emulator

ASKE is a software application that translates a high or low signal from a arduino then emulates a keypress on your pc or laptop.

The pupose of this applcation is to allow you to create custom game controllers for any game that requires a keyboard to play.

Open the Arduino sketch in the Arduino IDE.
Ensure TimerOne.h is install in the Arduino IDE - http://playground.arduino.cc/Code/Timer1
Assign the input names and totalnames variables
Assign the input pin numbers and totalpins variables.
Assign the output pin and totalouts vaiables. This will be a flashing led pin.
Upload the sketch to your arduino
Install the emulator software.
Build a key emulation list
Assign 2 new keypress's to the emulation list with the value of {LEFT} and {RIGHT}
Choose the COM port and baudrate and click connect. "Default baudrate is normally 9600"
Testing your controller. Open "Note Pad" type a random string of characters.
Push the corresponding button and try to move the cursor left and right along the random string and watch for a moving cursor. If the cursor moves it worked!
Use you new custom controller.