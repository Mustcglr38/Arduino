#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// LCD ve DHT Ayarları
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adres gelmezse 0x3F dene
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Hava Istasyonu");
  lcd.setCursor(0, 1);
  lcd.print("Baslatiliyor...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Verileri oku
  float nem = dht.readHumidity();
  float sicaklik = dht.readTemperature();

  // Okuma hatası kontrolü
  if (isnan(nem) || isnan(sicaklik)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Hatasi! ");
    return;
  }

  // Ekrana Yazdır
  lcd.setCursor(0, 0);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik, 1); // Virgülden sonra 1 basamak
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Nem: %");
  lcd.print((int)nem); // Tam sayı olarak nem
  lcd.print("         "); // Satırı temizlemek için boşluk

  delay(2000); // Sensörü yormamak için 2 saniyede bir güncelle
}