#include <esp_now.h>
#include <WiFi.h>

int EN1 = 5;
int EN2 = 18;
int F_R = 12;
int F_L = 14;
int B_R = 13;
int B_L = 15;
int speed = 150;

typedef struct message {
  char command[10];
} message;

message DATA;

void forward() {
  digitalWrite(F_R, HIGH);
  digitalWrite(F_L, HIGH);
  digitalWrite(B_R, LOW);
  digitalWrite(B_L, LOW);
}

void backward() {
  digitalWrite(F_R, LOW);
  digitalWrite(F_L, LOW);
  digitalWrite(B_R, HIGH);
  digitalWrite(B_L, HIGH);
}

void right() {
  digitalWrite(F_L, HIGH);
  digitalWrite(B_L, LOW);
  digitalWrite(F_R, LOW);
  digitalWrite(B_R, LOW);
}

void left() {
  digitalWrite(F_L, LOW);
  digitalWrite(B_L, LOW);
  digitalWrite(F_R, HIGH);
  digitalWrite(B_R, LOW);
}

void stop() {
  digitalWrite(F_R, LOW);
  digitalWrite(F_L, LOW);
  digitalWrite(B_R, LOW);
  digitalWrite(B_L, LOW);
}

void REC_DATA(const esp_now_recv_info *mac, const unsigned char *incomingData, int len) {
  memcpy(&DATA, incomingData, sizeof(DATA));
  Serial.print("Received: ");
  Serial.println(DATA.command);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  pinMode(F_R, OUTPUT);
  pinMode(F_L, OUTPUT);
  pinMode(B_R, OUTPUT);
  pinMode(B_L, OUTPUT);

  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW Initialized");
  }

  esp_now_register_recv_cb(REC_DATA);
}

void loop() {
  if (strcmp(DATA.command, "FORWARD") == 0) forward();
  else if (strcmp(DATA.command, "BACKWARD") == 0) backward();
  else if (strcmp(DATA.command, "RIGHT") == 0) right();
  else if (strcmp(DATA.command, "LEFT") == 0) left();
  else stop();

  delay(100);
}
