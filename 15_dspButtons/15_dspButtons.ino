
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Button.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW 

#define MAX_DEVICES 8
#define CS_PIN      10
#define CLK_PIN     13
#define DATA_PIN    11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi

Button UP = Button(8,BUTTON_PULLDOWN); // UP
Button RG = Button(7,BUTTON_PULLDOWN); // RIGHT
Button DW = Button(6,BUTTON_PULLDOWN); // DOWN
Button LF = Button(5,BUTTON_PULLDOWN); // LEFT 
Button EN = Button(4,BUTTON_PULLDOWN); // ENTER
Button CN = Button(3,BUTTON_PULLDOWN); // CANCEL
Button F1 = Button(2,BUTTON_PULLDOWN); // F1

char *displaybuffer = " ";

String text;

word counter;
byte i = 0;

void setup() {
 P.begin();
 counter=0;
}

void loop() {
  
 if (P.displayAnimate())
 {
  
  if(UP.isPressed()){  // uniquePress
     counter++; 
     delay(100);
  } 
  
  if(DW.isPressed()){  
     counter--;
     delay(100);     
  }
  
  sprintf(displaybuffer, "%04d", counter );    
  P.displayText( displaybuffer , PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);

 }

}
