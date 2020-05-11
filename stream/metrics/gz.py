import gzip
import shutil
import sys
import getopt


def cfile(x, y):

    with open(x, 'rb') as f_in, gzip.open(y, 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)

def dfile(x, y):
    with gzip.open(x, 'rb') as f_in, open(y, 'wb') as f_out:
        shutil.copyfileobj(f_in, f_out)        


def main(argv):
    input_file = ''
    ofile = ''

    try:
        opts, args = getopt.getopt(argv, "hi:o:", ["ifile=", "ofile="])
    except getopt.GetoptError:
        print('gz.py -i <inputfile> -o <option>')
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print('gz.py -i <inputfile> -o <option>')
            sys.exit()
        elif opt in ("-i", "--ifile"):
            input_file = arg
        elif opt in ("-o", "--ofile"):
            ofile = arg

    if (ofile == ''):
        cfile(input_file, input_file + '.gz')
    elif(ofile == 'd'):
        dfile(input_file, input_file + '.dec')


### https://linuxize.com/post/gzip-command-in-linux/

### compress: python3 gz.py -i tmp
### decompress: python3 gz.py -i tmp.gz -o d

if __name__ == "__main__": 
    main(sys.argv[1:])



# with open('stream-opt-200.json', 'rb') as f_in, gzip.open('stream-opt-200.json.gz', 'wb') as f_out:
#     shutil.copyfileobj(f_in, f_out)
