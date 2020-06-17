
#include <DS3231.h>
DS3231  rtc(SDA, SCL);

void setup(){
  Serial.begin(9600);
  rtc.begin();
}

void loop(){
  
  Serial.print("Temperature: ");
  Serial.print(rtc.getTemp());
  Serial.println(" C");
  delay (1000);
}
