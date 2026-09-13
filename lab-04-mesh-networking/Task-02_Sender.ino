// Task-02_Sender.ino
#include <painlessMesh.h>

#define   MESH_PREFIX     "CSE406"
#define   MESH_PASSWORD   "summer25"
#define   MESH_PORT       5555

uint32_t TARGET_NODE_ID = 1163269996;  

painlessMesh mesh;
Scheduler userScheduler;

// periodic direct send every 3s (change as you like)
Task taskSendSingle(TASK_SECOND * 3, TASK_FOREVER, []() {
  if (TARGET_NODE_ID == 0) {
    Serial.println("[WARN] TARGET_NODE_ID not set. Edit the sketch!");
    return;
  }

  if (mesh.isConnected(TARGET_NODE_ID)) {
    String msg = String("Direct hello from ") + mesh.getNodeId() + " @ " + millis();
    bool ok = mesh.sendSingle(TARGET_NODE_ID, msg);
    Serial.printf("[TX][SINGLE] to=%u ok=%d msg=%s\n", TARGET_NODE_ID, ok, msg.c_str());
  } else {
    Serial.printf("[INFO] Target %u not connected yet. Retrying...\n", TARGET_NODE_ID);
  }
});

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("[RX] from=%u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> New Connection, nodeId=%u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("** Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("~~ Adjusted time. Offset=%ld ms\n", (long)offset);
}

void setup() {
  Serial.begin(115200);
  delay(200);

  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);

  mesh.onReceive(receivedCallback);
  mesh.onNewConnection(newConnectionCallback);
  mesh.onChangedConnections(changedConnectionCallback);
  mesh.onNodeTimeAdjusted(nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendSingle);
  taskSendSingle.enable();

  Serial.println("Tip: set TARGET_NODE_ID and re-upload to the SENDER node.");
}

void loop() {
  mesh.update();
}
