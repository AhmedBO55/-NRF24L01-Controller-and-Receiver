#include <SPI.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(2, 3); // CE, CSN
const byte addr[6] = "00001";

// Array for servos makes it easier to handle
Servo s[6]; 
int pins[] = {4, 5, 6, 7, 8, 9};

struct Payload {
  int j1x, j1y;
  int j2x, j2y;
  float ax, ay;
};

Payload packet;
unsigned long lastSeen = 0;

void setup() {
  Serial.begin(9600);
  
  if (!radio.begin()) {
    Serial.println("RF Fail");
    while(1);
  }
  
  radio.openReadingPipe(0, addr);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  
  // Attach all servos and center them
  for(int i=0; i<6; i++) {
    s[i].attach(pins[i]);
    s[i].write(90);
  }
  
  Serial.println("RX Online...");
}

void loop() {
  if (radio.available()) {
    radio.read(&packet, sizeof(Payload));
    lastSeen = millis();
    
    // Map joy sticks (0-1023)
    int a1 = map(packet.j1x, 0, 1023, 0, 180);
    int a2 = map(packet.j1y, 0, 1023, 0, 180);
    int a3 = map(packet.j2x, 0, 1023, 0, 180);
    int a4 = map(packet.j2y, 0, 1023, 0, 180);
    
    // Map accel (-10 to 10) - doing some quick math here
    int a5 = map(constrain(packet.ax * 10, -100, 100), -100, 100, 0, 180);
    int a6 = map(constrain(packet.ay * 10, -100, 100), -100, 100, 0, 180);
    
    // Update servos
    s[0].write(a1); s[1].write(a2);
    s[2].write(a3); s[3].write(a4);
    s[4].write(a5); s[5].write(a6);
    
    // Quick debug
    Serial.print("Data -> ");
    Serial.print(a1); Serial.print("|"); Serial.println(a2);
  }
  
  // Failsafe if signal drops for > 1sec
  if (millis() - lastSeen > 1000) {
    for(int i=0; i<6; i++) s[i].write(90);
    Serial.println("!!! NO SIGNAL !!!");
    delay(100); 
  }
}