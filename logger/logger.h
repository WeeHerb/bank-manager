//
// Created by mslxl on 11/6/2022.
//

#pragma once

#include<fstream>

namespace __logger {

    class logger {
    private:
        std::ofstream stream;
    public:
        explicit logger(const std::string &file);

        explicit logger(const std::string &&file);

        template<typename T>
        logger &operator<<(const T &t) {
            stream << t;
            return *this;
        }

        void flush();

        ~logger();
    };

    extern logger __log; // NOLINT(bugprone-reserved-identifier)

    template<char ...tagName>
    struct TagEnable {
        enum {
            value = false
        };
    };

    template<char ...C>
    auto MakeFixTagName(TagEnable<C...>) ->
    TagEnable<C...>;

    template<std::size_t M, std::size_t N>
    constexpr char GetCharFromStr(const char(&arr)[N]) {
        return arr[M < N ? M : N - 1];
    }


#define MakeCharIndex(n, str)       __logger::GetCharFromStr<0x##n##0>(str),__logger::GetCharFromStr<0x##n##1>(str),\
                                    __logger::GetCharFromStr<0x##n##2>(str),__logger::GetCharFromStr<0x##n##3>(str),\
                                    __logger::GetCharFromStr<0x##n##4>(str),__logger::GetCharFromStr<0x##n##5>(str),\
                                    __logger::GetCharFromStr<0x##n##6>(str),__logger::GetCharFromStr<0x##n##7>(str),\
                                    __logger::GetCharFromStr<0x##n##8>(str),__logger::GetCharFromStr<0x##n##9>(str),\
                                    __logger::GetCharFromStr<0x##n##a>(str),__logger::GetCharFromStr<0x##n##b>(str),\
                                    __logger::GetCharFromStr<0x##n##c>(str),__logger::GetCharFromStr<0x##n##d>(str),\
                                    __logger::GetCharFromStr<0x##n##e>(str),__logger::GetCharFromStr<0x##n##f>(str)
#define MakeCharIndex64_L(str)      MakeCharIndex(0,str),MakeCharIndex(1,str),\
                                    MakeCharIndex(2,str),MakeCharIndex(3,str)
#define MakeCharIndex64_H(str)      MakeCharIndex(4,str),MakeCharIndex(5,str),\
                                    MakeCharIndex(6,str),MakeCharIndex(7,str)
#define MakeCharIndexSequence(str)  MakeCharIndex64_L(str),MakeCharIndex64_H(str)


#define MakeTagEnable(str) decltype(MakeFixTagName(::__logger::TagEnable<MakeCharIndexSequence(str)>{}))

#define LoggerEnableTag(tagName) template<> struct TagEnable<MakeCharIndexSequence(tagName)> { \
enum { value = true };\
};


#define LoggerPrinter(tag) if(MakeTagEnable(tag)::value)::__logger::__log << __FILE__ << "(" << __LINE__ << ") " << "[" << tag << "] "
#define LoggerFlush() ::__logger::__log.flush()


#ifndef NDEBUG
#include "enabled.h"
#endif



#undef LoggerEnableTag
} // __logger


