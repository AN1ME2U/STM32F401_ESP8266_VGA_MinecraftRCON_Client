#include <ESP8266WiFi.h>
#include <string.h>
#include <WiFiUdp.h>

String ssid = "HOME";
String password = "0663302740";


WiFiUDP Udp;

unsigned int localUdpPort = 4210;  // локальный порт для прослушки 

char incomingPacket[255];          // буфер для входящих пакетов

char  replyPacekt[] = "Hi there! Got the message :-)";  // ответ

                  //  "Привет! Сообщение получено :-)"


void setup()

{

  Serial.begin(115200);

  Serial.println();

  Serial.printf("Enter ssid");
  while(Serial.available() == 0);
  ssid = Serial.readString();
  Serial.printf("SSID is %s /n", ssid);

  Serial.printf("Enter WIFI password");
  while(Serial.available() == 0);
  password = Serial.readString();
  Serial.printf("Password is %s ", password);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println(" connected");

             //  " подключено "


  

}


void loop()

{



  

}
