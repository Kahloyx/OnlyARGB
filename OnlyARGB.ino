#include <Wire.h>

#include <FastLED.h>
int currpal = 4;        // This one is the palette by default (the aestethicc one)
int maxPalette = 5;     // This is the number of registrered palette we got
int argbSwitch = 5;     // This is the command of the relay

#define LED_PIN     3       // This is the signal pin for the leds
#define NUM_LEDS    14       // This is in fact 9(Headset support) + 37(Behind the screen) + 14(Inside the PC case)
#define BRIGHTNESS  64        // Was first at 64 then 16
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1 // I used 42 for the secondPalette() 2520/42=60   see line 73 to see the calculation of the speed and fluidity        in order to keep the 60 ratio we can also have like 60*1000=60000

CRGBPalette16 currentPalette;
TBlendType    currentBlending;


void setup() {
  delay( 200 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(32);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);  
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Serial.begin(115200);
  while (!Serial) {
    // will pause Zero, Leonardo, etc until serial console opens
    delay(1);
  }

  uint32_t currentFrequency;
  pinMode(argbSwitch, OUTPUT);
  int j = 0;
  while (j < 2) {               // Just an init as we love'em
    digitalWrite(argbSwitch, HIGH);
    fill_solid( currentPalette, 16, CRGB::Grey);
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    delay(420);
    j++;
  }
  Serial.println("Hello!");
}



void loop () {

  while (!Serial) {
    digitalWrite(argbSwitch, HIGH);
  }

  static uint8_t startIndex = 0;
  switch (currpal) {
    case 1 :
      FirstPalette();
      startIndex ++; /* motion speed */
      FillLEDsFromPaletteColors( startIndex);
      break;

    case 2 :
      SecondPalette();
      startIndex ++; /* motion speed */
      FillLEDsFromPaletteColors( startIndex);
      break;

    case 3 :
      ThirdPalette();
      break;

    case 4 :
      FourthPalette();
      startIndex ++; /* motion speed */
      FillLEDsFromPaletteColors( startIndex);
      break;

    case 5 :
      FifthPalette();
      break;

    default :
      currpal = 1;
      break;

  }
  FastLED.show();
  FastLED.delay(120 / UPDATES_PER_SECOND);

  //COMMUNICATION
  if ( Serial.available()) {     // Check if any char available on serial, if there's any instructions
    char c = Serial.read();
    if (c == 's') {
      Serial.println(c);
      Serial.println("Switching.");
      currpal = currpal + 1;
      if (currpal > maxPalette){
        currpal = 1;
      }
      Serial.println(currpal);
    }
    if (c == 'n') {
      Serial.println("Switching on");
      digitalWrite(argbSwitch, HIGH);
    }
    if (c == 'f') {
      Serial.println("Switching off");
      digitalWrite(argbSwitch, LOW);
    }
  }
}
