#include"aes_io.h"
#include"aes_user.h"
#include<fstream>
#include<cstring>
#include<ostream>
#include<iostream>

namespace AES{
    aes_io:: aes_io(char *key,const char *addr){
        this->out_file =new std:: ofstream(addr,std::ios::app);
        this->in_file =new std:: ifstream(addr,std::ios::in);
        //this->addr=addr;

        u_aes sc(key,key);
        char *new_key = sc.get_key();
        for(int i=0;i<16;i++){
            this->key[i]=new_key[i];
        }this->key[16]='\0';

        //std:: cout<<"running: "<<this->key<<std:: endl;

        sc.close();
        point = 0;
        point_in_end=-1;
        point_in_begin=0;
        place=0;
    }

    aes_io:: aes_io(const char *addr){
        this->out_file =new std:: ofstream(addr,std::ios::app);
        this->in_file =new std:: ifstream(addr,std::ios::in);
        //this->addr=addr;

        char this_is_aes[16];
        u_aes sc(this_is_aes);
        char *new_key = sc.get_key();
        for(int i=0;i<16;i++){
            this->key[i]=new_key[i];
        }this->key[16]='\0';
        sc.close();

        point=0;
        place=0;
        point_in_end=-1;
        point_in_begin=0;

        //std:: cout<<"Asdasfagsas";
    }

    char* aes_io::get_key(){
        return this->key;
    }

    void aes_io::write(const char *str){
        int len=strlen(str);
        int last=15-point+1;
        if(last>len){
            for(int i=0;i<len;i++){
                buff[point]=str[i];
                point++;
            }
        }else if(last==len){
            for(int i=0;i<len;i++){
                buff[point]=str[i];
                point++;
            }
            sync();
        }else{
            int js=0;
            while(point<=15){
                buff[point]=str[js];
                point++; js++;
            }
            sync();
            while(js<len){
                buff[point]=str[js];
                js++; point++;
                if(point==16){
                    sync();
                }
            }
        }

    }

    void aes_io::sync(){
        //std:: cout<<"point: "<<point<<"\n";

        if(!point) return;
        char buff_sec[17]; buff_sec[point]='\0';
        for(int i=0;i<point;i++) buff_sec[i]=buff[i];

        u_aes sc(buff_sec,key);
        char *sec = sc.encryption();

        //  std:: cout<<"sync_in: "<<buff_sec<<std:: endl;
        //  std:: cout<<"running aes: "<<sec<<std:: endl;

        for(int i=0;i<16;i++){
            *out_file<<sec[i];
        }
        sc.close();
        out_file->flush();
        std:: memset(buff,0,sizeof(buff));
        std:: memset(buff_sec,0,sizeof(buff_sec));
        this->point=0;
    }

    void aes_io::sync_in(){
        char ch; int js=0;
        char num[50];
        while(in_file->get(ch)){
            num[js]=ch; js++;
            if(js==32) break;
        }
        u_aes sc(num,key);
        char *sec=sc.decrypt();
        int len_sec=strlen(sec);
        for(int i=0;i<len_sec;i++){
            buff_in[i]=sec[i];
        }

        point_in_begin=0;
        point_in_end=len_sec-1;
        sc.close();
    }

    void aes_io::read(char *full,int len,char *key){
        int buff_len=point_in_end-point_in_begin+1;
        if(buff_len==0){
            sync_in();
            buff_len=point_in_end-point_in_begin+1;
        }

        //std:: cout<<"buff_len is ok"<<buff_len<<std:: endl;
        
        if(buff_len>len){
            for(int i=0;i<len;i++){
                full[i]=buff_in[point_in_begin]; point_in_begin++;
            }
        }else if(buff_len==len){
            for(int i=point_in_begin;i<=point_in_end;i++){
                full[i]=buff_in[i]; point_in_begin++;
            }
            sync_in();
        }else{
            for(int i=point_in_begin;i<point_in_end;i++){
                full[i]=buff_in[i]; point_in_begin++;
            }
            int point_full=buff_len;
            sync_in();
            while (point_full<len){
                if(point_in_begin<=point_in_end){
                    full[point_full]=buff_in[point_in_begin];
                    point_in_begin++;
                    point_full++;
                }else{
                    sync_in();
                }
            }
        }
    }

    aes_io::~aes_io(){
        sync();
        in_file->close();
        out_file->close();
        delete in_file;
        delete out_file;
    }
}