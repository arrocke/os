#ifndef INCLUDE_LOG_H
#define INCLUDE_LOG_H

// Specifies the level of the log.
enum LogLevel {
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARN,
    LOG_ERROR
};

// Prints a message to the log.
void log_println(char const *msg, int level);

// Initializes the log
void log_init();

#endif
