#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

/* change it with your ssid-password */
const char* ssid = "103-961-Lamarche";
const char* password = "LimeRouge16";
/* this is the IP of PC/raspberry where you installed MQTT Server 
on Wins use "ipconfig" 
on Linux use "ifconfig" to get its IP address */
const char* mqtt_server = "192.168.16.25";

/* create an instance of PubSubClient client */
WiFiClient espClient;
PubSubClient client(espClient);

// setting PWM properties
const int freq = 5000;
const int led1Channel = 0;
const int led2Channel = 1;
const int resolution = 8;
/* topics */

const char* update_Topic = "update";

#define led1_Topic "led1"
#define led1_Pin 22

#define led2_Topic "led2"
#define led2_Pin 23

void receivedCallback(char* topic, byte* payload, unsigned int length)
{
    String inData;
    StaticJsonBuffer<200> jsonBuffer;

    for (int i = 0; i < length; i++) {
        //Serial.print((char)payload[i]);
        inData += (char)payload[i];
    }
    Serial.println();
    Serial.println(topic);
    Serial.println(inData);

    String topicStr = topic;

    if (topicStr == led1_Topic) {
        Serial.println("led1!!!");
        JsonObject& root = jsonBuffer.parseObject(inData);
        int data = root["data"];
        Serial.println(data);
        ledcWrite(led1Channel, data);

    } else if (topicStr == led2_Topic) {
        Serial.println("led2!!");
        JsonObject& root = jsonBuffer.parseObject(inData);
        int data = root["data"];
        Serial.println(data);
        ledcWrite(led2Channel, data);
    }
    //JsonObject& root = jsonBuffer.parseObject(inData);

    //String axis = root["axis"];
    //int button = root["button"];
}

void mqttconnect()
{
    /* Loop until reconnected */
    while (!client.connected()) {
        Serial.print("MQTT connecting ...");
        /* client ID */
        String clientId = "ESP32Client";
        /* connect now */
        if (client.connect(clientId.c_str())) {
            Serial.println("connected");
            /* subscribe topic with default QoS 0*/
            client.subscribe(update_Topic);
            client.subscribe(led1_Topic);
            client.subscribe(led2_Topic);

            client.publish(update_Topic, "1");
            Serial.println("send update");

        } else {
            Serial.print("failed, status code =");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            /* Wait 5 seconds before retrying */
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    // We start by connecting to a WiFi network
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
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    /* configure the MQTT server with IPaddress and port */
    client.setServer(mqtt_server, 1883);
    /* this receivedCallback function will be invoked 
  when client received subscribed topic */
    client.setCallback(receivedCallback);

    ledcSetup(led1Channel, freq, resolution);
    ledcAttachPin(led1_Pin, led1Channel);

    ledcSetup(led2Channel, freq, resolution);
    ledcAttachPin(led2_Pin, led2Channel);

    delay(50);
}
void loop()
{
    /* if client was disconnected then try to reconnect again */
    if (!client.connected()) {
        mqttconnect();
    }

    client.loop();
}