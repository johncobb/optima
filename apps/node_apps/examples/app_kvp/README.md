# Optimized JSON Protocol

### Optimized JSON format for standard color.

This recommended approach allows the data to be inexed and displayed in the order they occur in the JSON document.
```json
{
    "data": [
        [1, ["Red", "#AA3532"]],
        [2, ["Tan", "#DBC992"]]
        ]
}
```

### Node Example
From the JSON example above we have two colors which can be loaded into a JSON object. The Node example listed below illustrates how to load the JSON data into a key-value pair for fast/efficient lookups with frame data. This same JSON can easily populate dropdown lists as well as other UI/UX elements.
```javascript
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
```