#include <SoftwareSerial.h>

SoftwareSerial ec200u(9, 5); // RX, TX

String APN = "your sim";
String URL = "https://script.google.com/macros/s/your google sheet api/exec";
String TOKEN = "iot-secret-123";

String lastResponse = ""; // HTTP buffer

void setup() {
  Serial.begin(115200);
  ec200u.begin(115200);
  delay(5000);

  Serial.println("\n=== Booting EC200U ===");
  sendAT("AT");
  sendAT("ATE0");

  sendAT("AT+CPIN?");
  sendAT("AT+CSQ");
  sendAT("AT+CREG?");
  sendAT("AT+QNWINFO");

  Serial.println("\n=== Setting APN ===");
  sendAT("AT+QICSGP=1,1,\"" + APN + "\",\"\",\"\",1");
  sendAT("AT+QIACT=1");
  delay(3000);

  Serial.println("\n=== Configuring HTTPS SSL ===");
  sendAT("AT+QSSLCFG=\"seclevel\",1");
  sendAT("AT+QHTTPCFG=\"sslctxid\",1");
  sendAT("AT+QHTTPCFG=\"responseheader\",1");
  // Make sure CA certificate is uploaded: AT+QFUPL="RAM:ca.pem",...
  delay(3000);

  Serial.println("\n===== STEP 1: GET MESSAGE FROM CLOUD =====");
  getMessage();
  delay(3000);

  Serial.println("\n===== STEP 2: POST ACK TO CLOUD =====");
  sendMessage("ACK Received");
}

void loop() {
  // nothing
}

/////////////////////////////////////////////////////
// GET + Print cloud message (plain text)
/////////////////////////////////////////////////////
void getMessage() {
  String fullURL = URL + "?token=" + TOKEN + "&noredirect=true";

  Serial.println("\n=== HTTP GET ===");
  Serial.println(fullURL);

  // Set URL
  sendAT("AT+QHTTPURL=" + String(fullURL.length()) + ",80");
  ec200u.println(fullURL);
  delay(2500);

  // Start GET request
  sendAT("AT+QHTTPGET=80");
  delay(4000);

  // Read HTTP response
  sendATcapture("AT+QHTTPREAD=80");

  Serial.println("\n=== RAW HTTP RESPONSE ===");
  Serial.println(lastResponse);

  // Plain text response
  String reply = lastResponse;
  reply.trim(); // remove newlines

  if (reply.length()) {
    Serial.print("\nCloud says: ");
    Serial.println(reply);
  } else {
    Serial.println("\n❌ No valid reply found!");
  }
}

/////////////////////////////////////////////////////
// POST to cloud (JSON)
/////////////////////////////////////////////////////
void sendMessage(String msg) {
  String json = "{\"token\":\"" + TOKEN + "\",\"message\":\"" + msg + "\"}";

  Serial.println("\n=== HTTP POST ===");
  Serial.println(json);

  // Set URL
  sendAT("AT+QHTTPURL=" + String(URL.length()) + ",80");
  ec200u.println(URL);
  delay(2500);

  // Start POST request
  sendAT("AT+QHTTPPOST=" + String(json.length()) + ",80,80");
  ec200u.println(json);
  delay(4000);

  // Read HTTP response
  sendATcapture("AT+QHTTPREAD=80");

  Serial.println("\n=== POST RESPONSE ===");
  Serial.println(lastResponse);
}

/////////////////////////////////////////////////////
// AT Helper (capture full response)
/////////////////////////////////////////////////////
void sendATcapture(String cmd) {
  lastResponse = "";
  ec200u.println(cmd);

  unsigned long timeout = millis() + 15000; // 15 sec timeout
  while (millis() < timeout) {
    while (ec200u.available()) {
      char c = ec200u.read();
      lastResponse += c;
      Serial.write(c);
    }
    // Optional: break if HTTP status received
    if (lastResponse.indexOf("+QHTTPREAD:") >= 0) break;
  }
}

/////////////////////////////////////////////////////
// Normal AT Helper
/////////////////////////////////////////////////////
void sendAT(String cmd) {
  ec200u.println(cmd);
  delay(900);
  while (ec200u.available()) {
    Serial.write(ec200u.read());
  }
}
