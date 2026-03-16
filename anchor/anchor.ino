#include <SPI.h>
#include "DW1000Ranging.h"
#include "DW1000.h"

#define PIN_RST  27
#define PIN_IRQ  34
#define PIN_SS    4

void newRange();
void newDevice(DW1000Device* d);
void inactiveDevice(DW1000Device* d);

void setup() {
  Serial.begin(115210);
  delay(1000);
  SPI.begin(18, 19, 23, PIN_SS);
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
  DW1000.setAntennaDelay(16520);
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  DW1000Ranging.startAsAnchor("84:00:5B:D5:A9:9A:E2:9C",
                               DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
  Serial.println("Anchor ready");
}

void loop() { DW1000Ranging.loop(); }

void newRange() {
  Serial.print("[Anchor] Distance: ");
  Serial.print(DW1000Ranging.getDistantDevice()->getRange(), 3);
  Serial.println(" m");
}
void newDevice(DW1000Device* d) {
  Serial.print("Tag connected: 0x");
  Serial.println(d->getShortAddress(), HEX);
}
void inactiveDevice(DW1000Device* d) {
  Serial.print("Tag lost: 0x");
  Serial.println(d->getShortAddress(), HEX);
}
