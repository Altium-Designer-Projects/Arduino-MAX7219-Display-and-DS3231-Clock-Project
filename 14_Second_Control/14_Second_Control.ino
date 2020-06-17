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

char *city[] =
{
  "Ankara",
  "izmir",
  "Antalya",
  "Tosya",
};

byte i = 0;

byte Second = 0;
byte Minute = 0;
byte lastSecond;
byte dspScene = 0;

void setup(void){
 Serial.begin(9600);  
 P.begin();
 
 noInterrupts();      // disable all interrupts  // Timer1 kesmesi ayarlanıyor
 TCNT1  = 0;          // initialize counter value to 0
 TCCR1A = 0;          // same for TCCR1B
 TCCR1B = 0;          // set entire TCCR1A register to 0
 OCR1A = 15624;       // set compare match register for 1hz increments // = (16*10^6) / (1*1024) - 1 ( must be < 65536 )
 TCCR1B |= (1 << WGM12);               // turn on CTC mode   
 TCCR1B |= (1 << CS12) | (1 << CS10);  // Set CS10 and CS12 bits for 1024 prescaler
 TIMSK1 |= (1 << OCIE1A);              // enable timer compare interrupt
 interrupts();        // enable
   
}

void loop(void){
  if(P.displayAnimate()){
     P.displayText(displayBuffer, PA_CENTER, 20, 1000, PA_SCROLL_DOWN , PA_SCROLL_DOWN);

    switch(dspScene){
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

   if(Second >= 0 && Second <= 30){
      dspScene = 0;
   }else if(Second>= 31 && Second <= 40){
      dspScene = 1;
   }else if(Second >= 41 && Second <= 50){
      dspScene = 2;
   }else if(Second >= 51 && Second <= 60){
      dspScene = 3;  
   }
    
  }
  
}


ISR(TIMER1_COMPA_vect){   

    Second++;
    if(Second >= 60){
       Second = 0;
       Minute++;
       if(Minute >= 60){
          Minute = 0;
       }
    }

   if(Second != lastSecond){
      Serial.println("Time -- " + String(Minute) +":"+ String(Second));  
   }
   lastSecond = Second;    

}
