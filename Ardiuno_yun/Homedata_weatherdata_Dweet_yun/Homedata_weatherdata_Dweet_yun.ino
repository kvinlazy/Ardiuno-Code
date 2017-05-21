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
float temp;
int sensor_1,light;
float  lightintensity;
float re, re1;

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
  
  lightintensity = analogRead(A5);
  light=map(lightintensity,0,1024,0,100);
  Temperaturesensor = analogRead(A0);
  if (light < 50 ){
  digitalWrite(12, HIGH);
  }
  else 
  {
    digitalWrite(12,LOW);
    //delay(60000);
  }
  //temp=Temperaturesensor*0.4689455791989076; //Sensor Calibration
  temp = map(Temperaturesensor,0,307,0,150);
  weatherreport(response, sizeof(response));
   
  if (temp < 25)
  {
    digitalWrite(11,HIGH);
  }
  else
  {
    digitalWrite(11,LOW);
    //delay(60000);
  }
  Serial.println(light);
  Serial.println(temp);
  senddata(); 
   
  Serial.flush();

  delay(5000);
}

void senddata(){
  HttpClient clientt;
  String dataString;
  dataString += getTimeStamp();
  clientt.get("http://www.dweet.io/dweet/for/SmartSystem?Temperature="+String(temp)+"&Light="+String(light)+"&OutsideTempearture="+String(webtemperature)+"&TimeStamp="+String(dataString));
  delay(1000); // To give time to the server for answering

}

void weatherreport(char* content, size_t maxSize) {
  HttpClient client;
  client.noCheckSSL();
  client.get("http://api.openweathermap.org/data/2.5/weather?id=1279233&appid=432e2b52e3801dbd19e167858d0a7d31");
  size_t length = client.readBytes(content, maxSize);
  content[length] = 0;
  Serial.println(content);
  StaticJsonBuffer<400> jsonBuffer;
  JsonObject& root1 = jsonBuffer.parseObject(content);

  if (!root1.success()) {
    Serial.println("JSON parsing failed!");
    return false;
  }
  webtemperature = (root1["main"]["temp"]);
  webtemperature = webtemperature/10;
  
   Serial.println(webtemperature);
  
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
