# Optimizing datasets

## Using the python script to compress/decompress
```console
# compress
python3 gz.py -i tmp

# decompress
python3 gz.py -i tmp.gz -o d
```

## Using Gzip to to compress/decompress

```console
gzip [OPTION]... [FILE]...
```

Compressing:
```console
gzip filename
```

Keep original filename
```console
gzip -k filename
```

Using standard output to redirect output to a file
```console
gzip -c filename > filename.gz
```

Verbose output
```console
gzip -v filename
```

Compressing multiple files
```console
gzip filex filey filez
```

Decompressing:
```console
gunzip filename.gz
```

Decompressing keep compressed file:
```console
gzip -dk filename.gz
```

### Decompressing file to a named pipe.
This allows us to write the file directly to memory avoiding temporary files.

```console
mkfifo fifo
```

```console
buffer -i fifo -o async_file -u 100000 -t &
```

```console
gzip --stdout -c -d vin_dataset_master.gz > fifo
```

```console
cat fifo
```



#### References:
https://linuxize.com/post/gzip-command-in-linux/