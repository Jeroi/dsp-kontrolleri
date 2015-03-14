#include "TFTLCD.h"
#include "TouchScreen.h"
#include <Wire.h>

//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:



#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
// optional
#define LCD_RESET A4

// Color definitions
#define BLACK           0x0000      /*   0,   0,   0 */
#define NAVY            0x000F      /*   0,   0, 128 */
#define DARKGREEN       0x03E0      /*   0, 128,   0 */
#define DARKCYAN        0x03EF      /*   0, 128, 128 */
#define MAROON          0x7800      /* 128,   0,   0 */
#define PURPLE          0x780F      /* 128,   0, 128 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY       0xC618      /* 192, 192, 192 */
#define DARKGREY        0x7BEF      /* 128, 128, 128 */
#define BLUE            0x001F      /*   0,   0, 255 */
#define GREEN           0x07E0      /*   0, 255,   0 */
#define CYAN            0x07FF      /*   0, 255, 255 */
#define RED             0xF800      /* 255,   0,   0 */
#define MAGENTA         0xF81F      /* 255,   0, 255 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define WHITE           0xFFFF      /* 255, 255, 255 */
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define PINK            0xF81F


TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

Wire i2c;

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

audiokanava channel[4];
uint8_t currentChannel = 0;
boolean loudness = false;
int volume = 0;

void setup(void) {
  Serial.begin(9600);
  i2c.begin();
  Serial.println("Paint!");
   p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
   
   //Mapataan voimakkuus alussa piirtopikselien mukaan oikeeseen korkeus kordinaattiin
   //Koska voimme vahvistaa 10db pitää alkuarvo nolla siirtää 10db eteenpäin
    volume = map(volume+10, 0, 110, 30, 250)
  
  tft.reset();
  
  /*
  uint16_t identifier = tft.readRegister(0x0);
  if (identifier == 0x9325) {
    Serial.println("Found ILI9325");
  } else if (identifier == 0x9328) {
    Serial.println("Found ILI9328");
  } else {
    Serial.print("Unknown driver chip ");
    Serial.println(identifier, HEX);
    while (1);
  }
*/
  tft.initDisplay(); 
  Serial.println(audioKanava[0].getMute);
  pyyhiruutu();
  
  /*
  tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
  tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
  tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, BLUE);
  tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
 // tft.fillRect(BOXSIZE*6, 0, BOXSIZE, BOXSIZE, WHITE);
 
 tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
 currentcolor = RED;
 */
  pinMode(13, OUTPUT);
}



#define MINPRESSURE 10
#define MAXPRESSURE 1000



void loop()
{

}
