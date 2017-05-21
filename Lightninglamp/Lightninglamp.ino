#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin=13; 
int ledpin1=12;
int ledpin2=9;
int ledpin3=8;
int ledpin4=7;
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(ledpin3,OUTPUT);
  pinMode(ledpin4,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Genotronex.available()){
    BluetoothData=Genotronex.read();
    Serial.println(BluetoothData);
      if(BluetoothData=='1'){
        digitalWrite(ledpin,1);
        }
        else if(BluetoothData=='2'){
          digitalWrite(ledpin,0);
          }
        else if(BluetoothData=='3'){  
      digitalWrite(ledpin1,1);   
           }
           else if(BluetoothData=='4'){  
           digitalWrite(ledpin1,0);
           }
           else if(BluetoothData=='5'){   
           digitalWrite(ledpin2,1);
           }
           else if(BluetoothData=='6'){   
           digitalWrite(ledpin2,0);
           }
           else if(BluetoothData=='7'){   
           digitalWrite(ledpin3,1);
           }
           else if(BluetoothData=='8'){  
           digitalWrite(ledpin3,0);
           }
           else if(BluetoothData=='9'){  
           digitalWrite(ledpin4,1);
           }
           else if(BluetoothData=='a'){   
           digitalWrite(ledpin4,0);
           }
          else if (BluetoothData=='0'){
          digitalWrite(ledpin,0);
          digitalWrite(ledpin1,0);
          digitalWrite(ledpin2,0);
          digitalWrite(ledpin3,0);
          digitalWrite(ledpin4,0);
          }
   }
 else
 {      
  }
 
delay(100);
}
