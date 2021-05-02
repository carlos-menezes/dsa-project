#ifndef SUPER_EDA_IO_H
#define SUPER_EDA_IO_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstdarg>

namespace io {
    const std::string RESET = "\033[0m";
    const std::string WHITE = "\033[37m";
    const std::string BOLDRED = "\033[1m\033[31m";
    const std::string BOLDYELLOW = "\033[1m\033[33m";
    const std::string BOLDBLUE = "\033[1m\033[34m";
    const std::string BOLDMAGENTA = "\033[1m\033[35m";
    const std::string BOLDGREEN = "\033[1m\033[32m";
    const std::string BOLDCYAN = "\033[1m\033[36m";

    #define BLACK   "\033[30m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN    "\033[36m"
    #define BOLDBLACK   "\033[1m\033[30m"
    #define BOLDWHITE   "\033[1m\033[37m"

    namespace output {
        void error(const char* msg, ...);
        void info(const char* msg, ...);
        void custom(std::string color, bool newLine, const std::string& messageType, const std::string& message);
        void custom(std::string color, bool newLine, const std::string& message);
        void divider(bool empty = false);
        void flushScreen();
    }

    namespace input {
        void getString(std::string& destination, const std::string& prompt);
        void getChar(char& destination, const std::string& prompt);
        void getInt(int& destination, const std::string& prompt);
    }
}

#endif //SUPER_EDA_IO_H
