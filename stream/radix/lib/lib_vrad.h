#ifndef VRADLIB_H
#define VRADLIB_H

#include "vrad.h"

extern void vmapencode(std::string src, std::string* dest);
extern uint64_t vradenc(std::string data, int base);
extern uint64_t vraddec(uint64_t vrad, int base, int len);

#endif