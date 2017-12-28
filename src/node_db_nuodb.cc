/****************************************************************************
 * Copyright (c) 2012, NuoDB, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of NuoDB, Inc. nor the names of its contributors may
 *       be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NUODB, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/

#include "./node_db_nuodb.h"
#include "./node_db_nuodb_connection.h"
#include "./node_db_nuodb_query.h"

Napi::FunctionReference node_db_nuodb::NuoDB::constructorTemplate;

node_db_nuodb::NuoDB::~NuoDB() {
    if (this->connection != NULL) {
        delete this->connection;
    }
}

void node_db_nuodb::NuoDB::Init(Napi::Object target) {
  Napi::Env env = target.Env();
  HandleScope scope(env);
  Napi::Function constructor = DefineClass(env, "NuoDB", {
#define XM(namestr, callback) \
      InstanceMethod(namestr, &node_db_nuodb::NuoDB::callback)
#define XC(name, intval) \
      StaticValue(#name, Napi::Number::New(env, intval))
      BINDING_PROPS
#undef XC
#undef XM
    });
  constructorTemplate.Reset(constructor);
  target.Set("NuoDB", constructor);
}

node_db_nuodb::NuoDB::NuoDB(const CallbackInfo& args) :
  node_db::Binding(args), ObjectWrap<NuoDB>(args) {
    Napi::Env env = args.Env();
    HandleScope scope(env);

    this->connection = new node_db_nuodb::Connection();
    assert(this->connection);

    if (args.Length() > 0) {
        ARG_CHECK_OBJECT(0, options);
	this->set(args[0].ToObject());
    }
}

Napi::Value node_db_nuodb::NuoDB::set(const Napi::Object options) {
    Napi::Env env = options.Env();
    ARG_CHECK_OBJECT_ATTR_OPTIONAL_STRING(options, hostname);
    ARG_CHECK_OBJECT_ATTR_OPTIONAL_STRING(options, schema);
    ARG_CHECK_OBJECT_ATTR_OPTIONAL_STRING(options, user);
    ARG_CHECK_OBJECT_ATTR_OPTIONAL_STRING(options, password);
    ARG_CHECK_OBJECT_ATTR_OPTIONAL_STRING(options, database);
    ARG_CHECK_OBJECT_ATTR_OPTIONAL_UINT32(options, port);

    node_db_nuodb::Connection* connection = static_cast<node_db_nuodb::Connection*>(this->connection);

    Napi::String hostname(env, options.Get(hostname_key).ToString());
    Napi::String user(env, options.Get(user_key).ToString());
    Napi::String password(env, options.Get(password_key).ToString());
    Napi::String database(env, options.Get(database_key).ToString());
    Napi::String schema(env, options.Get(schema_key).ToString());

    if (options.Has(hostname_key)) {
        connection->setHostname(hostname);
    }

    if (options.Has(user_key)) {
        connection->setUser(user);
    }

    if (options.Has(password_key)) {
        connection->setPassword(password);
    }

    if (options.Has(database_key)) {
        connection->setDatabase(database);
    }

    if (options.Has(schema_key)) {
        connection->setSchema(schema);
    }

    if (options.Has(port_key)) {
        connection->setPort(options.Get(port_key).ToNumber().Int32Value());
    }

    return Napi::Value();
}

ObjectReference node_db_nuodb::NuoDB::createQuery() const {
  ObjectReference query;
  query.Reset(node_db_nuodb::Query::constructorTemplate.Value().New({}));
  return query;
}
