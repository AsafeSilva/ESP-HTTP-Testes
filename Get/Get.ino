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

		client.begin("http://jsonplaceholder.typicode.com/todos/5");

		int httpCode = client.GET();

		if (httpCode > 0){

			String res = client.getString();

			Serial.print("HTTP CODE: ");
			Serial.println(httpCode);
			Serial.println("HTTP response: ");
			Serial.println(res);
			Serial.println();

			StaticJsonDocument<200> jsonDoc;

			DeserializationError error = deserializeJson(jsonDoc, res);

			if (error) {

			    Serial.print("deserializeJson() failed: ");
			    Serial.println(error.c_str());
			
			}else{

				int userId = jsonDoc["userId"];
				int id = jsonDoc["id"];
				const char* title = jsonDoc["title"];
				bool completed = jsonDoc["completed"];

				Serial.println("Valores do json:");
				Serial.println(userId);
				Serial.println(id);
				Serial.println(title);
				Serial.println(completed);

			}

		}else{

			Serial.println("HTTP GET falhou!");
			Serial.println("Erro: ");
			Serial.println(client.errorToString(httpCode));
		
		}

		client.end();

	}else{

		Serial.println("Erro na conexão!");

	}

	delay(30000);

}