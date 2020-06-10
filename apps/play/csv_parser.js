const csv = require('csv-parser');
const fs = require('fs');

const makes_json = [];
const models_json = [];
const colors_json = [];

const file_makes_csv = '../../datasets/csv/standard_makes.csv';
const file_models_csv = '../../datasets/csv/standard_models.csv';
const file_colors_csv = '../../datasets/csv/standard_colors.csv';

fs.createReadStream(file_makes_csv)
  .pipe(csv(['id', 'make']))
  .on('data', (data) => makes_json.push(data))
  .on('end', () => {
    console.log(makes_json);
});

fs.createReadStream(file_models_csv)
  .pipe(csv(['id', 'model_id', 'model']))
  .on('data', (data) => models_json.push(data))
  .on('end', () => {
    console.log(models_json);
});

fs.createReadStream(file_colors_csv)
  .pipe(csv(['id', 'color']))
  .on('data', (data) => colors_json.push(data))
  .on('end', () => {
    console.log(colors_json);
});