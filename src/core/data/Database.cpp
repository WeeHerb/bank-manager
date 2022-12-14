//
// Created by mslxl on 11/25/2022.
//

#include "Database.h"

Database *Database::singleton  = nullptr;

Database *Database::getInstance() {
    if(singleton == nullptr){
        singleton = new Database;

        std:: ifstream file_customer("data_customer.db");
        std:: string line;
        Customer input;
        while(std::getline(file_customer,line))
        {
            input.cardID = line;
            std::getline(file_customer, line);
            input.password = line;
            std::getline(file_customer, line);
            input.name = line;
            std::getline(file_customer, line);
            input.telephone = line;
            std::getline(file_customer, line);
            input.id = line;
            std::getline(file_customer, line);
            if(line=="0") input.vip= false;
            else input.vip=true;
            bool first=false;
            while (std::getline(file_customer, line)) {
                if (line == "|"||first== false){
                    first= true;
                }
                else if(line == "|"||first==true) break;
                else {
                    Transaction in_tran;
                    in_tran.name=line;
                    double in_offset;
                    file_customer>>in_offset;
                    //getchar();
                    in_tran.offset=in_offset;
                    input.amountChange.push_back(in_tran);
                    std::getline(file_customer,line);
                }
            }
            while (std::getline(file_customer, line)) {
                if (line == "|") break;
                else {
                    Transaction in_deb;
                    in_deb.name=line;
                    double in_offset;
                    file_customer>>in_offset;
                    //getchar();
                    in_deb.offset=in_offset;
                    input.debitChange.push_back(in_deb);
                    std::getline(file_customer, line);
                }
            }
            singleton->customer.push_back(input);
        }

        std:: ifstream file_staff("data_staff.db");
        Staff input_staff;
        while(std::getline(file_staff,line))
        {
            input_staff.cardID=line;
            std::getline(file_staff,line);
            input_staff.name=line;
            std::getline(file_staff,line);
            input_staff.telephone=line;
            std::getline(file_staff,line);
            input_staff.id=line;
            std::getline(file_staff,line);
            input_staff.level=line;
            singleton->staff.push_back(input_staff);
        }



//        int len_customer=line.size();
//         std:: string str;
//
//        auto cardDelimiter = line.find('@');
//        input.cardID = line.substr(0, cardDelimiter);
//        auto passDelimiter = line.find('@',cardDelimiter+1);
//        input.password = line.substr(cardDelimiter+1,passDelimiter-cardDelimiter);
//        auto nameDelimiter = line.find('@', passDelimiter+1);
//        input.name = line.substr(passDelimiter+1, nameDelimiter - passDelimiter);
//        auto teleDelimiter = line.find('@',nameDelimiter+1);
//        input.telephone = line.substr(nameDelimiter+1,teleDelimiter - nameDelimiter);
//        auto idDelimiter = line.find('@',teleDelimiter+1);
//        input.id = line.substr(teleDelimiter+1,idDelimiter-teleDelimiter);
//        auto vipDelimiter = line.find('@',idDelimiter+1);
//        input.vip = line.substr(vipDelimiter+1,vipDelimiter-idDelimiter);
//
//        for (int i=0;i<len_customer;i++){
//            if(line[i]='@') {
//                input.id = line.substr(0, i);
//
//            }
//        }
//        singleton->customer.push_back(input);

        //here
    }
    return singleton;
}

void Database::flush() {
    std::ofstream file_customer("data_customer.db");

    for(auto iter = this->customer.begin(); iter!= this->customer.end(); ++iter){
        file_customer<<iter->cardID<<std:: endl;
        file_customer<<iter->password<<std::endl;
        file_customer<<iter->name<<std:: endl;
        file_customer<<iter->telephone<<std:: endl;
        file_customer<<iter->id<<std:: endl;
        file_customer<<iter->vip<<std:: endl;
        file_customer<<"|"<<std:: endl;
        for(auto vec_am = iter->amountChange.begin();vec_am!=iter->amountChange.end();++vec_am){
            file_customer<<vec_am->name<<std:: endl;
            file_customer<<vec_am->offset<<std:: endl;
        }
        file_customer<<"|"<<std:: endl;
        for(auto vec_deb = iter->debitChange.begin();vec_deb!=iter->debitChange.end();++vec_deb){
            file_customer<<vec_deb->name<<std:: endl;
            file_customer<<vec_deb->offset<<std:: endl;
        }
    }
    file_customer.close();

    std:: ofstream file_staff("data_staff.db");
    for(auto iter = this->staff.begin();iter!=this->staff.end();++iter){
        file_staff<<iter->cardID<<std:: endl;
        file_staff<<iter->name<<std:: endl;
        file_staff<<iter->telephone<<std:: endl;
        file_staff<<iter->id<<std:: endl;
        file_staff<<iter->level<<std:: endl;
    }
    file_staff.close();


}

void Database::release() {
    if(singleton != nullptr){
        singleton->flush();
        delete singleton;
        singleton = nullptr;
    }
}

