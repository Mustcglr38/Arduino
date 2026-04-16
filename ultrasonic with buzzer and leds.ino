#define TRIG 12
#define ECHO 11
#define BUZ 10
#define LED 9
#define LED2 6

void setup(){
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZ, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long sure = pulseIn(ECHO, HIGH);
  long mesafe = sure * 0.034 / 2 ;

  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm"); 

  if (mesafe > 0 && mesafe <= 50 ){
    digitalWrite(BUZ, HIGH); digitalWrite(LED, HIGH); delay(50);
    digitalWrite(BUZ, LOW); digitalWrite(LED, LOW); delay(50);
  }
  else if (mesafe > 50 && mesafe <= 100 ){
    digitalWrite(BUZ, HIGH); digitalWrite(LED, HIGH); delay(50);
    digitalWrite(BUZ, LOW); digitalWrite(LED, LOW); delay(400);
  }
  else if (mesafe > 100 && mesafe <= 150 ){
    digitalWrite(BUZ, HIGH); digitalWrite(LED, HIGH); delay(50);
    digitalWrite(BUZ, LOW); digitalWrite(LED, LOW); delay(800);
  }
  else {
    digitalWrite(LED2, HIGH);
    delay(1000); 
    digitalWrite(LED2, LOW);
  }
  delay(50);
}