//
// Created by mslxl on 11/6/2022.
//

#pragma once
#include<fstream>

namespace logger {

    class logger {
    private:
        std::ofstream stream;
    public:
        explicit logger(const std::string& file);
        explicit logger(const std::string&& file);

        template<typename T>
        logger& operator<<(const T& t){
            stream << t;
            return *this;

        }

        void flush();
        ~logger();
    };

} // logger


extern logger::logger __log; // NOLINT(bugprone-reserved-identifier)

#define LoggerPrinter(tag) __log << __FILE__ << "(" << __LINE__ << ") " << "[" << tag << "] "
#define LoggerFlush() __log.flush()