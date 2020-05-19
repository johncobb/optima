#include <iostream>
#include <math.h>
#include <map>
#include <fstream>
#include <string>
#include <boost/format.hpp>

// #include "lib/vrad.h"
#include "lib/lib_vrad.h"

using namespace std;
using namespace boost;

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

void run_example_vin() {
 
    uint16_t rad_wmi;
    uint32_t rad_vds;
    uint64_t rad_ser;

    int base = 33;
    std::string buffer = "JTHKD5BH0D2170008";
    std::string data_wmi;
    std::string data_vds;
    std::string data_ser;    

    /* perform limited charset encoding */
    vmapencode(buffer.substr(0,3), &data_wmi);
    rad_wmi = (uint16_t) vradenc(data_wmi, base);

    vmapencode(buffer.substr(3,5), &data_vds);
    rad_vds = (uint32_t) vradenc(data_vds, base);      

    vmapencode(buffer.substr(8,9), &data_ser);
    rad_ser = (uint64_t) vradenc(data_ser, base);      

    // cout << "wmi: 0x" << boost::format("%02X") % rad_wmi << endl; 
    // cout << "vds: 0x" << boost::format("%02X") %  rad_vds << endl;
    // cout << "ser: 0x" << boost::format("%02X") % rad_ser << endl; 

    cout << " wmi      vds              ser" << endl;
    cout << "---- -------- ----------------" << endl;
    cout << boost::format("%04X") % rad_wmi << " ";
    cout << boost::format("%08X") % rad_vds << " ";
    cout << boost::format("%016X") % rad_ser;
    cout << endl;

    /* 
     * header:  wmi      vds              ser
     *         ---- -------- ----------------
     * output: 5460 0171B286 000001D34C4071A8
     */
}

int main() {
    // run_simple();
    cout << "running example(s)..." << endl;
    run_file_open_example();
    // run_example_vin();
    return 0;

}
