/*-----------------------------------------------------
'     
'     TRIG --> Pin 7
'     ECHO --> Pin 6
'     Baud Rate 9600 bps
'     Ogi sinatra
'     AT-MO PRODUCTION
'-----------------------------------------------------*/


//pin Ultrasonik
#define trigPin 7
#define echoPin 6

#define led1 13
#define buzz 11



void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  pinMode(led1, OUTPUT);
  pinMode(buzz, OUTPUT);
  
 
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(led1, redValue);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

//  Serial.println(distance);

  if (distance >= 30) 
  {
    digitalWrite(led1, LOW);
    digitalWrite(buzz, LOW);
    Serial.print("Jarak : ");
    Serial.print(distance);
    Serial.println(" (Aman)");
  }
//  else {
//    digitalWrite(led1, HIGH);
//    digitalWrite(buzz, HIGH);
//  }
  
  if (distance <= 25 && distance>15 ) 
  {
     Serial.print("Jarak : ");
    Serial.print(distance);
    Serial.println(" (Sedang)");
    digitalWrite(led1, HIGH);
    digitalWrite(buzz, HIGH);
    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(buzz, LOW);
    delay(500);
  }
  
  if (distance <= 15 && distance>3) {
    Serial.print("Jarak : ");
    Serial.print(distance);
    Serial.println(" (Dekat)");
    digitalWrite(led1, HIGH);
    digitalWrite(buzz, HIGH);
    delay(70);
    digitalWrite(led1, LOW);
    digitalWrite(buzz, LOW);
    delay(70);    
  }
  
  if (distance <= 3) {
     Serial.print("Jarak : ");
    Serial.print(distance);
    Serial.println(" (Terlalu Dekat)");
    digitalWrite(led1, HIGH);
    digitalWrite(buzz, HIGH);
  }
 
//  delay(500);
}
