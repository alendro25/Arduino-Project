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

#define led1 9
#define led2 10
#define led3 11



void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
 
}

void setColor(int redValue, int greenValue, int blueValue){
  analogWrite(led1, redValue);
  analogWrite(led2, greenValue);
  analogWrite(led3, blueValue);
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

  Serial.println(distance);

  if (distance >= 123) 
  {
    setColor(0, 0, 255);
  }
  else {
    setColor(0, 0, 0);
  }
  
  if (distance <= 122) 
  {
      setColor(0, 255, 0);
  }
  
  if (distance < 50) {
      setColor(255, 255,0);     
  } 
  
  if (distance < 37) {
    setColor(255, 0,0);
}
 
  delay(500);
}
