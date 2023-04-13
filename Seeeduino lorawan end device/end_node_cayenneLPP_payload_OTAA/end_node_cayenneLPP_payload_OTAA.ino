#include <LoRaWan.h>
#include<CayenneLPP.h>
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
CayenneLPP lpp(51);
char buffer[256];


void setup(void)
{
  SerialUSB.begin(115200);

  dht.begin();
  
  //while(!SerialUSB);
  lora.init();
  lora.setKey(0, 0, "1CB2FF08BEEE308966E3C0AF5567914E");
  
  lora.setDeciveMode(LWOTAA);
  lora.setDataRate(DR0, EU868);
  
  lora.setChannel(0, 868.1);
  lora.setChannel(1, 868.3);
  lora.setChannel(2, 868.5);
  
  lora.setReceiceWindowFirst(0, 868.1);
  lora.setReceiceWindowSecond(869.5, DR3);
  
  lora.setDutyCycle(false);
  lora.setJoinDutyCycle(false);
  
  lora.setPower(14);
  SerialUSB.print("int: ");
  SerialUSB.println(sizeof(int));
  while(!lora.setOTAAJoin(JOIN));
}


void loop(void)
{
  bool result = false;
  getSensorData();
  SerialUSB.println("Sending...");
  result = lora.transferPacket((unsigned char *)lpp.getBuffer(),lpp.getSize(),10);

  if(result)
  {
      short length;
      short rssi;
      memset(buffer, 0, 256);
      length = lora.receivePacket(buffer, 256, &rssi);
      if(length)
      {
          SerialUSB.print("Length is: ");
          SerialUSB.println(length);
          SerialUSB.print("RSSI is: ");
          SerialUSB.println(rssi);
          SerialUSB.print("Data is: ");
          for(unsigned char i = 0; i < length; i ++)
          {
              SerialUSB.print("0x");
              SerialUSB.print(buffer[i], HEX);
              SerialUSB.print(" ");
          }
          SerialUSB.println();
      }
  }
}

void getSensorData(){
    lpp.reset();
    int humidity = dht.readHumidity();
    lpp.addRelativeHumidity(3, humidity);
    int temp = dht.readTemperature();
    lpp.addTemperature(4, temp);


    SerialUSB.print("Temp: ");
    SerialUSB.print(temp);
    SerialUSB.print("     Hum: ");
    SerialUSB.println(humidity);
}
