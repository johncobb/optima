

#include <math.h>
#include <map>
#include <iostream>
#include <string>
#include "vrad.h"

char encc(int code) {
    return char(code + '0');
}
char decc(int code) {
    return char(code - '0');
}

std::string vmap = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ";

int vmapindexof(char c) {
    return vmap.find(c)+1;
}

char vmapcharat(int index) {
    return vmap[index-1];
}

void vmapencode(std::string src, std::string* dest) {
    for (int i=0; i<src.length(); i++) {
        // dest->push_back(vmapindexof(src[i]));
        dest->push_back(vmapindexof(toupper(src[i])));
    }
}

void vmapdecode(std::string src, std::string* dest) {
    for (int i=0; i<src.length(); i++) {
        dest->push_back(vmapcharat(src[i]));
    }
}

/* http://eecs.wsu.edu/~ee314/handouts/numsys.pdf */
/* https://www.cs.colostate.edu/~cs270/.Spring12/Notes/NumberSystems */
uint64_t vradenc(std::string data, int base) {
    uint64_t vrad = 0;
    uint64_t vradshxp = 0; /* used to track bitshift exponent */
    int exp = 0;


    // vmapdecode(data);
    // cout << " base: " << base << endl;
    
    for (int i=0; i<data.length(); i++) {


        exp = (data.length()-1) - i;

        /* get the index of the character at i(th) position */
        int mval = data[i];
        char mvalc = vmapcharat(mval);


        vrad += (mval * pow(base, exp)); // replace: bitshif

        // cout << "[" << i << "]";
        // cout << "[" << mval << "]";     
        // cout << "[" << mvalc << "]";   
        // cout << base << "^" << exp << "=" << vrad << endl;
    }

    return vrad;
}

uint64_t vraddec(uint64_t vrad, int base, int len) {
    int exp = 0;
    // cout << "vraddec: " << vrad << endl;
    
    for (int i=0; i<len; i++) {
        int vmapi = 0;
        uint64_t vdelta = 0;

        exp = (len-1) -i;

        uint64_t vradp = pow(base, exp);
        uint64_t vmod = vrad % vradp; // replace: bitshif

        // cout << "[" << i << "]";
        
        if (vmod > 0) {
            vdelta = vrad - vmod;
            vmapi = vdelta/vradp;
            // cout << "[" << vmapi << "]";
            // cout << "[" << vmapcharat(vmapi) << "]";
            vrad = vmod;
        }
        else {
            vdelta = vrad;
            vmapi = vrad;
            // cout << "[" << vmapi << "]";
            // cout << "[" << vmapcharat(vmapi) << "]";
        }
        // cout << base << "^" << exp << "=" << vdelta;
        // cout << endl;
    }

    return vrad;
}
