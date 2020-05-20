#include <iostream>
#include <math.h>
#include <map>
#include <fstream>
#include <string>
#include <boost/format.hpp>
#include <sstream>

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
    std::cout << "run_file_open_example..." << std::endl;
    fstream fio;
    std::string line;
    uint32_t counter = 0;
    size_t len = 0;
    int base = 33;
    
    file_open(&fio, "../../datasets/wmi_output");
    std::cout << " wmi" << std::endl;
    std::cout << "----" << std::endl;

    while(fio) {
        counter++;

        getline(fio, line);
        len = line.length();

        if (len > 0) {
            std::string buffer;
            line = line.substr(0, 3);
            vmapencode(line, &buffer);
            uint16_t vrad_wmi = (uint16_t) vradenc(buffer, base);

            std::cout << boost::format("%04X") % vrad_wmi;
            std::cout << std::endl;
              
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

    std::cout << "mval: " << hex << mval << std::endl;
}

// template<typename T2, typename T1>
// inline T2 lexical_cast(const T1 &in) {
//     T2 out;
//     std::stringstream ss;
//     ss << in;
//     ss >> out;
//     return out;
// }

void decode_tuple(std::string data, std::string* out) {

    uint16_t x = stoul(data.substr(0,4), 0, 16);
    uint32_t y = stoul(data.substr(4, 8), 0, 16);
    uint64_t z = stoull(data.substr(12, 16), 0, 16);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    std::cout << z << std::endl;
    vraddecx(x, 33, 3, out);
    vraddecx(y, 33, 5, out);
    vraddecx(z, 33, 9, out);    
}

void run_example_vin() {
    std::cout << "run_example_main: " << std::endl;

    uint16_t rad_wmi;
    uint32_t rad_vds;
    uint64_t rad_ser;

    vrad_t vrad;

    int base = 33;
    std::string buffer = "JTHKD5BH0D2170008";
    std::string data_wmi;
    std::string data_vds;
    std::string data_ser;    

    std::cout << "value: " << buffer << std::endl;

    /* perform limited charset encoding */
    vmapencode(buffer.substr(0,3), &vrad.wmi.mapped);
    vrad.wmi.rad = (uint16_t) vradenc(vrad.wmi.mapped, base);

    vmapencode(buffer.substr(3,5), &vrad.vds.mapped);
    vrad.vds.rad = (uint32_t) vradenc(vrad.vds.mapped, base);      

    vmapencode(buffer.substr(8,9), &vrad.ser.mapped);
    vrad.ser.rad = (uint64_t) vradenc(vrad.ser.mapped, base); 

    std::cout << "seg         val              rad" << std::endl;
    std::cout << "----- --------- ----------------" << std::endl;
    std::cout << "wmi   " << buffer.substr(0,3) << "                  " << vrad.wmi.rad << std::endl;    
    std::cout << "vds   " << buffer.substr(3,5) << "             " << vrad.vds.rad << std::endl; 
    std::cout << "ser   " << buffer.substr(8,9) << "    " << vrad.ser.rad << std::endl; 
    std::cout << "--------------------------------" << std::endl << std::endl;

    vrad.wmi.hex = str(boost::format("%04X") % vrad.wmi.rad);
    vrad.vds.hex = str(boost::format("%08X") % vrad.vds.rad);
    vrad.ser.hex = str(boost::format("%016X") % vrad.ser.rad);
    
    std::cout << "wmi  vds      ser" << std::endl;
    std::cout << "---- -------- ----------------" << std::endl;
    std::cout << vrad.wmi.hex << " ";
    std::cout << vrad.vds.hex << " ";
    std::cout << vrad.ser.hex;
    std::cout << std::endl << std::endl;  

    // vrad.result.val = vrad.wmi.hex + vrad.vds.hex + vrad.ser.hex;
    // std::string buffer_out = "";
    // decode_tuple(vrad.result.val, &buffer_out);
    // std::cout << "data: " << buffer_out << std::endl;

    /* 
     * header:  wmi      vds              ser
     *         ---- -------- ----------------
     * output: 5460 0171B286 000001D34C4071A8
     */
}





int main() {
    // run_simple();
    std::cout << "running example(s)..." << std::endl;
    // run_file_open_example();
    run_example_vin();
    return 0;

}



