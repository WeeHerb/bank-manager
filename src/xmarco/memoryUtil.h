//
// Created by mslxl on 12/6/2022.
//


#pragma once

#include<type_traits>
#include<ostream>

namespace xmacro {
    struct RawMemoryPtr {
        const void *ptr;
        std::size_t size;
    };

    inline std::ostream &operator<<(std::ostream &os, const RawMemoryPtr &ptr) {
        os.write(static_cast<const char *>(ptr.ptr), ptr.size);
        return os;
    }


    template<typename T>
    typename std::enable_if<std::is_pod<T>::value, RawMemoryPtr>::type
    rawMemory(const T &data) {
        return {
                &data,
                sizeof(T)
        };
    }

    template<typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, RawMemoryPtr>::type
    rawMemory(const std::string &data) {
        return {
                data.data(),
                data.size() + 1
        };
    }

    template<typename T>
    typename std::enable_if<std::is_same<T, std::wstring>::value, RawMemoryPtr>::type
    rawMemory(const std::wstring &data) {
        return {
                data.data(),
                (data.size() + 1) * 2
        };
    }

    template<typename T>
    void output(std::ostream& os, const T& data){
        auto v = rawMemory<T>(data);
        os << v;
    }
}

