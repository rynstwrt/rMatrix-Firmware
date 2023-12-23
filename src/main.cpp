/*
 * The firmware for the rMatrix project, as seen on https://www.rmatrix.xyz. 
 * 
 * Developed by Ryan Stewart, A.K.A. Ryn.
 * 
 * This firmware is licensed under the 
 * Creative Commons Attribution-NonCommercial-ShareAlike (CC-BY-NC-SA)
 * license: http://creativecommons.org/licenses/by-nc-sa/4.0/
 * 
 * This firmware can be modified and distributed, but can NOT be used for
 * commerical use. The licensing also requires that you release any 
 * modified works of this firmware under the same license.
 * 
 * This firmware is distributed "as is" and without any warranty.
 * 
 * Check the LICENSE.md file for details about licensing.
*/


#include <Arduino.h>
#include <constants.h>
#include <secrets.h>
#include <LittleFS.h>
#include <DNSServer.h>
#include <ESPAsyncWebServer.h>


AsyncWebServer server(80);


void setup()
{
    Serial.begin(SERIAL_SPEED);

    if (!LittleFS.begin())
    {
        Serial.println("Error mounting file system!");
        return;
    }
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi failed!");
        return;
    }

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(LittleFS, "/style.css", "text/css");        
    });

    server.on("/ui-handler.js", HTTP_GET, [](AsyncWebServerRequest* request)
    {
        request->send(LittleFS, "/ui-handler", "text/javascript");
    });
    
    server.onNotFound([](AsyncWebServerRequest* request)
    {
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.on("/effect", HTTP_POST, [](AsyncWebServerRequest* request)
    {
        if (request->hasParam("id"))
        {
            Serial.println("has param");
            Serial.println(request->getParam("id")->value());
            request->send(200);
            return;
        }

        request->send(400);
    });

    server.begin();
}


void loop() { }