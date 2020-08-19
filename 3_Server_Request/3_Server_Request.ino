#include <WiFi.h>
/*
 Hello 
 I design developer tools for embedded electronic systems. You can buy my projects design files.
 https://www.altiumdesignerprojects.com
*/
const char* ssid     = "TP-LINK-MCU";     
const char* password = "15253545";  

WiFiServer server(80);

String HTTP_req;            // stores the HTTP request
    
void setup()
{
  Serial.begin(115200);

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
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
    
  server.begin();
}

void loop()
{
    WiFiClient client = server.available();  // try to get client

    if (client) {  // got client?
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
                    if(HTTP_req.indexOf("req") > -1){  // 192.168.2.50/req

                        client.println("<br><h1>Altium Designer Projects</h1>"); 
                        client.println("<br><h1>www.altiumdesignerprojects.com</h1>");

                    }else{  // HTTP request for web page  // send web page - contains JavaScript with AJAX calls

                        client.println("<!DOCTYPE html>");
                        client.println("<html><body><h1>The XMLHttpRequest Object</h1>");
                        client.println("<!DOCTYPE html>");
                        client.println("<button type=\"button\" onclick=\"loadDoc()\">AJAX DATA</button> ");
                        client.println("<br/><p><div id=\"demo\"></div></p> ");
                        client.println("<script>");
                        client.println("function loadDoc(){");
                        client.println("var xhttp = new XMLHttpRequest();");
                        client.println("xhttp.onreadystatechange = function(){");
                        client.println("if (this.readyState == 4 && this.status == 200){document.getElementById(\"demo\").innerHTML = this.responseText;}}; ");
                        client.println("xhttp.open(\"GET\", \"req\", true);");
                        client.println("xhttp.send(null);");
                        client.println("}");
                        client.println("</script>");
                        client.println("</body>");
                        client.println("</html>");
                    }
                    
                    Serial.print(HTTP_req);   // display received HTTP request on serial port
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
        delay(1);      // ******* give the web browser time to receive the data
        client.stop(); // ******* close the connection
    } // ********* end if (client)
}
