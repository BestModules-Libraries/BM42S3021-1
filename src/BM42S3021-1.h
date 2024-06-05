/***********************************************************
File:           BM42S3021-1.h
Author:         BEST MODULES CORP.
Description:    Define classes and required variables
Version:        V1.0.1   -- 2024-06-05
***********************************************************/
#ifndef _BM42S3021_1_H__
#define _BM42S3021_1_H__

#include "Arduino.h"
#include <Wire.h> 

#define   CHECK_OK          0
#define   CHECK_ERROR       1
#define   TIMEOUT_ERROR     2

#define Type_K  0
#define Type_N  1
#define Type_E  2
#define Type_J  3
#define Type_R  4

const uint8_t BM42S3021_1_Addr = 0x28;    // I2C address

class BM42S3021_1
{     
 public:
    BM42S3021_1(TwoWire *theWire = &Wire);
    void begin();
    float readTemperature(); 
    uint8_t getThermocoupleType();
    uint16_t getFWver();
    void setThermocoupleType(uint8_t type = Type_K);
    void sleep();                                
  private:            
    void writeData(uint8_t wbuf[], uint8_t wlen);
    uint8_t readData(uint8_t CMD,uint8_t rbuf[], uint8_t rlen);
    TwoWire *_wire = NULL;
};

#endif
