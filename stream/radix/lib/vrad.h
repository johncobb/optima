#ifndef VRAD_H
#define VRAD_H

void vmapencode(std::string src, std::string* dest);
uint64_t vradenc(std::string data, int base);
uint64_t vraddec(uint64_t vrad, int base, int len);



#endif