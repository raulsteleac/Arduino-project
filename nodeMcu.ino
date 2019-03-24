#include <ESP8266WiFi.h>
 
const char* ssid = "AndroidAP6213";
const char* password = "26101997";
 
 int pin=D8;
int ledPin = BUILTIN_LED; // GPIO13
int pin2=D7;
int pin3=D6;
int pin4=D5;
int pin5=D4;
int pin6=D3;
WiFiServer server(80);
String request="/STOP";

void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(pin, OUTPUT); 
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request 
int value = 0;

if (request.indexOf("/FATA") != -1)  
{
    value = 1;  
    analogWrite(pin,200);
    analogWrite(pin2,0);
    analogWrite(pin3,0);
    analogWrite(pin4,0);
    analogWrite(pin5,0);
    analogWrite(pin6,0);
 }
 if (request.indexOf("/STANGA") != -1) 
 {
    value = 2;  
    analogWrite(pin,0);
    analogWrite(pin2,0);
    analogWrite(pin3,200);
    analogWrite(pin4,0);
    analogWrite(pin5,0);
    analogWrite(pin6,0);
  }
if (request.indexOf("/DREAPTA") != -1)  
{
  value = 3;  
  analogWrite(pin,0);
  analogWrite(pin2,0);
  analogWrite(pin3,0);
  analogWrite(pin4,200);
  analogWrite(pin5,0);
  analogWrite(pin6,0);
} 
if (request.indexOf("/SPATE") != -1)  
{
  value = 4;  
  analogWrite(pin,0);
  analogWrite(pin2,200);
  analogWrite(pin3,0);
  analogWrite(pin4,0);
  analogWrite(pin5,0);
  analogWrite(pin6,0);
}
if (request.indexOf("/STOP") != -1)  
{
   value =5;  
   analogWrite(pin,0);
   analogWrite(pin2,0);
   analogWrite(pin3,0);
   analogWrite(pin4,0);
   analogWrite(pin5,200);
   analogWrite(pin6,0);
}
  if (request.indexOf("/CANTA") != -1)  
 {
  value =6;  
  analogWrite(pin,0);
  analogWrite(pin2,0);
  analogWrite(pin3,0);
  analogWrite(pin4,0);
  analogWrite(pin5,0);
  analogWrite(pin6,200);
 }

 //Html code for all the pages that construct the different states of the robot 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<style>"
"body {    background-color: #363636;"
"    background-image:         linear-gradient(45deg, hsla(0,0%,0%,.25) 25%, transparent 25%, transparent 75%, hsla(0,0%,0%,.25) 75%, hsla(0,0%,0%,.25)), "
 "                             linear-gradient(45deg, hsla(0,0%,0%,.25) 25%, transparent 25%, transparent 75%, hsla(0,0%,0%,.25) 75%, hsla(0,0%,0%,.25));"
  "  background-position:0 0, 2px 2px;"
   " background-size:4px 4px;"
  
"}"
"button {"
   "margin-left: 2cm;"
"}"
"button:hover,"
"button:active {"
 "   outline: 0;"
"}"

/* 3D Button */

"button.depth {"
 "   background: #444;"
  "  border: none;"
   " border-radius: 80px;"
    "box-shadow: inset 0 0 2px 2px hsla(0,0%,0%,.2),"
     "           inset 0 0 2px 4px hsla(0,0%,0%,.2),"
      "          inset 0 0 2px 6px hsla(0,0%,0%,.2),"
       "         inset 0 0 1px 8px hsla(0,0%,0%,.5),"
        "       inset 0 1px 1px 8px hsla(0,0%,100%,.25),"
         "       inset 0 -30px 30px hsla(0,0%,0%,.2),"
          "      0 -4px 8px 4px hsla(0,0%,0%,.5),"
           "     0 10px 10px hsla(0,0%,0%,.25),"
            "    0 0 2px 2px hsla(0,0%,0%,.2),"
             "   0 0 2px 4px hsla(0,0%,0%,.2),"
              "  0 0 2px 6px hsla(0,0%,0%,.2),"
               " 0 0 2px 8px hsla(0,0%,0%,.5),"
               " 0 1px 2px 8px hsla(0,0%,100%,.25),"
               " 0 -1px 2px 8px hsla(0,0%,0%,.5);"
"    color: #303030;"
 "   cursor: pointer;"
  "  font: bold 85px/85px sans-serif;"
  "  height: 300px;"
  "width:400px;"
  "  padding:50px 70px;"
  "  text-shadow: 0 1px 1px hsla(0,0%,100%,.25),"
  "               0 -1px 1px hsla(0,0%,0%,.75);"
"}"

"button.depth:focus {"
"    color: #0ab;"
"    text-shadow: 0 0 20px hsla(240,75%,75%,.5),"
 "                0 1px 1px hsla(0,0%,100%,.25),"
 "                0 -1px 1px hsla(0,0%,0%,.75);"
"}"
"button.depth:active {"
 "   box-shadow: inset 0 0 2px 2px hsla(0,0%,0%,.2),"
 "               inset 0 0 2px 4px hsla(0,0%,0%,.2),"
 "               inset 0 0 2px 6px hsla(0,0%,0%,.2),"
 "               inset 0 0 1px 7px hsla(0,0%,0%,.5),"
 "               inset 0 5px 15px 7px hsla(0,0%,0%,.15),"
 "               inset 0 -4px 2px 3px hsla(0,0%,0%,.5),"
 "               inset 0 1px 1px 7px hsla(0,0%,100%,.25),"
 "               inset 0 -30px 30px hsla(0,0%,0%,.1),"
 "               inset 0 30px 30px hsla(0,0%,0%,.2),"
 "               0 -4px 8px 4px hsla(0,0%,0%,.5),"
 "               0 5px 10px hsla(0,0%,0%,.25),"
 "               0 0 2px 2px hsla(0,0%,0%,.2),"
 "               0 0 2px 4px hsla(0,0%,0%,.2),"
 "               0 0 2px 6px hsla(0,0%,0%,.2),"
  "              0 1px 2px 8px hsla(0,0%,100%,.25),"
   "             0 -1px 2px 8px hsla(0,0%,0%,.5);"
    "line-height: 86px;"
"}"
"p{margin-left=4cm;}"

"</style>");
 

  client.println("<br><br>");
  client.println("<a href=\"/FATA\"\"><button class='depth'>&#8593;</button></a>");
  client.println("<br><br>");
  client.println("<a href=\"/STANGA\"\"><button class='depth'>&#8592;</button></a>");  
  client.println("</html>");
  client.println("<a href=\"/DREAPTA\"\"><button class='depth'>&#8594;</button></a>");  
  client.println("</html>");
  client.println("<br><br>");
  client.println("<a href=\"/SPATE\"\"><button class='depth'>&#8595;</button></a>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/STOP\"\"><button class='depth'>STOP</button> </a>");
  client.println("<a href=\"/CANTA\"\"><button class='depth'>CANTA</button> </a>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
