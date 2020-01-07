#define SensorPin 1          
#include<dht.h>
#define dht_apin A0
#include <MQ2.h>
#include <Wire.h> 
int Analog_Input = A5;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);
dht DHT;
unsigned long int avgValue;  
float b;
int buf[10],temp;


void setup() {
  pinMode(13,OUTPUT);  
  Serial.begin(9600); 
  //Serial.begin(9600);
  mq2.begin();
}

void loop() {
  int k=0;
  while(k<60){
   for(int i=0;i<10;i++)       
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  DHT.read11(dht_apin);
  avgValue=0;
  for(int i=2;i<8;i++)                      
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; 
  phValue=3.5*phValue;
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  Serial.print(phValue,2);
  Serial.print(",");
  Serial.print(DHT.humidity);
  Serial.print(",");
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.print(lpg);
  Serial.print(",");
  Serial.print(co);
  Serial.print(",");
  //Serial.setCursor(0,1);
  Serial.println(smoke);
  delay(2000);
  k++;
  }
  while(1);
}
