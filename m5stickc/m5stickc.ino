#include <M5StickC.h>
#include <HijelHID_BLEMouse.h> 
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <WiFiManager.h> 

#include "index.h" 

HijelBLEMouse bleMouse("CogniLink Finger", "CogniLink");

WebServer server(80);
WebSocketsServer ws(81);

const float sensitivity = 0.6; 
const float deadzone = 1.2;    

float gx, gy, gz;
float offset_gx = 0, offset_gy = 0, offset_gz = 0;
int batteryPct = 100;

// --- Power Management Variables ---
unsigned long lastActivityTime = 0;
int currentBrightness = 20; 

TFT_eSprite canvas = TFT_eSprite(&M5.Lcd);

void configModeCallback(WiFiManager *myWiFiManager) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(5, 10);
  M5.Lcd.println("1. Scan QR");
  M5.Lcd.setCursor(5, 30);
  M5.Lcd.println("2. Sign In");
  M5.Lcd.setCursor(5, 50);
  M5.Lcd.println("3. Add WiFi");

  String qrString = "WIFI:S:" + myWiFiManager->getConfigPortalSSID() + ";T:nopass;;";
  M5.Lcd.qrcode(qrString, 85, 10, 60, 3);
}

void updateBatteryStatus() {
  float vbat = M5.Axp.GetBatVoltage();
  batteryPct = (int)((vbat - 3.0) / 1.2 * 100.0);
  if (batteryPct > 100) batteryPct = 100;
  if (batteryPct < 0) batteryPct = 0;

  if (bleMouse.isPaired()) {
    bleMouse.setBatteryLevel(batteryPct);
  }
}

void sendSensorData() {
  String json = "{";
  json += "\"gx\":" + String(gx, 2) + ",";
  json += "\"gy\":" + String(gz, 2) + ","; 
  json += "\"click\":" + String(M5.BtnA.isPressed() ? "true" : "false") + ",";
  json += "\"bat\":" + String(batteryPct);
  json += "}";
  ws.broadcastTXT(json);
}

void setup() {
  M5.begin();
  M5.IMU.Init();
  M5.Axp.ScreenBreath(currentBrightness); 
  M5.Lcd.setRotation(1);

  // --- CALIBRATION ROUTINE ---
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(20, 30);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Calibrating IMU...");
  M5.Lcd.setCursor(20, 45);
  M5.Lcd.setTextColor(TFT_ORANGE);
  M5.Lcd.println("Keep finger still!");
  
  delay(1000); 

  float temp_gx, temp_gy, temp_gz;
  int num_samples = 150;
  for (int i = 0; i < num_samples; i++) {
    M5.IMU.getGyroData(&temp_gx, &temp_gy, &temp_gz);
    offset_gx += temp_gx;
    offset_gy += temp_gy;
    offset_gz += temp_gz;
    delay(10);
  }
  offset_gx /= num_samples;
  offset_gy /= num_samples;
  offset_gz /= num_samples;

  // --- SMART WIFI SETUP ---
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback); 

  if (!wifiManager.autoConnect("CogniLink_Setup")) {
    delay(3000);
    ESP.restart(); 
  }

  canvas.createSprite(160, 80); 

  server.on("/", []() {
    server.send(200, "text/html", INDEX_HTML);
  });
  server.begin();
  ws.begin();

  bleMouse.begin();
  
  lastActivityTime = millis(); // Initialize activity timer
}

void drawUI() {
  static int offset = 0;
  canvas.fillSprite(BLACK);

  canvas.setCursor(5, 5);
  canvas.setTextColor(TFT_CYAN);
  canvas.setTextSize(1);
  canvas.print("WiFi: ");
  
  String ssid = WiFi.SSID();
  if(ssid.length() > 10) ssid = ssid.substring(0, 10) + "..";
  canvas.println(ssid);
  
  canvas.setCursor(5, 15);
  canvas.setTextColor(TFT_WHITE);
  canvas.println(WiFi.localIP().toString()); 

  canvas.setCursor(5, 27);
  if (bleMouse.isPaired()) {
    canvas.setTextColor(TFT_GREEN);
    canvas.println("BLE: Connected");
  } else {
    canvas.setTextColor(TFT_RED);
    canvas.println("BLE: Disconnected");
  }

  canvas.setCursor(110, 5);
  if (batteryPct < 20) canvas.setTextColor(TFT_RED);
  else if (batteryPct < 50) canvas.setTextColor(TFT_ORANGE);
  else canvas.setTextColor(TFT_GREEN);
  canvas.printf("Bat:%d%%", batteryPct);

  for (int x = 0; x < 160; x++) {
    int y = 60 + sin((x + offset) * 0.15) * 12;
    canvas.drawPixel(x, y, TFT_CYAN);
  }
  
  if (M5.BtnA.isPressed()) {
    canvas.fillCircle(145, 20, 6, TFT_ORANGE);
  } else {
    canvas.drawCircle(145, 20, 6, TFT_DARKGREY);
  }

  offset += 3;
  canvas.pushSprite(0, 0); 
}

