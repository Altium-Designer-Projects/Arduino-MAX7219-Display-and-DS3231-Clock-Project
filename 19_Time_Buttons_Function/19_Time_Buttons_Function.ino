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

Button UP = Button(8,BUTTON_PULLDOWN);
Button RG = Button(7,BUTTON_PULLDOWN);
Button DW = Button(6,BUTTON_PULLDOWN);
Button LF = Button(5,BUTTON_PULLDOWN);
Button EN = Button(4,BUTTON_PULLDOWN);
Button CN = Button(3,BUTTON_PULLDOWN);
Button F1 = Button(2,BUTTON_PULLDOWN);

char displayBuffer[12];

char *days_name[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; 
                    
byte dataDirection;

byte timeHour;
byte timeMinute;
byte timeSecond;
byte timeDay;
byte timeMonth;  
byte timeDate;
word timeYear;

byte wait = 100;

void setup(void){
 P.begin();
 timeHour   = 15;  // bunlar sadece bu projede örnek
 timeMinute = 25;
 timeSecond = 35;

 timeDay    = 3;
 
 timeMonth  = 12;
 timeDate   = 12;
 timeYear   = 2015;
    
}

void loop(void){
  
 if(P.displayAnimate()){
    P.displayText(displayBuffer, PA_CENTER, 15, 100, PA_PRINT , PA_NO_EFFECT);
  
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
    sprintf(displayBuffer, "%s", days_name[timeDay - 1]);  // - 1 important
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
   case 0: // hour
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
   case 1:   // minute
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
    case 2:   // second
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
    case 4:  // Date 
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
    case 5: // Month
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
  
   if(F1.heldFor(2000)){   // ayarlar bölümüne gideceğiz
     // _value = true;
   } 


 } //// dsp son

  
}
