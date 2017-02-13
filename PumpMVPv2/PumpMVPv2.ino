#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


#define MAXCS1   8
#define MAXCS2   4
#define MAXCS3   5
#define MAXCS4   6

#define Pump1 26
#define Pump2 24
#define Pump3 28
#define Pump4 22

#define Heater1 33
#define Heater2 25
#define Heater3 27
#define Heater4 29
#define Heater5 31
#define Heater6 33
#define Heater7 35
#define Heater8 37
#define Heater9 39
#define Heater10 41
int setTemp = 30;
int setTemp1 = 30;
int pump1FillTime = 5000;
int pump2FillTime = 5000;
int pump3Filltime = 5000;



// initialize the Thermocouple
Adafruit_MAX31855 thermocouple1(MAXCS1);
Adafruit_MAX31855 thermocouple2(MAXCS2);
Adafruit_MAX31855 thermocouple3(MAXCS3);
Adafruit_MAX31855 thermocouple4(MAXCS3);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

void setup() {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  pinMode(Pump1, OUTPUT);
  pinMode(Pump2, OUTPUT);
  pinMode(Pump3, OUTPUT);
  pinMode(Pump4, OUTPUT);
  pinMode(Heater1, OUTPUT);
  pinMode(Heater2, OUTPUT);
  pinMode(Heater3, OUTPUT);
  pinMode(Heater4, OUTPUT);
  pinMode(Heater5, OUTPUT);
  pinMode(Heater6, OUTPUT);
  pinMode(Heater7, OUTPUT);
  pinMode(Heater8, OUTPUT);
  pinMode(Heater9, OUTPUT);
  pinMode(Heater10, OUTPUT);

  digitalWrite(Pump1, HIGH);
  digitalWrite(Pump2, HIGH);
  digitalWrite(Pump3, HIGH);
  digitalWrite(Pump4, HIGH);
  digitalWrite(Heater1, HIGH);
  digitalWrite(Heater2, HIGH);
  digitalWrite(Heater3, HIGH);
  digitalWrite(Heater4, HIGH);
  digitalWrite(Heater5, HIGH);
  digitalWrite(Heater6, HIGH);
  digitalWrite(Heater7, HIGH);
  digitalWrite(Heater8, HIGH);
  digitalWrite(Heater9, HIGH);
  digitalWrite(Heater10, HIGH);

  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();


  Serial.begin(9600);
  //Serial.println("MAX31855 test");
  // wait for MAX chip to stabilize
  delay(500);
}
//110 to drain
//36sec to fill 50ml
//chamber1(); -1-3
//drain();
//MonitorTempOverTime



void loop() {
  //flushy(10);
  testrun1();
  delay(1000000);
}

void testrun1() {
  drain(100);
  chamber1(40);
  MonitorTempOverTime(55,96);
  drain(100);
  chamber2(30);
  drain(100);
  chamber2(30);
  drain(100);
  chamber2(30);
  MonitorTempOverTime(10, 24);
  drain(100);
  chamber3(30);
  MonitorTempOverTime(55, 96);
  finished();
}


void MonitorTempOverTime(double temp, unsigned long hour) {
  int j;
  unsigned long long milisec = hour*60*60*1000;
  unsigned long long sec = (hour*60*60);
  unsigned long minuet = sec/60;
  unsigned long long milisecdiv = milisec / sec;
  for (j = 0; j < sec; j++) {
    int i;
    for (i = 0; i < milisecdiv; i++) {
      monitorTempOne(temp);
    }
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Heating to ");
    display.print(temp);
    display.println("C for ");
    display.print(minuet);
    display.print(" minuets");
    display.print('\n');
    display.display();
    display.clearDisplay();

    double c1 = thermocouple1.readCelsius();

    display.println("Current TC temp: ");
    display.println(c1);
    display.print(minuet - j/60);
    display.print(" minuets left");

  }
  display.clearDisplay();
}

double H = 3;

void monitorTempOne(double setTemp) {
  // H = hysteresis
  double currentTemp = thermocouple1.readCelsius();
  if  (setTemp+H <= currentTemp){
    // set temp + high bang is greater than actaul, turn off
      digitalWrite(Heater1, HIGH);
      //off
  }
   else if (setTemp-H >= currentTemp){
    //low point - low bang is lower than actaul, turn on
        digitalWrite(Heater1, LOW);
        //on
        }
}

void finished() {
  digitalWrite(Heater1, HIGH); // kill the heater once we are waiting
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Finished");
  display.display();
  display.clearDisplay();
  delay(60 * 60 * 60 * 60);
}

void drain(unsigned long sec) {
  digitalWrite(Heater1, HIGH); // kill the heater once we drain
  digitalWrite(Pump4, LOW);
  unsigned long milisec = sec * 1000;
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Draining for ");
  display.print(sec);
  display.print(" seconds");
  display.display();
  display.clearDisplay();
  /*
    Serial.print('\n');
    Serial.print("Draining for ");
    Serial.print(sec);
    Serial.print(" seconds");
  */
  delay(milisec);
  digitalWrite(Pump4, HIGH);
}

