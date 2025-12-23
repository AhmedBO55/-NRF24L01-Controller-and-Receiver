#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_ADXL345_U.h>

// Screen stuff
#define SCR_W 128 
#define SCR_H 64
Adafruit_SSD1306 oled(SCR_W, SCR_H, &Wire, -1);

// Sensors and Radio
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
RF24 radio(6, 5); 
const byte addr[6] = "00001";

// Pin mapping
#define J1X A0
#define J1Y A1
#define J2X A2
#define J2Y A3

struct Payload {
  int j1x, j1y;
  int j2x, j2y;
  float ax, ay;
};

Payload packet;

void setup() {
  Serial.begin(9600);
  
  // init display
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // halt
  }
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Booting...");
  oled.display();

  // init sensor
  if(!accel.begin()) {
    oled.println("No ACCEL found");
    oled.display();
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);

  // radio setup
  if (!radio.begin()) {
    oled.println("Radio Error");
    oled.display();
    while(1);
  }
  
  radio.openWritingPipe(addr);
  radio.setPALevel(RF24_PA_LOW); // keep low for desk testing
  radio.stopListening();
  
  // inputs
  pinMode(J1X, INPUT);
  pinMode(J1Y, INPUT);
  pinMode(J2X, INPUT);
  pinMode(J2Y, INPUT);

  delay(500);
  oled.clearDisplay();
}

void loop() {
  sensors_event_t evt;
  accel.getEvent(&evt);

  // Grab data
  packet.j1x = analogRead(J1X);
  packet.j1y = analogRead(J1Y);
  packet.j2x = analogRead(J2X);
  packet.j2y = analogRead(J2Y);
  packet.ax = evt.acceleration.x;
  packet.ay = evt.acceleration.y;

  // Send it
  bool ok = radio.write(&packet, sizeof(Payload));

  // Update screen
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(1);
  
  oled.print("TX STATUS: ");
  oled.println(ok ? "OK" : "FAIL");
  oled.println("-----------");
  
  oled.print("J1: "); oled.print(packet.j1x); oled.print("/"); oled.println(packet.j1y);
  oled.print("J2: "); oled.print(packet.j2x); oled.print("/"); oled.println(packet.j2y);
  oled.print("A: "); oled.print(packet.ax, 1); oled.print(","); oled.println(packet.ay, 1);
  
  oled.display();
  delay(30); // smooth out the loop a bit
}