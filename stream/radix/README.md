### Radix

Radix encoding strings to numbers

### Strings


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


#### References:
https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html