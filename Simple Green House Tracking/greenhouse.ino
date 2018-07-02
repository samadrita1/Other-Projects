
#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include<dht.h>
dht DHT;

// if you require to change the pin number, Edit the pin with your arduino pin.

#define DHT11_PIN D3
WiFiServer server(81); // Setting the Server Port

HTTPClient http;

/* Function to get settings from database online. */

String SendSettings(String strH, String strT)
{
  String  httpurl;
  server.begin(); // Tells the server to begin listening for incoming connections.
  //  httpurl="http://192.168.225.180:81/iotserver/put.php?hum=$strH&temp=$strT";
  httpurl="http://127.0.0.1/put.php?hum=";
 httpurl+=strH;
 //httpurl+="&temp=";
 //httpurl+=strT;
   
  http.begin(httpurl);
  http.GET();
  
  String result=http.getString();
  http.end();
  
  return result;
}


/* Put your setup code here, to run once:*/
void setup()
{
pinMode(D2,INPUT);
  pinMode(D3,INPUT);
  int i=0;

 // pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  
  WiFi.disconnect(); // To disconnect any previously connected WIFI/Access Point.
  delay(1000); // Delay before connecting again to WIFI/Access Point.

  /*
   * SSID: Your WIFI SSID (e.g. "mywifi")
   * PASSWORD: Your WIFI Password (e.g. "mywifipswd")
   */
  WiFi.begin("moto","qwertyqwerty"); // To start the WIFI connection.

  Serial.print("\n\nConnecting");
  while (!(WiFi.status() == WL_CONNECTED))
  {
    /* To check whether wifi is connected or not. 
     * If NOT, The while loop will continue trying to connect to the WIFI/Access Point with a delay.
     * If YES, The while loop will end.
     */
    delay(300);
    Serial.print(".");
    i++;
    if(i>50){break;}
  }
  Serial.print(localIP());
  if(WiFi.status()==WL_CONNECTED)
  {
    Serial.println("\nConnected");
    /*Sending settings to updateon the server*/
  }
  else
  {
    Serial.println("Not Connected");
  }
}

/* Put your main code here, to run repeatedly: */
void loop()
{ String data;
  int chk = DHT.read11(DHT11_PIN);

Serial.println(" Humidity " );

Serial.println(DHT.humidity, 1);
float H=DHT.humidity;
Serial.println(" Temparature ");
float T=DHT.temperature;
Serial.println(DHT.temperature, 1);
//data=Serial.readString();
    data=digitalRead(D2);
    Serial.print("Sil data");
    Serial.print(data);
delay(2000);
 
  String Hstr = String(H);
  String Tstr = String(T);
    
    SendSettings(Hstr,Tstr);
   // delay(1000);
  
    
}
