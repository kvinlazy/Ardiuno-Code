#include <Bridge.h>
#include <HttpClient.h>
int analogIn = A0; int analogVal = 0; int analogIn1 = A1; int analogVal1 = 0;int light = 0;
float temp;
void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  pinMode(0, OUTPUT);
}

void loop() {
// Initialize the client library
String dataString;
  analogVal = analogRead(analogIn);analogVal1 = analogRead(analogIn1);
  light=map(analogVal,0,1024,0,100);// To convert Analog values to % of luminosity
  temp=analogVal1*0.4689455791989076; //Sensor Calibration
  HttpClient client;
  dataString += getTimeStamp(); // CAll routine to obtain current timestamp from the linino side of the YUN
  // Make a HTTP request:To send analog input values of A0 and A1
  client.get("http://www.dweet.io/dweet/for/Cept_demo?Light="+String(light)+"&TimeStamp="+String(dataString));
  delay(1000); // To give time to the server for answering
  HttpClient client1;
  
 }


String getTimeStamp() {
   String result;
   Process time;
   time.begin("date");
   time.addParameter("+%D-%T");  
   time.run(); 
   while(time.available()>0) {
     char c = time.read();
     if(c != '\n')
       result += c;
   }
   return result;
}

