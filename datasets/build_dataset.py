import os
import csv
import sys
import pandas
import json
# from util import ValidateVIN

# python ml.py training/vin_master_origin

def footer():
     print("")

frame_json_id = []
frame_json_val = []
meta_json = []

def build_makes_kvp_json(file1):
    frame = pandas.read_csv(file1, sep=',', header=None, names=['id', 'make'], usecols=['id', 'make'], skiprows=[1])
    frame.sort_values(by=['id'], ascending=True)

    for index, row in frame.iterrows():
        meta_json.append({ 'key': int(row['id']), 'val': row['make']})

    return meta_json

def build_models_kvp_json(file1):
    frame = pandas.read_csv(file1, sep=',', header=None, names=['id', 'make_id', 'model'], usecols=['id', 'make_id', 'model'], skiprows=[1])
    frame.sort_values(by=['id'], ascending=True)

    for index, row in frame.iterrows():
        meta_json.append({ 'key': int(row['id']), 'val': row['model']})

    return meta_json

def build_models_json(file1):
    frame = pandas.read_csv(file1, sep=',', header=None, names=['id', 'make_id', 'model'], usecols=['id', 'make_id', 'model'], skiprows=[1])
    frame.sort_values(by=['id'], ascending=True)

    for index, row in frame.iterrows():
        frame_json_id.append(int(row['id']))
        frame_json_val.append(row['model'])

    return [frame_json_id, frame_json_val]    

def build_vehicles_json(file1):
    frame = pandas.read_csv(file1, sep=',', header=None, names=['vin', 'year', 'make_id', 'model_id', 'lat', 'lng', 'accuracy', 'dealership_id', 'log_entry_dt', 'last_scan_dt'], usecols=['vin', 'year', 'make_id', 'model_id', 'lat', 'lng', 'accuracy', 'dealership_id', 'log_entry_dt', 'last_scan_dt'], skiprows=[1])
    frame.sort_values(by=['vin'], ascending=True)

    for index, row in frame.iterrows():
        frame_json_id.append(row['vin'])
        frame_json_val.append(row['year'])

    return [frame_json_id, frame_json_val]  
  
# cat vinValidation.txt | grep False > invalidVins.txt
# cat vinValidation.txt | grep True > validVins.txt
# python ml.py > vinValidation.txt

"""
decompress dataset:
gzip -dk vin_dataset_master

activate virtual environment:
. /env/bin/activate

running:
python3 build_dataset.py archives/vin_dataset_master > output
"""

def build_wmi(list):
    index_vin = 0

    wmi = []
    for x in list:
        wmi.append(x[index_vin][0:3])
        # wmi.append([x[0][0:3], x[1]])

    return wmi

if __name__ == "__main__":

    file = sys.argv[1]


    # results = pandas_build(file, wmi_filter)
    # results = build_makes_json(file)
    # results = build_models_json(file)
    # results = build_vehicles_json(file)

    # frame_json = {
    #     "data": results
    # }

    # result = build_models_meta_json(file)
    result = build_makes_kvp_json(file)
    print(json.dumps(result))



    
 
