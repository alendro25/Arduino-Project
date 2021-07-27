#define waterSensor A1
byte nilai;
byte ketinggian;

void setup() {
  Serial.begin(9600);
}

byte bacaSensor(){
  nilai = analogRead(waterSensor);
  return nilai;
}

void loop() {
  ketinggian = bacaSensor();

  Serial.print("Ketinggian Air : ");
  Serial.println(ketinggian);

  delay(1000);
}
