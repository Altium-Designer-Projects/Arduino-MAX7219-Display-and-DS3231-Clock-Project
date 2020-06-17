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

/*
  PA_LEFT;  sol tarafa yaslıyor
  PA_CENTER
  PA_RIGHT  // dene
  
  PA_PRINT,
  PA_NO_EFFECT,
  
  PA_SCAN_HORIZ,
  PA_SCAN_VERT
  
  PA_SCROLL_LEFT,
  PA_SCROLL_RIGHT
  
  PA_WIPE,
  PA_WIPE_CURSOR
  
  PA_SCROLL_UP_RIGHT,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_MESH,

  PA_BLINDS,
  
  PA_OPENING
  PA_CLOSING,
  PA_CLOSING_CURSOR
  
  PA_RANDOM,
  PA_GROW_DOWN,
  
  PA_DISSOLVE
  PA_SLICE,
  
  PA_SCROLL_DOWN
  PA_SCROLL_DOWN_LEFT,
  PA_SCROLL_DOWN_RIGHT,

*/

void setup(void){
  P.begin();
}
 
void loop(void){
  
 if(P.displayAnimate()){
   P.displayText("12-15-40", PA_CENTER, 25, 1000, PA_SCROLL_LEFT, PA_SCROLL_RIGHT);
   //             char *      align, speed, pause, effectIn, effectOut
 }
  
}
