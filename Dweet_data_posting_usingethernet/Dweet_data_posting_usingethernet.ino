#include <SPI.h>
#include <Ethernet.h>

const int trigPin = 2;
const int echoPin = 4;
float Temperaturesensor;
float temp;
int sensor_1,light;
float  lightintensity;
long duration, inches, cm;


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
//IPAddress gateway(192, 168,1, 1);
// the subnet:
//IPAddress subnet(255, 255, 0, 0);
IPAddress ip(192,168,1,100 );

// initialize the library instance:
EthernetClient client;

char server[] = "www.dweet.io";

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

void setup() {
  // start serial port:
  Serial.begin(9600);
  pinMode(A5,INPUT);
  pinMode(A0,INPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  Serial.println("--- Start ---");
  
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
 //Ethernet.begin(mac, ip); 
 Serial.println(Ethernet.begin(mac));
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  pinMode(trigPin, OUTPUT);
}

void loop() {
 
  lightintensity = analogRead(A5);
  light=map(lightintensity,0,1024,0,100);
  Temperaturesensor = analogRead(A0);
  temp=Temperaturesensor*0.4689455791989076;
  httpRequest();
  delay(1000);

}



// this method makes a HTTP connection to the server:
void httpRequest() {
    client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connected");
    String s = "POST /dweet/for/Ethernettest?Temperature=";
    //String s = "www.dweet.io/dweet/for/Ethernettest?Temperature=";
    s.concat(temp);
    Serial.println(s);
    client.println(s);
    client.println("Host: www.dweet.io");
    client.println("Connection: close");
    client.println(); 
    // note the time that the connection was made:
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}
