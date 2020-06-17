#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW 

#define MAX_DEVICES 8
#define CS_PIN      10
#define CLK_PIN     13
#define DATA_PIN    11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi

char displayBuffer[12];

char *city[] =
{
  "Ankara",
  "izmir",
  "Antalya",
  "Tosya",
};

byte i = 0;


void setup(void){
  P.begin();
}

void loop(void){
  if(P.displayAnimate()){
    
    P.displayText(displayBuffer, PA_CENTER, 20, 1000, PA_SCROLL_DOWN , PA_SCROLL_DOWN);

    switch(i){
      case 0: 
       P.setTextBuffer(city[0]);
       P.setTextEffect(0, PA_OPENING, PA_CLOSING);
      break;
      case 1: 
       P.setTextBuffer(city[1]);
       P.setTextEffect(0, PA_SCROLL_DOWN, PA_SCROLL_RIGHT);
      break;
      case 2: 
       P.setTextBuffer(city[2]);
       P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      break;
      case 3: 
       P.setTextBuffer(city[3]);
       P.setTextEffect(0, PA_SCROLL_UP_LEFT, PA_SCROLL_UP_RIGHT);
      break;
      case 4:  
       strcpy(displayBuffer,"vedat");
       P.setTextBuffer(displayBuffer);
      break;
    }

    i++; 
    if (i >= 5){
      i=0;
    }
    delay(1000);
     
  }
  
}
