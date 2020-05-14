#ifndef VRADLIB_H
#define VRADLIB_H

extern void ext_vmapencode(std::string src, std::string* dest);
extern uint64_t ext_vradenc(std::string data, int base);
extern uint64_t ext_vraddec(uint64_t vrad, int base, int len);

#endif