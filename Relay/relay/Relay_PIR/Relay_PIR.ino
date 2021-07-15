byte PIR = 7;
byte relay = 8;
byte val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIR, INPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(PIR);
  Serial.println(val);
  if(val == HIGH){
    digitalWrite(relay, LOW);  
    delay(10000);
  }else{
    digitalWrite(relay, HIGH);
  }
}
