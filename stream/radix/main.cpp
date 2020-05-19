#include <iostream>
#include <math.h>
#include <map>
#include <fstream>
#include <string>
#include <boost/format.hpp>
#include <sstream>

// #include "lib/vrad.h"
#include "lib/lib_vrad.h"

using namespace std;
using namespace boost;

struct vrad_format_t {
    uint64_t rad;
    std::string hex;
    std::string mapped;
    std::string val;
};

struct vrad_t {
    vrad_format_t wmi;
    vrad_format_t vds;
    vrad_format_t ser;
    vrad_format_t result;
};


void file_open(fstream* fio, string path) {
    (*fio).open(path);
    (*fio).seekg(0, ios::beg);
}

void file_close(fstream* fio) {
    (*fio).close();
}
    
void run_file_open_example() {
    cout << "run_file_open_example..." << endl;
    fstream fio;
    std::string line;
    uint32_t counter = 0;
    size_t len = 0;
    int base = 33;
    
    file_open(&fio, "../../datasets/wmi_output");
    cout << " wmi" << endl;
    cout << "----" << endl;

    while(fio) {
        counter++;

        getline(fio, line);
        len = line.length();

        if (len > 0) {
            std::string buffer;
            line = line.substr(0, 3);
            vmapencode(line, &buffer);
            uint16_t vrad_wmi = (uint16_t) vradenc(buffer, base);

            cout << boost::format("%04X") % vrad_wmi;
            cout << endl;
              
        }        
        // cout << "line: " << line << " len: " << len << endl;   
    }

    file_close(&fio);
}

void run_simple() {
    int base = 33;
    std::string buffer = "JTH";
    std::string data;
    /* perform limited charset encoding */
    vmapencode(buffer, &data);
    uint64_t mval = vradenc(data, base);    

    cout << "mval: " << hex << mval << endl;
}

// template<typename T2, typename T1>
// inline T2 lexical_cast(const T1 &in) {
//     T2 out;
//     std::stringstream ss;
//     ss << in;
//     ss >> out;
//     return out;
// }
string xvmap = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ";

int xvmapindexof(char c) {
    return xvmap.find(c)+1;
}

char xvmapcharat(int index) {
    return xvmap[index-1];
}

uint64_t myvraddec(uint64_t vrad, int base, int len, string* out) {
    int exp = 0;
    cout << "vraddec: " << vrad << endl;
    
    for (int i=0; i<len; i++) {
        int vmapi = 0;
        uint64_t vdelta = 0;

        exp = (len-1) -i;

        uint64_t vradp = pow(base, exp);
        uint64_t vmod = vrad % vradp; // replace: bitshif

        cout << "[" << i << "]";
        
        if (vmod > 0) {
            vdelta = vrad - vmod;
            vmapi = vdelta/vradp;
            cout << "[" << vmapi << "]";
            cout << "[" << xvmapcharat(vmapi) << "]";
            vrad = vmod;
        }
        else {
            vdelta = vrad;
            vmapi = vrad;
            cout << "[" << vmapi << "]";
            cout << "[" << xvmapcharat(vmapi) << "]";
        }
        // out->append(xvmapcharat(vmapi));
        out->push_back(xvmapcharat(vmapi));
        cout << base << "^" << exp << "=" << vdelta;
        cout << endl;
    }

    return vrad;
}

void decode_tuple(string data, string* out) {
    cout << "decoding: " << data << endl;

    uint16_t x = stoul(data.substr(0,4), 0, 16);
    uint32_t y = stoul(data.substr(4, 8), 0, 16);
    uint64_t z = stoull(data.substr(12, 16), 0, 16);
    cout << x << endl;
    cout << y << endl;
    cout << z << endl;
    myvraddec(x, 33, 3, out);
    myvraddec(y, 33, 5, out);
    myvraddec(z, 33, 9, out);    


}

void run_example_vin() {
 
    uint16_t rad_wmi;
    uint32_t rad_vds;
    uint64_t rad_ser;

    vrad_t vrad;

    vrad.wmi.hex = "%";
    vrad.vds.hex = "%";
    vrad.ser.hex = "%";


    int base = 33;
    std::string buffer = "JTHKD5BH0D2170008";
    std::string data_wmi;
    std::string data_vds;
    std::string data_ser;    

    /* perform limited charset encoding */
    vmapencode(buffer.substr(0,3), &vrad.wmi.mapped);
    vrad.wmi.rad = (uint16_t) vradenc(vrad.wmi.mapped, base);

    vmapencode(buffer.substr(3,5), &vrad.vds.mapped);
    vrad.vds.rad = (uint32_t) vradenc(vrad.vds.mapped, base);      

    vmapencode(buffer.substr(8,9), &vrad.ser.mapped);
    vrad.ser.rad = (uint64_t) vradenc(vrad.ser.mapped, base); 

    vrad.wmi.hex = str(boost::format("%04X") % vrad.wmi.rad);
    vrad.vds.hex = str(boost::format("%08X") % vrad.vds.rad);
    vrad.ser.hex = str(boost::format("%016X") % vrad.ser.rad);
    
    cout << " wmi      vds              ser" << endl;
    cout << "---- -------- ----------------" << endl;
    cout << vrad.wmi.hex << " ";
    cout << vrad.vds.hex << " ";
    cout << vrad.ser.hex;
    cout << endl;  

    vrad.result.val = vrad.wmi.hex + vrad.vds.hex + vrad.ser.hex;
    string buffer_out = "";
    decode_tuple(vrad.result.val, &buffer_out);
    cout << "data: " << buffer_out << endl;

    /* 
     * header:  wmi      vds              ser
     *         ---- -------- ----------------
     * output: 5460 0171B286 000001D34C4071A8
     */
}





int main() {
    // run_simple();
    cout << "running example(s)..." << endl;
    // run_file_open_example();
    run_example_vin();
    return 0;

}
