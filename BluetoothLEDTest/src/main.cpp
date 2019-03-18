#include "bluetooth.h"	//Bluetooth wrapper. https://github.com/dennistreysa/HC-06-BT

#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 100
#define LED_PIN 13
#define BT_BAUD_RATE 19200

Bluetooth BT(2, 3, BT_BAUD_RATE);	//RX Pin: 2; TX Pin: 3; Baud Rate: BT_BAUD_RATE
char buffer[BUFFER_SIZE] = {};
int ledValue = 0;

void setup () {
	//Start board host serial and LED Pin
    Serial.begin(BT_BAUD_RATE);
	pinMode(LED_PIN, OUTPUT);
	
	//Start bluetoooth device
	BT.Begin();
	BT.Reset();
	BT.setDeviceName("BluetoothLEDTest");
	BT.setDevicePin("6789");
}

void loop () {
	//Parse bluetooth command and set LED state
	BT.Read(buffer, BUFFER_SIZE);
	if (buffer[0] == 'L') 
		digitalWrite(LED_PIN, HIGH); //LED On

	else if (buffer[0] == 'D') 
		digitalWrite(LED_PIN, LOW); //LED Off

	//Read actual LED state and create a status message
	ledValue = digitalRead(LED_PIN);
	if (ledValue == HIGH) 
		sprintf(buffer, "LED ligado\n");
	
	else if(ledValue == LOW) 
		sprintf(buffer, "LED desligado\n");
	
	else 
		sprintf(buffer, "LED indefinido\n");

	//Print LED state 
	BT.Write(buffer);					//Print state to bluetooth device
	//Serial.print(buffer);				//Print state to board host device
	memset(buffer, 0, strlen(buffer));	//Clear message buffer
	delay(5000);						//Wait and start the loop again
}
