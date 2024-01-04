#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6W1h4pQ2q"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "3ldRd1K64haCfdSHfnGUNKaeSi6ChPPV"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

char auth[] = "3ldRd1K64haCfdSHfnGUNKaeSi6ChPPV";
char ssid[] = "UiTiOt-E3.1";
char pass[] = "UiTiOtAP";


BlynkTimer timer;
const int motionSensorPin = D3; // Chân D3 cho cảm biến chuyển động
const int ledPin = D4; // Chân D4 cho đèn LED
int motionState = LOW;
int sec = 0;
unsigned long motionStartTime = 0;
const unsigned long motionTimeout = 1 * 60 * 1000; // 7 phút

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(motionSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  //timer.setInterval(1000, checkMotionState);
}

void loop() {
  Blynk.run();
  checkMotionState();
  delay(1000);
}

/*BLYNK_WRITE(V1)
{
  //sec = param.asInt();
  Serial.print("Blynk.Cloud");

}*/
/*BLYNK_WRITE(V1) {
    sec = param.asInt();
}*/

void checkMotionState() {
  int newMotionState = digitalRead(motionSensorPin);
  
    if (newMotionState == 1) {
      // Phát hiện chuyển động, bật đèn
      digitalWrite(ledPin, HIGH);
      Serial.print("on");
      //Blynk.virtualWrite(V1, "Motion Detected!");
      //motionStartTime = millis(); // Ghi lại thời điểm bắt đầu phát hiện chuyển động
    } else {
      // Không có chuyển động, tắt đèn
      digitalWrite(ledPin, LOW);
      Serial.print("off");
      //Blynk.virtualWrite(V1, "No Motion");
    }
    // Không có thay đổi trong trạng thái chuyển động, kiểm tra timeout
 /*   if (newMotionState == 1 && sec == 1) {
      Blynk.logEvent("notifications", "Phát hiện có xâm nhập");
    }
  */
}
