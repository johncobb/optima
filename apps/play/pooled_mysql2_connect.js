let mysql2 = require('mysql2');
const fs = require('fs');
const lookupMeta = require('./lookup.js');

console.log(lookupMeta.getLookupMeta());
/*
 * table: inventory
 * 
 * query model:
 * select make, model, color, etc...
 *
 * where clause:
 * id (==)
 * vin (==)
 * make_id (==)
 *  - model_id (==)
 * color_id (==)
 * class_id (==)
 * org_id (==)
 * dealership_id (==)
 * location_id (==)
 * 
 * created (>=, <=, ==)
 * printed (>=, <=, ==)
 * scanned (>=, <=, ==)
 * 
 * default sort order:
 * scanned, year, make model, color
 * 
 * custom sort by:
 * created
 * printed
 * scanned
 * 
 * sort order:
 * asc
 * desc
 */ 

var field_id = 1;
/* note using ` instead of ' */
const sql_inventory_by_id = "select * from inventory where id = ?";

let configPool = {
    host: 'db-free.cds7f5aucfsr.us-east-2.rds.amazonaws.com',
    user: 'admin',
    password: 'mckenzie',
    database: 'mydb',
    waitForConnections: true,
    connectionLimit: 15,
    queueLimit: 0
}

var frames = []
function run_query() {
    /* https://www.npmjs.com/package/mysql2#first-query */
    const pool = mysql2.createPool(configPool);

    const inventoryId = 1;
    const queryString = "select * from inventory where id = ?";
    pool.query(queryString, [inventoryId], (error, rows, fields) => {

        if (error) {
            console.log("ERROR " + error);
            return;
        }
    
        if (rows.length > 0) {
            console.log("rows: " + rows.length + " fields: " + fields.length);
   
            rows.forEach(function(row) {
                // console.log([row.id, row.vin, row.year, row.make_id, row.model_id, row.color_id, row.lat, row.lng])
                frames.push([row.id, row.vin, row.year, row.make_id, row.model_id, row.color_id, row.lat, row.lng]);
            });

        } else {
            console.log('query returned zero results');
        }
    });

}

run_query();