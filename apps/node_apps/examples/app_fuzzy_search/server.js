// server.js
// load the things we need

var express = require('express');
var app = express();
const fs = require('fs');
const metaLookup = require('./lookup.js');
var FuzzySearch = require('fuzzy-search');

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

const makeSearch = new FuzzySearch(metaLookup.getMakes(), ['make'], {
    caseSensitive: false,
});

const modelSearch = new FuzzySearch(metaLookup.getModels(), ['model'], {
    caseSensitive: false,
});

const colorSearch = new FuzzySearch(metaLookup.getColors(), ['color'], {
    caseSensitive: false,
});

app.get("/search", function(req, res) {
    if(req.query.search) {
        // const regex = new RegExp(escapeRegex(req.query.search), 'gi');
        const makeResults = makeSearch.search(req.query.search);
        console.log(makeResults);

        res.render('pages/index', {
            makeResults: makeResults
        });        

        const modelResults = modelSearch.search(req.query.search);
        console.log(modelResults);        

        // res.render('pages/index', {
        //     modelResults: modelResults
        // });     

    }
});

app.get("/omni", function(req, res) {

    const standardMakes = metaLookup.getMakes();

    const page = parseInt(req.query.page);
    const limit = parseInt(req.query.limit);

    const startIndex = (page - 1) * limit;
    const endIndex = page * limit;

    const results = {};

    if (endIndex < standardMakes.length) {
        results.next = {
            page: page + 1,
            limit: limit
        }
    }

    if (startIndex > 0) {
        results.previous = {
            page: page - 1,
            limit: limit
        }
    }


    results.results = standardMakes.slice(startIndex, endIndex);

    res.json(results);

});

function paginatedResults(model) {
    return (req, res, next) => {

        const page = parseInt(req.query.page);
        const limit = parseInt(req.query.limit);
    
        const startIndex = (page - 1) * limit;
        const endIndex = page * limit;
    
        const results = {};
    
        if (endIndex < model.length) {
            results.next = {
                page: page + 1,
                limit: limit
            }
        }
    
        if (startIndex > 0) {
            results.previous = {
                page: page - 1,
                limit: limit
            }
        }
    
        results.results = model.slice(startIndex, endIndex);
        res.paginatedResults = results
    };
}

app.listen(8080);
console.log('8080 is the magic port');