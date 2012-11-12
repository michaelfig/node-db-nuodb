/*
    Copyright (c) 2012, NuoDB, Inc.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    * Neither the name of NuoDB, Inc. nor the names of its contributors may
    be used to endorse or promote products derived from this software
    without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL NUODB, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
    OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
 tests-settings.json:
   {
    "hostname": "localhost",
    "schema": "Hockey",
    "user": "dba",
    "password": "goalie",
    "database": "test",
    "port": 48004
   }

 Database:
   NuoDB Quickstart
*/

var nodeunit = require("nodeunit");
var nuodb = require("../");
var connection;

var rows = [[1, 'Doug', 'Forward', 'Bruins'],
            [11, 'Belle', 'Goalie', 'Bruins'],
            [12, 'Bebe', 'Forward', 'Bruins'],
            [15, 'Penny', 'Defense', 'Bruins']];

var settings = JSON.parse(require('fs').readFileSync('./tests-settings.json','utf8'));

exports['IntegrationTest'] = nodeunit.testCase({
  setUp: function(callback) {
    new nuodb.Database(settings).connect(function(error) {
        if (error) {
            callback(error); return;
        }
        connection = this;

        connection.query().delete().from('hockey').
        execute(function(err, results) {
            if(err) { callback(err); return; }
            callback();
        });
    });
  },

  tearDown: function(callback) {
    if (connection) {
       connection.disconnect();
    }
    callback();
  },

  "insert": function(test) {

      connection.query().insert("hockey", ["NUMBER", "NAME", "POSITION", "TEAM"],
          rows, true).execute(function(error, result) {
          test.ifError(error);
          test.equal(result.affected,4);
          test.done();
    });
  },

  "insertQueryUpdate": function(test) {

      // add some data
      connection.query().insert("hockey", ["NUMBER", "NAME", "POSITION", "TEAM"],
          rows, true).execute(function(error, result) {
          test.ifError(error);
          test.equal(result.affected,4);

          // query and verify
          connection.query().select(["NUMBER", "NAME", "POSITION", "TEAM"])
            .from("hockey")
            .execute(function(error, actualRows, columns){
              test.ifError(error);
              test.equal(actualRows.length, 4);
              for (row = 0; row < actualRows.length; row++) {
                  test.equal(actualRows[row].NUMBER, rows[row][0]);
                  test.equal(actualRows[row].NAME, rows[row][1]);
                  test.equal(actualRows[row].POSITION, rows[row][2]);
                  test.equal(actualRows[row].TEAM, rows[row][3]);
              }

              // update it
              connection.query()
               .update('hockey')
               .set({ 'TEAM': 'Mods' })
               .where('NUMBER > ?', [10])
               .execute(function(error, result) {
                  test.ifError(error);
                  test.equal(result.affected,3);

                  // query and verify
                  connection.query().select(["NUMBER", "NAME", "POSITION", "TEAM"])
                    .from("hockey")
                    .execute(function(error, actualRows, columns){
                      test.ifError(error);
                      test.equal(actualRows.length, 4);
                      for (row = 0; row < actualRows.length; row++) {
                          if (actualRows[row].NUMBER > 10) {
                              test.equal('Mods', actualRows[row].TEAM);
                          } else {
                              test.equal('Bruins', actualRows[row].TEAM);
                          }
                      }
                      test.done();
                  });
               });
          });
      });
  }

  // TODO: negative tests and more tests in general
});
