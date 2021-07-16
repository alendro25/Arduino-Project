byte rcwl = 6;
byte led = 13;
byte nilai;

void setup() {
  // put your setup code here, to run once:
  pinMode(rcwl, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  nilai = digitalRead(rcwl);
//  Serial.println(nilai);
  if(nilai == HIGH){
    Serial.println("Ada Gerakan");
    digitalWrite(led, HIGH);  
  }else{
    Serial.println("Tidak ada Gerakan");
    digitalWrite(led, LOW);  
  }
  delay(50);
}
