# ASKE
Arduino Serial Keyboard Emulator

ASKE is a software application that translates a high or low signal from a arduino then emulates a keypress on your pc or laptop.

The pupose of this applcation is to allow you to create custom game controllers for any game that requires a keyboard to play.

1. Open the Arduino sketch in the Arduino IDE. 
2. Assign the input names and totalnames variables
3. Assign the input pin numbers and totalpins variables.
4. Assign the output pin and totalouts vaiables. This will be a flashing led pin.
5. Upload the sketch to your arduino
6. Install the emulator software.
7. Build a key emulation list
8. Assign 2 new keypress's to the emulation list with the value of {LEFT} and {RIGHT}
9. Choose the COM port and baudrate and click connect. "Default baudrate is normally 9600"
10. Testing your controller. Open "Note Pad" type a random string of characters.
11. Push the corresponding button and try to move the cursor left and right along the random
    string and watch for a moving cursor. If the cursor moves it worked!
12. Use you new custom controller.
