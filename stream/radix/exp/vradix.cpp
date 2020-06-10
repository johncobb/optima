#include <iostream>
#include <math.h>
#include <map>
#include <fstream>

using namespace std;

struct Vradix{
    uint64_t wmi;
    uint64_t vds;
    uint64_t ser;
};

char encc(int code) {
    return char(code + '0');
}
char decc(int code) {
    return char(code - '0');
}

string vmap = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ";

int vmapindexof(char c) {
    return vmap.find(c)+1;
}

char vmapcharat(int index) {
    return vmap[index-1];
}

void vmapencode(string src, string* dest) {
    for (int i=0; i<src.length(); i++) {
        // dest->push_back(vmapindexof(src[i]));
        dest->push_back(vmapindexof(toupper(src[i])));
    }
}

void vmapdecode(string data) {
    for (int i=0; i<data.length(); i++) {
        // cout << "vmap[" << i << "] " << vmapcharat(data[i]) << endl;
        cout << vmapcharat(data[i]);
    }
}



/* http://eecs.wsu.edu/~ee314/handouts/numsys.pdf */
/* https://www.cs.colostate.edu/~cs270/.Spring12/Notes/NumberSystems */
uint64_t vradenc(string data, int base) {
    uint64_t lograd = 0;
    uint64_t vrad = 0;
    uint64_t vradshxp = 0; /* used to track bitshift exponent */
    int exp = 0;

    cout << "vradenc: ";
    vmapdecode(data);
    cout << " base: " << base << endl;

    for (int i=0; i<data.length(); i++) {


        exp = (data.length()-1) - i;

        /* get the index of the character at i(th) position */
        int mval = data[i];
        char mvalc = vmapcharat(mval);

        lograd = (mval * pow(base, exp));
        vrad += (mval * pow(base, exp)); // replace: bitshif

        cout << "[" << i << "]";
        cout << "[" << mval << "]";     
        cout << "[" << mvalc << "]";   
        // cout << base << "^" << exp << "=" << vrad << endl;
        cout << base << "^" << exp << "=" << lograd << endl;
    }

    return vrad;
}

uint64_t vraddec(uint64_t vrad, int base, int len) {
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
            cout << "[" << vmapcharat(vmapi) << "]";
            vrad = vmod;
        }
        else {
            vdelta = vrad;
            vmapi = vrad;
            cout << "[" << vmapi << "]";
            cout << "[" << vmapcharat(vmapi) << "]";
        }
        cout << base << "^" << exp << "=" << vdelta;
        cout << endl;
    }

    return vrad;
}

void file_open(fstream* fio, string path) {
    (*fio).open(path);
    (*fio).seekg(0, ios::beg);
}

void file_close(fstream* fio) {
    (*fio).close();
}

/* base 10 encodes sequence of numbers 0...9 */
void run_example_encdec_base10() {
    int base = 10;
    string buffer = "843";
    string data;

    vmapencode(buffer, &data);
    vradenc(data, base);    
}

/* base 33 can encodes sequence of alphanumeric 0...9 A...Z (excluding IOQ) */
void run_example_encdec_base33(string buffer) {

    int base = 33;
    string data;

    vmapencode(buffer, &data);
    uint64_t vrad = vradenc(data, base);
    cout << "enc result: " << vrad << endl;
    vraddec(vrad, base, buffer.length());
}

void run_example_vradenc() {

    int base = 33;
    string buffer = "JTH";
    string data;
    /* perform limited charset encoding */
    vmapencode(buffer, &data);
    vradenc(data, base);
}

/* 
 * used to illustrate optimizing exponents using bit shifting
 * up to 23x more efficient
 */
void run_example_exp() {
    uint64_t eval = 8;

    cout << eval << "^n using pow." << endl;
    cout << eval << "^0=" << pow(eval,0) << endl;
    cout << eval << "^1=" << pow(eval,1) << endl;
    cout << eval << "^2=" << pow(eval,2) << endl;

    cout << eval << "^n using bitshift." << endl;

    uint64_t sheval = 8;
    for (int i=0; i<3; i++) {
        cout << eval << "^" << i << "=" << (sheval <<= i) << endl;
    }
}

/*
 * example to exercise encoding buffer to base 33 charset
 */
