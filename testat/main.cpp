/**
 * @file main.cpp
 * @brief Program to determine the cheapest gas station within a specified area.
 */

 #include <iostream>
 #include <string>
 #include <curl/curl.h>
 #include <nlohmann/json.hpp>
 #include "sms_notification.h"
 #include "email_notification.h"
 #include "mqtt_notification.h"
 
/**
 * @brief Callback function for receiving HTTP responses with libcurl.
 * @param content Pointer to the received data.
 * @param size Size of each data unit.
 * @param nmemb Number of data units.
 * @param userData Pointer to the string where the response will be stored.
 * @return Total size of the received data.
 */

 size_t handleresponse(void* contents, size_t size, size_t nmemb, void* userp) {
     ((std::string*)userp)->append((char*)contents, size * nmemb);
     return size * nmemb;
 }
 
 /**
 * @brief Sends an HTTP request to the Tankerkönig API and returns the response.
 * 
 * @param apiKey API key for the Tankerkönig API.
 * @param latitude Latitude of the search area.
 * @param longitude Longitude of the search area.
 * @param searchRadius Search radius in kilometers.
 * @param fuelType Type of fuel (e.g., diesel, e5, e10).
 * @return JSON string containing the API response.
 */

 std::string fuelprices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType) {
     CURL* curl;
     CURLcode res;
     std::string readBuffer;
 
     curl = curl_easy_init();
     if (curl) {
         std::string url = "https://creativecommons.tankerkoenig.de/json/list.php?lat=" + lat 
                         + "&lng=" + lng + "&rad=" + radius + "&sort=price&type=" + fuelType + "&apikey=" + apiKey;
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
         res = curl_easy_perform(curl);
         curl_easy_cleanup(curl);
     }
     return readBuffer;
 }
 
/**
 * @brief Retrieves detailed information about a specific gas station.
 * 
 * @param apiKey API key for the Tankerkönig API.
 * @param stationId Unique ID of the gas station.
 * @return JSON string containing gas station details.
 */

 std::string stationdetails(const std::string& apiKey, const std::string& stationId) {
     CURL* curl;
     CURLcode res;
     std::string readBuffer;
 
     curl = curl_easy_init();
     if (curl) {
         std::string url = "https://creativecommons.tankerkoenig.de/json/detail.php?id=" + stationId + "&apikey=" + apiKey;
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
         res = curl_easy_perform(curl);
         curl_easy_cleanup(curl);
     }
     return readBuffer;
 }
 
/**
 * @brief Main program to find the cheapest gas station and send notifications.
 * @return 0 if the program runs successfully, otherwise an error code.
 */

 int main() {
     std::string apiKey = "6548316a-6bce-f3cc-b70d-5560b29485aa";
     std::string lat = "47.6561"; // latitude for friedrichshafen
     std::string lng = "9.4797";  // longitude for friedrichshafen
     std::string radius = "4"; // radius in kilometers
     std::string fuelType = "diesel"; // fueltype diesel, e5, e10
 
     // retrieving stationlist data
     std::string fuelpricesresponse = fuelprices(apiKey, lat, lng, radius, fuelType);
     auto fuelpricesjson = nlohmann::json::parse(fuelpricesresponse);
 
     if (fuelpricesjson.contains("ok") && fuelpricesjson["ok"]) {
         auto stations = fuelpricesjson["stations"];
         double minPrice = std::numeric_limits<double>::max();
         nlohmann::json cheapestStation;
 
         // Search for the station with the lowest price
         for (const auto& station : stations) {
             if (station.contains("price") && station["price"] < minPrice) {
                 minPrice = station["price"];
                 cheapestStation = station;
             }
         }
 
         if (!cheapestStation.empty()) {
             std::cout << "Cheapest Station: " << cheapestStation["name"] 
                       << " at " << cheapestStation["place"] 
                       << " with price: " << cheapestStation["price"] << std::endl;
 
             // Retrieve details of the cheapest gas station
             std::string stationId = cheapestStation["id"];
             std::string stationDetailsResponse = stationdetails(apiKey, stationId);
             auto stationDetailsJson = nlohmann::json::parse(stationDetailsResponse);
 
             if (stationDetailsJson.contains("ok") && stationDetailsJson["ok"]) {
                 std::cout << "Station Details: " << stationDetailsJson.dump(4) << std::endl;
                 
                 // Send SMS notification
                 std::string phoneNumber = "+491234567890"; // Beispiel-Telefonnummer
                 std::string smsMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                          " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                 smsnotification(phoneNumber, smsMessage);
 
                 // Send email notification
                 std::string emailRecipient = "sultantbl@icloud.com"; // Beispiel-E-Mail-Adresse
                 std::string emailSubject = "Günstigste Tankstelle gefunden";
                 std::string emailBody = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                         " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                 emailnotification(emailRecipient, emailSubject, emailBody);
 
                 // Send MQTT notification
                 std::string mqttTopic = "fuel/cheapest_station";
                 std::string mqttMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() +
                                           " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                 mqttnotification(mqttTopic, mqttMessage);
                 
             } else {
                 std::cerr << "Error: " << stationDetailsJson["message"] << std::endl;
             }
         } else {
             std::cout << "No stations found." << std::endl;
         }
     } else {
         std::cerr << "Error: " << fuelpricesjson["message"] << std::endl;
     }
 
     return 0;
 }
 