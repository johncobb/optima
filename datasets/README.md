### Standard make/model datasets

### Building Datasets
First we need to prepare virtual environment
Order
 - Install
 - Activate enviornment
 - Install dependencies
 - Running the code
```console

virutalenv env -p python3
. env/bin/activate
pip install pandas
```

Running the script
```console
python3 build_dataset.py csv/standard_makes.csv
```


Stats:
```console
standard_makes - csv 674 bytes
standard_model - csv 13,043 bytes

standard_makes - json 917 bytes
standard_models - json 13,770 bytes

standard_makes - json/gzip 562 bytes
standard_models - json/gzip 5,923 bytes
```

### Testing 

Installing Express
```console
npm install express
```

