#include <EEPROM.h>
#include <Button.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <DS3231.h>
DS3231 rtc(SDA, SCL);
Time  t;

Button UP = Button(8,BUTTON_PULLDOWN);
Button RG = Button(7,BUTTON_PULLDOWN);
Button DW = Button(6,BUTTON_PULLDOWN);
Button LF = Button(5,BUTTON_PULLDOWN);
Button EN = Button(4,BUTTON_PULLDOWN);
Button CN = Button(3,BUTTON_PULLDOWN);
Button F1 = Button(2,BUTTON_PULLDOWN);

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define MAX_DEVICES 8
#define CS_PIN      10
#define CLK_PIN     13
#define DATA_PIN    11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi

char displayBuffer[12];

char *daysName[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; 

bool systemMainLoop     = true;  // normal çalışma
bool systemSettingsLoop = false; // ayarlar kısmı

byte dspScene = 0;
byte dspEffect = 0;

uint8_t degC[] = { 6, 3, 3, 56, 68, 68, 68 }; // Deg C
uint8_t degF[] = { 6, 3, 3, 124, 20, 20, 4 }; // Deg F

float temp;

byte dataDirection;

byte timeHour;
byte timeMinute;
byte timeSecond;
byte timeDay;
byte timeMonth;  
byte timeDate;
word timeYear;

byte wait = 100;

bool mainLoop = true;  
bool timeSync = true;
bool eepromControl = true;

void setup(){

  P.begin();
  rtc.begin();
  P.addChar('$', degC); 
  P.addChar('&', degF);
  
  for(byte i = 0; i < 20; i++){
    displayBuffer[i] = '\0';
  }
 
}

void loop(){
 
 if(eepromControl == true){  
   if( EEPROM.read(0) != 150){
      rtc.setDOW(MONDAY);       
      rtc.setTime(12,12,12);    
      rtc.setDate(1,1,2018);  
   }
   eepromControl = false;  // enter butonundan sonra true yap
 }
 
if(P.displayAnimate()){
   P.displayText(displayBuffer , PA_CENTER, 25, 100, PA_PRINT, PA_NO_EFFECT);
   
   t = rtc.getTime(); // read rtcc
   
   if(systemMainLoop == true && systemSettingsLoop == false){
      if(mainLoop == true){
         P.setSpeed(40);          
         P.setPause(500);     
         P.setTextEffect(0, PA_SCROLL_DOWN, PA_NO_EFFECT);     
         mainLoop = false;
      }
  
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
         if(dspEffect == 1){
            P.setTextEffect(PA_RANDOM, PA_NO_EFFECT);
            dspEffect = 2;
         } 
       break;
       case 2:
         strcpy(displayBuffer,rtc.getDateStr());
         if(dspEffect == 2){
            P.setTextEffect(PA_SCROLL_UP, PA_NO_EFFECT);
            dspEffect = 3;
         }  
       break;
       case 3:
         temp = rtc.getTemp();
         dtostrf(temp, 4, 2, displayBuffer);
         strcat(displayBuffer, " $");
     
         if(dspEffect == 3){
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
  
   } // main loop
  
  // **************** ******************** **************************
   
  if(systemMainLoop == false && systemSettingsLoop == true){
      if(mainLoop == false){
         P.setSpeed(40);          
         P.setPause(500);     
         P.setTextEffect(0, PA_SCROLL_UP, PA_NO_EFFECT);       
         mainLoop = true;
      }
      
      if(timeSync == true){ 
         timeHour   = t.hour; 
         timeMinute = t.min;
         timeSecond = t.sec;
         timeDay    = t.dow;
         timeMonth  = t.mon;
         timeDate   = t.date;
         timeYear   = t.year;
         timeSync   = false;   //  enter dan sonra true yap
      }
    
      switch(dataDirection){
       case 0:
        displayBuffer[0]  = timeHour / 10 + 48;
        displayBuffer[1]  = timeHour % 10 + 48;
        displayBuffer[2]  = ':';
        displayBuffer[3]  = '-';
        displayBuffer[4]  = '-';
        displayBuffer[5]  = ':';
        displayBuffer[6]  = '-';
        displayBuffer[7]  = '-';
        displayBuffer[8]  = '\0';
        displayBuffer[9]  = '\0'; 
        displayBuffer[10] = '\0';
        displayBuffer[11] = '\0';  
       break;
       case 1:
        displayBuffer[0]  = '-';
        displayBuffer[1]  = '-';
        displayBuffer[2]  = ':';
        displayBuffer[3]  = timeMinute / 10 + 48;
        displayBuffer[4]  = timeMinute % 10 + 48;
        displayBuffer[5]  = ':';
        displayBuffer[6]  = '-';
        displayBuffer[7]  = '-';
        displayBuffer[8]  = '\0';
        displayBuffer[9]  = '\0'; 
        displayBuffer[10] = '\0';
        displayBuffer[11] = '\0';     
       break;
       case 2: 
        displayBuffer[0]  = '-';
        displayBuffer[1]  = '-';
        displayBuffer[2]  = ':';
        displayBuffer[3]  = '-';
        displayBuffer[4]  = '-';
        displayBuffer[5]  = ':';
        displayBuffer[6]  = timeSecond / 10 + 48;
        displayBuffer[7]  = timeSecond % 10 + 48;
        displayBuffer[8]  = '\0';
        displayBuffer[9]  = '\0'; 
        displayBuffer[10] = '\0';
        displayBuffer[11] = '\0';     
       break;
       case 3:        
        sprintf(displayBuffer, "%s", daysName[timeDay - 1]);  // - 1 important
       break;
       case 4:
        displayBuffer[0]  = timeDate / 10 + 48;
        displayBuffer[1]  = timeDate % 10 + 48;
        displayBuffer[2]  = '.';
        displayBuffer[3]  = '-';
        displayBuffer[4]  = '-';
        displayBuffer[5]  = '.';
        displayBuffer[6]  = '-';
        displayBuffer[7]  = '-';
        displayBuffer[8]  = '-';
        displayBuffer[9]  = '-'; 
        displayBuffer[10] = '\0';
        displayBuffer[11] = '\0';     
        break;
       case 5:
        displayBuffer[0]  = '-';
        displayBuffer[1]  = '-';
        displayBuffer[2]  = '.';
        displayBuffer[3]  = timeMonth / 10 + 48;
        displayBuffer[4]  = timeMonth % 10 + 48;
        displayBuffer[5]  = '.';
        displayBuffer[6]  = '-';
        displayBuffer[7]  = '-';
        displayBuffer[8]  = '-';
        displayBuffer[9]  = '-'; 
        displayBuffer[10] = '\0';
        displayBuffer[11] = '\0';   
        break;
       case 6:
        displayBuffer[0]  = '-';
        displayBuffer[1]  = '-';
        displayBuffer[2]  = '.';
        displayBuffer[3]  = '-';
        displayBuffer[4]  = '-';
        displayBuffer[5]  = '.';
        displayBuffer[6]  = timeYear / 1000 % 10 + 48;
        displayBuffer[7]  = timeYear / 100  % 10 + 48;
        displayBuffer[8]  = timeYear / 10   % 10 + 48;
        displayBuffer[9]  = timeYear % 10 + 48;  
        displayBuffer[10] = '\0';
        displayBuffer[11] = '\0';  
        break;    
      }

      switch(dataDirection){
       case 0:
         if(UP.isPressed()){
            timeHour++; 
            delay(wait);
            if(timeHour >= 24){
                 timeHour = 0;
            } 
         }
         if(DW.isPressed()){
            timeHour--; 
            delay(wait);     
            if(timeHour >= 255){
               timeHour = 23;
            }             
         }
       break;
       case 1:   // dakika kısmı
        if(UP.isPressed()){
            timeMinute++;  
            delay(wait);          
            if(timeMinute >= 60){
               timeHour++;
               timeMinute = 0;
            } 
         }
         if(DW.isPressed()){
            timeMinute--; 
            delay(wait);          
            if(timeMinute >= 255){
               timeMinute = 59;        
               timeHour--;
            }             
         }
        break;
        case 2:   // saniye kısmı
         if(UP.isPressed()){
            timeSecond++; 
            delay(wait);          
            if(timeSecond >= 60){
               timeSecond = 0;        
               timeMinute++;
            }  
         }
         if(DW.isPressed()){
            timeSecond--; 
            delay(wait);            
            if(timeSecond >= 255){
               timeSecond = 59;  
               timeMinute--;
            }  
         }
        break;
        case 3:
         if(UP.isPressed()){
            timeDay++;  
            delay(wait);            
            if(timeDay >= 8){
               timeDay = 1;
            } 
         }
         if(DW.isPressed()){
            timeDay--; 
            delay(wait);            
            if(timeDay < 1){
               timeDay = 7;
            } 
         }
        break;
        case 4:// Date
         if(UP.isPressed()){ 
            timeDate++; 
            delay(wait);
            if(timeDate >= 32){
               timeDate = 1;
            } 
         }
         if(DW.isPressed()){
            timeDate--;
            delay(wait);           
            if(timeDate <= 0){
               timeDate = 31;
            }             
         }
        break;
        case 5:  // month
         if(UP.isPressed()){  
            timeMonth++;  
            delay(wait);          
            if(timeMonth >= 13){
               timeMonth = 1;
            } 
         }
         if(DW.isPressed()){
            timeMonth--; 
            delay(wait);          
            if(timeMonth <= 0 ){  // 252 253 254 255 0 1 2 3  
               timeMonth = 12;
            }             
         }
        break;        
        case 6:
         if(UP.isPressed()){  // timeDate timeYear
            timeYear++; 
            delay(wait);           
            if(timeYear >= 2099){
               timeYear = 2010;
            } 
         }
         if(DW.isPressed()){
            timeYear--; 
            delay(wait);          
            if(timeYear <= 1950){
               timeYear = 2099;
            }             
         }
        break;
        } // switch son
    
        if(RG.uniquePress()){  
           dataDirection++;
           if(dataDirection >= 7){
              dataDirection=0;   
           }
        }
       
        if(LF.uniquePress()){ 
           dataDirection--;
           if(dataDirection >= 255){
              dataDirection = 6;   
           }
        }
   
        if(EN.heldFor(3000)){  // enter button
           rtc.setTime(timeHour, timeMinute, timeSecond);    
           rtc.setDOW(timeDay); 
           rtc.setDate(timeDate, timeMonth, timeYear);  // gün ay yıl
                      
           EEPROM.write(0 , 150);
           dataDirection = 0;
           eepromControl = true;
           timeSync = true;
           
           mainLoop = true;
           systemMainLoop = true; 
           systemSettingsLoop = false;    
        }
  
   } // if(systemTime == false && systemSettings == true) end off

  
  if(F1.heldFor(2000)){  // ana döngüde olmalı // ayarlar bölümüne giriş yapıyoruz
     systemMainLoop = false; 
     systemSettingsLoop = true;
  }
  
} // if(P.displayAnimate()) end off

} // main loop
