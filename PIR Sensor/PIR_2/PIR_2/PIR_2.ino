byte PIR = 7;
byte led = 13;
byte val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIR, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(PIR);
  Serial.println(val);
  if(val == HIGH){
    for(int i = 1; i <= 35; i++){
    digitalWrite(led, HIGH);
    delay(40);
    digitalWrite(led, LOW);
    delay(40);
    }
  
  }else{
    digitalWrite(led, LOW);
  }
}