void run_vmap_example() {
    /* what we want to encode */
    string buffer = "JTH";
    /* where we store encoding */ 
    string data;            

    /* perform limited charset encoding */
    vmapencode(buffer,  &data);
    /* log what was encoded */
    vmapdecode(data);

}

void run_example_vencode() {
    /* 
     * JTHKD5BH0D2170008
     * JTH
     * KD5BH0
     * D2170008
     */
    
    Vradix vradix = {0,0,0};
    int base = 33;
    string data_x;
    string data_y;
    string data_z;

    string buffer_x = "JTH";
    string buffer_y = "KD5BH";
    string buffer_z = "0d2170008";

    vmapencode(buffer_x, &data_x);
    vradix.wmi = vradenc(data_x, base);

    vmapencode(buffer_y, &data_y);
    vradix.vds = vradenc(data_y, base); 

    vmapencode(buffer_z, &data_z);
    vradix.ser = vradenc(data_z, base);

    vraddec(vradix.wmi, base, data_x.length());
    vraddec(vradix.vds, base, data_y.length());
    vraddec(vradix.ser, base, data_z.length());

}

void run_example_map() {
    map<int, char> dict;
    dict.insert(pair<int, char>(0, 'A'));
    dict.insert(pair<int, char>(1, 'B'));
    dict.insert(pair<int, char>(2, 'C'));

    cout << "dict[0]: " << dict.at(0) << endl;
    cout << "dict[1]: " << dict.at(1) << endl;
    cout << "dict[2]: " << dict.at(2) << endl;
}

// void run_example_checksum(string data) {
//     cout << "checksum: " << (valid(data) ? "true" : "false") << endl;
// }

void run_file() {
    fstream fio;
    string line;

    fio.open("output");
    fio.seekg(0, ios::beg);
    cout << "start of file" << endl;
    uint32_t counter = 0;
    size_t len = 0;

    while(fio) {
        counter++;

        getline(fio, line);
        len = line.length();
        cout << "len: " << len << endl;

        if (counter == 10) {
            break;
        }        

        if (len >= 17) {
            Vradix vradix = {0,0,0};
            int base = 33;
            string data_x;
            string data_y;
            string data_z;

            string buffer_x = line.substr(0,3);
            string buffer_y = line.substr(3,5);
            string buffer_z = line.substr(8,9);
            cout << "bufer_x: " << buffer_x << endl;
            cout << "bufer_y: " << buffer_y << endl;
            cout << "bufer_z: " << buffer_z << endl;


            vmapencode(buffer_x, &data_x);
            vradix.wmi = vradenc(data_x, base);

            vmapencode(buffer_y, &data_y);
            vradix.vds = vradenc(data_y, base); 

            vmapencode(buffer_z, &data_z);
            vradix.ser = vradenc(data_z, base);  
        }
    }



    fio.close();
    cout << "end of the line." << endl;
}



void run_file_open_example() {

    fstream fio;
    string line;
    uint32_t counter = 0;
    size_t len = 0;
    int base = 33;
    
    file_open(&fio, "../../datasets/wmi_output");

    while(fio) {
        counter++;

        getline(fio, line);
        len = line.length();

        if (len > 0) {
            string data_x;
            string buffer_x = line.substr(0,3);
            vmapencode(buffer_x, &data_x);
            uint16_t vrad_wmi = vradenc(data_x, base);

            cout << "vwmi: 0x" << vrad_wmi << endl;

              
        }
        // cout << "line: " << line << " len: " << len << endl;   
    }

    file_close(&fio);
}

void run_example_substr(string data) {
    cout << "sub[0,3]:" << data.substr(0,3) << endl;
    cout << "sub[3,5]:" << data.substr(3,5) << endl;
    cout << "sub[8,9]:" << data.substr(8,9) << endl;
}

int main() {
    // run_file_open_example();
    // return 0;
    // run_example_checksum("JTHKD5BH0D2170008");
    // run_example_map();
    // run_example_exp();
    // return 0;
    
    // run_example_encdec_base10();
    // run_example_encdec_base33("JTH");
    // run_example_substr("JTHKD5BH0D2170008");
    run_example_vencode();
    // run_file();

    return 0;


}