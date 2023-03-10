1.	#include <ESP8266WiFi.h>
2.	#include "Adafruit_MQTT.h"
3.	#include "Adafruit_MQTT_Client.h"
4.	// WiFi parameters
5.	#define WLAN_SSID       "Marvel"
6.	#define WLAN_PASS       "**********"
7.	 
8.	// Adafruit IO
9.	#define AIO_SERVER      "io.adafruit.com"
10.	#define AIO_SERVERPORT  1883
11.	#define AIO_USERNAME    "ashu24"
12.	#define AIO_KEY         "*******************"  // Obtained from account info on io.adafruit.com
13.	 
14.	// Create an ESP8266 WiFiClient class to connect to the MQTT server.
15.	WiFiClient client;
16.	 
17.	// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
18.	Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
19.	 
20.	Adafruit_MQTT_Publish Attendance = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/Attendance");
21.	 
22.	char ID;
23.	/*************************** Sketch Code ************************************/
24.	 
25.	void setup() {
26.	  Serial.begin(115200);
27.	  Serial.println(F("Adafruit IO Example"));
28.	 
29.	  // Connect to WiFi access point.
30.	  Serial.println(); Serial.println();
31.	  delay(10);
32.	  Serial.print(F("Connecting to "));
33.	  Serial.println(WLAN_SSID);
34.	 
35.	  WiFi.begin(WLAN_SSID, WLAN_PASS);
36.	  while (WiFi.status() != WL_CONNECTED) {
37.	    delay(500);
38.	    Serial.print(F("."));
39.	  }
40.	  Serial.println();
41.	 
42.	  Serial.println(F("WiFi connected"));
43.	  Serial.println(F("IP address: "));
44.	  Serial.println(WiFi.localIP());
45.	  // connect to adafruit io
46.	  connect();
47.	 
48.	}
49.	 
50.	// connect to adafruit io via MQTT
51.	void connect() {
52.	  Serial.print(F("Connecting to Adafruit IO... "));
53.	  int8_t ret;
54.	  while ((ret = mqtt.connect()) != 0) {
55.	    switch (ret) {
56.	      case 1: Serial.println(F("Wrong protocol")); break;
57.	      case 2: Serial.println(F("ID rejected")); break;
58.	      case 3: Serial.println(F("Server unavail")); break;
59.	      case 4: Serial.println(F("Bad user/pass")); break;
60.	      case 5: Serial.println(F("Not authed")); break;
61.	      case 6: Serial.println(F("Failed to subscribe")); break;
62.	      default: Serial.println(F("Connection failed")); break;
63.	    }
64.	 
65.	    if(ret >= 0)
66.	      mqtt.disconnect();
67.	 
68.	    Serial.println(F("Retrying connection..."));
69.	    delay(5000);
70.	  }
71.	  Serial.println(F("Adafruit IO Connected!"));
72.	}
73.	 
74.	void loop() {
75.	  // ping adafruit io a few times to make sure we remain connected
76.	  if(! mqtt.ping(3)) {
77.	    // reconnect to adafruit io
78.	    if(! mqtt.connected())
79.	      connect();
80.	  }
81.	   if ( Serial.available() ) { // Update and send only after 1 seconds
82.	   char a = Serial.read();
83.	   ID = a;  
84.	   
85.	   if (! Attendance.publish(ID)) {                     //Publish to Adafruit
86.	      Serial.println(F("Failed"));
87.	    } else {
88.	      Serial.println(F("Sent!"));
89.	    }
90.	}
