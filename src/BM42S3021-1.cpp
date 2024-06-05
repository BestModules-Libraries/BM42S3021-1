/***********************************************************
File:           BM42S3021_1.cpp
Author:         BEST MODULES CORP.
Description:    BM42S3021_1.cpp is the library for controlling the BM42S3021_1 Fingerprint Sensor Module
Version:        V1.0.1   -- 2024-06-05
***********************************************************/
#include "BM42S3021-1.h"
/**********************************************************
Description: Constructor
Parameters:  *theSerial: Wire object if your board has more than one IIC interface      
                         parameter range:&wire、&wire1、&wire2
Return:          
Others:     
**********************************************************/
BM42S3021_1::BM42S3021_1(TwoWire *theWire)
{
    _wire = theWire;
}

/**********************************************************
Description: Initialize mode
Parameters:    
Return:      void         
Others:      
**********************************************************/
void BM42S3021_1::begin()
{
  _wire->begin();
  _wire->setClock(100000);
  delay(1000);
}

/**********************************************************
Description:  Start the distance measurement
Parameters:          
Return:       Temperature:The detected temperature(unit:Degree Celsius)
Others:      
**********************************************************/
float BM42S3021_1::readTemperature()
{
  uint8_t buff[3] = {0};
  float Temperature = 0;
  int16_t TemperatureValue = 0;
  if(readData(0x09,buff,3) == CHECK_OK)
  {
   delay(10);
   TemperatureValue = ((buff[1]<<8)+buff[0]);
   Temperature = TemperatureValue*0.1;
   return Temperature; 
  }
   delay(10);
   return 0; 
}

/**********************************************************
Description:  get Thermocouple Type
Parameters:      
Return:       Thermocouple type   
                  0: Type_K  
                  1: Type_N  
                  2: Type_E  
                  3: Type_J  
                  4: Type_R        
Others:       
**********************************************************/
uint8_t  BM42S3021_1::getThermocoupleType()
{
  uint8_t buff[3] = {0};
  uint8_t ThermocoupleType = 0;
  if(readData(0x28,buff,3) == CHECK_OK)
  {
   delay(10);
   ThermocoupleType = (buff[0]& 0x07);
   return ThermocoupleType; 
  }
   delay(10);
   return 0; 
}

/**********************************************************
Description:  Get version number
Parameters:   
Return:       FWver: version number   
Others:  
**********************************************************/
uint16_t BM42S3021_1::getFWver()
{
  uint8_t buff[3] = {0};
  uint16_t FWver = 0;
  if(readData(0x1f,buff,3) == CHECK_OK)
  {
   delay(10);
   FWver = (buff[1]<<8)+buff[0];
   return FWver; 
  }
   delay(10);
   return 0; 
}

/**********************************************************
Description:  set Thermocouple Type
Parameters:   type: Thermocouple type   
                  0: Type_K  
                  1: Type_N  
                  2: Type_E  
                  3: Type_J  
                  4: Type_R    
Return:       void        
Others: 
**********************************************************/
void BM42S3021_1::setThermocoupleType(uint8_t type)
{
  uint8_t sendBuf[4] = {0x28,0x00,0x00,0x00};
  sendBuf[1] = type;
  sendBuf[3] = (sendBuf[0]+sendBuf[1]+sendBuf[2]) & 0xff;
  writeData(sendBuf,4);
  delay(10);
}

/**********************************************************
Description: sleep module
Parameters:              
Return:      void        
Others:     
**********************************************************/
void BM42S3021_1::sleep()
{
  uint8_t sendBuf[4] = {0xff,0x34,0x12,0x00};
  sendBuf[3] = (sendBuf[0]+sendBuf[1]+sendBuf[2]) & 0xff;
  writeData(sendBuf,4);
  delay(10);
}

/**********************************************************
Description: writeData
Parameters:  wbuf[]:Variables for storing Data to be sent
             wlen:Length of data sent  
Return:      void    
Others:
**********************************************************/
void BM42S3021_1::writeData(uint8_t wbuf[], uint8_t wlen)
{
    while (_wire->available() > 0)
    {
      _wire->read();
    }
    _wire->beginTransmission(BM42S3021_1_Addr);
    _wire->write(wbuf, wlen);
    _wire->endTransmission();
}

/**********************************************************
Description: readData
Parameters:  
             CMD: Command
             rbuf[]: Variables for storing Data to be obtained
             rlen: Length of data to be obtained
Return:      Module recovery status
Others:
**********************************************************/
uint8_t BM42S3021_1::readData(uint8_t CMD,uint8_t rbuf[], uint8_t rlen)
{
   uint8_t i = 0;
    while (_wire->available() > 0)
    {
      _wire->read();
    }
    _wire->beginTransmission(BM42S3021_1_Addr);
    _wire->write(CMD);
    _wire->endTransmission(false);
    delay(10);
    _wire->requestFrom(BM42S3021_1_Addr, rlen);
    if (_wire->available() == rlen)
   {
     for (i = 0; i < rlen; i++)
     {
      rbuf[i] = _wire->read();
     }
   }
   else
   {
    return TIMEOUT_ERROR;
   }
 
/* check Sum */
  if (((rbuf[0] +rbuf[1])&0xff)  == rbuf[rlen - 1])
  {
    return CHECK_OK; // Check correct
  }
  else
  {
    return CHECK_ERROR; // Check error
  }
}
