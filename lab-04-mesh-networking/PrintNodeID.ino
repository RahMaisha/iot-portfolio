// File: PrintNodeID.ino
#include <painlessMesh.h>

#define   MESH_PREFIX     "cse406"
#define   MESH_PASSWORD   "summer25"
#define   MESH_PORT       5555

painlessMesh mesh;

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
}

void loop() {
  mesh.update();
  static uint32_t last = 0;
  if (millis() - last > 2000) {
    last = millis();
    Serial.printf("My Node ID: %u\n", mesh.getNodeId());
  }
}
