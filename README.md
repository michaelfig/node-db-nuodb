# NuoDB    - node.js

[![Build Status](https://travis-ci.org/nuodb/node-db-nuodb.png?branch=master)](https://travis-ci.org/nuodb/node-db-nuodb)

This module lets you integrate your [node.js](http://www.nodejs.org) web applications with [NuoDB](http://www.nuodb.com).

## Install

    $ npm install db-nuodb

## Example

```javascript
var nuodb = require('db-nuodb');
new nuodb.Database({
    hostname: 'localhost',
    user: 'root',
    password: 'password',
    database: 'node'
}).connect(function(error) {
    if (error) {
        return console.log("CONNECTION ERROR: " + error);
    }

    this.query().select('*').from('users').execute(function(error, rows) {
        if (error) {
            return console.log('ERROR: ' + error);
        }
        console.log(rows.length + ' ROWS');
    });
});
```

## License

[NuoDB License](https://github.com/nuodb/nuodb-drivers/blob/master/LICENSE)