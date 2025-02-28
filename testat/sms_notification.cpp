#include <iostream>
#include <curl/curl.h>
#include "sms_notification.h"

// Funktion zum Senden einer SMS-Benachrichtigung über Nexmo API
void sendSMSNotification(const std::string& phoneNumber, const std::string& message) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        std::string apiKey = "60d33150";
        std::string apiSecret = "3rzWDIQj8iJayorA";
        std::string from = "MaxisTank";

        std::string url = "https://rest.nexmo.com/sms/json";
        std::string postFields = "api_key=" + apiKey + "&api_secret=" + apiSecret + "&to=" + phoneNumber + "&from=" + from + "&text=" + curl_easy_escape(curl, message.c_str(), message.length());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}