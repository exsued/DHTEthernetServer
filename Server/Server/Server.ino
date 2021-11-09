#include <Ethernet.h>

int port = 80;  //Port number
EthernetServer server(port);

#include "DHT.h"
#define DHTPIN 13

DHT dht(DHTPIN, DHT11); //Инициация датчика

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

void setup() {
  Serial.begin(9600);
  
  Serial.println();
  Serial.println();

  if(Ethernet.begin(mac) == 0){
    Serial.println("Failed to configure IP address using DHCP");
  }
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());

  Serial.println("Starting server");
  server.begin();
  Serial.println("Starting DHT");
  dht.begin();
}
void loop() {
  EthernetClient client = server.available();

  if (client.connected()) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          float h = dht.readHumidity(); 
          float t = dht.readTemperature(); 
          if (isnan(h) || isnan(t)) {
           Serial.println("err");
          }else{
            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.print(" Temperature: ");
            Serial.println(t);
          }
          client.println("</html>");
          client.stop();
    }
}
