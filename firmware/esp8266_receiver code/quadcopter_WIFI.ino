#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

//output Setting...
Servo Sthrottle;
Servo Spitch;
Servo Syaw;
Servo Sroll;
Servo Saux1;
Servo Saux2;
Servo Saux3;

//wifi Setting...
const char* ssid = "A13";
const char* password = "829713111197";

//WiFi Setting...                            
WiFiUDP Udp;
const unsigned int localUdpPort = 1234;
char incomingPacket[255];
unsigned long lastRssiCheck = 0;

//control Setting...
uint16_t pitch = 0;    //y
uint16_t roll = 0;     //left or right X
uint16_t throttle = 0;
uint16_t Slider = 0;

//others...
float lng,lat;
float lngG,latG;
String latStr, lngStr;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(5, -1); 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  gpsSerial.begin(9600);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected. IP address: ");
  Serial.println(WiFi.localIP());

  Udp.begin(localUdpPort);
  Serial.printf("Listening on UDP port %d\n", localUdpPort);

  Sthrottle.attach(2,1000,2000);
  Sroll.attach(4,1000,2000);
  Spitch.attach(0,1000,2000);
  Saux1.attach(14,1000,2000);
  Saux2.attach(13,1000,2000);
  Saux3.attach(15,1000,2000);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0';
    }
  }

  String packetStr = String(incomingPacket);
  packetStr.trim(); 

  char buf[255];
  packetStr.toCharArray(buf, 255);  
  
  int n = sscanf(buf, "R%d,P%d,T%d", &roll, &pitch, &throttle);

  Serial.print("Roll = "); Serial.println(roll);
  Serial.print("Pitch = "); Serial.println(pitch);
  Serial.print("Throttle = "); Serial.println(throttle);

  if(n == 3) {
    throttle = map(throttle,200,0,1000,2000);
    pitch = map(pitch,200,0,1000,2000);
    roll = map(roll,0,200,1000,2000);

    //write the pwm pins...
    Sthrottle.writeMicroseconds(throttle);
    Spitch.writeMicroseconds(pitch);
    Sroll.writeMicroseconds(roll);
  }

  if(packetStr == "ARM"){
    Saux1.write(2000);
  }
  else if(packetStr == "nARM"){
    Saux1.write(1000);
  }
}
