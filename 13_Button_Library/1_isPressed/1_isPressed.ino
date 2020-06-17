
#include <Button.h>

Button UP = Button(8,BUTTON_PULLDOWN); // UP
Button RG = Button(7,BUTTON_PULLDOWN); // RIGHT
Button DW = Button(6,BUTTON_PULLDOWN); // DOWN
Button LF = Button(5,BUTTON_PULLDOWN); // LEFT 
Button EN = Button(4,BUTTON_PULLDOWN); // ENTER
Button CN = Button(3,BUTTON_PULLDOWN); // CANCEL
Button F1 = Button(2,BUTTON_PULLDOWN); // F1

byte counter = 0;
byte lastcounter;

void setup(){
 Serial.begin(115200);
}

void loop(){

  if(UP.isPressed()){  // basılı tutabiliriz 
    counter++; 
  } 
  
  if(DW.isPressed()){  
    counter--;
  }
  
  if(counter != lastcounter)              
  {
   Serial.print("Counter...");
   Serial.println(counter);
   //delay(250);
  }
  lastcounter = counter;  
 
} 
