#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
// ESP32 default I2C: SDA = 21, SCL = 22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT Configuration
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Hardware Pins
#define LDR_PIN 34
#define RELAY_PIN 5

// Menu Logic
int menuIndex = 0;
int screen = 0; // 0 = menu, 1 = data
bool relayState = false;

String menuItems[] = {
  "Temperature",
  "Humidity",
  "Light (LDR)",
  "Relay Control"
};

void setup() {
  // Use 115200 baud in your Serial Monitor
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();

  // Initialize I2C for ESP32
  Wire.begin(21, 22);

  // Initialize OLED (Address 0x3C is most common)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed. Check wiring or address."));
    for (;;); 
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
  
  Serial.println(F("System Booted."));
  Serial.println(F("Controls: Type 'w' (up), 's' (down), 'e' (select), 'b' (back) + Press ENTER"));
}

void loop() {
  char key = 0;

  // Check for Serial Input
  if (Serial.available() > 0) {
    key = Serial.read();
    
    // Logic for Screen Switching
    if (screen == 0) {
      if (key == 'w') menuIndex--;
      if (key == 's') menuIndex++;
      if (key == 'e') screen = 1;
      
      // Keep index in bounds
      if (menuIndex < 0) menuIndex = 3;
      if (menuIndex > 3) menuIndex = 0;
    } 
    else {
      if (key == 'b') screen = 0;
    }
  }

  // Refresh Display every loop
  display.clearDisplay();
  if (screen == 0) {
    drawMenu();
  } else {
    drawSubmenu(key);
  }
  display.display();

  delay(50); // Fast enough for smooth interaction
}

// ================= DRAWING FUNCTIONS =================

void drawMenu() {
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("--- MAIN MENU ---"));
  display.println(F(""));

  for (int i = 0; i < 4; i++) {
    if (i == menuIndex) {
      display.print(F("> "));
    } else {
      display.print(F("  "));
    }
    display.println(menuItems[i]);
  }

  display.setCursor(0, 53);
  display.println(F("W/S:Move  E:Select"));
}

void drawSubmenu(char key) {
  display.setCursor(0, 0);
  
  switch (menuIndex) {
    case 0: // Temperature
      display.setTextSize(1);
      display.println(F("Temperature:"));
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.print(dht.readTemperature());
      display.println(F(" C"));
      break;

    case 1: // Humidity
      display.setTextSize(1);
      display.println(F("Humidity:"));
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.print(dht.readHumidity());
      display.println(F(" %"));
      break;

    case 2: // LDR
      display.setTextSize(1);
      display.println(F("Light Level (LDR):"));
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.print(analogRead(LDR_PIN));
      break;

    case 3: // Relay
      if (key == 'e') {
        relayState = !relayState;
        digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
      }
      display.setTextSize(1);
      display.println(F("Relay Control:"));
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.println(relayState ? F("ON") : F("OFF"));
      display.setTextSize(1);
      display.setCursor(0, 43);
      display.println(F("Press E to Toggle"));
      break;
  }

  display.setTextSize(1);
  display.setCursor(0, 55);
  display.println(F("B: Back to Menu"));
}
