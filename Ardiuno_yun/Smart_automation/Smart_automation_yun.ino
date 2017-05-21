#include <Bridge.h>
#include <HttpClient.h>
#include <ArduinoJson.h>
float webtemperature;
float Temperaturesensor;
int stateoflight;
int stateoffan;
int motion_1 = 2;
const size_t MAX_CONTENT_SIZE = 512;
char response[512];
char responsee[512];
float temp;
int sensor_1,light;
float  lightintensity;

int mode = 0;
int re = 1;
int re1 = 1;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(2, INPUT);
  pinMode(0, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A5,INPUT); 
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  while (!Serial); 
}

void loop() {
  //sensor_1 = digitalRead(motion_1);
  //Serial.println(sensor_1);
  //if (sensor_1 == HIGH){
  lightintensity = analogRead(A5);
  light=map(lightintensity,0,1024,0,100);
  Temperaturesensor = analogRead(A0);
  temp=Temperaturesensor*0.4689455791989076;
  weatherreport(response, sizeof(response));
  senddata();
  readReponseContent(response, sizeof(response));

  if (mode == 0)
  {
  
    if (light < 50 ){
      digitalWrite(12, HIGH);
      }
    else 
    {
      digitalWrite(12,LOW);
    }
    
    if (temp > 25)
    {
      digitalWrite(11,HIGH);
    }
    else
    {
      digitalWrite(11,LOW);
    }
  }
  Serial.println(light);
  Serial.println(temp);

   
   if (mode == 1){
   

   if (re == 1){
    digitalWrite(12,HIGH);
   }
   else
   {
    digitalWrite(12,LOW);
    }
    if (re1 == 1){
    digitalWrite(11,HIGH);
   }
   else
   {
    digitalWrite(11,LOW);
    }
   }
  /* }
   else
   {
    Serial.println("No Motion Detection");
   }
  */
  //}
  Serial.flush();

  delay(5000);
}

void senddata(){//float light,float temp){
  HttpClient clientt;
  String dataString;
  dataString += getTimeStamp(); // CAll routine to obtain current timestamp from the linino side of the YUN
  // Make a HTTP request:To send analog input values of A0 and A1
  clientt.get("http://www.dweet.io/dweet/for/SmartSystem?Temperature="+String(temp)+"&Light="+String(light)+"&OutsideTempearture="+String(webtemperature)+"&TimeStamp="+String(dataString));
  delay(1000); // To give time to the server for answering

}

void weatherreport(char* content, size_t maxSize) {
  HttpClient client;
  client.noCheckSSL();
  // Make a HTTP request:
  client.get("http://api.openweathermap.org/data/2.5/weather?id=1279233&appid=432e2b52e3801dbd19e167858d0a7d31");
  size_t length = client.readBytes(content, maxSize);
  content[length] = 0;
  //Serial.println(content);
   StaticJsonBuffer<400> jsonBuffer;
  // If the memory pool is too big for the stack, use this instead:
  // DynamicJsonBuffer jsonBuffer;

  JsonObject& root1 = jsonBuffer.parseObject(content);

  if (!root1.success()) {
    Serial.println("JSON parsing failed!");
    return false;
  }
  webtemperature = (root1["main"]["temp"]);
  webtemperature = webtemperature/10;
  
   Serial.println(webtemperature);
  //SerialUSB.println(re1); 
}

void readReponseContent(char* content, size_t maxSize) {
  HttpClient client;
  client.noCheckSSL();
  // Make a HTTP request:
  client.get("https://dweet.io/get/latest/dweet/for/Controller");
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
  mode = root["with"][0]["content"]["Automatic_Manual"];
  re = root["with"][0]["content"]["Lightstatus"];
  re1 = root["with"][0]["content"]["Fanstatus"];
  //Serial.println(re);
  //Serial.println(re1);
  
}


String getTimeStamp() {
   String result;
   Process time;
   time.begin("date");
   time.addParameter("+%D+%T");  
   time.run(); 
   while(time.available()>0) {
     char c = time.read();
     if(c != '\n')
       result += c;
   }
   return result;
}
