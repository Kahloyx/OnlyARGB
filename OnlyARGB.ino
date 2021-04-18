#include <Wire.h>

#include <FastLED.h>
int currpal = 4;        // This one is the palette by default (the aestethicc one)
int maxPalette = 4;     // This is the number of registrered palette we got

#define LED_PIN     3       // This is the signal pin for the leds
#define NUM_LEDS    60       // This is in fact 9 + 37 + 14
#define BRIGHTNESS  128        // Was first at 64 then 16
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1 // I used 42 for the secondPalette() 2520/42=60   see line 73 to see the calculation of the speed and fluidity        in order to keep the 60 ratio we can also have like 60*1000=60000

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void setup() {
  delay( 200 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Serial.begin(115200);
  while (!Serial) {
    // will pause Zero, Leonardo, etc until serial console opens
    delay(1);
  }

  uint32_t currentFrequency;
	//pinMode(argbSwitch, OUTPUT);
  int j = 0;
  while (j < 2) {               // Just an init as we love'em
    fill_solid( currentPalette, 16, CRGB::White);
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
	  //digitalWrite(argbSwitch, HIGH);  // By activating this output we feed the Vin of the color ring and so it light up
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    //digitalWrite(argbSwitch, LOW);   // And then we shut it off, init thing ya know
    delay(420);
    j++;
  }
  Serial.println("Hello!");
  //digitalWrite(argbSwitch, HIGH);           // This means that once the init done we light the argb on on the default palette
}
void loop () {
  if (currpal == 1){
    FirstPalette();
  }
  if (currpal == 2){
    SecondPalette();
  }
  if (currpal == 3){
    ThirdPalette();
  }
  if (currpal == 4){
    FourthPalette();
  }
  if (currpal > maxPalette){    // This way we cycle throught the palette we got
    currpal = 1;
  }


  static uint8_t startIndex = 0;     //Displaying the palette we've choosen
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(120 / UPDATES_PER_SECOND);

  if ( Serial.available()) {     // Check if any char available on serial, if there's any instructions
    char c = Serial.read();
    if (c == 's'){
      Serial.println(c);
      Serial.println("Switching.");
      currpal = currpal +1;
    }
    /*if (c == 'n'){
      digitalWrite(argbSwitch, HIGH);
    }
    if (c == 'f'){
      digitalWrite(argbSwitch, LOW);
    } */
  }
}

// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.

void FirstPalette()
{
  //Serial.println(HUE_PURPLE);
  CRGB c1 = CHSV( HUE_RED, 255, 255);
  CRGB c2 = CHSV( HUE_ORANGE, 255, 255);
  CRGB c3 = CHSV( HUE_YELLOW, 255, 255);
  CRGB c4 = CHSV( HUE_GREEN, 255, 255);
  CRGB c5 = CHSV( HUE_AQUA, 255, 255);
  CRGB c6 = CHSV( HUE_BLUE, 255, 255);
  CRGB c7 = CHSV( HUE_PURPLE, 255, 255);
  CRGB c8 = CHSV( HUE_PINK, 255, 255);
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = c1;
  currentPalette[2] = c2;
  currentPalette[4] = c3;
  currentPalette[6] = c4;
  currentPalette[8] = c5;
  currentPalette[10] = c6;
  currentPalette[12] = c7;
  currentPalette[14] = c8;

}

// This function sets up a palette of pink and cyan stripes.
/*void SecondPalette()                 // What I got in This Function is a half and half circle cyan and pink, way too much aestethicc and the speed is calculated and smooth enought.
{
  CRGB c1 = CHSV( HUE_AQUA, 255, 255);
  //CRGB green  = CHSV( HUE_PURPLE, 255, 255);
  CRGB c2 = CHSV( HUE_PINK, 255, 255);
  CRGB c3  = CRGB::Black;
  //fill_solid( currentPalette, 16, c2);

  currentPalette = CRGBPalette16(
                     c1, c2, c1, c2,
                     c1, c2, c1, c2,
                     c1, c2, c1, c2,
                     c1, c2, c1, c2 );
}
*/
void SecondPalette()                 // What I got in This Function is a half and half circle cyan and pink, way too much aestethicc and the speed is calculated and smooth enought.
{
  CRGB c1 = CHSV( HUE_AQUA, 255, 255);
  //CRGB green  = CHSV( HUE_PURPLE, 255, 255);
  CRGB c2 = CHSV( HUE_PINK, 255, 255);
  CRGB c3  = CRGB::Black;
  //fill_solid( currentPalette, 16, c2);

  currentPalette = CRGBPalette16(
                     c1, c1, c2, c2,
                     c1, c1, c2, c2,
                     c1, c1, c2, c2,
                     c1, c1, c2, c2 );
}
void ThirdPalette()                 // What I got in This Function is a half and half circle cyan and pink, way too much aestethicc and the speed is calculated and smooth enought.
{
  CRGB c1 = CHSV( HUE_RED, 255, 255);
  CRGB c2  = CHSV( HUE_ORANGE, 255, 255);
  CRGB c3 = CHSV( HUE_YELLOW, 255, 255);
  CRGB c4 = CHSV( HUE_PINK, 255, 255);
  CRGB c5  = CRGB::Black;
  //fill_solid( currentPalette, 16, c2);

  currentPalette = CRGBPalette16(
                     c1, c2, c3, c4,
                     c1, c2, c3, c4,
                     c1, c2, c3, c4,
                     c1, c2, c3, c4 );
}

void FourthPalette()
{
  CRGB c1 = CHSV(HUE_YELLOW, 255, 255);
  CRGB c2 = CHSV(HUE_PINK, 255, 255);
  fill_solid( currentPalette, 16, CRGB::Black);
  currentPalette[0] = c1;
  currentPalette[2] = c2;
  currentPalette[5] = c1;
  currentPalette[8] = c2;
  currentPalette[11] = c1;
  currentPalette[14] = c2;
  Serial.println("PALETTE 4 SELECTED");
}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.