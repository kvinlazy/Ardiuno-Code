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
IPAddress ip(192,168, 1, 250);

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
  Ethernet.begin(mac, ip); 
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  pinMode(trigPin, OUTPUT);
}

void loop() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
  delay(1000);
  lightintensity = analogRead(A5);
  light=map(lightintensity,0,1024,0,100);
  Temperaturesensor = analogRead(A0);
  temp=Temperaturesensor*0.4689455791989076;
 if (cm <= 10)
 {
  if (light > 50)
  {
    digitalWrite(7,HIGH);
  }
  else
  {
    digitalWrite(7,LOW);
   }
   if (temp > 25)
    {
      digitalWrite(8,LOW);
    }
    else
    {
      digitalWrite(8,HIGH);
     }
  
    httpRequest();
}
else
{
  digitalWrite(7, HIGH);
  digitalWrite(8,HIGH);
  }
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

// this method makes a HTTP connection to the server:
void httpRequest() {
    client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connected");
    String s = "POST /dweet/for/Ethernettest?Temperature="+String(temp)+"&LightIntensity="+String(light)+"&Distance="+String(cm);
   // s.concat(temp);
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
