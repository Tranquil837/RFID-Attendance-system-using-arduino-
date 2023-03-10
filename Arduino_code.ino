1.	#include <SPI.h>
2.	#include <MFRC522.h>
3.	#include "SoftwareSerial.h"
4.	#define SS_PIN 10
5.	#define RST_PIN 9
6.	#define LED_PIN 8
7.	MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
8.	SoftwareSerial ser(2,3); // RX, TX 
9.	void setup() 
10.	{
11.	  Serial.begin(9600);   // Initiate a serial communication
12.	  ser.begin (115200);
13.	  SPI.begin();      // Initiate  SPI bus
14.	  mfrc522.PCD_Init();   // Initiate MFRC522
15.	  pinMode(LED_PIN, OUTPUT);
16.	  Serial.println("Put RFID Card to Scan...");
17.	  Serial.println();
18.	 
19.	}
20.	void loop() 
21.	{
22.	  // Look for new cards
23.	  if ( ! mfrc522.PICC_IsNewCardPresent()) 
24.	  {
25.	    return;
26.	  }
27.	  // Select one of the cards
28.	  if ( ! mfrc522.PICC_ReadCardSerial()) 
29.	  {
30.	    return;
31.	  }
32.	  //Show UID on serial monitor
33.	  
34.	  String content= "";
35.	  byte letter;
36.	  for (byte i = 0; i < mfrc522.uid.size; i++) 
37.	  {
38.	     
39.	     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
40.	     content.concat(String(mfrc522.uid.uidByte[i], HEX));
41.	  }
42.	  Serial.println();
43.	  Serial.print("User No./Name:    ");
44.	  content.toUpperCase();
45.	  if (content.substring(1) == "33 31 6E 1B" ) //change here the UID of the card/cards that you want to give access
46.	  {
47.	    Serial.println("Ashutossh");
48.	    ser.write(1);
49.	    Serial.println();
50.	    
51.	    delay(3000);
52.	  }
53.	   if (content.substring(1) ==  "5B BA 2B 22" ) //change here the UID of the card/cards that you want to give access
54.	  {
55.	    Serial.println("Abdullah");
56.	    ser.write(7);
57.	    Serial.println();
58.	    
59.	    delay(3000);
60.	  }
61.	   if (content.substring(1) == "FB F4 DB 1A" ) //change here the UID of the card/cards that you want to give access
62.	  {
63.	    Serial.println("Siddesh");
64.	    ser.write(6);
65.	    Serial.println();
66.	    
67.	    delay(3000);
68.	  } 
69.	}  
