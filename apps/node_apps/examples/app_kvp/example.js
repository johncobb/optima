var fs = require('fs');

var sampleJson = JSON.parse(fs.readFileSync('sample.json', 'utf8'));

meta = {
    colorMap: {}
};

sampleJson.data.forEach(el => {

    // console.log(el);
    // console.log(el[0]);
    // console.log(el[1]);
    // console.log(el[1][0]);
    // console.log(el[1][1]);

    let colorId = el[0];
    let colorName = el[1][0];
    let colorHex = el[1][1]

    meta.colorMap[colorId] = {"color": colorName, "hex": colorHex};

});

var getColor = function(id) {
    return meta.colorMap[id];
}


