// 'use strict';

// let AWS = require('aws-sdk');
// var mysql2 = require('mysql2');

let connection;

console.log("Starting query ...\n");


    let connectionConfig = {
      host: 'db-free.cds7f5aucfsr.us-east-2.rds.amazonaws.com', // Store your endpoint as an env var
      user: 'admin',
      database: 'mydb', // Store your DB schema name as an env var
      // ssl: { rejectUnauthorized: false }, // pem
      password: 'mckenzie',
      // authSwitchHandler: function ({ pluginName, pluginData }, cb) {
      //   console.log("Setting new auth handler.");
      // }
    };

    connection = mysql2.createConnection(connectionConfig);

    connection.connect(function (err) {
      if (err) {
        console.log('error connecting: ' + err.stack);
        return;
      }

      console.log('connected as id ' + connection.threadId + "\n");
      
    });

    connection.query("SELECT * FROM inventory", (error, results, fields) => {
      if (error) {
        //throw error;
        reject("ERROR " + error);
      }
      
      console.log(results)

      if (results.length > 0) {
        let result = results[0].id + ' ' + results[0].vin + ' ' + results[0].year;
        console.log(result);

        let response = {
          "statusCode": 200,
          "statusDescription": "200 OK",
          "isBase64Encoded": false,
          "headers": {
            "Content-Type": "text/html"
          },
          body: result,
        };


      } else {
          let response = {
            "statusCode": 204,
            "statusDescription": "204 OK",
            "isBase64Encoded": false,
            "headers": {
              "Content-Type": "text/html"
            },
            body: result,
          };
      }

      connection.end((error, results) => {
        if (error) {
          reject("ERROR");
        }
        // The connection is terminated now 
        console.log("Connection ended\n");
        
// module.exports.<your function name>
module.exports.dbtest = async event => {
  const promise = new Promise(function (resolve, reject) {

    console.log("Starting query ...\n");


    let connectionConfig = {
      host: 'db-free.cds7f5aucfsr.us-east-2.rds.amazonaws.com', // Store your endpoint as an env var
      user: 'admin',
      database: 'mydb', // Store your DB schema name as an env var
      // ssl: { rejectUnauthorized: false }, // pem
      password: 'mckenzie',
      // authSwitchHandler: function ({ pluginName, pluginData }, cb) {
      //   console.log("Setting new auth handler.");
      // }
    };

    connection = mysql2.createConnection(connectionConfig);

    connection.connect(function (err) {
      if (err) {
        console.log('error connecting: ' + err.stack);
        return;
      }

      console.log('connected as id ' + connection.threadId + "\n");
      
    });

    connection.query("SELECT * FROM inventory", (error, results, fields) => {
      if (error) {
        //throw error;
        reject("ERROR " + error);
      }
      
      console.log(results)

      if (results.length > 0) {
        let result = results[0].id + ' ' + results[0].vin + ' ' + results[0].year;
        console.log(result);

        let response = {
          "statusCode": 200,
          "statusDescription": "200 OK",
          "isBase64Encoded": false,
          "headers": {
            "Content-Type": "text/html"
          },
          body: result,
        };


      } else {
          let response = {
            "statusCode": 204,
            "statusDescription": "204 OK",
            "isBase64Encoded": false,
            "headers": {
              "Content-Type": "text/html"
            },
            body: result,
          };
      }

      connection.end((error, results) => {
        if (error) {
          reject("ERROR");
        }
        // The connection is terminated now 
        console.log("Connection ended\n");

        resolve(response);
      });      
    });
  });
  return promise;
};
