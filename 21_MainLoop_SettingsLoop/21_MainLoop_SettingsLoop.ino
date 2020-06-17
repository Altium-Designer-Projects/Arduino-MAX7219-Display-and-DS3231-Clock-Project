#include <Button.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define MAX_DEVICES 8
#define CS_PIN      10
#define CLK_PIN     13
#define DATA_PIN    11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi

char displayBuffer[12];

bool mainLoop = true; 
bool systemMainLoop = true;   // normal section
bool systemSettingsLoop = false;  // settings section

Button UP = Button(8,BUTTON_PULLDOWN);
Button RG = Button(7,BUTTON_PULLDOWN);
Button DW = Button(6,BUTTON_PULLDOWN);
Button LF = Button(5,BUTTON_PULLDOWN);
Button EN = Button(4,BUTTON_PULLDOWN);
Button CN = Button(3,BUTTON_PULLDOWN);
Button F1 = Button(2,BUTTON_PULLDOWN);

void setup(){

  P.begin();
    
}

void loop(){
  
if(P.displayAnimate()){
   P.displayText(displayBuffer , PA_CENTER, 25, 100, PA_PRINT, PA_NO_EFFECT);

   if(systemMainLoop == true && systemSettingsLoop == false){
   if(mainLoop == true){
      P.setSpeed(40);          
      P.setPause(500);     
      P.setTextEffect(0, PA_SCROLL_DOWN, PA_NO_EFFECT);     
      mainLoop = false;
   }
   
   strcpy(displayBuffer,"clock");

  
   } 
  
  // **************** ******************** **************************
   
  if(systemMainLoop == false && systemSettingsLoop == true){
     if(mainLoop == false){
        P.setSpeed(40);          
        P.setPause(500);     
        P.setTextEffect(0, PA_SCROLL_UP, PA_NO_EFFECT);       
        mainLoop = true;
     }
     
     strcpy(displayBuffer,"settings");  
   

     if(EN.heldFor(2000)){  // içeride
        systemMainLoop = true;
        systemSettingsLoop = false;       
     }
  
   }
  
  
  if(F1.heldFor(2000)){  // ana döngüde olmalı
     systemMainLoop = false; 
     systemSettingsLoop = true;
  }
  
} 





}
