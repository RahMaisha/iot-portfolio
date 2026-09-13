Task-01_BaseBroadcast.ino
#include <painlessMesh.h>

#define   MESH_PREFIX     "cse406"
#define   MESH_PASSWORD   "summer25"
#define   MESH_PORT       5555

painlessMesh mesh;
Scheduler userScheduler;

// ---- periodic broadcast task (random 1–5s) ----
Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, []() {
  String msg = String("Hello from ") + mesh.getNodeId() + " @ " + millis();
  mesh.sendBroadcast(msg);
  // randomize next interval 1–5s
  uint32_t nextS = random(1, 6);
  taskSendMessage.setInterval(TASK_SECOND * nextS);
  Serial.printf("[TX][BROADCAST] interval=%lus msg=%s\n", nextS, msg.c_str());
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
  randomSeed(analogRead(A0)); // simple entropy

  mesh.setDebugMsgTypes(ERROR | STARTUP); // minimal; add more if needed
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);

  mesh.onReceive(receivedCallback);
  mesh.onNewConnection(newConnectionCallback);
  mesh.onChangedConnections(changedConnectionCallback);
  mesh.onNodeTimeAdjusted(nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}
