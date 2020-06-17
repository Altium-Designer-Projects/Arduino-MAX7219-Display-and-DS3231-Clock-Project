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

char displayBuffer[12];

struct sCatalog
{
  textEffect_t  effect;   // text effect to display
  const char *  psz;      // text string nul terminated
  uint16_t      speed;    // speed multiplier of library default
  uint16_t      pause;    // pause multiplier for library default
};

sCatalog catalog[] =
{
  { PA_PRINT, "PRINT", 1, 1 },
  { PA_SCROLL_UP, "SC_UP", 5, 1 },
  { PA_SCROLL_DOWN, "SCR_DOWN", 5, 1 },
  { PA_SCROLL_LEFT, "SCR_LEFT", 5, 1 },
  { PA_SCROLL_RIGHT, "SCR_RIGHT", 5, 1 },
#if ENA_SPRITE
  { PA_SPRITE, "SPRITE", 5, 1 },
#endif
#if ENA_MISC
  { PA_SLICE, "SLICE", 1, 1 },
  { PA_MESH, "MESH", 20, 1 },
  { PA_FADE, "FADE", 20, 1 },
//  { PA_DISSOLVE, "DSLVE", 7, 1 },
//  { PA_BLINDS, "BLIND", 7, 1 },
  { PA_RANDOM, "RANDOM", 3, 1 },
#endif
#if ENA_WIPE
  { PA_WIPE, "WIPE", 5, 1 },
  { PA_WIPE_CURSOR, "WPE_C", 4, 1 },
#endif
#if ENA_SCAN
  { PA_SCAN_HORIZ, "SCNH", 4, 1 },
  { PA_SCAN_HORIZX, "SCNHX", 4, 1 },
  { PA_SCAN_VERT, "SCNV", 3, 1 },
  { PA_SCAN_VERTX, "SCNVX", 3, 1 },
#endif
#if ENA_OPNCLS
  { PA_OPENING, "OPEN", 3, 1 },
  { PA_OPENING_CURSOR, "OPN_CURSOR", 4, 1 },
  { PA_CLOSING, "CLOSE", 3, 1 },
  { PA_CLOSING_CURSOR, "CLS_CURSOR", 4, 1 },
#endif
#if ENA_SCR_DIA
  { PA_SCROLL_UP_LEFT, "SCR_UL", 7, 1 },
  { PA_SCROLL_UP_RIGHT, "SCR_UR", 7, 1 },
  { PA_SCROLL_DOWN_LEFT, "SCR_DL", 7, 1 },
  { PA_SCROLL_DOWN_RIGHT, "SCR_DR", 7, 1 },
#endif
#if ENA_GROW
  { PA_GROW_UP, "GRW_UP", 7, 1 },
  { PA_GROW_DOWN, "GRW_DOWN", 7, 1 },
#endif
};

// Sprite Definitions
const uint8_t F_PMAN1 = 6;
const uint8_t W_PMAN1 = 8;
static const uint8_t PROGMEM pacman1[F_PMAN1 * W_PMAN1] =  // gobbling pacman animation
{
  0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
};

const uint8_t F_PMAN2 = 6;
const uint8_t W_PMAN2 = 18;
static const uint8_t PROGMEM pacman2[F_PMAN2 * W_PMAN2] =  // ghost pursued by a pacman
{
  0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe,
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x73, 0xfb, 0x7f, 0xf3, 0x7b, 0xfe,
};

void setup(void){
  P.begin();
#if ENA_SPRITE
  P.setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman2, W_PMAN2, F_PMAN2);
#endif

  for(uint8_t i=0; i<ARRAY_SIZE(catalog); i++){
      catalog[i].speed *= P.getSpeed();
      catalog[i].pause *= 500;
  }
  
}

void loop(void){
  static uint8_t i = 0;   // text effect index

  if(P.displayAnimate()){
    if(i == ARRAY_SIZE(catalog)){
       i = 0;  // reset loop index
    }

    // set up new animation
    P.displayText(catalog[i].psz, PA_CENTER, catalog[i].speed, catalog[i].pause, catalog[i].effect, catalog[i].effect);

    i++;   // then set up for next text effect
    
  }
}
