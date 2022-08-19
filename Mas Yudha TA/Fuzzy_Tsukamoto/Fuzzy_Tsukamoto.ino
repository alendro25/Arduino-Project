// Variabel Stepper
float a,b,c; /* a = Dekat, b = Sedang, c = Jauh */
// Variabel Beban
float d,e,f; /* d = Ringan, e = Sedang, f = Berat */

// Variabel alpha dan z
float a1,a2,a3,a4,a5,a6,a7,a8,a9;
float z,z1,z2,z3,z4,z5,z6,z7,z8,z9;

// Variabel Total
float Total_AiZi;
float Total_a;
float Kecepatan;

// Variabel Status
String Vkecepatan;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Vkecepatan = " ";
}

void loop() {
  /* Definisi Nilai Untuk Stepper dan Beban */
  // Untuk nilai stepper (0-2200)
  a = 900;
  b = 900;
  c = 900;
  // Untuk nilai Beban (0-236)
  d = 100;
  e = 100;
  f = 100;
  
  /*  FUZZIFIKASI */
  Serial.println("~~~~ FUZZIFIKASI ~~~~");

  Serial.println("-- Stepper --");
  //  Fuzzifikasi Stepper (Langkah)
  if(a <= 1400){ // μDekat 
    a = 1;
    Serial.print("Nilai μDekat : ");
    Serial.println(a);
  }else if (a >= 1800){
    a = 0;
    Serial.print("Nilai μDekat : ");
    Serial.println(a);
  }else if (a > 1400 && a < 1800){
    a = (1800 - a) / (1800 - 1400);
    Serial.print("Nilai μDekat : ");
    Serial.println(a);
  }
  if(b <= 1400 or b >= 2200 ){ // μSedang
    b = 0;
    Serial.print("Nilai μSedang : ");
    Serial.println(b);
  }else if(b == 1800){ // μSedang
    b = 1;
    Serial.print("Nilai μSedang : ");
    Serial.println(b);
  }else if (b > 1400 && b < 1800){
    b = (b - 1400) / (1800 - 1400);
    Serial.print("Nilai μSedang : ");
    Serial.println(b);
  }else if (b > 1800 && b < 2200){
    b = (2200 - b) / (2200 - 1800);
    Serial.print("Nilai μSedang : ");
    Serial.println(b);
  }
  if(c <= 1800 ){ // μJauh
    c = 0;
    Serial.print("Nilai μJauh : ");
    Serial.println(c);
  }else if (c >= 2200){
    c = 1;
    Serial.print("Nilai μJauh : ");
    Serial.println(c);
  }else if (c > 1800 && c < 2200){
     c = (c - 1800) / (2200 - 1800);
    Serial.print("Nilai μJauh : ");
    Serial.println(c);
  }

  Serial.println("-- Beban (gr) --");
  //  Fuzzifikasi Beban (gram)
  if(d <= 86){ // μRingan 
    d = 1;
    Serial.print("Nilai μRingan : ");
    Serial.println(d);
  }else if (d >= 161){
    d = 0;
    Serial.print("Nilai μRingan : ");
    Serial.println(d);
  }else if (d > 86 && d < 161){
    d = (161 - d) / (161 - 86);
    Serial.print("Nilai μRingan : ");
    Serial.println(d);
  }
  if(e < 86 or e > 236 ){ // μSedang
    e = 0;
    Serial.print("Nilai μSedang : ");
    Serial.println(e);
  }else if(e == 161){ // μSedang
    e = 1;
    Serial.print("Nilai μSedang : ");
    Serial.println(e);
  }else if (e >= 86 && e <= 161){
    e = (e - 86) / (161 - 86);
    Serial.print("Nilai μSedang : ");
    Serial.println(e);
  }else if (e >= 161 && e <= 236){
    e = (236 - e) / (236 - 161);
    Serial.print("Nilai μSedang : ");
    Serial.println(e);
  }
  if(f <= 161 ){ // μBerat
    f = 0;
    Serial.print("Nilai μBerat : ");
    Serial.println(f);
  }else if (f >= 236){
    f = 1;
    Serial.print("Nilai μBerat : ");
    Serial.println(f);
  }else if (f > 161 && f < 236){
     f = (f - 161) / (236 - 161);
    Serial.print("Nilai μBerat : ");
    Serial.println(f);
  }
  Serial.println();

  /* INFERENSI - RULES */
  Serial.println("~~~~ INFERENSI ~~~~");
  
  //  R1 - DEKAT, RINGAN, LAMABT
  a1 = min(a, c); // Rules 1
  Serial.print("Alpha predikat1 : ");
  Serial.println(a1);
  z1 = 900 - a1 * (900 - 300);
  Serial.print("Nilai z1 : ");
  Serial.println(z1);

   //  R2 - DEKAT, SEDANG, SEDANG
  a2 = min(a, e); // Rules 2
  Serial.print("Alpha predikat2 : ");
  Serial.println(a2);
  z2 = a2 * (900 - 300) + 300;
  Serial.print("Nilai z2 : ");
  Serial.println(z2);

   //  R3 - DEKAT, BERAT, LAMBAT
  a3 = min(a, f); // Rules 3
  Serial.print("Alpha predikat3 : ");
  Serial.println(a3);
  z3 = 900 - a3 * (900 - 300);
  Serial.print("Nilai z3 : ");
  Serial.println(z3);

  //  R4 - SEDANG, RINGAN, CEPAT
  a4 = min(b, d); // Rules 4
  Serial.print("Alpha predikat4 : ");
  Serial.println(a4);
  z4 = a4 * (1500 - 900) + 1500;
  Serial.print("Nilai z4 : ");
  Serial.println(z4);

  //  R5 - SEDANG, SEDANG, CEPAT
  a5 = min(b, e); // Rules 5
  Serial.print("Alpha predikat5 : ");
  Serial.println(a5);
  z5 = a5 * (1500 - 900) + 1500;
  Serial.print("Nilai z5 : ");
  Serial.println(z5);

  //  R6 - SEDANG, BERAT, SEDANG
  a6 = min(b, f); // Rules 6
  Serial.print("Alpha predikat6 : ");
  Serial.println(a6);
  z6 = a6 * (900 - 300) + 300;
  Serial.print("Nilai z6 : ");
  Serial.println(z6);

  //  R7 - JAUH, RINGAN, SEDANG
  a7 = min(c, d); // Rules 7
  Serial.print("Alpha predikat7 : ");
  Serial.println(a7);
  z7 = 300 - a7 * (900 - 300);
  Serial.print("Nilai z7 : ");
  Serial.println(z7);

  //  R8 - JAUH, SEDANG, LAMBAT
  a8 = min(c, e); // Rules 8
  Serial.print("Alpha predikat8 : ");
  Serial.println(a8);
  z8 = 900 - a8 * (900 - 300);
  Serial.print("Nilai z8 : ");
  Serial.println(z8);

  //  R9 - JAUH, BERAT, LAMBAT
  a9 = min(c, f); // Rules 9
  Serial.print("Alpha predikat9 : ");
  Serial.println(a9);
  z9 = 900 - a9 * (900 - 300);
  Serial.print("Nilai z9 : ");
  Serial.println(z9);
  
  Serial.println();

  /* DEFUZZIFIKASI */
  Serial.println("~~~~ DEFUZZIFIKASI ~~~~");
  Total_AiZi = (a1*z1)+(a2*z2)+(a3*z3)+(a4*z4)+(a5*z5)+(a6*z6)+(a7*z7)+(a8*z8)+(a9*z9);
  Total_a = a1+a2+a3+a4+a5+a6+a7+a8+a9;
  z = Total_AiZi/Total_a;

  Kecepatan = z;
  if(Kecepatan <= 900){
    Vkecepatan = "Lambat";
  }else if(Kecepatan > 300 && Kecepatan < 1500){
    Vkecepatan = "Sedang";
  }else if(Kecepatan >= 1500){
    Vkecepatan = "Cepat";
  }
  Serial.print("Kecepatan (" + Vkecepatan + ") : ");
  Serial.println(Kecepatan);

  Serial.println();
  delay(1000);  
}
