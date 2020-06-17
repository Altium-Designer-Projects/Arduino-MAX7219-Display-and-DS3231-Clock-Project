#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW  // FC16_HW

#define MAX_DEVICES 8
#define CLK_PIN     13
#define DATA_PIN    11
#define CS_PIN      10

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi

char displayBuffer[12];

textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;

#define	BUF_SIZE	75
char displaybuffer[BUF_SIZE] = { "" };
char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
bool newMessageAvailable = true;

void readSerial(void){
  static char *cp = newMessage;

  while(Serial.available()){
    *cp = (char)Serial.read();
    if((*cp == '\n') || (cp - newMessage >= BUF_SIZE-2)){ // end of message character or full buffer
       *cp = '\0'; // end the string
        cp = newMessage;  // restart the index for next filling spree and flag we have a message waiting
        newMessageAvailable = true;
    }else{
        cp++;// move char pointer to next position
    }  
  }
  
}

void setup(){
  Serial.begin(9600);
  Serial.print("Parola Scrolling Display");
  P.begin();
  P.displayText(displaybuffer, scrollAlign, 25, 2000, scrollEffect, scrollEffect);
}

void loop(){

  if (P.displayAnimate()){
    if (newMessageAvailable){
      strcpy(displaybuffer, newMessage);
      newMessageAvailable = false;
    }
    P.displayReset();
  }
  readSerial();
}
