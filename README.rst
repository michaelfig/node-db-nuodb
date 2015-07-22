===============
NuoDB - Node.js
===============

.. image:: https://travis-ci.org/nuodb/node-db-nuodb.svg?branch=master
	:target: https://travis-ci.org/nuodb/node-db-nuodb 

.. contents::
This module contains the official NuoDB_ Node.js driver built from native `Google V8 <https://developers.google.com/v8/>`_ C++ binding to let you easily integrate your `node.js <http://www.nodejs.org>`_ web applications with NuoDB_.

Requirements
------------

* GNU Compiler Collection -- both of the following

 	- Make

 	- g++

* NuoDB -- one of the following

   - NuoDB_ >= 2.0.4

If you haven't done so already, `Download and Install NuoDB <http://dev.nuodb.com/download-nuodb/request/download/>`_.

Install
------------
For distribution installations use::

    $ npm install db-nuodb

Alternatively (e.g. if ``npm`` is not available), a tarball can be downloaded
from GitHub and installed with node-gyp::

    $ curl -L https://github.com/nuodb/node-db-nuodb/archive/master.tar.gz | tar xz
    $ cd node-db-nuodb*
    $ make install
    $ # The folder node-db-nuodb* can be safely removed now.

Example
------------
Here is basic use of the driver that includes connecting to a NuoDB server, then printing the host name and server version:

.. code:: javascript

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

For further information on getting started with NuoDB, please refer to the Documentation_.


License
------------
This NuoDB Node.js driver is licensed under a `BSD 3-Clause License <https://github.com/nuodb/node-db-nuodb/blob/master/LICENSE>`_.

.. _NuoDB: http://www.nuodb.com/ 
.. _Documentation: http://doc.nuodb.com/display/doc/
