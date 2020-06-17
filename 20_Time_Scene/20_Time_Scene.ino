#include <Button.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#include <DS3231.h>
DS3231 rtc(SDA, SCL);
Time  t;

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define MAX_DEVICES 8
#define CS_PIN      10
#define CLK_PIN     13
#define DATA_PIN    11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi


char displayBuffer[12];
byte dspScene = 0;
byte dspEffect = 0;

uint8_t degC[] = { 6, 3, 3, 56, 68, 68, 68 }; // Deg C
uint8_t degF[] = { 6, 3, 3, 124, 20, 20, 4 }; // Deg F

float temp;


void setup() {
  
  P.begin();
  rtc.begin();
  P.addChar('$', degC); 
  P.addChar('&', degF);
  
  rtc.setDOW(FRIDAY);        // Set Day-of-Week to SUNDAY
  rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(25, 04, 2020);   // Set the date to October 3th, 2010

}

void loop() {

if(P.displayAnimate()){
   t = rtc.getTime();

    P.displayText(displayBuffer , PA_CENTER, 25, 100, PA_PRINT, PA_NO_EFFECT);
  
    switch(dspScene){
     case 0:
       strcpy(displayBuffer,rtc.getTimeStr());
       if(dspEffect == 0 ){
          P.setTextEffect(PA_OPENING, PA_NO_EFFECT);  
          dspEffect = 1;
       }
     break;
     case 1:
       strcpy(displayBuffer, rtc.getDOWStr()); 
       if(dspEffect == 2){
          P.setTextEffect(PA_RANDOM, PA_NO_EFFECT);
          dspEffect = 3;
       } 
     break;
     case 2:
       strcpy(displayBuffer,rtc.getDateStr());
       if(dspEffect == 3){
          P.setTextEffect(PA_SCROLL_UP, PA_NO_EFFECT);
          dspEffect = 4;
       }  
     break;
     case 3:
       temp = rtc.getTemp();
       dtostrf(temp, 4, 2, displayBuffer);
       strcat(displayBuffer, " $");
   
       if(dspEffect == 4){
          P.setTextEffect(PA_SCROLL_DOWN, PA_NO_EFFECT);
          dspEffect = 0;
       }
     break;
    }

    // t.sec  0    30   31   40   41   50   51    59 
    //         time       dow       date      temp
  
   if(t.sec >= 0 && t.sec <= 30){
      dspScene = 0;
   }else if(t.sec >= 31 && t.sec <= 40){
      dspScene = 1;
   }else if(t.sec >= 41 && t.sec <= 50){
      dspScene = 2;
   }else if(t.sec >= 51 && t.sec <= 60){
      dspScene = 3;  
   }  
 
}
}
