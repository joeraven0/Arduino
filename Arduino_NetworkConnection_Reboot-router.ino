#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server[] = { "http://www.google.se" }; // Google
int failedConnect = 0;
int failedConnectGlobal = 0;
EthernetClient client;
const int ledPin =  2;// the number of the LED pin

void setup()
{
  Ethernet.begin(mac);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, LOW);
  delay(1000);
  Serial.print("...");
  if (client.connect(server, 80)) {
    Serial.print("+");
    failedConnect = 0;    
  } else {
    Serial.print("~");
    failedConnect = failedConnect + 1;
    if(failedConnect>=3){
      digitalWrite(ledPin, HIGH);
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
