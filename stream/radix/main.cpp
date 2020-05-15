#include <iostream>
#include <math.h>
#include <map>
#include <fstream>
#include <string>

// #include "lib/vrad.h"
#include "lib/lib_vrad.h"

using namespace std;

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

    while(fio) {
        counter++;

        getline(fio, line);
        len = line.length();

        if (len > 0) {
            std::string buffer;
            line = line.substr(0, 3);
            vmapencode(line, &buffer);
            uint16_t vrad_wmi = vradenc(buffer, base);

            cout << "vwmi: 0x" << std::hex << vrad_wmi;
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
    rad_wmi = vradenc(data_wmi, base);

    vmapencode(buffer.substr(3,5), &data_vds);
    rad_vds = vradenc(data_vds, base);      

    vmapencode(buffer.substr(8,9), &data_ser);
    rad_ser = vradenc(data_ser, base);      

    cout << "wmi: " << hex << rad_wmi << endl; 
    cout << "vds: " << hex << rad_vds << endl;
    cout << "ser: " << hex << rad_ser << endl;  
}

int main() {
    // run_simple();
    cout << "running main..." << endl;
    // run_file_open_example();
    run_example_vin();
    return 0;

}