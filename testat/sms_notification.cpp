#include <iostream>
#include <curl/curl.h>
#include "sms_notification.h"

/**
 * @brief Sends an SMS notification using the Nexmo API.
 * 
 * This function utilizes the Nexmo (Vonage) API to send an SMS message 
 * to a specified phone number. It establishes a connection using cURL 
 * and sends an HTTP POST request with the required authentication and 
 * message details.
 * 
 * @param phoneNumber The recipient's phone number, including the country code.
 * @param message The text message to be sent.
 */
void smsnotification(const std::string& phoneNumber, const std::string& message) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        std::string apiKey = "60d33150";      ///< Nexmo API key (replace with your own)
        std::string apiSecret = "3rzWDIQj8iJayorA"; ///< Nexmo API secret (replace with your own)
        std::string from = "MaxisTank";      ///< Sender name displayed in the SMS

        std::string url = "https://rest.nexmo.com/sms/json";

        // Construct POST fields for the API request
        std::string postFields = "api_key=" + apiKey + 
                                 "&api_secret=" + apiSecret + 
                                 "&to=" + phoneNumber + 
                                 "&from=" + from + 
                                 "&text=" + curl_easy_escape(curl, message.c_str(), message.length());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        // Perform the HTTP request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " 
                      << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup cURL resources
        curl_easy_cleanup(curl);
    }
}

