const parse = require('csv-parse/lib/sync');
const fs = require('fs');
const assert = require('assert');
var FuzzySearch = require('fuzzy-search');

const FILE_MAKES_CSV = '../../../../datasets/csv/standard_makes.csv';
const FILE_MODELS_CSV = '../../../../datasets/csv/standard_models.csv';
const FILE_COLORS_CSV = '../../../../datasets/csv/standard_colors.csv';

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

const makeSearch = new FuzzySearch(getMakes(), ['make'], {
  caseSensitive: false,
});

const modelSearch = new FuzzySearch(getModels(), ['model'], {
  caseSensitive: false,
});

const colorSearch = new FuzzySearch(getColors(), ['color'], {
  caseSensitive: false,
});

console.log(makeSearch.search("Niss"));
console.log(modelSearch.search("335"));
console.log(colorSearch.search("Blu"));
