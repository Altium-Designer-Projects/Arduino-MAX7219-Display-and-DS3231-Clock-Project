#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW 

#define MAX_DEVICES 8
#define CS_PIN      10
#define CLK_PIN     13
#define DATA_PIN    11

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES); // Software spi

char msg[] = "Parola Sprites";

char *buffer_text[] =
{
  "istanbul",
  "ankara",
  "antalya",
  "vedat",
  "baloglu",
  "ABCDEF",
  "123456"
};

byte i = 0;

// Sprite Definition
const uint8_t F_ROCKET = 2;
const uint8_t W_ROCKET = 11;
const uint8_t PROGMEM rocket[F_ROCKET * W_ROCKET] =  // rocket
{
  0x18, 0x24, 0x42, 0x81, 0x99, 0x18, 0x99, 0x18, 0xa5, 0x5a, 0x81,
  0x18, 0x24, 0x42, 0x81, 0x18, 0x99, 0x18, 0x99, 0x24, 0x42, 0x99,
};

void setup(void)
{
  P.begin();

  P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
}

void loop(void)
{
 if (P.displayAnimate()){
     P.displayText(buffer_text[i], PA_CENTER, 20, 1000, PA_SPRITE, PA_SPRITE);
    
     delay(1000);
     i++;
     if( i >= 7){
       i=0;
      }
 }
}
