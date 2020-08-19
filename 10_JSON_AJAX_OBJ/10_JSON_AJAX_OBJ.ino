#include <WiFi.h>
#include "index.h"
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
const char* ssid     = "TP-LINK-MCU";     
const char* password = "15253545";  

WiFiServer server(80);

String HTTP_req;   // stores the HTTP request

int analog_val;

String convert_char = index_page; 

void setup(){
  Serial.begin(115200);
  delay(10);
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

int value = 0;

void loop(){
 
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    //Serial.println("-------------");           // print a message out the serial port
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: keep-alive");
                    client.println();
                    // AJAX request....
                    if (HTTP_req.indexOf("request") > -1) {  // 192.168.2.113/request

                    // client.println("Content-Type: application/json");
                    // client.println("Connection: close");
                     client.print("{\"name\":\"VEDAT BALOĞLU\", \"year\":\"2020\",\"city\":\"İSTANBUL\"}");
                      
                    }
                    else {  // HTTP request for web page
                      
                      client.println(convert_char); 
            
                    }
                    // display received HTTP request on serial port
                    Serial.print(HTTP_req);
                    HTTP_req = "";            // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    currentLineIsBlank = true;   // last character on line of received text  
                }                                // starting new line with next character read
                else if (c != '\r') {
                    currentLineIsBlank = false;  // a text character was received from client
                }
            } // ******* end if (client.available())
        }  // ********** end while (client.connected())

    delay(1);  
    client.stop();
    Serial.println("************");
  }
}
