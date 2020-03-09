/* -------------------------------------------------------------
 *  Project Name: Joystick and Matrix
 *  Author:       ScottC
 *  Date:         08 March 2020
 *  IDE version:  1.8.5 (Windows 10)
 *  Tutorial at:  https://arduinobasics.blogspot.com/2020/03/matrix-and-joystick.html
 *  ------------------------------------------------------------
 */

#include <SPI.h>

/* DEFINE MATRIX PINS */
const int CE = 10; 

/* DEFINE JOYSTICK PINS */
const int Button_pin = 2;  // Button connected to Digital pin D2
const int X_pin = A0;      // X connected to Analog pin A0
const int Y_pin = A1;      // Y connected to Analog pin A1

/* GLOBAL VARIABLES */
int Xval, Yval, Bval; 
byte row = 1;
byte col = 1;
byte myColour = 0;


/* --------------------------------------------------------
 *  SETUP: used to configure the joystick and matrix pins
 ----------------------------------------------------------*/
void setup() {
  pinMode(Button_pin, INPUT_PULLUP);
  pinMode(CE, OUTPUT);        
  SPI.begin();      
  delay(1000);
}

/* --------------------------------------------------------
 *  LOOP: read the X, Y and button values from the 
 *        joystick, and then map them to matrix positions
 ----------------------------------------------------------*/
void loop() {
  //Read the button pin, if pressed, then change the colour
  Bval= digitalRead(Button_pin);
  if(Bval==0){   
    myColour++;
    if(myColour>2){
      myColour=0;
    }
    delay(200);
  }

  //Read the X pin, and map this value to the matrix row
  Xval=analogRead(X_pin);
  row = map(Xval, 0, 1000, 0, 7);

  //Read the Y pin, and map this value to the matrix column
  Yval=analogRead(Y_pin);
  col = map(Yval, 0, 1000, 0, 7);

  //Display the pixel based on the row, column and colour
  displayPixel(row, col, myColour);
  delay(2);
}


/* --------------------------------------------------------
 *  displayPixel: This function uses a row (r), column (c)
 *                and colour variable to display a pixel
 *                on the matrix using SPI.
 ----------------------------------------------------------*/
void displayPixel(byte r, byte c, byte colour){
  byte myRow = ~(0x01<<r);
  byte myColumn= 0x01<<c;
  byte myPixel[3] = {0xFF, 0xFF, 0xFF};
    myPixel[colour] = myRow;
     
    digitalWrite(CE, LOW);
    SPI.transfer(myPixel[0]);  //red pixel   (0xFF = off)
    SPI.transfer(myPixel[1]);  //blue pixel  (0xFF = off)
    SPI.transfer(myPixel[2]);  //green pixel (0xFF = off)
    SPI.transfer(myColumn);          
    digitalWrite(CE, HIGH);
}
