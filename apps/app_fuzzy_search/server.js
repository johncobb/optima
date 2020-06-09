// server.js
// load the things we need
const fs = require('fs');
var FuzzySearch = require('fuzzy-search');

var express = require('express');
var app = express();
var FuzzySearch = require('fuzzy-search');

// var searchRoutes = require("./routes/search");



// set the view engine to ejs
app.set('view engine', 'ejs');

// use res.render to load up an ejs view file



// index page 
app.get('/', function(req, res) {
    
    var name = "OzzyO";
    var tagline = "The road to nowhere leads to me.";
    
    res.render('pages/index', {
        name: name,
        tagline: tagline
    });

});

function escapeRegex(string) {
    return string.replace(/[-\/\\^$*+?.()|[\]{}]/g, '\\$&');
}

const makesJson = [{"key": 1, "val": "Acura"}, {"key": 3, "val": "Aston Martin"}, {"key": 4, "val": "Audi"}, {"key": 5, "val": "Bentley"}, {"key": 6, "val": "BMW"}, {"key": 7, "val": "Bugatti"}, {"key": 8, "val": "Buick"}, {"key": 9, "val": "Cadillac"}, {"key": 10, "val": "Chevrolet"}, {"key": 11, "val": "Chrysler"}, {"key": 12, "val": "Daewoo"}, {"key": 13, "val": "Dodge"}, {"key": 14, "val": "Ducati"}, {"key": 15, "val": "Eagle"}, {"key": 16, "val": "Ferrari"}, {"key": 17, "val": "FIAT"}, {"key": 18, "val": "Ford"}, {"key": 19, "val": "Genesis"}, {"key": 20, "val": "Geo"}, {"key": 21, "val": "GMC"}, {"key": 22, "val": "Harley Davidson"}, {"key": 23, "val": "Honda"}, {"key": 24, "val": "Hummer"}, {"key": 25, "val": "Hyundai"}, {"key": 26, "val": "INFINITI"}, {"key": 27, "val": "International"}, {"key": 28, "val": "Isuzu"}, {"key": 29, "val": "Jaguar"}, {"key": 30, "val": "Jeep"}, {"key": 31, "val": "Kawasaki"}, {"key": 32, "val": "Kia"}, {"key": 33, "val": "Lamborghini"}, {"key": 34, "val": "Land Rover"}, {"key": 35, "val": "Lexus"}, {"key": 36, "val": "Lincoln"}, {"key": 37, "val": "Lotus"}, {"key": 38, "val": "Maserati"}, {"key": 39, "val": "Mazda"}, {"key": 40, "val": "McLaren"}, {"key": 41, "val": "Mercedes-Benz"}, {"key": 42, "val": "Mercury"}, {"key": 43, "val": "MINI"}, {"key": 44, "val": "Mitsubishi"}, {"key": 45, "val": "Nissan"}, {"key": 46, "val": "Oldsmobile"}, {"key": 47, "val": "Plymouth"}, {"key": 48, "val": "Pontiac"}, {"key": 49, "val": "Porsche"}, {"key": 50, "val": "RAM"}, {"key": 51, "val": "Rolls-Royce"}, {"key": 52, "val": "Saab"}, {"key": 53, "val": "Saturn"}, {"key": 54, "val": "Scion"}, {"key": 55, "val": "smart"}, {"key": 56, "val": "Subaru"}, {"key": 57, "val": "Suzuki"}, {"key": 58, "val": "Tesla"}, {"key": 59, "val": "Toyota"}, {"key": 60, "val": "Triumph"}, {"key": 61, "val": "Volkswagen"}, {"key": 62, "val": "Volvo"}, {"key": 63, "val": "Yamaha"}];

const makeSearch = new FuzzySearch(makesJson, ['val'], {
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



// // about page 
// app.get('/about', function(req, res) {
//     res.render('pages/about');
// });

// app.use("/", searchRoutes);

app.listen(8080);
console.log('8080 is the magic port');