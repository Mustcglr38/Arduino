#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// I2C tarayıcıda bulduğun adresi buraya yaz (Genelde 0x27 veya 0x3F olur)
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define TRIG 12
#define ECHO 11
#define BUZ 10
#define LED 9   // Kırmızı Uyarı LED'i
#define LED2 6  // Sabit Yanan Mavi LED

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);

  lcd.init();
  lcd.backlight();
  
  // Açılış Mesajı
  lcd.setCursor(0, 0);
  lcd.print("SISTEM AKTIF");
  lcd.setCursor(0, 1);
  lcd.print("YOL KONTROL...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // 1. Mesafe Ölçümü (Stabilizasyonlu)
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long sure = pulseIn(ECHO, HIGH, 30000); 
  long mesafe = sure * 0.034 / 2;

  // 2. Filtreleme: Eğer sensör hatalı (0) okursa loop'u burada kes
  if (mesafe <= 0 || mesafe > 400) return;

  // 3. LCD Üst Satır: Mesafe Bilgisi
  lcd.setCursor(0, 0);
  lcd.print("MESAFE: ");
  lcd.print(mesafe);
  lcd.print(" cm   "); // Eski rakamları temizlemek için boşluklar

  // 4. Karar Mekanizması
  if (mesafe <= 150) {
    // ENGEL VAR
    digitalWrite(LED2, LOW); // Mavi söner
    lcd.setCursor(0, 1);
    lcd.print("DUR! ENGEL VAR ");

    if (mesafe <= 50) {
      ikaz(50);  // Çok hızlı
    } else if (mesafe <= 100) {
      ikaz(300); // Orta
    } else {
      ikaz(600); // Yavaş
    }
  } 
  else {
    // YOL ACIK
    digitalWrite(LED2, HIGH); // MAVİ LED SABİT YANAR
    digitalWrite(BUZ, LOW);
    digitalWrite(LED, LOW);
    
    lcd.setCursor(0, 1);
    lcd.print("YOL TEMIZ...   ");
  }
}

// Bip sesi ve Kırmızı LED için yardımcı fonksiyon
void ikaz(int bekleme) {
  digitalWrite(BUZ, HIGH);
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(BUZ, LOW);
  digitalWrite(LED, LOW);
  delay(bekleme);
}