#include<ESP8266WebServer.h>  //ESP WebServer library

ESP8266WebServer server;  //Declaring ESP8266WebServer as server

//Access point credentials
const char username[] = "<Username>";   //Username for Access Point
const char password[] = "<Password>";   //Password for Access Point

#define pin 16  //Declaring 16 as pin

void setup() {
  pinMode(pin,OUTPUT);  //Setting pin 16 as output
  Serial.begin(115200); //Set baudrate to 115200 bps

  WiFi.softAP(username,password); //Setting up access point
  IPAddress myIP = WiFi.softAPIP(); //fetching IP address
  Serial.print("AP IP Address: ");
  Serial.println(myIP); //Printing the IP address

  server.begin(); //Starts the server
  server.on("/led",led);  //When server receives a request "IP Address/led", it calls the led() function
  }

void loop(){
  server.handleClient();  //Endlessly check for requests by clients
}

void led() {
  String myHTML = "<html><head><title>LED IOT</title></head><body style=\"background-color: skyblue\"><h1><center>LED IOT</center></h1><form><center><button type=\"submit\" name=\"state\" value=\"0\">LED ON</button></center></form><form><center><button type=\"submit\" name=\"state\" value=\"1\">LED OFF</button></center></form></body></html>";  //HTML code for the webpage

  server.send(200,"text/html",myHTML);  //Send the HTML code to Node MCU. Code 200 corresponds to "no error"

  if (server.arg("state")=="0"){  //if server argument "state" is 0
    digitalWrite(pin,0);  //LED ON
  }
  else{
    digitalWrite(pin,1);  //LED OFF
  }
}
