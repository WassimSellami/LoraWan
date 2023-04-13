#include <LoRaWan.h>
#include "DHT.h"

#define DHTPIN 2 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
char buffer[256];
int payloadNumber = 0;
struct payload{
  int temperature;
  int humidity;
  int payloadNumber;
};
payload data;

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
  result = lora.transferPacket((unsigned char *)&data, sizeof(payload),10);

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
  
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    data.payloadNumber = ++payloadNumber;
    

    SerialUSB.print("Temp: ");
    SerialUSB.print(data.temperature);
    SerialUSB.print("     Hum: ");
    SerialUSB.println(data.humidity);
}
