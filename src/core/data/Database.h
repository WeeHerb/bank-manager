//
// Created by mslxl on 11/25/2022.
//

#pragma once

#include<memory>
#include "Staff.h"
#include "Customer.h"
#include "struct/linkedlist.h"

class Database {
public:
    LinkedList<Customer> customer;
    LinkedList<Staff> staff;
private:
    Database()= default;

public:

    static Database *singleton;

    Database(Database &other) = delete;

    void operator=(const Database &) = delete;

    void flush();

    static Database *getInstance();

    static void release();
};