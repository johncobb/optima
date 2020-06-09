// server.js
// load the things we need



var express = require('express');
var app = express();
const fs = require('fs');
var FuzzySearch = require('fuzzy-search');



const file_makes_json = '../../datasets/json/standard_makes_kvp.json';
const file_models_json = '../../datasets/json/standard_models_kvp.json';
const file_colors_json = '../../datasets/json/standard_colors_kvp.json';

const makesJson = JSON.parse(fs.readFileSync(file_makes_json, 'utf8'));
const modelsJson = JSON.parse(fs.readFileSync(file_models_json, 'utf8'));
const colorsJson = JSON.parse(fs.readFileSync(file_colors_json, 'utf8'));
// var searchRoutes = require("./routes/search");

console.log(makesJson);
console.log(modelsJson);
console.log(colorsJson);

function escapeRegex(string) {
    return string.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
}

// set the view engine to ejs
app.set('view engine', 'ejs');

// index page 
app.get('/', function(req, res) {
    
    var name = "OzzyO";
    var tagline = "The road to nowhere leads to me.";
    
    res.render('pages/index', {
        name: name,
        tagline: tagline
    });

});

const makeSearch = new FuzzySearch(makesJson, ['val'], {
    caseSensitive: false,
});

const modelSearch = new FuzzySearch(modelsJson, ['val'], {
    caseSensitive: false,
});

const colorSearch = new FuzzySearch(modelsJson, ['val'], {
    caseSensitive: false,
});

app.get("/search", function(req, res) {
    if(req.query.search) {
        // const regex = new RegExp(escapeRegex(req.query.search), 'gi');
        const fresult = makeSearch.search(req.query.search);
        console.log(fresult);

        res.render('pages/index', {
            fresult: fresult
        });        
    }
});


app.listen(8080);
console.log('8080 is the magic port');