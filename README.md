# Arduino-supplying-machine-code-and-description
I built a 30cm x 30cm x 30cm vending machine using Arduino and box and 3D printed rail. This repository show instructor and advice and code. It gives two items.
Steps : 
(1) Download and install library below 
1.Stepper.h
2.Wire.h
3.LiquidCrystal_I2C.h
4.Keypad.h
***press Ctrl + Shift + M in Arduino to open the window to install those library
(3) Read and implement Arduino_first.cpp , in main branch. You should set your pin position as mentioned in the file.
3-1 Link two motors to two ULN2003 repectively. Afterward, set the pin of ULN2003 as mentioned in the file. 
3-2 Set the pin of buttons as mentioned in the file.
*** You may need to use an bread board in order to deliver the power.
(4) Read and implement Arduino_second.cpp , in main branch. You should set your pin position as mentioned in the file.
4-1 Link two motors to two ULN2003 repectively. Afterward, set the pin of ULN2003 as mentioned in the file. 
4-2 Set the pin of 4x4 keypad. !! Notice the row and column.
4-3 Set the pin of the LCD.
*** You may need to use an bread board in order to deliver the power.
*** We use two Arduino UNO here , since our power is not enough. The first UNO is the major UNO, it delivers power to two motors and 4 X 4 keypad; it also control those item. The second UNO give power to LCD, but the control is on the first. 
(5) Then you will get two module. Combine them and build them in an cardboard, and you will get a supply machine. In my case, I supply tissue paper and toilet cover.
*** You may need to build rooms to hide the wires and holes to layout the wires.
