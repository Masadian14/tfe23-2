#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include "email_notification.h"

/**
 * @brief Callback function for libcurl to send the email payload.
 * 
 * This function is used as a callback by libcurl to read the email data 
 * and send it to the server during the email sending process.
 * 
 * @param ptr Pointer to the memory where the data will be written.
 * @param size Size of each data chunk.
 * @param nmemb Number of chunks.
 * @param userp Pointer to the email data (provided by the caller).
 * @return The number of bytes sent.
 */
size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    std::string* data = reinterpret_cast<std::string*>(userp);
    size_t len = data->size() < size * nmemb ? data->size() : size * nmemb;
    memcpy(ptr, data->c_str(), len);
    data->erase(0, len);
    return len;
}

/**
 * @brief Sends an email notification using the Gmail SMTP server.
 * 
 * This function connects to the Gmail SMTP server, authenticates with the 
 * provided credentials, and sends an email to the specified recipient 
 * with the given subject and message content.
 * 
 * @param recipient The recipient's email address.
 * @param subject The subject of the email.
 * @param message The body content of the email.
 */
void emailnotification(const std::string& recipient, const std::string& subject, const std::string& message) {
    CURL* curl;
    CURLcode res;

    struct curl_slist* recipients = NULL;

    curl = curl_easy_init();
    if (curl) {
        // SMTP server and port for Gmail (TLS)
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); // Use TLS

        // Gmail login credentials
        curl_easy_setopt(curl, CURLOPT_USERNAME, "nichtsnichts68@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "meke biye wdzj yhmi");

        // Sender email address
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<nichtsnichts68@gmail.com>");
        recipients = curl_slist_append(recipients, recipient.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Format the email message
        std::string emaildata = "To: " + recipient + "\r\n" +
                                "From: <nichtsnichts68@gmail.com>\r\n" +
                                "Subject: " + subject + "\r\n" +
                                "\r\n" + message + "\r\n";

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &emaildata);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Debugging output before sending the email
        std::cout << "Sending email to: " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Message: " << message << std::endl;

        // Enable debugging output in libcurl
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Perform the HTTP request to send the email
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            // Additional debugging information
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cerr << "Response code: " << response_code << std::endl;
        } else {
            std::cout << "Email sent successfully!" << std::endl;
        }

        // Free recipients list and clean up
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}
