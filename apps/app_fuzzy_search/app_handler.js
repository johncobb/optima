require('dotenv').config({path: __dirname + '/.env'});
let mysql2 = require('mysql2');
const fs = require('fs');
const lookupMeta = require('./lookup.js');


function appExpress() {

    
    const express = require('express');
    const app = express();

    const db_name = process.env['DATABASE_NAME'];
    const db_userid = process.env['DATABASE_USERID'];
    const db_password = process.env['DATABASE_PASSWORD'];

    let configPool = {
        host: db_name,
        user: db_userid,
        password: db_password,
        database: 'mydb',
        waitForConnections: true,
        connectionLimit: 15,
        queueLimit: 0
    }    

    app.get('/inv/:id', (req, res) => {

        console.log('query inventory by id: ' + req.params.id);
            
        /* https://www.npmjs.com/package/mysql2#first-query */
        const pool = mysql2.createPool(configPool);

        const inventoryId = req.params.id;
        const queryString = 'select * from inventory where id = ?';
        
        pool.query(queryString, [inventoryId], (error, rows, fields) => {
            if (error) {
                res.sendStatus(500);
                res.json({'error': error});
                console.log("ERROR " + error);
                return;
            }
        
            if (rows.length > 0) {
                var objs = lookupMeta.getLookupMeta();

                console.log("rows: " + rows.length + " fields: " + fields.length);

                rows.forEach(function(row) {
                    objs.data.frame.push([row.id, row.vin, row.year, row.make_id, row.model_id, row.color_id, row.lat, row.lng]);
                });

                res.json(objs); 

            } else {
                console.log('query returned zero results');
            }
        });        
    });


    app.get('/', (req, res) => {
        res.send('Hello Nic Bander.');
    });
    
    app.listen(3000, () => {
        console.log('app express running http://localhost:3000\n');
    });    
}

function appHttp() {
    var http = require('http');

    var app = http.createServer(function(req, res) {
        res.setHeader('Content-Type', 'application/json');
        var objs = lookupMeta.getLookupMeta();
    
        res.end(JSON.stringify(objs, null, 3));
    
    });
    
    app.listen(3000, () => {
        console.log('app http running http://localhost:3000\n');
    });
}

// appHttp();
appExpress();

/* async await
 * promises
 */