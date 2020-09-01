#include <FastLED.h>

#define second 1000
#define NUM_LEDS 300
#define DATA_PIN 7
#define BRIGHTNESS 80

static long long currentMillis2 = 0;
CRGB leds[NUM_LEDS];

long mode;
int sensorPin = 5;
bool val = 0;

int hue = 0;
double max = 0; //548;
double min = 1000; //536;
int _i = 0;
double it = 1;

const long long keitmosi_laikas = 70000;

void setup() {

  pinMode(sensorPin, INPUT);
  Serial.begin(2000000);
  //Serial.begin(9600);
  LEDS.addLeds < WS2812B, DATA_PIN, GRB > (leds, NUM_LEDS);
  FastLED.setMaxPowerInMilliWatts(1700);
  //LEDS.setBrightness(BRIGHTNESS);
  FastLED.clear();
  /* for (int i = 0; i <= NUM_LEDS; i++)
    {
     leds[i] = CRGB (255, 0, 0);
    }
    delay(2000);
    FastLED.clear();
  */for (int i = 0; i <= NUM_LEDS; i++)
  {
    leds[i] = CRGB (0, 0, 255);


  }
  // delay(2000);
  randomSeed(analogRead(A0));
  mode = random(4);
  FastLED.show();
}

bool _read() {

  val = digitalRead(sensorPin);
  Serial.println(val);

}
void fadeout() {

  for (int i = BRIGHTNESS; i >= 0; i -= 3) {
    LEDS.setBrightness(i);
    FastLED.show();
  }
  FastLED.clear();
  LEDS.setBrightness(BRIGHTNESS);
}

void anim1() {
  while (true) {
    if (millis() - currentMillis2 >= keitmosi_laikas) {
      break;
    }
    _read();
    if (val) {
      hue += 2;
      int a = 0;
      while (a <= 3) {
        leds[_i] = CHSV(hue, 255, 255);
        _i += it;
        a++;
      }

      if (_i >= (NUM_LEDS - 1)) {
        it = -1;
        fadeout();
      }
      if (_i <= 1) {
        it = 1;
        fadeout();
      }
      FastLED.show();
    }

  }
}
int _tnum = 50;
int tempnum = 0;
int __i = NUM_LEDS - 1;
int __it = -1;
bool turn_on = true;
bool change = true;
void melynaraudona () {
  if (turn_on)
  {
    leds[_i] = CRGB(255, 0, 0);
    leds[__i] = CRGB(255, 0, 0);
    __i += __it;
    _i += it;
    change = true;

  } else {

    if (it == -1) {
      leds[_i - tempnum] = CRGB(0, 0, 255);
      leds[__i + tempnum] = CRGB(0, 0, 255);
    }
    else {
      leds[_i + tempnum] = CRGB(0, 0, 255);
      leds[__i - tempnum] = CRGB(0, 0, 255);
    }

    tempnum--;
    //delay(100);
    if (tempnum == 0)
    {
      turn_on = true;
      
    }
  }




  if (_i >= _tnum && it == 1)
    leds[_i - _tnum] = CRGB(0, 0, 255);
  else if (_i <= 299 - _tnum && it == -1)
  {
    leds[_i + _tnum] = CRGB(0, 0, 255);

  }
  if (_i == NUM_LEDS && turn_on && change) {
    it = -1;
    turn_on = false;
    tempnum = _tnum;
    change = false;

  }
  if (_i == 0 && turn_on && change) {
    it = 1;
    turn_on = false;
    tempnum = _tnum;
    change = false;
  }
  //---------------------------------//

  if (__i >= _tnum && __it == 1)
    leds[__i - _tnum] = CRGB(0, 0, 255);
  else if (__i <= 299 - _tnum && __it == -1)
    leds[__i + _tnum] = CRGB(0, 0, 255);
  if (__i == NUM_LEDS && turn_on && change) {
    __it = -1;
  }
  if (__i == 0 && turn_on && change) {
    __it = 1;
  }

  FastLED.show();
}


