#include <iostream>
#include <math.h>
#include <map>
#include <fstream>
#include <string>
#include <boost/format.hpp>
#include <sstream>
#include <chrono>

#include "lib/lib_vrad.h"

using namespace std;
using namespace boost;

/* 
 * reference: great tutorial on youtube from The Cherno 
 * https://www.youtube.com/watch?v=YG4jexlSAjc
 * title: BENCHMARKING in C++ (how to measure performance)
 */
class Timer {
public:
    Timer() {
        startTimepoint = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        stop();
    }
    void stop() {

        auto endTime = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

        auto delta = end - start;
        double ms = delta * 0.001;

        std::cout << "elapsed: " << delta << "us (" << ms << "ms) "<< std::endl;
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
};

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

void benchmark_load_file(std::vector<std::string>* list) {
    fstream fio;
    std::string line;
    size_t len;
    int base = 33;
    std::cout << "open file..." << std::endl;
    // file_open(&fio, "../../datasets/output");
    {
        Timer timer;
        file_open(&fio, "../../datasets/archives/vin_dataset_5m");        
    }
    std::cout << "load contents..." << std::endl;    
    {
        Timer timer;

        while(fio) {
            
            getline(fio, line);        
            len = line.length();

            if (len > 0) {
                list->push_back(line);
            }
        }
    }
    std::cout << "iterate records..." << std::endl;    
    {
        Timer timer;

        for(std::string& s: *list) {
            
        }
    }

    std::cout << "encode records..." << std::endl;    
    {
        Timer timer;

        for(std::string& s: *list) {
            vrad_t vrad;

            vmapencode(line.substr(0, 3), &vrad.wmi.mapped);
            vrad.wmi.rad = (uint16_t) vradenc(vrad.wmi.mapped, base);

            vmapencode(line.substr(3,5), &vrad.vds.mapped);
            vrad.vds.rad = (uint32_t) vradenc(vrad.vds.mapped, base);      

            vmapencode(line.substr(8,9), &vrad.ser.mapped);
            vrad.ser.rad = (uint64_t) vradenc(vrad.ser.mapped, base);              
        }
    }    

   
}

void run_file_open_example() {
    std::cout << "run_file_open_example..." << std::endl;
    fstream fio;
    std::string line;
    uint32_t counter = 0;
    size_t len = 0;
    int base = 33;
    
    file_open(&fio, "../../datasets/output");

    std::cout << " wmi" << std::endl;
    std::cout << "----" << std::endl;
    

{
    Timer timer;

    while(fio) {

        vrad_t vrad;
        counter++;

        getline(fio, line);
        len = line.length();

        if (len > 0) {

            vmapencode(line.substr(0, 3), &vrad.wmi.mapped);
            vrad.wmi.rad = (uint16_t) vradenc(vrad.wmi.mapped, base);

            vmapencode(line.substr(3,5), &vrad.vds.mapped);
            vrad.vds.rad = (uint32_t) vradenc(vrad.vds.mapped, base);      

            vmapencode(line.substr(8,9), &vrad.ser.mapped);
            vrad.ser.rad = (uint64_t) vradenc(vrad.ser.mapped, base); 
             
        }        
    }
}

    file_close(&fio);
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

    // std::cout << "decoding data: " << data << std::endl;
    uint64_t buffer = stoull(data, 0, 16);
    
    vraddecx(buffer, 33, data.length(), out);  
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

    std::cout << "encoding_value: " << buffer << std::endl;

    /* perform limited charset encoding */
    vmapencode(buffer.substr(0,3), &vrad.wmi.mapped);
    vrad.wmi.rad = (uint16_t) vradenc(vrad.wmi.mapped, base);

    vmapencode(buffer.substr(3,5), &vrad.vds.mapped);
    vrad.vds.rad = (uint32_t) vradenc(vrad.vds.mapped, base);      

    vmapencode(buffer.substr(8,9), &vrad.ser.mapped);
    vrad.ser.rad = (uint64_t) vradenc(vrad.ser.mapped, base); 

    vrad.wmi.hex = str(boost::format("%X") % vrad.wmi.rad);
    vrad.vds.hex = str(boost::format("%X") % vrad.vds.rad);
    vrad.ser.hex = str(boost::format("%X") % vrad.ser.rad);    

    std::cout << "seg         val          base-10      base-16" << std::endl;
    std::cout << "----- --------- ---------------- ------------" << std::endl;
    std::cout << "wmi   " << buffer.substr(0,3) << "                  " << vrad.wmi.rad << "         " << vrad.wmi.hex << std::endl;    
    std::cout << "vds   " << buffer.substr(3,5) << "             " << vrad.vds.rad << "      " << vrad.vds.hex << std::endl; 
    std::cout << "ser   " << buffer.substr(8,9) << "    " << vrad.ser.rad << "  " << vrad.ser.hex << std::endl; 
    std::cout << "---------------------------------------------" << std::endl << std::endl;    
    
    std::string swmi = "";
    std::string svds = "";
    std::string sser = "";
    
    std::cout << "decoding_tuples: " << vrad.wmi.hex << " " << vrad.vds.hex << " " << vrad.ser.hex << std::endl;
    decode_tuple(vrad.wmi.hex, &swmi);
    decode_tuple(vrad.vds.hex, &svds);
    decode_tuple(vrad.ser.hex, &sser);

    std::cout << "decoding_result: " << swmi << svds << sser << std::endl << std::endl;

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

int main() {

    run_example_vin();
    return 0;

    std::vector<std::string> list;
    benchmark_load_file(&list);
    return 0;

}



