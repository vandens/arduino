/**
 *  ESPClientFor8R.ino
 *  Created by Vandens mc Maddens
 *  Created 1: 24.05.2015
 *  Deploy 1 Board NodeMCU 0.9 (ESP-12 Module) 80Mhz 115200
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

int R1 = 16; //D1 1 ESP Board 
int R2 = 5; //D2 1 ESP Board 
int R3 = D2; //D3
int R4 = D3; // D12
int R5 = D5; //D5
int R6 = D6; //D6
int R7 = D7; //D7
int R8 = D9; //D8

int indicator = D4;


void setup() {
    WiFi.hostname("IoT-C1troller");
    pinMode(indicator,OUTPUT);
    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
    }

    WiFiMulti.addAP("IoT", "P@5sW0rd");
    pinMode(R1,OUTPUT);
    pinMode(R2,OUTPUT); //D1
    pinMode(R3,OUTPUT);
    pinMode(R4,OUTPUT);
    pinMode(R5,OUTPUT);
    pinMode(R6,OUTPUT);
    pinMode(R7,OUTPUT);
    pinMode(R8,OUTPUT);
    digitalWrite(R1,HIGH);
    digitalWrite(R2,HIGH);
    digitalWrite(R3,HIGH);
    digitalWrite(R4,HIGH);
    digitalWrite(R5,HIGH);
    digitalWrite(R6,HIGH);
    digitalWrite(R7,HIGH);
    digitalWrite(R8,HIGH);
    
    digitalWrite(indicator,LOW);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void loop() {
    // wait for WiFi c1necti1
    if((WiFiMulti.run() == WL_CONNECTED)) {
        
        
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // c1figure traged server and url
        //http.begin("https://xxx", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin("http://192.168.64.103/test"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start c1necti1 and send HTTP header
        int httpCode = http.GET();
       
        // httpCode will be negative 1 error
        if(httpCode > 0) {
            // HTTP header has been send and Server resp1se header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                digitalWrite(indicator,LOW);
                
                String payload = http.getString();
                payload.replace("﻿","");
                USE_SERIAL.println(payload);
                if(getValue(payload, '|',0).equals("R1=1")){
                    digitalWrite(R1,LOW);
                    USE_SERIAL.println(getValue(payload, '|',0));
                }
                if(getValue(payload, '|',0).equals("R1=0")){
                    digitalWrite(R1,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',0));
                }                
                if(getValue(payload, '|',1).equals("R2=1")){
                    digitalWrite(R2,LOW);
                    USE_SERIAL.println(getValue(payload, '|',1));
                }
                if(getValue(payload, '|',1).equals("R2=0")){
                    digitalWrite(R2,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',1));
                }                
                if(getValue(payload, '|',2).equals("R3=1")){
                    digitalWrite(R3,LOW);
                    USE_SERIAL.println(getValue(payload, '|',2));
                }
                if(getValue(payload, '|',2).equals("R3=0")){
                    digitalWrite(R3,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',2));
                }
                if(getValue(payload, '|',3).equals("R4=1")){
                    digitalWrite(R4,LOW);
                    USE_SERIAL.println(getValue(payload, '|',3));
                }
                if(getValue(payload, '|',3).equals("R4=0")){
                    digitalWrite(R4,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',3));
                }
                if(getValue(payload, '|',4).equals("R5=1")){
                    digitalWrite(R5,LOW);
                    USE_SERIAL.println(getValue(payload, '|',4));
                }
                if(getValue(payload, '|',4).equals("R5=0")){
                    digitalWrite(R5,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',4));
                }
                if(getValue(payload, '|',5).equals("R6=1")){
                    digitalWrite(R6,LOW);
                    USE_SERIAL.println(getValue(payload, '|',5));
                }
                if(getValue(payload, '|',5).equals("R6=0")){
                    digitalWrite(R6,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',5));
                }
                if(getValue(payload, '|',6).equals("R7=1")){
                    digitalWrite(R7,LOW);
                    USE_SERIAL.println(getValue(payload, '|',6));
                }
                if(getValue(payload, '|',6).equals("R7=0")){
                    digitalWrite(R7,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',6));
                }
                if(getValue(payload, '|',7).equals("R8=1")){
                    digitalWrite(R8,LOW);
                    USE_SERIAL.println(getValue(payload, '|',7));
                }
                if(getValue(payload, '|',7).equals("R8=0")){
                    digitalWrite(R8,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',7));
                }
            }else{
              
                for(uint8_t n = 2; n > 0; n--) {
                  digitalWrite(indicator,LOW);
                  delay(900);
                  for(uint8_t m = 0; m<=4; m++){
                    (m%2 == 0) ? digitalWrite(indicator,HIGH) : digitalWrite(indicator,LOW);
                    delay(150);
                  }
                  delay(300);
                }
            }
            
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());            
            for(uint8_t m = 0; m<=10; m++){
              (m%2 == 0) ? digitalWrite(indicator,HIGH) : digitalWrite(indicator,LOW);
              delay(300);
            }
        }
        
        http.end();
    }else{
       for(uint8_t n = 2; n > 0; n--) {
          delay(500);
          for(uint8_t m = 0; m<=20; m++){
            (m%2 == 0) ? digitalWrite(indicator,HIGH) : digitalWrite(indicator,LOW);
            delay(100);
          }
        }
    }

    delay(5000);
}

