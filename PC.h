//
// Created by 施昊 on 2019-04-17.
//

#ifndef PROJECT_3_PC_H
#define PROJECT_3_PC_H


#include <cstdint>

typedef int64_t count;

class PC {
private:
    count counter;
public:
    count get();
    void set(count c);
    void next();
};


#endif //PROJECT_3_PC_H
