#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* WIFI_NAME = "wifiname";
const char* WIFI_PASSWORD = "*******";

void setup(){
	Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED){
		delay(500);
		Serial.print(".");
	}
	Serial.println();
	Serial.println("WiFi connected");
	Serial.println();
}

void loop(){

	if (WiFi.status() == WL_CONNECTED){
		
		HTTPClient client;

		client.begin("http://jsonplaceholder.typicode.com/posts/2");
		client.addHeader("Content-Type", "application/json");

		StaticJsonDocument<100> jsonDoc;

		jsonDoc["userId"] = 2;
		jsonDoc["title"] = "Hello World!";
		jsonDoc["body"] = "body";

		char jsonMessage[100];
		serializeJsonPretty(jsonDoc, jsonMessage, sizeof(jsonMessage));
		Serial.println(jsonMessage);
		Serial.println();

		int httpCode = client.PUT(jsonMessage);

		if (httpCode > 0){

			String res = client.getString();

			Serial.print("HTTP CODE: ");
			Serial.println(httpCode);
			Serial.println("HTTP response: ");
			Serial.println(res);
			Serial.println();

		}else{

			Serial.println("HTTP PUT falhou!");
			Serial.println("Erro: ");
			Serial.println(client.errorToString(httpCode));
		
		}

		client.end();

	}else{

		Serial.println("Erro na conexão!");

	}

	delay(30000);

}