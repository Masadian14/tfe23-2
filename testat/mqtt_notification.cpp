#include "mqtt_notification.h"
#include <mqtt/client.h>
#include <iostream>

const std::string SERVER_ADDRESS = "tcp://broker.hivemq.com:1883"; // MQTT Broker (can be changed)
const std::string CLIENT_ID = "fuel_price_notifier";

/**
 * @brief Sends an MQTT notification with a message to a specified topic.
 * 
 * This function connects to the MQTT broker, publishes the message to the given topic 
 * with Quality of Service (QoS) level 1 (at least once), and then disconnects from the broker.
 * 
 * @param topic The MQTT topic to which the message will be published.
 * @param message The message content that will be sent to the MQTT topic.
 */
void mqttnotification(const std::string& topic, const std::string& message) {
    try {
        // Create an MQTT client and connect to the broker
        mqtt::client client(SERVER_ADDRESS, CLIENT_ID);
        client.connect();
        
        // Create the MQTT message and set its QoS level to 1 (at least once delivery)
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
        pubmsg->set_qos(1);
        
        // Publish the message to the specified topic
        client.publish(pubmsg);
        
        // Disconnect from the broker after publishing
        client.disconnect();
        std::cout << "MQTT Notification sent to topic: " << topic << std::endl;
    } catch (const mqtt::exception& e) {
        // Handle any exceptions (errors) that occur during the MQTT process
        std::cerr << "MQTT Error: " << e.what() << std::endl;
    }
}