void melynaraudonatemp () {
  for (int i = 0; i <= NUM_LEDS / 2 - 1; i++) {
    leds[i] = CRGB(0, 0, 0);
    leds[NUM_LEDS - 1 - i] = CRGB(0, 0, 255);
  }
  FastLED.show();
  delay(150);
  for (int i = 0; i <= NUM_LEDS / 2 - 1; i++) {
    leds[i] = CRGB(255, 0, 0);
    leds[NUM_LEDS - 1 - i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(150);
}
void anim2()
{
  while (true) {
    if (millis() - currentMillis2 >= keitmosi_laikas) {
      _i = 0;
      break;
    }
    _read();
    hue++;
    if (val)
    {
      leds[0] = CHSV(hue, 255, 255);
    } else
    {
      leds[0] = CRGB (0, 0, 0);
    }

    for (int i = NUM_LEDS - 1; i >= 1  ; i--) {
      leds[i] = leds[i - 1];
    }
    FastLED.show();
  }

  // leds[0]=CRGB (0, 255, 0);
  // FastLED.show();
  // delay(30);
}
void anim3() {
  static long mili = 0;
  int _bright = 255;
  while (true) {
    if (millis() - currentMillis2 >= keitmosi_laikas) {
      break;
    }
    _read();
    hue += 1;
    if (val) {
      mili = millis();
      _bright = 255;
      fill_solid( leds, NUM_LEDS /*number of leds*/, CHSV(hue, 255, 255));
      FastLED.show();

      // delay(25);
    } else if (millis() - mili >= 800 && _bright >= 5)
    {
      _bright -= 5;
    }
    LEDS.setBrightness(_bright);
    FastLED.show();

  }
}
void anim4()
{
  while (true) {
    if (millis() - currentMillis2 >= keitmosi_laikas) {
      _i = 0;
      break;
    }
    _read();
    hue++;
    if (val)
    {
      leds[NUM_LEDS] = CHSV(hue, 255, 255);
    } else
    {
      leds[0] = CRGB (0, 0, 0);
      leds[NUM_LEDS] = CRGB (0, 0, 0);
    }

    for (int i = 0 ; i <= NUM_LEDS  ; i++) {
      leds[i] = leds[i + 1];
    }
    FastLED.show();
  }

  // leds[0]=CRGB (0, 255, 0);
  // FastLED.show();
  // delay(30);
}
void anim5()
{
  while (true) {
    if (millis() - currentMillis2 >= keitmosi_laikas) {
      _i = 0;
      break;
    }

    _read();
    hue++;
    if (val)
    {

      leds[150] = CHSV(hue, 255, 255);

    } else
    {
      leds[150] = CRGB (0, 0, 0);
    }

    for (int i = NUM_LEDS - 1; i >= 150  ; i--) {
      leds[i] = leds[i - 1];
      leds[NUM_LEDS - i] = leds[NUM_LEDS - i + 1];
    }
    //for (int i = 0 ; i <= 150  ; i++) {
    //leds[i] = leds[i + 1];
    //}
    FastLED.show();
  }

  // leds[0]=CRGB (0, 255, 0);
  // FastLED.show();
  // delay(30);
}



double a = 0;
void loop() {


  //val = _read;
  // _read();
  /*while (true) {
    a+=it;LEDS.setBrightness(a);
    if(a== 0 || a==255)
    {it=-it;delay(15000);}

     FastLED.show();delay(50);
    }*/
   // fill_solid( leds, NUM_LEDS /*number of leds*/, CRGB (0, 0, 255));
     // FastLED.show();
  melynaraudona();


  /*if (millis() - currentMillis2 >= keitmosi_laikas) {

    currentMillis2 = millis();
    mode++;
    fadeout();
    if (mode >= 5)
    {
      mode = 0;
    }
    }
    if (hue >= 1000)
    {
    hue = 0;
    }
    if (mode == 0)
    {
    anim1(); //filing strips on beat
    }
    if (mode == 1)
    {
    anim2();//moving pixel through strip start to end
    }
    if (mode == 2)
    {
    anim3(); //fill_solid
    }
    if (mode == 3)
    {
    anim4(); //moving pixel through strip end to start
    }
    if (mode == 4)
    {
    anim5(); //moving pixel through strip starting from middle to both ends.
    }



    //if max
    if(val>max+i/25. || val<min-i/25.)
    {
    anim1();
    }//else  {fadeout();}
  */

  //MIN 536.00, MAX 548.00

}
