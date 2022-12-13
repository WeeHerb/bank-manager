#include"aes_user.h"
#include"aes.h"
#include<cstring>
#include<assert.h>
#include<random>


namespace AES{
    u_aes:: u_aes(char *str){
        srand(time(NULL));
        this->row_key_len=0;
        this->new_key_len=16;
        this->key=new char[this->new_key_len+1];
        this->key[new_key_len]='\0';
        for(int i=0;i<this->new_key_len;i++){
            int x=rand()%26;
            this->key[i]=char(x+97);
        }
        
        this->row_str_len=strlen(str);

        if(this->row_str_len%16==0){
            this->new_str_len=this->row_str_len+16;
        }else{
            this->new_str_len=32-this->row_str_len%16+this->row_str_len;
        }
        this->str=new char[this->new_str_len+1];
        this->str[this->new_str_len]='\0';
        int stuff=this->new_str_len-this->row_str_len;
        for(int i=0;i<this->new_str_len;i++){
            if(i<this->row_str_len) this->str[i]=str[i];
            else this->str[i]=char(stuff);
        }

    }
    u_aes:: u_aes(char *str,char *key){
        this->row_str_len=strlen(str);

        if(this->row_str_len%16==0){
            this->new_str_len=this->row_str_len+16;
        }else{
            this->new_str_len=(32-(this->row_str_len%16))+this->row_str_len;
        }
        int stuff = this->new_str_len-this->row_str_len;

        this->str=new char[this->new_str_len+1];
        this->str[this->new_str_len]='\0';

        for(int i=0;i<this->new_str_len;i++){
            if(i<this->row_str_len) this->str[i]=str[i];
            else{
                this->str[i]=(char)stuff;
            }
        }

        
        this->row_key_len=strlen(key);
        this->key=new char[17]; this->key[16]='\0';
        if(this->row_key_len>=16){
            for(int i=0;i<16;i++){
                this->key[i]=key[i];
            }
        }else{
            srand(time(NULL));
            for(int i=0;i<16;i++){
                if(i<this->row_key_len) this->key[i]=key[i];
                else{
                    int x=rand()%26;
                    this->key[i]=char(x+97);
                }
            }
        }
    }

    void u_aes:: close(){
        this->has_close=true;
        delete this->str;
        delete this->key;
    }
    u_aes:: ~u_aes(){
        if(!has_close){
            delete this->str;
            delete this->key;
        }
    }
    
    char* u_aes:: encryption(){
        if(has_close){
            assert("Str has been deleted!");
        }
        aes aes_en(this->key,this->str);
        aes_en.run_aes();
        return this->str;
    }

    char* u_aes:: decrypt(){
        if(has_close){
            assert("Str has been deleted!");
        }
        aes aes_en(this->key,this->str);
        aes_en.de_aes();
        this->str[this->row_str_len]='\0';
        return this->str;
    }

    char* u_aes:: get_key(){
        return this->key;
    }
}