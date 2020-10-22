#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server[] = { "http://www.google.se" }; // Google
int failedConnect = 0;  //Connection failed count, 3 times reboot router
int failedConnectGlobal = 0;  //Reboot counter
EthernetClient client;
const int relayPin =  2;  //Relay pin

void setup()
{
  Ethernet.begin(mac);
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
}

void loop()
{
  digitalWrite(relayPin, LOW);
  delay(60000);
  Serial.print("...");
  if (client.connect(server, 80)) {
    Serial.print("+");
    failedConnect = 0;    
  } else {
    Serial.print("~");
    failedConnect = failedConnect + 1;
    if(failedConnect>=3){
      digitalWrite(relayPin, HIGH);
      delay(5000);
      failedConnectGlobal = failedConnectGlobal + 1;
      failedConnect = 0;
      
      }
    
  }
  delay(1000);
  client.stop();
  if (client.available()) {
    char c = client.read();
    Serial.println(c);
  }
  
  if (!client.connected()) {
    Serial.print("-");
    Serial.print("||Fails: " + String(failedConnect));
    Serial.print(" ||Reboots: " + String(failedConnectGlobal));
    Serial.println();
    
   
  }
}
