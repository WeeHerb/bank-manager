//
// Created by mslxl on 11/6/2022.
//

#include <sys/time.h>
#include <iostream>
#include "logger.h"

namespace logger {

    logger::logger(const std::string &file): stream("./" +file) {

    }

    logger::logger(const std::string &&file): stream("./" + file) {

    }

    void logger::flush() {
        stream.flush();
    }

    logger::~logger() {
        flush();
        stream.close();
    }

} // logger

logger::logger __log = logger::logger(std::to_string(time(nullptr)) + ".log");