# 📟 ESP32 Smart Sensor Menu System

A simple and interactive embedded system project built using **ESP32**, featuring a menu-driven interface on an **OLED display**. The system allows users to navigate through different environmental parameters and control a relay using keyboard input via serial communication.

---

## 🚀 Features

* 📺 OLED-based menu UI (0.96" SSD1306)
* ⌨️ Keyboard navigation via Serial Monitor
* 🌡️ Temperature monitoring (DHT11)
* 💧 Humidity monitoring (DHT11)
* 💡 Light intensity measurement (LDR)
* 🔌 Relay control (ON/OFF)
* 🧭 Menu navigation (Up / Down / Select / Back)

---

## 🎮 Controls

| Key | Function  |
| --- | --------- |
| `w` | Move Up   |
| `s` | Move Down |
| `e` | Select    |
| `b` | Back      |

---

## 🧰 Hardware Components

* ESP32
* 0.96" OLED Display (SSD1306, I2C)
* DHT11 Sensor
* LDR (Light Dependent Resistor)
* Relay Module
* Jumper Wires

---

## 🔌 Pin Configuration

| Component | ESP32 Pin |
| --------- | --------- |
| OLED SDA  | GPIO 21   |
| OLED SCL  | GPIO 22   |
| DHT11     | GPIO 4    |
| LDR       | GPIO 34   |
| Relay     | GPIO 5    |

---

## 📦 Libraries Required

Install the following libraries via Arduino IDE:

* Adafruit SSD1306
* Adafruit GFX
* DHT sensor library

---

## ⚙️ How It Works

* The ESP32 receives keyboard input via serial communication.
* A menu is displayed on the OLED screen.
* Users navigate through options using keyboard keys.
* Selected sensor data is displayed in real time.
* Relay can be toggled ON/OFF through the interface.

---

## 🖥️ Setup Instructions

1. Connect all components as per the pin configuration.
2. Install required libraries in Arduino IDE.
3. Upload the code to ESP32.
4. Open Serial Monitor:

   * Baud Rate: `9600`
   * Select "No Line Ending"
5. Use keyboard keys (`w`, `s`, `e`, `b`) to navigate.

---

## ⚠️ Troubleshooting

* OLED not working? Check I2C address (`0x3C` or `0x3D`)
* Ensure correct wiring (SDA → GPIO21, SCL → GPIO22)
* Try powering OLED with 5V if not working on 3.3V
* Run an I2C scanner to verify connection

---

## 🔮 Future Improvements

* 📊 Graphical data visualization
* 🌐 Web-based control using WiFi
* 📱 Mobile app integration
* 🔔 Alert system (buzzer/notifications)
* 🌡️ Smart automation (auto relay triggers)

---

## 📄 License

This project is open-source and free to use for educational purposes.

---

## 👨‍💻 Author

Developed as an embedded systems project using ESP32.
