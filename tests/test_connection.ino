#include <SPI.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_PWMServoDriver.h>


#define ssid "Kong"
#define pwd "12345567"
#define UDP_PORT 4210


WiFiUDP UDP;
char receivedData[255];
char packet[255];
int32_t rssi;
char reply[] = "packet Received";

void connectToWiFi() {
    Serial.println("connecting to WiFi ...");
    WiFi.begin(ssid, pwd);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.println(".");
        delay(2000);
    }

    Serial.println("Connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP().toString().c_str());
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    connectToWiFi();
    UDP.begin(UDP_PORT);
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wifi Disconnected...");
        connectToWiFi();
    }

    int packetSize = UDP.parsePacket();
    if (packetSize) {
        UDP.read(receivedData, sizeof(receivedData));
        receivedData[packetSize] = '\0';
        Serial.print("Input Key: ");
        Serial.println(receivedData);

        UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
        UDP.write(reply);
        UDP.endPacket();
        
    }
}