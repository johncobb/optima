

var express = require('express');
var router = express.Router();
var app = express();

const file_standard_makes = '../../datasets/json/standard_makes.json';
var FuzzySearch = require('fuzzy-search');

const makes = [{
    kv: {
        k: 0,
        v: "Acura"
    },
    kv: {
        k: 1,
        v: "Aston Martin"
    },
    kv: {
        k: 2,
        v: "Audi"
    }
}];

function escapeRegex(string) {
    return string.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
}

router.get("/", function(req, res) {
    if(req.query.search) {
        const regex = new RegExp(escapeRegex(req.query.search), 'gi');
        const fresult = fsearch.search(regex);

        res.render('pages/index', {
            fuzzy: fresult
        });        
    }
});