#include "CTBot.h"
CTBot myBot;

String ssid = "FA-30";     // Sesuikan dengan nama wifi anda
String pass = "19222511"; // sesuaikan password wifi
String token = "2064758286:AAG6F2LY4J6MZnbCHk9wDWqblrmsM6CSe1c"; // token bot telegram yang telah dibuat

String data = "";
String arrayData[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("Connection : OK");
  else
    Serial.println("Connection : ERROR");
}

void loop() {
  // put your main code here, to run repeatedly:
  TBMessage msg;

  if(myBot.getNewMessage(msg)){

    if (msg.text.equalsIgnoreCase("LED ON")) {
      Serial.print("LED ON");
    }
    else if (msg.text.equalsIgnoreCase("LED OFF")) {
      Serial.print("LED OFF");
    }
    else if (msg.text.equalsIgnoreCase("SENSOR1")) {
      Serial.print("SENSOR1");
    }
    else if (msg.text.equalsIgnoreCase("SENSOR2")) {
      Serial.print("SENSOR2");
    }
    else if (msg.text.equalsIgnoreCase("STATUS")) {
      Serial.print("STATUS");
    }
    else {
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Try LED ON, LED OFF, SENSOR1, SENSOR2, or STATUS.";
      myBot.sendMessage(msg.sender.id, reply);
    }      
  }

  //  Menunggu adanya data dari Arduino
  while(Serial.available() > 0){ // Berati ada data
    char c = Serial.read();
    data += c;
  }

  if (data.length() > 15){ // Jika panjang data lebih dari 15 karakter alias monitor status semua sensor Arduino
    // Membuat parsing (memisah/memecah) data dari arduino
    String lihat = data;
    Serial.print(lihat);
    int index = 0;
      for (int i = 0; i < data.length(); i++){
        char delimiter  = '#'; // Pembatas data yg akan diolah
        if (data[i] != delimiter){ // Jika data i tidak sama dengan '#'
          arrayData[index] += data[i]; // Maka ini dianggap sbg index ke-i
        }else{  // Berarti jika datanya berupa '#', maka indexnya bertambah
          index++; 
        }
      }
      if (index == 2){ // Index Array dimulai dari 0, index ke-0 adalah data ke-1
        // Cara mengeluarkan data yg masuk ke ESP sprti ini
        // arrayData[0], arrayData[1], dst....
        myBot.sendMessage(msg.sender.id, arrayData[0] + "\n" + arrayData[1] + "\n" + arrayData[2]);
      }
     arrayData[0] = "";
     arrayData[1] = "";
     arrayData[2] = "";
     data = "";
  }
  else { // Jika panjang data kurang dari 15 karakter
     myBot.sendMessage(msg.sender.id, data);
     data = "";
  }
  
}
