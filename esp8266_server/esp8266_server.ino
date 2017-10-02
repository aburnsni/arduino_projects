#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "wifisettings.h"
#include <ESP8266WebServer.h>
#include <FS.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
ESP8266WebServer server(80);

void setup() {
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  delay(200);

  // We start by connecting to a WiFi network
  lcd.setCursor(0, 0);
  lcd.print("Connecting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int i = 4;
  while (WiFi.status() != WL_CONNECTED) { // Wait for WIFI to connect
    delay(500);
    Serial.print(".");
    if (i < 4) {
      lcd.setCursor(10 + i, 0);
      lcd.print (".");
      i++;
    } else {
      lcd.setCursor(10, 0);
      lcd.print ("    ");
      i = 0;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(WiFi.localIP());
  lcd.print("         ");

  lcd.setCursor(0,1);
  if (!SPIFFS.begin())
  {
    // Serious problem
    lcd.print("SPIFFS mnt Fail");
  } else {
    lcd.print("SPIFFS Mounted");
  }

  delay(2000);
  setupPageHandlers();  //  Set page handlers
 
  server.begin();
  lcd.setCursor(0,1);
  lcd.print("Server ready    ");
}

void loop() {
  server.handleClient();
}

void setupPageHandlers() {
  server.serveStatic("/", SPIFFS, "/index.html");
  server.serveStatic("/css/style.css", SPIFFS, "/css/style.css");
}

