const parse = require('csv-parse/lib/sync');
const fs = require('fs');
const assert = require('assert');

const FILE_MAKES_CSV = '../../../datasets/csv/standard_makes.csv';
const FILE_MODELS_CSV = '../../../datasets/csv/standard_models.csv';
const FILE_COLORS_CSV = '../../../datasets/csv/standard_colors.csv';

const makesCsv = fs.readFileSync(FILE_MAKES_CSV, 'utf8');
const modelsCsv = fs.readFileSync(FILE_MODELS_CSV, 'utf8');
const colorsCsv = fs.readFileSync(FILE_COLORS_CSV, 'utf8');

const makesJson = parse(makesCsv, {
  columns: ['id', 'make'],
  skip_empty_lines: true
});

const modelsJson = parse(modelsCsv, {
  columns: ['id', null, 'model'],
  skip_empty_lines: true
});

const colorsJson = parse(colorsCsv, {
  columns: ['id', 'color'],
  skip_empty_lines: true
});


const getMakes = () => {
    return makesJson;
}

const getModels = () => {
    return modelsJson;
}

const getColors = () => {
    return colorsJson;
}

exports.getMakes = getMakes;
exports.getModels = getModels;
exports.getColors = getColors;

const input = `
"key_1","key_2"
"value 1","value 2"
`;
const records = parse(input, {
  columns: true,
  skip_empty_lines: true
})
assert.deepEqual(records, [{ key_1: 'value 1', key_2: 'value 2' }]);