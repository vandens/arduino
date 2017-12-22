/**
 *  ESPClientFor8Relay.ino
 *  Created by Vandens mc Maddens
 *  Created on: 24.05.2015
 *  Deploy on Board NodeMCU 0.9 (ESP-12 Module) 80Mhz 115200
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

int relay1 = 16; //D1 on ESP Board 
int relay2 = 5; //D2 on ESP Board 
int relay3 = D2; //D3
int relay4 = D3; // D12
int relay5 = D5; //D5
int relay6 = D6; //D6
int relay7 = D7; //D7
int relay8 = D9; //D8

int indicator = D4;


void setup() {
    WiFi.hostname("IoT-Controller");
    pinMode(indicator,OUTPUT);
    USE_SERIAL.begin(115200);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
    }

    WiFiMulti.addAP("IoT", "");
    pinMode(relay1,OUTPUT);
    pinMode(relay2,OUTPUT); //D1
    pinMode(relay3,OUTPUT);
    pinMode(relay4,OUTPUT);
    pinMode(relay5,OUTPUT);
    pinMode(relay6,OUTPUT);
    pinMode(relay7,OUTPUT);
    pinMode(relay8,OUTPUT);
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    digitalWrite(relay3,HIGH);
    digitalWrite(relay4,HIGH);
    digitalWrite(relay5,HIGH);
    digitalWrite(relay6,HIGH);
    digitalWrite(relay7,HIGH);
    digitalWrite(relay8,HIGH);
    
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
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        
        
        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://xxx", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin("http://xxx"); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();
       
        // httpCode will be negative on error
        //if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                digitalWrite(indicator,LOW);
                
                String payload = http.getString();
                payload.replace("﻿","");
                USE_SERIAL.println(payload);
                if(getValue(payload, '|',0).equals("RELAY1=ON")){
                    digitalWrite(relay1,LOW);
                    USE_SERIAL.println(getValue(payload, '|',0));
                }
                if(getValue(payload, '|',0).equals("RELAY1=OFF")){
                    digitalWrite(relay1,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',0));
                }                
                if(getValue(payload, '|',1).equals("RELAY2=ON")){
                    digitalWrite(relay2,LOW);
                    USE_SERIAL.println(getValue(payload, '|',1));
                }
                if(getValue(payload, '|',1).equals("RELAY2=OFF")){
                    digitalWrite(relay2,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',1));
                }                
                if(getValue(payload, '|',2).equals("RELAY3=ON")){
                    digitalWrite(relay3,LOW);
                    USE_SERIAL.println(getValue(payload, '|',2));
                }
                if(getValue(payload, '|',2).equals("RELAY3=OFF")){
                    digitalWrite(relay3,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',2));
                }
                if(getValue(payload, '|',3).equals("RELAY4=ON")){
                    digitalWrite(relay4,LOW);
                    USE_SERIAL.println(getValue(payload, '|',3));
                }
                if(getValue(payload, '|',3).equals("RELAY4=OFF")){
                    digitalWrite(relay4,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',3));
                }
                if(getValue(payload, '|',4).equals("RELAY5=ON")){
                    digitalWrite(relay5,LOW);
                    USE_SERIAL.println(getValue(payload, '|',4));
                }
                if(getValue(payload, '|',4).equals("RELAY5=OFF")){
                    digitalWrite(relay5,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',4));
                }
                if(getValue(payload, '|',5).equals("RELAY6=ON")){
                    digitalWrite(relay6,LOW);
                    USE_SERIAL.println(getValue(payload, '|',5));
                }
                if(getValue(payload, '|',5).equals("RELAY6=OFF")){
                    digitalWrite(relay6,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',5));
                }
                if(getValue(payload, '|',6).equals("RELAY7=ON")){
                    digitalWrite(relay7,LOW);
                    USE_SERIAL.println(getValue(payload, '|',6));
                }
                if(getValue(payload, '|',6).equals("RELAY7=OFF")){
                    digitalWrite(relay7,HIGH);
                    USE_SERIAL.println(getValue(payload, '|',6));
                }
                if(getValue(payload, '|',7).equals("RELAY8=ON")){
                    digitalWrite(relay8,LOW);
                    USE_SERIAL.println(getValue(payload, '|',7));
                }
                if(getValue(payload, '|',7).equals("RELAY8=OFF")){
                    digitalWrite(relay8,HIGH);
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
         /*   
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());            
            for(uint8_t m = 0; m<=10; m++){
              (m%2 == 0) ? digitalWrite(indicator,HIGH) : digitalWrite(indicator,LOW);
              delay(300);
            }
        }
        */
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

    delay(7500);
}

