//
// Created by mslxl on 12/20/2022.
//


#pragma once
#include<string>
#include<sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}
template <typename T>
std::wstring to_wstring_with_precision(const T a_value, const int n = 6)
{
    std::wostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}
