

/*
  Yún HTTP Client

 This example for the Arduino Yún shows how create a basic
 HTTP client that connects to the internet and downloads
 content. In this case, you'll connect to the Arduino
 website and download a version of the logo as ASCII text.

 created by Tom igoe
 May 2013

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/HttpClient

 */

#include <Bridge.h>
#include <HttpClient.h>
#include <ArduinoJson.h>

const size_t MAX_CONTENT_SIZE = 512;
char response[512];
void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  SerialUSB.begin(9600);
  

  while (!SerialUSB); // wait for a serial connection
}

void loop() {
  // Initialize the client library
  HttpClient client;
  client.noCheckSSL();
  // Make a HTTP request:
  client.get("https://dweet.io/get/latest/dweet/for/Cept_demo");
  //SerialUSB.print('geting');
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    digitalWrite(0,HIGH);
    String c = client.readString();
    //SerialUSB.println(c);
    char response[MAX_CONTENT_SIZE];
    readReponseContent(response, sizeof(response));
  
  }
  SerialUSB.flush();

  delay(5000);
}
void readReponseContent(char* content, size_t maxSize) {
  HttpClient client;
  client.noCheckSSL();
  // Make a HTTP request:
  client.get("https://dweet.io/get/latest/dweet/for/Cept_demo");
  size_t length = client.readBytes(content, maxSize);
  content[length] = 0;
  Serial.println(content);
   StaticJsonBuffer<400> jsonBuffer;
  // If the memory pool is too big for the stack, use this instead:
  // DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.parseObject(content);

  if (!root.success()) {
    Serial.println("JSON parsing failed!");
    return false;
  }
  String re = root["success"];
  Serial.println(re);
  
}


