#include <DS3231.h>
DS3231  rtc(SDA, SCL);

void setup(){
  Serial.begin(9600);
  rtc.begin();
  
  rtc.setDOW(MONDAY);    
  rtc.setTime(12, 12, 12);    
  rtc.setDate(1, 1, 2018);  
}

void loop(){
  
  Serial.print(rtc.getTimeStr());    // Send time
  Serial.print(" -- ");
  
  Serial.print(rtc.getDOWStr());    // Send Day-of-Week
  Serial.print(" -- ");
  
  Serial.println(rtc.getDateStr());  // Send date

  delay (1000);
}
