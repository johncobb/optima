### Radix
Radix encoding strings to numbers.
Our goal is encode a vehicle identification number (VIN) into 14 bytes represented by three radix encoded values. The VIN is composed of three segments: world manufacturer identifier (wmi), vehicle descriptor section (vds), and vehicle identifier section or (serial). The wmi consisting of the first three alphanumeric characters is radix encoded to a uint16_t, the vds encoded to a uint32_t and serial uint64_t respectively. This compresses the vin from 17 down to 14 bytes.

### Dependencies
Installing boost
```console
brew install boost
```

### Compiling example

```console
g++ main.cpp lib/vrad.cpp -I /lib -o runme
```

### Compiling to a shared library
```console
g++ -shared lib/vrad.cpp -I /lib -o libvrad.so
```

### Linking shared library
Note g++ looks for libraries starting with lib and ending with .so. We tell 
g++ where to find the library with the -L parameter.
```console
g++ main.cpp lib/vrad.cpp -I /lib -L . -o runme -lvrad
```


 

The encoding method converts the vin from the ASCII base set to base 33. The valid characters of a vin are 0-9...A-Z excluding I, O, and Q. This gives us 33 base characters to work with. Cutting down from the original ASCII set also prevents the radix from winding up to exceptionaly large numbers which can overflow the desired data type.
```c++
std::string vmap = "0123456789ABCDEFGHJKLMNPRSTUVWXYZ";

void vmapencode(std::string src, std::string* dest) {
    for (int i=0; i<src.length(); i++) {
        dest->push_back(vmapindexof(toupper(src[i])));
    }
}
```
After successfully encoding the sequence to the limited subset we can radix encode each of the segments into the data types we require for optimal storage. The example below illustrates radix encoding the wmi or the first 3 characters of the vin to a uint16_t.
```c++
int base = 33;
std::string out;
std::string vin = "JTHKD5BH0D2170008";

/* encode vin to subset */
vmapencode(buffer.substr(0,3), &buffer);

/* encode radix value of wmi */
uint16_t vrad_wmi = (uint16_t) vradenc(buffer, base);
```

#### References:
https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html