void loop() {
  M5.update();
  server.handleClient();
  ws.loop();

  // --- WIFI RESET LOGIC (Accessible anytime) ---
  static unsigned long holdStart = 0;
  static bool isResetting = false;

  if (M5.BtnB.isPressed()) {
    if (!isResetting) {
      isResetting = true;
      holdStart = millis(); 
    }
    
    unsigned long heldTime = millis() - holdStart;

    canvas.fillSprite(BLACK);
    canvas.setCursor(10, 20);
    canvas.setTextColor(TFT_ORANGE);
    canvas.setTextSize(1);
    canvas.println("Wipe WiFi Data?");
    canvas.setCursor(10, 35);
    canvas.println("Keep holding button...");
    
    int progress = (heldTime * 160) / 5000; 
    if (progress > 160) progress = 160;
    canvas.fillRect(0, 60, progress, 15, TFT_RED);
    
    // Force screen awake if user initiates a reset while screen is asleep
    if (currentBrightness == 0) M5.Axp.ScreenBreath(30);
    canvas.pushSprite(0, 0);

    if (heldTime >= 5000) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(10, 35);
      M5.Lcd.setTextColor(TFT_RED);
      M5.Lcd.println("WIPING WIFI DATA...");
      WiFiManager wifiManager;
      wifiManager.resetSettings(); 
      delay(2000);
      ESP.restart(); 
    }
    
    lastActivityTime = millis(); // Reset sleep timer
    delay(20);
    return; 
  } else {
    if (isResetting) {
      isResetting = false; 
    }
  }

  // --- NORMAL OPERATION ---
  M5.IMU.getGyroData(&gx, &gy, &gz);
  gx -= offset_gx;
  gy -= offset_gy;
  gz -= offset_gz;

  updateBatteryStatus();

  // --- SMART SLEEP / WAKE LOGIC ---
  bool isActive = false;
  
  // Check if there is movement or button presses
  if (abs(gz) > deadzone || abs(gx) > deadzone) isActive = true;
  if (M5.BtnA.isPressed()) isActive = true;

  if (isActive) {
    lastActivityTime = millis();
    if (currentBrightness != 30) {
      currentBrightness = 30; // Full brightness
      M5.Axp.ScreenBreath(currentBrightness);
    }
  } else {
    unsigned long idleTime = millis() - lastActivityTime;
    
    if (idleTime > 60000) { // 60 seconds: Turn Off
      if (currentBrightness != 0) {
        currentBrightness = 0;
        M5.Axp.ScreenBreath(0);
      }
    } else if (idleTime > 30000) { // 30 seconds: Dim Display
      if (currentBrightness != 9) {
        currentBrightness = 9; // Very dim
        M5.Axp.ScreenBreath(currentBrightness);
      }
    }
  }

  // --- BLE MOUSE CONTROL ---
  if (bleMouse.isPaired()) {
    int moveX = 0;
    int moveY = 0;
    
    if (abs(gz) > deadzone) {
      moveX = (int)(gz * sensitivity);
    }
    if (abs(gx) > deadzone) {
      moveY = (int)(gx * sensitivity); 
    }

    if (moveX != 0 || moveY != 0) {
      bleMouse.move(-moveX, -moveY); 
    }

    if (M5.BtnA.wasPressed()) {
      bleMouse.press(MouseButton::Left);
    }
    if (M5.BtnA.wasReleased()) {
      bleMouse.release(MouseButton::Left);
    }
  }

  sendSensorData();
  
  // Only draw the screen graphics if the screen is actually turned on! 
  // This saves a lot of battery processing power while the user is resting.
  if (currentBrightness > 0) {
    drawUI();
  }

  delay(20); 
}