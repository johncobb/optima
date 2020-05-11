# Testing dataset sizes.

### Compress/Decompress Gzip

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


#### References:
https://linuxize.com/post/gzip-command-in-linux/