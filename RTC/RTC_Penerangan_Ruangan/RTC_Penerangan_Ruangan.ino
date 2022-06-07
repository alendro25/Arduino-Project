#include <DS3231.h>
#include <Wire.h>

DS3231 rtc(SDA, SCL); // Inisialisasi penggunaan I2C
Time t;
String hari, jam, tanggal;

//Inisialisasi Pin Pada Arduino
const int PIR_A = 2;
const int PIR_B = 4;
const int RELAY_1 = 7;
const int RELAY_2 = 8;

//Deklarasi variabel untuk Status
String MATKUL5 = " ";
String MATKUL6 = " ";
String STATE_5 = " ";
String STATE_6 = " ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Buka Serial Monitor u/ cek Status
  rtc.begin();
  initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  t = rtc.getTime();
  hari = rtc.getDOWStr();
  jam = rtc.getTimeStr();
  tanggal = rtc.getDateStr();

  // Cek kondisi ruangan untuk penerangan otomatis
  ruang_405();
  ruang_406();

  /*Nama_Function(Hari, Waktu Nyala (HH, MM), Waktu Mati (HH, MM), MATKUL)
  Hari(English - Awal Kapital) : Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday */

  /*-------------------------- Jadwal Ruang 405 -----------------------------------*/
  // Hari Senin
  Jadwal_405("Monday", 18, 42, 18, 43, "Bhs. Indonesia"); // Matkul 1
  Jadwal_405("Monday", 19, 0, 21, 0, "Agama"); // Matkul 2
  // Hari Selasa
  Jadwal_405("Tuesday", 18, 42, 18, 43, "Matematika Diskrit"); // Matkul 1
  Jadwal_405("Tuesday", 18, 44, 18, 45, "Database"); // Matkul 2
  // Hari Rabu
  Jadwal_405("Wednesday", 18, 42, 18, 43, "Augmented Reality"); // Matkul 1
  // Hari Kamis
  Jadwal_405("Thursday", 15, 22, 15, 23, "Pemrograman Android"); // Matkul 1
  Jadwal_405("Thursday", 14, 54, 14, 55, "IMK"); // Matkul 2
  // Hari Jumat
  Jadwal_405("Friday", 15, 39, 15, 40, "Pemrograman Dasar"); // Matkul 1
  Jadwal_405("Friday", 14, 41, 14, 42, "IMK"); // Matkul 2
  /*---------------------------- Akhir Ruang 405 ----------------------------------*/

  /*-------------------------- Jadwal Ruang 406 -----------------------------------*/
  // Hari Senin
  Jadwal_406("Monday", 18, 42, 18, 43, "Kalkulus I"); // Matkul 1
  Jadwal_406("Monday", 19, 0, 21, 0, "Interpersonal Skill"); // Matkul 2
  // Hari Selasa
  Jadwal_406("Tuesday", 18, 42, 18, 44, "Computer Vision"); // Matkul 1
  // Hari Rabu
  Jadwal_406("Wednesday", 18, 42, 18, 43, "Metode Numerik"); // Matkul 1
  Jadwal_406("Wednesday", 19, 0, 21, 0, "Sistem Operasi"); // Matkul 2
  // Hari Kamis
  Jadwal_406("Thursday", 15, 22, 15, 23, "Pemrograman Dasar"); // Matkul 1
  Jadwal_406("Thursday", 14, 41, 14, 42, "IMK"); // Matkul 2
  // Hari Jumat
  Jadwal_406("Friday", 15, 18, 15, 19, "Pengolahan Sinyal Digital"); // Matkul 1
  Jadwal_406("Friday", 14, 41, 14, 42, "Pemrograman Framework"); // Matkul 2
  /*---------------------------- Akhir Ruang 406 ----------------------------------*/
  
  Serial.println();
  Serial.println("--------------- STATUS ---------------");
  Serial.print("Hari, Tanggal : "); Serial.print(hari); Serial.print(", ");Serial.println(tanggal);
  Serial.print("Jam : "); Serial.println(jam); 
  Serial.print("STATUS Ruang 405" ); Serial.print("("); Serial.print(MATKUL5); Serial.print("): "); Serial.println(STATE_5);
  Serial.print("STATUS Ruang 406" ); Serial.print("("); Serial.print(MATKUL6); Serial.print("): "); Serial.println(STATE_6);
  Serial.println("--------------------------------------");
  Serial.println();
  delay(1000);
}

void initialize(){
  pinMode(PIR_A, INPUT);
  pinMode(PIR_B, INPUT);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  digitalWrite(RELAY_2, HIGH);
  digitalWrite(PIR_A, LOW);
  digitalWrite(PIR_B, LOW);
  for (int i = 1; i < 6; i++){
    Serial.print(i);
    delay(1000);
  }
}

void Jadwal_405(String Hari, int OnHour , int OnMin, int OffHour, int OffMin, String MataKuliah){
  if(hari == Hari){
    if(t.hour == OnHour && t.min == OnMin){
      digitalWrite(RELAY_1, LOW);
      STATE_5 = "NYALA";
      MATKUL5 = MataKuliah;
    }
    else if(t.hour == OffHour && t.min == OffMin){
      digitalWrite(RELAY_1, HIGH);
      STATE_5 = "MATI";
      MATKUL5 = " ";
    }
  }  
}
  
void Jadwal_406(String Hari, int OnHour , int OnMin, int OffHour, int OffMin, String MataKuliah){
  if(hari == Hari){
      if(t.hour == OnHour && t.min == OnMin){
        digitalWrite(RELAY_2, LOW);
        STATE_6 = "NYALA";
        MATKUL6 = MataKuliah;
      }
      else if(t.hour == OffHour && t.min == OffMin){
        digitalWrite(RELAY_2, HIGH);
        STATE_6 = "MATI";
        MATKUL6 = " ";
      }
    }  
}
  
void ruang_405(){
  int statusPIR_A = digitalRead(PIR_A);
  if (statusPIR_A == HIGH){ //jika sensor membaca gerakan maka relay akan aktif 
    digitalWrite(RELAY_1, LOW);
    Serial.print("(Ruang 405)Gerakan Terdeteksi - ");
    Serial.print("("); Serial.print(statusPIR_A); Serial.println(")");
    STATE_5 = "NYALA";
  }else {
    digitalWrite(RELAY_1, HIGH);//jika sensor tidak membaca gerakan maka relay akan off
    Serial.print("(Ruang 405)Gerakan Tidak Terdeteksi - ");
    Serial.print("("); Serial.print(statusPIR_A); Serial.println(")");
    STATE_5 = "MATI";
  }
}

void ruang_406(){
  int statusPIR_B = digitalRead(PIR_B);
  if (statusPIR_B == HIGH) { //jika sensor membaca gerakan maka relay akan aktif
    digitalWrite(RELAY_2, LOW);
    Serial.print("(Ruang 406)Gerakan Terdeteksi - ");\
    Serial.print("("); Serial.print(statusPIR_B); Serial.println(")");
    STATE_6 = "NYALA";
  }else {
    digitalWrite(RELAY_2, HIGH);//jika sensor tidak membaca gerakan maka relay akan off
    Serial.print("(Ruang 406)Gerakan Tidak Terdeteksi - ");
    Serial.print("("); Serial.print(statusPIR_B); Serial.println(")");
    STATE_6 = "MATI";
  }
} 
