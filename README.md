# NuoDB - Node.js

[![Build Status](https://travis-ci.org/nuodb/node-db-nuodb.png?branch=master)](https://travis-ci.org/nuodb/node-db-nuodb)

This module contains the community driven NuoDB Node.js driver built from native [Google V8](https://developers.google.com/v8/) C++ binding to let you easily integrate your [Node.js](http://www.nodejs.org) web applications with [NuoDB](http://www.nuodb.com). This is a community driven driver with limited support and testing from NuoDB.

### Requirements
Node.js -- one of the following
   - [Node.js](http://www.nodejs.org>) <= 0.10.X

GNU Compiler Collection -- both of the following
   - `make`  
   - `g++`

NuoDB -- one of the following
   -  [NuoDB](http://www.nuodb.com) >= 2.0.4
   
If you haven't done so already, [Download and Install NuoDB](http://dev.nuodb.com/download-nuodb/request/download/).

### Install
For distribution installations use:

    $ npm install db-nuodb

Alternatively (e.g. if ``npm`` is not available), a tarball can be downloaded
from GitHub and installed with node-gyp:

    $ curl -L https://github.com/nuodb/node-db-nuodb/archive/master.tar.gz | tar xz
    $ cd node-db-nuodb*
    $ make install
    $ # The folder node-db-nuodb* can be safely removed now.
    
### Example
Here is basic use of the driver that includes connecting to a NuoDB server, then printing the host name and server version:

```javascript
var nuodb = require('db-nuodb');
new nuodb.Database({
    hostname: 'localhost',
    user: 'dba',
    password: 'goalie',
    database: 'test',
    schema: 'hockey'
}).on('error', function(error) {
    console.log('ERROR: ' + error);
}).on('ready', function(server) {
    console.log('Connected to ' + server.hostname + ' (' + server.version + ')');
}).connect();
```
For further information on getting started with NuoDB, please refer to the [Documentation](http://doc.nuodb.com/display/doc/).
### License

[NuoDB License](https://github.com/nuodb/node-db-nuodb/blob/master/LICENSE)
