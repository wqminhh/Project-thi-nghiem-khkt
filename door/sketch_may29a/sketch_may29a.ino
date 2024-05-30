#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define trigPinIn 3
#define echoPinIn 2
#define ledPin 6
#define buzzerPin 7                                                
int a = 0;
int count = 0;
bool isInside = false;
bool updateLCD = true;

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(trigPinIn, OUTPUT);
  pinMode(echoPinIn, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("XinChaoQuyKhach");
  lcd.setCursor(1, 1);
  lcd.print("QuaySoatVe KHKT");
  delay(5000);
}

void beep(int duration) {
  digitalWrite(buzzerPin, HIGH);
  delay(duration);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  long durationIn, distanceIn, durationOut;
  
  digitalWrite(trigPinIn, LOW);// Đặt chân trig bên trong xuống mức thấp.
  delayMicroseconds(2);// Delay 2 microseconds.
  digitalWrite(trigPinIn, HIGH);// Đặt chân trig bên trong lên mức cao.
  delayMicroseconds(10);// Delay 10 microseconds.
  digitalWrite(trigPinIn, LOW);// Đặt chân trig bên trong xuống mức thấp.
  durationIn = pulseIn(echoPinIn, HIGH);// Đo thời gian phản hồi từ cảm biến echo bên trong.
  distanceIn = (durationIn / 2) / 29.1;// Tính khoảng cách từ thời gian phản hồi.
  
  if (distanceIn < 30) {
    if (!isInside) {
      isInside = true;
      count++;
      updateLCD = true;
      beep(100);
      delay(400);
    }
  } else if (distanceIn >= 30 && distanceIn < 40) {
    if (!isInside) {
      isInside = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Dung Qua Xa  !!");
      lcd.setCursor(2, 1);
      lcd.print("Dung Gan Hon");
      beep(500);
      delay(2000);
    }
  } else {
    isInside = false; 
  }
  
  if (count <= 0) {
    if (updateLCD) { 
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Moi Quy Khach");
      lcd.setCursor(1, 1);
      lcd.print(" Xuat Trinh Ve ");
      updateLCD = false;
    }
    delay(200);
  } else {
    if (updateLCD) { 
      a = count * 30;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tong so tien ve:");   
      lcd.setCursor(0, 1);
      lcd.print(a);      
      lcd.setCursor(8, 1);
      lcd.print("k;");
      lcd.setCursor(10, 1);
      lcd.print(count);
      lcd.setCursor(14, 1);
      lcd.print("ng");
      updateLCD = false;
    }
    delay(200);
  }
}