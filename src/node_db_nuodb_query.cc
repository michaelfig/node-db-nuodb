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

#include "./node_db_nuodb_query.h"
using namespace Napi;

Napi::FunctionReference node_db_nuodb::Query::constructorTemplate;

void node_db_nuodb::Query::Init(Napi::Object target) {
    Napi::Env env = target.Env();
    HandleScope scope(env);

    Napi::FunctionReference t;
    t.Reset(Napi::Function::New(env, New));

    node_db::Query::Init(target, t);

    NODE_ADD_PROTOTYPE_METHOD(t, "limit", Limit);

    target.Set("Query", t.Value());
}

Napi::Value node_db_nuodb::Query::New(const CallbackInfo& args) {
    Napi::Env env = args.Env();
    EscapableHandleScope scope(env);

    node_db_nuodb::Query* query = new node_db_nuodb::Query(args);
    if (query == NULL) {
        THROW_EXCEPTION("Can't create query object")
    }

    if (args.Length() > 0) {
        Napi::Value set = query->set(args);
        if (!set.IsEmpty()) {
            return scope.Escape(set);
        }
    }

    query->Reset(args.This().As<Object>());

    return scope.Escape(args.This());
}

Napi::Value node_db_nuodb::Query::Limit(const CallbackInfo& args) {
    Napi::Env env = args.Env();
    EscapableHandleScope scope(env);

    if (args.Length() > 1) {
        ARG_CHECK_UINT32(0, offset);
        ARG_CHECK_UINT32(1, rows);
    } else {
        ARG_CHECK_UINT32(0, rows);
    }

    node_db_nuodb::Query* query = reinterpret_cast<node_db_nuodb::Query*>(Unwrap(args.This().As<Object>()));
    assert(query);

    std::string currentSql = query->sql.str();

    query->sql.str("");
    query->sql.clear();

    uint32_t offset = args[0].ToNumber().Int32Value(), rows = 0;
    if (args.Length() > 1) {
      rows = args[1].ToNumber().Int32Value();
    }

    query->sql << "SELECT * FROM (" << currentSql << ") OFFSET " << offset << " ROWS";
    if (rows > 0) {
        query->sql << " FETCH NEXT " << rows << " ROWS ONLY ";
    }

    return scope.Escape(args.This());
}
