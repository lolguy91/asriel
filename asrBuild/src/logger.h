#ifndef __LOGGER_H__
#define __LOGGER_H__
/*
 * @brief Logs info
 * @param `message` The message to log
 * @param `location` The location of the message
*/
void log_info(const char* message,const char* location);
/*
 * @brief Logs errors
 * @param `message` The message to log
 * @param `location` The location of the message
*/
void log_err(const char* message,const char* location);


#endif // __LOGGER_H__