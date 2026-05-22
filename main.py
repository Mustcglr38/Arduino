import serial
import serial.tools.list_ports
import os
import time
import random

# Dosyalarının bulunduğu tam klasör yolu
KLASOR_YOLU = r"C:\Users\admin\OneDrive\Desktop\Muzikli_sensor_projesi\python_kodu"

def portu_bul():
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        # COM1 dışındaki aktif portu (Arduino'yu) bulur
        if "COM" in p.device and p.device != "COM1":
            return p.device
    return None

port = portu_bul()

if port:
    print(f"✅ Arduino bulundu: {port}")
    ser = serial.Serial(port, 9600)
    
    print("\n🚀 SISTEM HAZIR! Sensörün önünden geç, rastgele şarkı çalsın...")
    
    while True:
        try:
            if ser.in_waiting > 0:
                veri = ser.readline().decode('utf-8').strip()
                
                if veri == "TETIK":
                    # 1 ile 5 arasında rastgele bir sayı seçer
                    rastgele_sayi = random.randint(1, 6)
                    dosya_adi = f"music{rastgele_sayi}.mp4"
                    
                    # Klasör yolu ile dosya adını birleştirir
                    tam_dosya_yolu = os.path.join(KLASOR_YOLU, dosya_adi)
                    
                    print(f"🎶 Sensör algıladı! Rastgele seçilen şarkı: {dosya_adi}")
                    
                    # Videoyu/Şarkıyı varsayılan oynatıcıda açar
                    os.startfile(tam_dosya_yolu)
                    
                    # Şarkı açıldıktan sonra ardı ardına tetiklenmesin diye 5 saniye bekler
                    time.sleep(5) 
                    print("Sistem tekrar aktif, yeni tetikleme beklenebilir.\n")
                    
        except KeyboardInterrupt:
            print("\nProgram kullanıcı tarafından kapatıldı.")
            ser.close()
            break
        except Exception as e:
            print(f"❌ Bir hata oluştu: {e}")
            break
else:
    print("❌ HATA: Bilgisayara bağlı aktif bir Arduino bulunamadı!")
    print("Lütfen USB kablosunu ve Arduino IDE'den portu kontrol edin.")