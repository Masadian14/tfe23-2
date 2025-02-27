#ifndef EMAIL_NOTIFICATION_H
#define EMAIL_NOTIFICATION_H

#include <string>

void sendEmailNotification(const std::string& recipient, const std::string& subject, const std::string& message);

#endif // EMAIL_NOTIFICATION_H