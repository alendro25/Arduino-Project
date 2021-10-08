#include "CTBot.h"
CTBot myBot;

String ssid = "FA-30";     // Sesuikan dengan nama wifi anda
String pass = "19222511"; // sesuaikan password wifi
String token = "1951322617:AAHKVpn2mzqJ5iWo-wLFMRt4qUputor2cI4"; // token bot telegram yang telah dibuat

String data;
char c;

void setup() {
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
	TBMessage msg;

	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("LAMPU ON")) {              
			myBot.sendMessage(msg.sender.id, "LAMPU SUDAH ON");  //kirim pesan ke bot telegram
		  Serial.print("LAMPU ON");
		}
		else if (msg.text.equalsIgnoreCase("LAMPU OFF")) {        
			myBot.sendMessage(msg.sender.id, "LAMPU SUDAH OFF"); 
		  Serial.print("LAMPU OFF");
		}
    else if (msg.text.equalsIgnoreCase("TEMPERATURE")) {
      Serial.print("TEMPERATURE");
    }
		else {                                                    
			// membalas pesan selain kode diatas
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)". Command: LAMPU ON, LAMPU OFF, TEMPERATURE.";
			myBot.sendMessage(msg.sender.id, reply);         
		}
	}
  
  while(Serial.available()>0){
    delay(10);
    c = Serial.read();
    data += c;
  }
  if (data.length()>0) {
    myBot.sendMessage(msg.sender.id, data + " ℃");
    delay(10);
    data = "";
  }

	delay(500);
}
