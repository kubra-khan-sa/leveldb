// -------------------------------------------------------------------
//
// expiry.h:  background expiry management for Basho's modified leveldb
//
// Copyright (c) 2016 Basho Technologies, Inc. All Rights Reserved.
//
// This file is provided to you under the Apache License,
// Version 2.0 (the "License"); you may not use this file
// except in compliance with the License.  You may obtain
// a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// -------------------------------------------------------------------

#ifndef EXPIRY_H
#define EXPIRY_H 1

namespace leveldb {

class Slice;
class Logger;

class ExpiryModule
{
public:
    ExpiryModule() {};
    ~ExpiryModule() {};

    // Print expiry options to LOG file
    virtual void Dump(Logger * log) const = 0;

    // db/write_batch.cc MemTableInserter::Put() calls this.
    //  using uint8_t and uint64_t types instead of ValType and ExpiryTime
    //  to prevent exposing internal db/dbformat.h
    // returns false on internal error
    virtual bool MemTableInserterCallback(
        const Slice & Key,   // input: user's key about to be written
        const Slice & Value, // input: user's value object
        uint8_t & ValType,   // input/output: key type. call might change
        uint64_t & Expiry)   // input/output: 0 or specific expiry. call might change
    {return(true);};

};  // ExpiryModule


} // namespace leveldb

#endif // ifndef
