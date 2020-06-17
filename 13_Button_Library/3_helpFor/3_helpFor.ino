#include <Button.h>

Button UP = Button(8,BUTTON_PULLDOWN); // UP
Button RG = Button(7,BUTTON_PULLDOWN); // RIGHT
Button DW = Button(6,BUTTON_PULLDOWN); // DOWN
Button LF = Button(5,BUTTON_PULLDOWN); // LEFT 
Button EN = Button(4,BUTTON_PULLDOWN); // ENTER
Button CN = Button(3,BUTTON_PULLDOWN); // CANCEL
Button F1 = Button(2,BUTTON_PULLDOWN); // F1

boolean display_settings = false;  
byte counter = 0;


void setup(){
  Serial.begin(9600);
}

void loop(){
  
 Serial.println("main loop");
 delay(500);
  
 if(F1.heldFor(2000)){    // 2000 milliseconds
    display_settings = true;
 }

 while(display_settings == true){
  Serial.print("Counter...");
  Serial.println(counter);
  counter++;
  delay(500);
 }

  
  
}