void flushy(unsigned long sec) {
  digitalWrite(Heater1, HIGH); // kill the heater once we drain
  digitalWrite(Pump1, LOW);
  digitalWrite(Pump2, LOW);
  digitalWrite(Pump3, LOW);
  unsigned long milisec = sec * 1000;
  Serial.print('\n');
  Serial.print("Flushing for ");
  Serial.print(sec);
  Serial.print(" seconds (times four with drain)");
  delay(milisec);
  digitalWrite(Pump1, HIGH);
  digitalWrite(Pump2, HIGH);
  digitalWrite(Pump3, HIGH);
  digitalWrite(Pump4, LOW);
  delay(milisec * 4);
  digitalWrite(Pump4, HIGH);
}


void chamber2(unsigned long sec) {
  unsigned long milisec = sec * 1000;
  /*
    Serial.print('\n');
    Serial.print("Filling from chamber 1 for ");
    Serial.print(sec);
    Serial.print(" seconds");
  */
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Filling from");
  display.print("chamber 2 for ");
  display.print(sec);
  display.print(" seconds");
  display.display();
  display.clearDisplay();

  digitalWrite(Pump2, LOW);
  delay(milisec);
  digitalWrite(Pump2, HIGH);
}

void chamber1(unsigned long sec) {
  unsigned long milisec = sec * 1000;
  /*
    Serial.print('\n');
    Serial.print("Filling from chamber 1 for ");
    Serial.print(sec);
    Serial.print(" seconds");
  */

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Filling from");
  display.print("chamber 1 for ");
  display.print(sec);
  display.print(" seconds");
  display.display();
  display.clearDisplay();
  digitalWrite(Pump1, LOW);
  delay(milisec);
  digitalWrite(Pump1, HIGH);
}

void chamber3(unsigned long sec) {
  unsigned long milisec = sec * 1000;
  /*
    Serial.print('\n');
    Serial.print("Filling from chamber 3 for ");
    Serial.print(sec);
    Serial.print(" seconds");
  */


  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Filling from");
  display.print("chamber 3 for ");
  display.print(sec);
  display.print(" seconds");
  display.display();
  display.clearDisplay();

  digitalWrite(Pump3, LOW);
  delay(milisec);
  digitalWrite(Pump3, HIGH);
}



void temp1() {
  double c1 = thermocouple1.readCelsius();
  Serial.print("TC1: ");
  Serial.println(c1);
}
void prog1() {
  //monitorTemp();
  double c1 = thermocouple1.readCelsius();
  Serial.print("C1 = ");
  Serial.println(c1);
  delay(10);
  double c2 = thermocouple2.readCelsius();
  Serial.print("C2 = ");
  Serial.println(c2);
  delay(10);
  double c3 = thermocouple3.readCelsius();
  Serial.print("C3 = ");
  Serial.println(c3);
  delay(10);
  double c4 = thermocouple4.readCelsius();
  Serial.print("C4 = ");
  Serial.println(c4);
  delay(10);
}

void fillAndDrain() {
  digitalWrite(Pump1, LOW);
  delay(50000);
  digitalWrite(Pump1, HIGH);
  delay(5000);
  digitalWrite(Pump4, LOW);
  delay(70000);
  digitalWrite(Pump4, HIGH);
  delay(5000);
  digitalWrite(Pump2, LOW);
  delay(50000);
  digitalWrite(Pump2, HIGH);
  delay(5000);
  digitalWrite(Pump4, LOW);
  delay(70000);
  digitalWrite(Pump4, HIGH);
  delay(5000);
  digitalWrite(Pump3, LOW);
  delay(50000);
  digitalWrite(Pump3, HIGH);
  delay(5000);
  digitalWrite(Pump4, LOW);
  delay(70000);
  digitalWrite(Pump4, HIGH);
  delay(5000);

}


void monitorTemp() {
  double c1 = thermocouple1.readCelsius();
  double c2 = thermocouple2.readCelsius();
  double c3 = thermocouple3.readCelsius();
  double c4 = thermocouple4.readCelsius();
  double tempAverages = ((c1 + c2 + c3 + c4) / 4);
  if (setTemp > tempAverages) {
    digitalWrite(Heater1, LOW);
    digitalWrite(Heater2, LOW);
    digitalWrite(Heater3, LOW);
    digitalWrite(Heater4, LOW);
    digitalWrite(Heater5, LOW);
    digitalWrite(Heater6, LOW);
    digitalWrite(Heater7, LOW);
    digitalWrite(Heater8, LOW);
    digitalWrite(Heater9, LOW);
    digitalWrite(Heater10, LOW);
  }
  else if (setTemp <= tempAverages) {
    digitalWrite(Heater1, HIGH);
    digitalWrite(Heater2, HIGH);
    digitalWrite(Heater3, HIGH);
    digitalWrite(Heater4, HIGH);
    digitalWrite(Heater5, HIGH);
    digitalWrite(Heater6, HIGH);
    digitalWrite(Heater7, HIGH);
    digitalWrite(Heater8, HIGH);
    digitalWrite(Heater9, HIGH);
    digitalWrite(Heater10, HIGH);

  }

}
