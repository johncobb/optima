import gzip
import shutil

if __name__ == "__main__": 
    print("compressing using gzip...")


with open('stream-opt-200.json', 'rb') as f_in, gzip.open('stream-opt-200.json.gz', 'wb') as f_out:
    shutil.copyfileobj(f_in, f_out)
