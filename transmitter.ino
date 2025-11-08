#include <WiFi.h>
#include <Wire.h>
#include <esp_now.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
int x, y;

// Replace with your receiver’s MAC Address
uint8_t broadcastAddress[] = {0x3C, 0x8A, 0x1F, 0xBA, 0x1C, 0x00};

typedef struct message {
  char command[10];
} message;

message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  Serial.println(sendStatus == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not connected!");
    while (1);
  }
  delay(1000);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) == ESP_OK) {
    Serial.println("Peer added successfully");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.println("MPU6050 Ready...");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  x = map(a.acceleration.x, -9, 9, -10, 10);
  y = map(a.acceleration.y, -9, 9, -10, 10);

  if (x < -4) strcpy(myData.command, "FORWARD");
  else if (x > 4) strcpy(myData.command, "BACKWARD");
  else if (y < -4) strcpy(myData.command, "LEFT");
  else if (y > 4) strcpy(myData.command, "RIGHT");
  else strcpy(myData.command, "STOP");

  esp_err_t res = esp_now_send(broadcastAddress, (uint8_t*)&myData, sizeof(myData));

  if (res == ESP_OK)
    Serial.println(myData.command);
  else
    Serial.println("Send Failed");

  delay(100);
}
