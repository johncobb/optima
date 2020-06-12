// server.js
// load the things we need

var express = require('express');
var app = express();

users = [
    {
        "id": 1,
        "name": "User 1"
    },
    {
        "id": 2,
        "name": "User 2"
    },
    {
        "id": 3,
        "name": "User 3"
    },
    {
        "id": 4,
        "name": "User 4"
    },
    {
        "id": 5,
        "name": "User 5"
    },
    {
        "id": 6,
        "name": "User 6"
    },
    {
        "id": 7,
        "name": "User 7"
    },
    {
        "id": 8,
        "name": "User 8"
    },
    {
        "id": 9,
        "name": "User 9"
    },
    {
        "id": 10,
        "name": "User 10"
    } 
]

posts = [
    {
        "id": 1,
        "name": "Post 1"
    },
    {
        "id": 2,
        "name": "Post 2"
    },
    {
        "id": 3,
        "name": "Post 3"
    },
    {
        "id": 4,
        "name": "Post 4"
    },
    {
        "id": 5,
        "name": "Post 5"
    },
    {
        "id": 6,
        "name": "Post 6"
    },
    {
        "id": 7,
        "name": "Post 7"
    },
    {
        "id": 8,
        "name": "Post 8"
    },
    {
        "id": 9,
        "name": "Post 9"
    },
    {
        "id": 10,
        "name": "Post 10"
    } 
]

app.get('/posts', paginatedResults(posts), (req, res) => {

    res.json(res.paginatedResults);
});

app.get('/users', paginatedResults(users), (req, res) => {

    res.json(res.paginatedResults);
});

function paginatedResults(model) {
    return (req, res, next) => {

        const page = parseInt(req.query.page);
        const limit = parseInt(req.query.limit);
    
        const startIndex = (page - 1) * limit;
        const endIndex = page * limit;
    
        const results = {};
    
        if (endIndex < model.length) {
            results.next = {
                page: page + 1,
                limit: limit
            }
        }
    
        if (startIndex > 0) {
            results.previous = {
                page: page - 1,
                limit: limit
            }
        }
    
        results.results = model.slice(startIndex, endIndex);
        res.paginatedResults = results;
        next();
    };
}

app.listen(8080);
console.log('8080 is the magic port');