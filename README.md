## Pulse Oximeter using IoT project Summary

**IoT-based Health Monitoring System**

Designed and implemented an IoT-based health monitoring system that measures pulse rate and blood oxygen levels using a MAX30100 Pulse Oximeter sensor and transmits the data to Adafruit IO for remote monitoring. This project utilized Wi-Fi connectivity for real-time data publishing and MQTT protocol for data communication.

**Key Contributions:**
- **Sensor Integration:** Integrated the MAX30100 Pulse-Oximeter sensor to capture pulse and blood oxygen saturation data.
- **IoT Connectivity:** Established Wi-Fi connectivity to link the system with the internet, ensuring seamless data transmission.
- **MQTT Communication:** Implemented MQTT protocol to publish health data (pulse rate and SpO2 levels) to Adafruit IO, enabling remote health monitoring.
- **Data Handling:** Developed robust routines to handle sensor data acquisition and periodic reporting with a 10-second interval, ensuring reliable data updates.
- **Web page:** Created web page to get live data directly from sensor.

**Technologies Used:**
- Arduino IDE for firmware development
- MAX30100 Pulse Oximeter for biometric data acquisition
- ESP32 Wi-Fi module for internet connectivity
- Adafruit IO for cloud data storage and visualization
- MQTT protocol for efficient data communication
- HTML and CSS for web page development to show live updates




Circuit connections:


![spo2_monitor](https://github.com/aditya-142/IoT-PulseOximeter/assets/105287623/32abb247-3494-4ca0-b43b-a941346d04b1)
