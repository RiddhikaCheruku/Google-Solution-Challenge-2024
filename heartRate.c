#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Khush_EXT";
const char* password = "9023669791";
int pulsePin = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int ledPin = LED_BUILTIN;   //  The on-board Arduion LED

int bpm;
int pulseValue;
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;  

const int GSR=A9;
int sensorValue=0;
int gsr_average=0;          // Determine which Signal to "count as a beat", and which to ingore.



String datalink = "https://script.google.com/macros/s/AKfycbywWDXpf9HTAWKyj_sEEPrrFkVjOx_WxuxXpoaBI_Mdj9g0GDjmzxHCDdgRRdSI5vqmqQ/exec?";
String datalink2;

unsigned long lastTime = 0;

unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(9600); 
 pinMode(ledPin,OUTPUT); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
  pulseValue = analogRead(pulsePin);

  // Detect the pulse
  if (pulseValue > 600) {
    digitalWrite(ledPin, LOW); // turn on the LED
    delay(100); // wait for a short time
    digitalWrite(ledPin, HIGH); // turn off the LED
    bpm = 150000 / pulseValue; // calculate the heart rate in beats per minute
    Serial.print("Heart rate: ");
    Serial.print(bpm);
    Serial.println(" BPM");

  }
   long sum=0;
  for(int i=0;i<20;i++)           //Average the 10 measurements to remove the glitch
      {
      sensorValue=analogRead(GSR);
      sum += sensorValue;
      delay(50);
      }
   gsr_average = sum/20;
   Serial.println(gsr_average);
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
              datalink2 = datalink + "&" + "BPM=" + bpm +"&" + "StressLevel=" + gsr_average;
  
              String serverPath = datalink2;

          http.begin(serverPath.c_str());

         
          int httpResponseCode = http.GET();
          http.end();
}
}