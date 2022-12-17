//
// Created by mslxl on 11/25/2022.
//
#include <sstream>
#include <unistd.h>
#include "Database.h"

const static char* customerFile = "customer.db";
const static char* staffFile = "staff.db";


Database *Database::singleton = nullptr;

Database *Database::getInstance() {
    if (singleton == nullptr) {
        singleton = new Database;
        // read customer info
        do{
            if(access(customerFile,F_OK) == -1){
                break;
            }


            std::ifstream customer(customerFile);

            std::string line;
            std::getline(customer, line);
            std::size_t n = std::stoull(line);
            for(std::size_t idx = 0; idx < n; idx++){
                Customer item;

                std::getline(customer, line);
                item.telephone = line;

                std::getline(customer, line);
                item.name = line;
                std::getline(customer, line);
                item.password =line;
                std::getline(customer, line);
                item.cardID =line;
                std::getline(customer, line);
                item.id =line;
                std::getline(customer, line);
                item.vip = std::stoi(line);

                std::getline(customer, line);
                std::size_t amountN = std::stoull(line);
                for(std::size_t amountIdx = 0; amountIdx < amountN; amountIdx++){
                    Transaction record;
                    std::getline(customer, line);
                    record.name = line;

                    std::getline(customer, line);
                    record.offset = std::stold(line);

                    std::getline(customer, line);
                    record.timestamp = std::stoll(line);
                    item.amountChange.push_back(std::move(record));
                }

                std::getline(customer, line);
                std::size_t debitN = std::stoull(line);
                for(std::size_t debitIdx = 0; debitIdx < debitN; debitIdx++){
                    Transaction record;
                    std::getline(customer, line);
                    record.name = line;

                    std::getline(customer, line);
                    record.offset = std::stold(line);

                    std::getline(customer, line);
                    record.timestamp = std::stoll(line);
                    item.debitChange.push_back(std::move(record));
                }
                singleton->customer.push_back(item);
            }
        }while(false);

        // read staff info
        do{
            if(access(staffFile,F_OK) == -1){
                break;
            }
            std::ifstream staff(staffFile);
            std::string line;
            std::getline(staff, line);
            std::size_t n = std::stoull(line);
            for(std::size_t idx = 0; idx < n; idx++){
                Staff item;
                std::getline(staff, line);
                item.telephone = line;
                std::getline(staff, line);
                item.name = line;
                std::getline(staff, line);
                item.cardID =line;
                std::getline(staff, line);
                item.id =line;
                std::getline(staff, line);
                item.level=line;
                singleton->staff.push_back(item);
            }
        }while(false);

    }


    return singleton;

}

template<typename T>
std::string to_string(const T &t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

void saveDoc(){
    mkdir("doc");
    auto db = Database::getInstance();
    char UTF_8BOM[4] = {char(0xEF), char(0xBB), char(0xBF), char(0)};
    for(auto&item: db->customer){
        std::ofstream file("doc/" + item.name + ".csv");
        file << UTF_8BOM;
        file << "姓名, " << item.name << std::endl;
        file << "电话, " << item.telephone << std::endl;
        file << "卡号, " << item.cardID << std::endl;
        file << "身份证号, " << item.id << std::endl;
        file << "VIP, " << (item.vip ? "是": "否") << std::endl;
        file << "余额, " << item.amount() << std::endl;
        file << "贷款, " << item.debit() << std::endl;

        file << std::endl;
        file << "余额变化" << std::endl << "时间, 业务, 变化"  << std::endl;
        for(auto &i : item.amountChange){
            file << i.timeStr() << ", " << i.name << ", " << i.offset << std::endl;
        }

        file << std::endl;
        file << "负债变化" << std::endl << "时间, 业务, 变化"  << std::endl;
        for(auto &i : item.debitChange){
            file << i.timeStr() << ", " << i.name << ", " << i.offset << std::endl;
        }
    }

}


void Database::flush() {
    // customer
    {
        std::string buff;
        buff += std::to_string(this->customer.size()) + "\n";
        for (auto &item: this->customer) {
            buff += item.telephone + "\n";
            buff += item.name + "\n";
            buff += item.password + "\n";
            buff += item.cardID + "\n";
            buff += item.id + "\n";
            buff += std::to_string(int(item.vip)) + "\n";
            buff += std::to_string(item.amountChange.size()) + "\n";
            for (auto &amountItem: item.amountChange) {
                buff += amountItem.name + "\n";
                buff += std::to_string(amountItem.offset) + "\n";
                buff += std::to_string(amountItem.timestamp) + "\n";
            }
            buff += std::to_string(item.debitChange.size()) + "\n";
            for (auto &debitItem: item.debitChange) {
                buff += debitItem.name + "\n";
                buff += std::to_string(debitItem.offset) + "\n";
                buff += std::to_string(debitItem.timestamp) + "\n";
            }
        }
        int rowSize = buff.size();
        if (buff.size() % 16 != 0) {
            buff.resize((buff.size() / 16 + 1) * 16);
        }else{
            buff.resize(buff.size() + 16);
        }
        char *origin_data = buff.data();

        std::ofstream customer(customerFile);
        customer << buff;
        customer.close();
    }

    //staff
    {
        std::string buff;
        buff += std::to_string(this->staff.size()) + "\n";
        for (auto &item: this->staff) {
            buff += item.telephone + "\n";
            buff += item.name + "\n";
            buff += item.cardID + "\n";
            buff += item.id + "\n";
            buff += item.level + "\n";
        }
        if (buff.size() % 16 != 0) {
            buff.resize((buff.size() / 16 + 1) * 16);
        }
        char *origin_data = buff.data();
        // put your aes code here
        std::ofstream staff(staffFile);
        staff << buff;
        staff.close();
    }
    saveDoc();


}

void Database::release() {
    if (singleton != nullptr) {
        singleton->flush();
        delete singleton;
        singleton = nullptr;
    }
}

