#include"aes_user.h"
#include"aes.h"
#include<cstring>
#include<assert.h>
#include<random>

#include<iostream>

namespace AES{
    u_aes:: u_aes(char *str){
        std:: cout<<"\n"<<"test user begin: \n";
        this->key_complement=true;
        srand(time(NULL));
        this->row_key_len=0;
        this->new_key_len=16;
        this->key=new char(this->new_key_len+1);
        this->key[new_key_len]='\0';
        for(int i=0;i<this->new_key_len;i++){
            int x=rand()%26;
            this->key[i]=char(x+97);
        }
        
        this->row_str_len=strlen(str);
        if(this->row_str_len%16==0){
            this->new_str_len=row_str_len;
            this->str_complement=false;
        }else{
            this->new_str_len=row_str_len+(16-row_str_len%16);
            this->str_complement=true;
        }
        this->str=new char(this->new_str_len+1);
        this->str[new_str_len]='\0';
        for(int i=0;i<this->new_str_len;i++){
            if(i<this->row_str_len) this->str[i]=str[i];
            else this->str[i]='0';
        }
        std:: cout<<"len: "<<this->row_str_len<<" "<<this->new_str_len<<"\n";
        std:: cout<<"key: "<<this->key<<"\n";
        std:: cout<<"str: "<<this->str<<"\n";
        std:: cout<<"end! \n";

    }
    u_aes:: u_aes(char *str,char *key){
        this->row_str_len=strlen(str);
        this->row_key_len=strlen(key);

        if(this->row_key_len==16){
            this->new_key_len=row_key_len;
            this->key_complement=false;
        }else{
            if(row_key_len>16){
                assert("A wrong key!");
            }
            this->new_key_len=row_key_len+(16-row_key_len%16);
            this->key_complement=true;
        }
        if(this->row_str_len%16==0){
            this->new_str_len=row_str_len;
            this->str_complement=false;
        }else{
            this->new_str_len=row_str_len+(16-row_key_len%16);
            this->str_complement=true;
        }

        this->str=new char(this->new_str_len+1);
        this->key=new char(this->new_key_len+1);
        this->key[new_key_len]='\0';
        this->str[new_str_len]='\0';
        
        for(int i=0;i<this->new_key_len;i++){
            if(i<this->row_key_len) this->key[i]=key[i];
            else this->key[i]='0';
        }
        for(int i=0;i<this->new_str_len;i++){
            if(i<this->row_str_len) this->str[i]=str[i];
            else this->str[i]='0';
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
        return this->str;
    }

    char* u_aes:: get_key(){
        if(has_close){
            assert("Key has been deleted!");
        }
        return this->key;
    }
}