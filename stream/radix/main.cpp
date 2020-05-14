#include <iostream>
#include <math.h>
#include <map>
#include <fstream>
#include <string>

#include "lib/vrad.h"

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
            std::string data_x;
            std::string buffer_x = line.substr(0,3);
            vmapencode(buffer_x, &data_x);
            uint16_t vrad_wmi = vradenc(data_x, base);

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

int main() {
    // run_simple();
    cout << "running main..." << endl;
    run_file_open_example();
    return 0;

}