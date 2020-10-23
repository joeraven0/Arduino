#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x5E, 0xAD };
byte server[] = { "http://www.google.se" }; // Google
int failedConnect = 0;  //Connection failed count, 3 times reboot router
int failedConnectGlobal = 0;  //Reboot counter
bool firstBoot = true;
EthernetClient client;
const int relayPin =  2;  //Relay pin

void setup()
{
  Ethernet.begin(mac);
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if(firstBoot){
      digitalWrite(relayPin, LOW);
      Serial.println("First boot, power on!");
      delay(120000);
      Serial.println("First boot ready, now cycling");
      firstBoot = false;
    }
  digitalWrite(relayPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  
  delay(5000);
  Serial.print("...");
  if (client.connect(server, 80)) {
    Serial.print("+");
    digitalWrite(LED_BUILTIN, HIGH);
    failedConnect = 0;    
  } else {
    Serial.print("~");
    failedConnect = failedConnect + 1;
    if(failedConnect>=3){
      digitalWrite(relayPin, HIGH);
      delay(5000);
      failedConnectGlobal = failedConnectGlobal + 1;
      failedConnect = 0;
      firstBoot = true;
      
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
