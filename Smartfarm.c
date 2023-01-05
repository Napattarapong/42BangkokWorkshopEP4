#include <WiFi.h>
#include <TridentTD_LineNotify.h>

int SMsensorPin = 35; 
int SMsensorValue;
int WLsensorPin = 34; 
int WLsensorValue;
int LED1 = 14; 
int LED2 = 26; 
int LED3 = 33; 
int MO = 15; 

#define SSID        "guest"
#define PASSWORD    "Guest42guest"
#define LINE_TOKEN  "cPSO8fcgdOfbzL7yCli3jo2WOUa9yIFsp9PJNzCJnF7" 

void setup() {
 Serial.begin(9600);
 pinMode(SMsensorPin, INPUT);
 pinMode(WLsensorPin, INPUT);
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 pinMode(MO, OUTPUT);

  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting ",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  
  LINE.setToken(LINE_TOKEN);
  // ส่งข้อความ
  LINE.notify("เริ่มการใช้งานระบบ");
  LINE.notify("Detector");
}

void loop() {

 SMsensorValue = analogRead(SMsensorPin);
 Serial.print("SM Analog Value : ");
 Serial.println(SMsensorValue);
 
 WLsensorValue = analogRead(WLsensorPin);
 Serial.print("WL Analog Value : ");
 Serial.println(WLsensorValue);

 if (WLsensorValue > 3000) {
   digitalWrite(LED2, HIGH );
   digitalWrite(MO, LOW );
   digitalWrite(LED3, LOW );
   LINE.notify("น้ำหมด");
 }
 else {
   digitalWrite(LED2, LOW );
   if(SMsensorValue > 3000) {
     digitalWrite(MO, HIGH );
     digitalWrite(LED3, HIGH );
     LINE.notify("ปั๊มทำงาน");
    }  else {
   digitalWrite(MO, LOW );
   digitalWrite(LED3, LOW );
   } 
 }
 delay(1000);
}