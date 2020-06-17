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

char *displayBuffer[] ={"15:15:25","40:40:60"}; 
byte i;

// 3, 66, 127, 64,       *****   5, 64, 66, 127, 64, 64,

void setup(void){
  P.begin();
}

void loop(void){
  
  if(P.displayAnimate()){
     
   P.displayText(displayBuffer[i], PA_CENTER, 20, 1000, PA_PRINT , PA_NO_EFFECT);
     delay(1000);
     i++;
     if( i >= 2){ i=0; }
  }
  
}
