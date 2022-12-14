//
// Created by gjh on 11/22/2022.
//


#pragma once

#include<cstdlib>

namespace aes {
    class aes {
    private:
        std::size_t len_str = 0;
        const char *str = nullptr;
        char *key= nullptr;
        int mode;
        int w[44];


        inline bool deal_index(std::size_t index){
            return index>len_str ? false:true;
        }


    public:
        aes(const char *str,const char *key=nullptr);
        explicit aes(const char *str);
    };

}