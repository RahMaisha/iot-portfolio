#include "painlessMesh.h"

#define MESH_PREFIX     "cse406"
#define MESH_PASSWORD   "summer25"
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh  mesh;

uint32_t targetNodeld = 1163269996;

void sendMessage() ;

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() {
  String msg = "Direct hello from Swarna and Maisha";
  msg += mesh.getNodeId();

  if (mesh.isConnected(targetNodeld)) {
    mesh.sendSingle(targetNodeld, msg);
    Serial.printf("Sent direct message to node %u: %s\n", targetNodeld, msg.c_str());
  } else {
    Serial.printf("Target node %u is not connected. Message not sent.\n", targetNodeld);
  }
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: %u Received from %u msg=%s\n", mesh.getNodeId(),from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);

  mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION | COMMUNICATION );

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}
