const int pinSound = A0; 
const int pinSoundDO = 2; 
const int pinDen1 = 3;  // Chân kết nối đèn LED 1
const int pinDen2 = 5;  // Chân kết nối đèn LED 2
const int pinDen3 = 6;  // Chân kết nối đèn LED 3
const int pinDen4 = 9;  // Chân kết nối đèn LED 4
const int pinDen5 = 13; // Chân kết nối đèn LED 5

int denLEDs[] = {pinDen1, pinDen2, pinDen3, pinDen4, pinDen5};
int trangThaiDen[] = {LOW, LOW, LOW, LOW, LOW};
int countclap = 0;

void setup() {
  pinMode(pinSound, INPUT);
  pinMode(pinSoundDO, INPUT);
  pinMode(pinDen1, OUTPUT);
  pinMode(pinDen2, OUTPUT);
  pinMode(pinDen3, OUTPUT);
  pinMode(pinDen4, OUTPUT);
  pinMode(pinDen5, OUTPUT);
  Serial.begin(9600);

}

void batRandomDen() {
  int denNgauNhien = random(5);
  digitalWrite(denLEDs[denNgauNhien], HIGH);
  trangThaiDen[denNgauNhien] = HIGH;
}

void tatTatCaDen() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(denLEDs[i], LOW);
    trangThaiDen[i] = LOW;
  }
}

void loop() {
  int sound = analogRead(pinSound);
  int soundDO = digitalRead(pinSoundDO);
  Serial.println("Giá trị âm thanh: " + String(sound));
  Serial.print("Giá trị âm thanh (DO): " + String(soundDO));

  // Kiểm tra nếu có âm thanh (tiếng vỗ tay)
  if (sound > 100 || soundDO == HIGH) {
    countclap++;

    if (countclap <= 5) {
      batRandomDen();
    } else if (countclap == 6) {
      tatTatCaDen();
    } else if (countclap == 7) {
      // Quay lại trạng thái ban đầu
      for (int i = 0; i < 5; i++) {
        digitalWrite(denLEDs[i], trangThaiDen[i]);
      }
      countclap = 0;
    }

    Serial.println(" - Sound detected");
    delay(1000);  // Đợi 1 giây để tránh việc đọc liên tục trong thời gian ngắn
  } else {
    if (sound > 100 || soundDO == HIGH) {
      Serial.print("Khong phat hien am thanh");
      delay(1000000);
    }
  }

}
