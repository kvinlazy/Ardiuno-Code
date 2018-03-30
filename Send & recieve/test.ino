#include <SPI.h>
#include <Ethernet.h>


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10,20,11,250);

// initialize the library instance:
EthernetClient client;

char server[] = "10.20.24.16";
const size_t maxSize = 512;
char response[512];

void setup() {
  // start serial port:
  Serial.begin(9600);
  
  Serial.println("--- Start ---");
  
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip); 
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
 
}

void loop() {
 httpRequest();
}

// this method makes a HTTP connection to the server:
void httpRequest() {
    client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connected");
    String s = "GET /write.php?Value=1200";
   // s.concat(temp);
    Serial.println(s);
    client.println(s);
    
    client.println("Host: 10.20.24.16");
    delay(1000);
    size_t len = client.readBytes(response, maxSize);
    response[len] = 0;
// Serial.println(content);
    client.println("Connection: close");
    client.println();
    Serial.println(response);
    // note the time that the connection was made:
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
  delay(1000);
}
