//
// Created by mslxl on 12/6/2022.
//

#ifndef MESSAGE_HEAD
#error MESSAGE_HEAD not defined
#endif

#ifndef MESSAGE_BODY
#error MESSAGE_BODY not defined
#endif


#include <ostream>
#include <istream>
#include "memoryUtil.h"

struct MESSAGE_HEAD {
#define FIELD_STR(NAME, ...) std::string NAME = {__VA_ARGS__};
#define FIELD_WSTR(NAME, ...) std::wstring NAME = {__VA_ARGS__};
#define FIELD_I32(NAME, ...) int NAME = {__VA_ARGS__};
#define FIELD_I64(NAME, ...) long NAME = {__VA_ARGS__};
#define FIELD_I128(NAME, ...) long long NAME = {__VA_ARGS__};
#define FIELD_F32(NAME, ...) float NAME = {__VA_ARGS__};
#define FIELD_F64(NAME, ...) double NAME = {__VA_ARGS__};
#define FIELD_BOOL(NAME, ...) bool NAME = {__VA_ARGS__};
    MESSAGE_BODY

#undef FIELD_STR
#undef FIELD_WSTR
#undef FIELD_I32
#undef FIELD_I64
#undef FIELD_I128
#undef FIELD_F32
#undef FIELD_F64
#undef FIELD_BOOL
};

inline std::ostream &operator<<(std::ostream &os, const MESSAGE_HEAD &data) {
#define FIELD_STR(NAME, ...)  xmacro::output(os, data. NAME );
#define FIELD_WSTR(NAME, ...)  xmacro::output(os, data. NAME );
#define FIELD_I32(NAME, ...) xmacro::output(os, data. NAME );
#define FIELD_I64(NAME, ...) xmacro::output(os, data. NAME );
#define FIELD_I128(NAME, ...) xmacro::output(os, data. NAME );
#define FIELD_F32(NAME, ...) xmacro::output(os, data. NAME );
#define FIELD_F64(NAME, ...) xmacro::output(os, data. NAME );
#define FIELD_BOOL(NAME, ...) xmacro::output(os, data. NAME );
    MESSAGE_BODY
    return os;
}

#undef FIELD_STR
#undef FIELD_WSTR
#undef FIELD_I32
#undef FIELD_I64
#undef FIELD_I128
#undef FIELD_F32
#undef FIELD_F64
#undef FIELD_BOOL

#undef MESSAGE_HEAD
#undef MESSAGE_BODY