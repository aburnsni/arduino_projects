#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "wifisettings.h"
#include <ESP8266WebServer.h>
#include <FS.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
ESP8266WebServer server(80);

unsigned long startMillis = 0;
unsigned long wifitimout = 20000;

void setup() {
  Serial.begin(115200);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight

  // We start by connecting to a WiFi network
  lcd.setCursor(0, 0);
  lcd.print("Connecting");
  Serial.println("connecting");
  WiFi.mode(WIFI_STA);
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(ssidh);
  for (int i = strlen(ssidh)+3; i < 16; i=i+1) {
    Serial.print(strlen(ssidh));
    lcd.print(" ");
  }
  // lcd.print("             ");
  Serial.println("Home");
  wifiConnect(ssidh, passwordh);

  if (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 1); 
    lcd.print("W: "); 
    lcd.print(ssidw);
    for (int i = strlen(ssidw)+3; i < 16; i=i+1) {
      Serial.print(strlen(ssidw));
      lcd.print(" ");
    }
    Serial.println("Work");
    wifiConnect(ssidw, passwordw);
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

void wifiConnect(const char* ssid, const char* password) {
  startMillis = millis();
  Serial.print("SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int i = 4;
  while ((WiFi.status() != WL_CONNECTED) && (millis() - startMillis < wifitimout)) { // Wait for WIFI to connect
    delay(500);
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
}

void setupPageHandlers() {
  server.serveStatic("/", SPIFFS, "/index.html");
  server.serveStatic("/css/style.css", SPIFFS, "/css/style.css");
}

