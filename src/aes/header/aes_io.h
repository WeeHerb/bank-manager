#pragma once
#include"aes_user.h"
#include<fstream>

namespace AES{
    class aes_io{
        private:
        const char *addr;

        char key[17];
        char buff[16];

        char buff_in[50];
        int point_in_end;
        int point_in_begin;
        
        int place;
        int point;
        std:: ofstream *out_file=NULL;
        std:: ifstream *in_file=NULL;
        public:
        explicit aes_io(const char *addr="encryption.as");
        explicit aes_io(char *key,const char *addr="encryption.as");
        char *get_key();
        void write(const char *);
        void sync();
        void sync_in();
        void read(char *full,int,char *key);
        ~aes_io();
    };
}