//
// Created by 施昊 on 2019-04-17.
//

#include "SignExt.h"

uint32_t SignExt::extend(uint16_t num) {
    return (int32_t) num; // the compiler will do it for us
}
