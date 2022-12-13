#pragma once

namespace AES{
    class u_aes{
        private:
        char *str;
        char *key;

        int row_key_len,new_key_len;
        int row_str_len,new_str_len;

        //bool str_complement;
        //bool key_complement;

        bool has_close;
        
        public:
        explicit u_aes(char *str);
        u_aes(char *str,char *key);
        
        void close();
        
        char *encryption();
        char *decrypt();
        
        char *get_key();

        ~u_aes();
    };
}