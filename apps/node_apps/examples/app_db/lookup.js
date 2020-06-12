const fs = require('fs');

const file_standard_makes = '../datasets/json/standard_makes.json';
const file_standard_models = '../datasets/json/standard_models.json';
const file_standard_colors = '../datasets/json/standard_colors.json';
const file_tags = '../datasets/json/tags.json';

let standardMakes = fs.readFileSync(file_standard_makes, 'utf8', function(err, data) { 
    // return data;
    data = JSON.parse(data);
});

let standardModels = fs.readFileSync(file_standard_models, 'utf8', function(err, data) { 
    // return data;
    data = JSON.parse(data);
});

let standardColors = fs.readFileSync(file_standard_colors, 'utf8', function(err, data) { 
    // return data;
    data = JSON.parse(data);
});

let tags = fs.readFileSync(file_tags, 'utf8', function(err, data) { 
    // return data;
    data =  JSON.parse(data);
});

standardMakes = JSON.parse(standardMakes);
standardModels = JSON.parse(standardModels);
standardColors = JSON.parse(standardColors);
tags = JSON.parse(tags);

let dictInventory = ["inv", ["id", "year", "make_id", "model_id", "color_id", "lat", "lng", "accuracy", "log_entry_dt", "last_scanned_dt"]];

var objs = {
    'data': {
        set: [],
        dict: [],
        meta: [],
        frame: []
    }
}

objs.data.dict.push([0, dictInventory]);
objs.data.set.push([0, "inv"])
objs.data.meta.push([0, standardMakes]);
objs.data.meta.push([0, standardModels]);
objs.data.meta.push([0, standardColors]);
objs.data.meta.push([0, tags]);

// objs.data.dict.forEach(element => console.log(element));
// objs.data.set.forEach(element => console.log(element));
// objs.data.meta.forEach(element => console.log(element));
// objs.data.frame.forEach(element => console.log(element));


const getLookupMeta = () => {
    return objs;
}
exports.getLookupMeta = getLookupMeta;

