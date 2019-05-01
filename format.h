//
// Created by Shi Hao on 2019-05-01.
//

#ifndef PROJECT_3_FORMAT_H
#define PROJECT_3_FORMAT_H

#include <string>

template<typename ... Args>
std::string string_format(const std::string &format, Args...args) {
    auto cstr_format = format.c_str();
    int size = std::snprintf(nullptr, 0, cstr_format, args...) + 1;
    std::unique_ptr<char[]> buffer(new char[size]);
    std::snprintf(buffer.get(), size, cstr_format, args ...);
    return std::string(buffer.get(), buffer.get() + size - 1);
}

#endif //PROJECT_3_FORMAT_H
