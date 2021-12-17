#include <Arduino.h>
#include "bugC.h"
#include <M5StickCPlus.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//bluetooth
//name M5-7443
//UUID: 1bc68b2a

BluetoothSerial SerialBT;

BUGC brouk;

int engine1 = 0;
int engine2 = 0;
int engine3 = 0;
int engine4 = 0;

void setup() {
  M5.begin();
  M5.Lcd.begin();
  brouk.Init();
  Serial.begin(38400);
  SerialBT.begin("Brouk", false);
  brouk.BugCSetAllSpeed(0, 0, 0, 0);
}

String message = "A5555";
String command[4];

void loop() {
  M5.Lcd.fillRect(0, 0, 135, 240, BLACK);
  if(SerialBT.available()){
    message = SerialBT.readStringUntil('F');
  }

  command[0] = message.charAt(3);
  command[1] = message.charAt(4);
  command[2] = message.charAt(5);
  command[3] = message.charAt(6);

  if (message.charAt(2) == 'A')
  {
    engine1 = 22 * ((int)command[0].toInt()) - 88;
    engine2 = 22 * ((int)command[1].toInt()) - 88;
    engine3 = 22 * ((int)command[2].toInt()) - 88;
    engine4 = 22 * ((int)command[3].toInt()) - 88;
  }
  else if(message.charAt(2) == 'B'){
    engine1 = 22 * ((int)command[0].toInt()) - 88;
    engine2 = 22 * ((int)command[1].toInt()) - 88;
    engine3 = -22 * ((int)command[2].toInt()) + 88;
    engine4 = -22 * ((int)command[3].toInt()) + 88;
  }
  else if(message.charAt(2) == 'C'){
    engine1 = 22 * ((int)command[0].toInt()) - 88;
    engine2 = -22 * ((int)command[1].toInt()) + 88;
    engine3 = 22 * ((int)command[2].toInt()) - 88;
    engine4 = -22 * ((int)command[3].toInt()) + 88;
  }

  //engine 1
  brouk.BugCSetSpeed(0, engine1);
  //engine 2
  brouk.BugCSetSpeed(1, engine2);
  //engine 3
  brouk.BugCSetSpeed(2, engine3);
  //engine 4
  brouk.BugCSetSpeed(3, engine4);

  M5.Lcd.setCursor(60, 5);
  M5.Lcd.println(engine1);
  M5.Lcd.setCursor(60, 20);
  M5.Lcd.println(engine2);
  M5.Lcd.setCursor(60, 40);
  M5.Lcd.println(engine3);
  M5.Lcd.setCursor(60, 60);
  M5.Lcd.println(engine4);



  M5.Lcd.setCursor(5, 5);
  M5.Lcd.print(message);
  message = "5555";
  //delay(50);
}