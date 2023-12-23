// /*
//  * The firmware for the rMatrix project, as seen on https://www.rmatrix.xyz. 
//  * 
//  * Developed by Ryan Stewart, A.K.A. Ryn.
//  * 
//  * This firmware is licensed under the 
//  * Creative Commons Attribution-NonCommercial-ShareAlike (CC-BY-NC-SA)
//  * license: http://creativecommons.org/licenses/by-nc-sa/4.0/
//  * 
//  * This firmware can be modified and distributed, but can NOT be used for
//  * commerical use. The licensing also requires that you release any 
//  * modified works of this firmware under the same license.
//  * 
//  * This firmware is distributed "as is" and without any warranty.
//  * 
//  * Check the LICENSE.md file for details about licensing.
// */


// // ───────── ⋆⋅☆⋅⋆ ───────── //
// #include <Arduino.h>
// #include <constants.h>
// #include <secrets.h>
// #include <DNSServer.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266WiFi.h> 
// #include <public/index.h>
// // #include <WiFiClient.h>


// const char* WIFI_SSID = "Network Not Found";
// const char* WIFI_PASSWORD = "mikkagrrl";
// WiFiServer server(80);
// String header;


// void sendHTML()
// {

// }


// void setup()
// {
//     Serial.begin(SERIAL_SPEED);
    
//     // WiFi.mode(WIFI_AP_STA);
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("");
//     Serial.print("IP address: ");
//     Serial.println(WiFi.localIP());
    
//     // server.on("/", handleRoot);

//     server.begin();

//     // if (!SPIFFS.begin())
//     // {
//     //     Serial.println("SPIFFS failed to mount!");
//     // }
//     // else 
//     // {
//     //     Serial.println("SPIFFS was successfully mounted.");
//     // }

//     // server.serveStatic("/", SPIFFS, "/joystick.html"); 
//     // server.serveStatic("/virtualjoystick.js", SPIFFS, "/virtualjoystick.js");

//     // server.on("/jsData.html", handleJSData);
//     // server.begin();
// }


// void loop()
// {
//     WiFiClient client = server.accept();

//     if (client)
//     {
//         String currentLine = "";

//         if (client.available())
//         {
//             Serial.println(client.read());
//         }
//     }
// }