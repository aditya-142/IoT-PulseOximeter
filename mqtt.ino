#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define REPORTING_PERIOD_MS     10000 // Reporting every 10 seconds

PulseOximeter pox;
uint32_t tsLastReport = 0;

// Wi-Fi credentials
const char* ssid = "realme 6i";
const char* password = "12345678";

// Adafruit IO credentials
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "adisharma1400"
#define AIO_KEY         "key"

// Create an MQTT client
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Create an MQTT feed
Adafruit_MQTT_Publish pulseFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/pulse");
Adafruit_MQTT_Publish oxygenFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/oxygen");

void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Initialize MQTT connection
    mqtt.connect();

    Serial.println("Initializing pulse oximeter..");

    // Initialize sensor
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    // Configure sensor to use 7.6mA for LED drive
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback routine
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
    pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        if (pox.getHeartRate() != 0.0 && pox.getSpO2() != 0.0) {
            // If valid data is available, publish to Adafruit IO
            publishData(pox.getHeartRate(), pox.getSpO2());
        } else {
            Serial.println("Invalid data received. Skipping...");
        }

        tsLastReport = millis();
    }
}

void publishData(float pulse, float oxygen) {
    // Publish pulse data
    if (pulseFeed.publish(pulse)) {
        Serial.println("Pulse Data Published: " + String(pulse));
    } else {
        Serial.println("Failed to Publish Pulse Data");
    }

    // Publish oxygen data
    if (oxygenFeed.publish(oxygen)) {
        Serial.println("Oxygen Data Published: " + String(oxygen));
    } else {
        Serial.println("Failed to Publish Oxygen Data");
    }
}
