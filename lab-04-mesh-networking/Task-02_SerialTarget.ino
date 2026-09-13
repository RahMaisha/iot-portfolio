// Task_2_SerialTarget.ino
#include <painlessMesh.h>

#define   MESH_PREFIX     "CSE406"
#define   MESH_PASSWORD   "summer25"
#define   MESH_PORT       5555

painlessMesh mesh;
Scheduler userScheduler;
uint32_t TARGET_NODE_ID = 1163269996;

Task taskSendSingle(TASK_SECOND * 3, TASK_FOREVER, []() {
  if (TARGET_NODE_ID == 0) return;
  if (mesh.isConnected(TARGET_NODE_ID)) {
    String msg = String("Direct hello from ") + mesh.getNodeId() + " @ " + millis();
    bool ok = mesh.sendSingle(TARGET_NODE_ID, msg);
    Serial.printf("[TX][SINGLE] to=%u ok=%d msg=%s\n", TARGET_NODE_ID, ok, msg.c_str());
  } else {
    Serial.printf("[INFO] Target %u not connected.\n", TARGET_NODE_ID);
  }
});

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("[RX] from=%u msg=%s\n", from, msg.c_str());
}

void parseSerial() {
  static String line;
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      line.trim();
      if (line.startsWith("set ")) {
        String idStr = line.substring(4);
        TARGET_NODE_ID = (uint32_t) strtoul(idStr.c_str(), nullptr, 10);
        Serial.printf("[CMD] TARGET_NODE_ID set to %u\n", TARGET_NODE_ID);
      } else if (line == "whoami") {
        Serial.printf("[CMD] My Node ID: %u\n", mesh.getNodeId());
      } else if (line == "now") {
        if (TARGET_NODE_ID) {
          String msg = String("Manual ping from ") + mesh.getNodeId();
          mesh.sendSingle(TARGET_NODE_ID, msg);
          Serial.println("[CMD] Sent immediate message.");
        }
      } else {
        Serial.println("[CMD] Usage: set <nodeId> | whoami | now");
      }
      line = "";
    } else {
      line += c;
    }
  }
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(receivedCallback);

  userScheduler.addTask(taskSendSingle);
  taskSendSingle.enable();

  Serial.println("Commands: set <nodeId>, whoami, now");
}

void loop() {
  mesh.update();
  parseSerial();
}
