#include <Adafruit_NeoPixel.h>
#define btn 2
#define PIXEL 6
#define LED 7
int MOD = 0 ;

Adafruit_NeoPixel strip(LED,PIXEL,NEO_GRB+NEO_KHZ800);

void RGB(uint32_t color,int t){
  for(int i=0;i<LED;i++){
    strip.setPixelColor(i,color);
    strip.show();
    delay(t);
    }
}

void rainbow(uint32_t color,int n){
  for(int i=0;i<n;i++){
   
    strip.setPixelColor(i,color);strip.show();
    strip.setPixelColor(i-1,strip.Color(0,0,0));strip.show();
    delay(500);
  }
}

void rainboww(int wait) {
  delay(100);
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    if(digitalRead(btn))break;
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

void breathe(){
int TOTAL_LEDS = 60;
float MaximumBrightness = 255;
float SpeedFactor = 0.008; // I don't actually know what would look good
float StepDelay = 5; // ms for a step delay on the lights

// Make the lights breathe
for (int i = 0; i < 65535; i++) {
   if(digitalRead(btn))break;
// Intensity will go from 10 - MaximumBrightness in a "breathing" manner
float intensity = MaximumBrightness /2.0 * (1.0 + sin(SpeedFactor * i));
strip.setBrightness(intensity);
// Now set every LED to that color
for (int ledNumber=0; ledNumber<TOTAL_LEDS; ledNumber++) {
strip.setPixelColor(ledNumber, 0, 0, 255);
}

strip.show();
//Wait a bit before continuing to breathe
delay(StepDelay);

}
}

void setup(){
  strip.begin();
  strip.show();
  strip.setBrightness(1000);
}
void loop() {
  if(digitalRead(btn))MOD=MOD+1;
  switch(MOD%3){
    case 0:
      rainboww(10);
      break;
    case 1:
      breathe();
      break;
    case 2:
      rainbow(strip.Color(255,0,0),7);
      rainbow(strip.Color(255,127,0),6);
      rainbow(strip.Color(255,255,0),5);
      rainbow(strip.Color(0,255,0),4);
      rainbow(strip.Color(0,127,255),3);
      rainbow(strip.Color(0,0,255),2);
      rainbow(strip.Color(139,0,255),1);
      delay(500);
      rainbow(strip.Color(0,0,0),7);
       MOD=MOD+1;
      delay(500);
      }
}
