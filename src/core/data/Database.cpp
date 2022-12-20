//
// Created by mslxl on 11/25/2022.
//
#include <sstream>
#include <unistd.h>
#include <map>
#include <codecvt>
#include<locale>
#include <stringapiset.h>
#include "Database.h"
#include "aes/aes.h"
#include "logger/logger.h"
#include "core/util.h"

const static char *customerFile = "customer.db";
const static char *staffFile = "staff.db";
const static char *aesKey = "1234567890abcdef";


Database *Database::singleton = nullptr;

void trim(std::string &str) {
    for (int i = 0; i < 2; i++) {
        for (auto iter = str.begin(); iter != str.end();) {
            if (*iter == ' ' || *iter == '\0' || *iter == '\t') {
                iter = str.erase(iter);
                continue;
            } else {
                iter++;
                break;
            }
        }
        std::reverse(str.begin(), str.end());
    }
}

Database *Database::getInstance() {
    if (singleton == nullptr) {
        singleton = new Database;
        // read customer info
        do {
            if (access(customerFile, F_OK) == -1) {
                break;
            }


            std::ifstream fileIn(customerFile);

            std::string input;
            char ch;
            while (fileIn.get(ch)){
                input+=ch;
            }
            fileIn.close();
            unsigned long long len = input.size();
            len = 16*20000;
            input.resize(len);
            AES::aes de(aesKey,input.data(),len);
            de.de_aes();
            if(input.empty()){
                break;
            }

            std::stringstream customer(input);

            std::string line;
            std::getline(customer, line);
            trim(line);
            if (line.empty()) {
                break;
            }
            std::size_t n = std::stoull(line);
            for (std::size_t idx = 0; idx < n; idx++) {
                Customer item;

                std::getline(customer, line);
                item.telephone = line;

                std::getline(customer, line);
                item.name = line;
                std::getline(customer, line);
                item.password = line;
                std::getline(customer, line);
                item.cardID = line;
                std::getline(customer, line);
                item.id = line;
                std::getline(customer, line);
                item.vip = std::stoi(line);

                std::getline(customer, line);
                std::size_t amountN = std::stoull(line);
                for (std::size_t amountIdx = 0; amountIdx < amountN; amountIdx++) {
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
                for (std::size_t debitIdx = 0; debitIdx < debitN; debitIdx++) {
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
        } while (false);

        // read staff info
        do {
            if (access(staffFile, F_OK) == -1) {
                break;
            }
            std::ifstream staff(staffFile);
            std::string line;
            std::getline(staff, line);
            trim(line);
            if (line.empty()) {
                break;
            }
            std::size_t n = std::stoull(line);
            for (std::size_t idx = 0; idx < n; idx++) {
                Staff item;
                std::getline(staff, line);
                item.telephone = line;
                std::getline(staff, line);
                item.name = line;
                std::getline(staff, line);
                item.cardID = line;
                std::getline(staff, line);
                item.id = line;
                std::getline(staff, line);
                item.level = line;
                singleton->staff.push_back(item);
            }
            staff.close();
        } while (false);

    }


    return singleton;

}

template<typename T>
std::string to_string(const T &t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}
std:: string utf8_to_gb2312(const char* utf8) {
    using std:: string;
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    string strTemp = str;
    if (wstr)
        delete[] wstr;
    if (str)
        delete[] str;

    return strTemp;
}

void saveDoc() {
    mkdir("doc");
    auto db = Database::getInstance();
    char UTF_8BOM[4] = {char(0xEF), char(0xBB), char(0xBF), char(0)};
    std::map<std::string, std::ofstream> files;
    for (auto &item: db->customer) {

        std::string filename = "doc/" + utf8_to_gb2312(item.name.data()) + "-" + utf8_to_gb2312(item.id.data()) + ".csv";
        if (!files.count(filename)) {
            files[filename] = std::ofstream(filename);
            files[filename] << UTF_8BOM;
        }
        auto &file = files[filename];
        file << "姓名, " << item.name << std::endl;
        file << "电话, " << item.telephone << std::endl;
        file << "卡号, " << item.cardID << std::endl;
        file << "身份证号, " << item.id << std::endl;
        file << "VIP, " << (item.vip ? "是" : "否") << std::endl;
        file << "余额, " << item.amount() << std::endl;
        file << "贷款, " << item.debit() << std::endl;

        file << std::endl;
        file << "余额变化" << std::endl << "时间, 业务, 变化" << std::endl;
        for (auto &i: item.amountChange) {
            file << i.timeStr() << ", " << i.name << ", " << i.offset << std::endl;
        }

        file << std::endl;
        file << "负债变化" << std::endl << "时间, 业务, 变化" << std::endl;
        for (auto &i: item.debitChange) {
            file << i.timeStr() << ", " << i.name << ", " << i.offset << std::endl;
        }
    }
    for (auto &[path, stream]: files) {
        stream.close();
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
                buff += to_string_with_precision(amountItem.offset, 2) + "\n";
                buff += std::to_string(amountItem.timestamp) + "\n";
            }
            buff += std::to_string(item.debitChange.size()) + "\n";
            for (auto &debitItem: item.debitChange) {
                buff += debitItem.name + "\n";
                buff += to_string_with_precision(debitItem.offset, 2) + "\n";
                buff += std::to_string(debitItem.timestamp) + "\n";
            }
        }
        if (buff.size() % 16 != 0) {
            int row_size = buff.size();
            int new_size = (buff.size()/16)*16+16;
            //buff.resize((buff.size() / 16 + 1) * 16);
            for(int i=row_size;i<new_size;i++){
                buff+='\n';
            }
        }
        LoggerPrinter("AES") << buff;
        char *origin_data = buff.data();

        AES::aes en(aesKey,buff.data(),buff.size());
        en.run_aes();
        std::ofstream customer(customerFile);
        customer << origin_data;
        LoggerPrinter("AES") << origin_data;
        LoggerFlush();
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

