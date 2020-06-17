#include <DS3231.h>
DS3231  rtc(SDA, SCL);

Time  t;    // struct

void setup(){
  Serial.begin(9600);
  rtc.begin();

  rtc.setDOW(MONDAY);       
  rtc.setTime(10,10,10);    
  rtc.setDate(20,05,2020); // gün ay yıl
}

void loop(){
  
  t = rtc.getTime();
  
  Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");  
  Serial.print(t.sec, DEC);
  
  Serial.print("   "); 
  Serial.print(t.dow, DEC); // 1
  Serial.print("   ");
  
  Serial.print(t.mon, DEC);
  Serial.print(".");
  Serial.print(t.date,DEC);
  Serial.print(".");
  Serial.println(t.year, DEC);

  delay (1000);
}
