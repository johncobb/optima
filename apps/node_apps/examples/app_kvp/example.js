var fs = require('fs');

let colorJson = JSON.parse(fs.readFileSync('sample.json', 'utf8'));

/*
 * meta to store colorMap key value pair for integer based lookups
 */
let meta = {
    colorMap: {}
}

/*
 * method to load standard colors into meta.colorMap as key value pair
 */
colorJson.data.forEach(el => {
    let colorId = el[0];
    let colorName = el[1][0];
    let colorHex = el[1][1]

    meta.colorMap[colorId] = {"color": colorName, "hex": colorHex}; 
});

/*
 * method to lookup color by id
 * useful when looking up integer based frame data
 */
var getColor = function(id) {
    return meta.colorMap[id];
}

let standardColor = getColor(1);

console.log(standardColor.color);
console.log(standardColor.hex);


