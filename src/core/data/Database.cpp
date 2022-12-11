//
// Created by mslxl on 11/25/2022.
//

#include "Database.h"

Database *Database::singleton  = nullptr;

Database *Database::getInstance() {
    if(singleton == nullptr){
        singleton = new Database;
    }
    return singleton;
}

void Database::flush() {

}

void Database::release() {
    if(singleton != nullptr){
        singleton->flush();
        delete singleton;
        singleton = nullptr;
    }
}

