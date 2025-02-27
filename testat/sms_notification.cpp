#include "sms_notification.h"
#include <curl/curl.h>
#include <iostream>

void sendSMS(const std::string& recipient, const std::string& message) {
    std::string apiKey = "60d33150";
    std::string apiSecret = "3rzWDIQj8iJayorA";
    std::string fromNumber = "015117204987";

    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://rest.nexmo.com/sms/json";
        std::string postFields = "api_key=" + apiKey + "&api_secret=" + apiSecret + "&to=" + recipient + "&from=" + fromNumber + "&text=" + message;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
}