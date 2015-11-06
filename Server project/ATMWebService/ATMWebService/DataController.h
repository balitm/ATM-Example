/*
Copyright (c) 2015 Balazs Kilvady

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "DataModel.h"
#include <cpprest\json.h>
#include <cpprest\asyncrt_utils.h>
using namespace web;


// Controls data handling for the web service.
class DataController
{
public:
    static const utility::string_t kUrlString;
    static const utility::string_t kBaseTag;

    static const utility::string_t kUriString() { return kUrlString + kBaseTag; }

    // Singleton instance.
    static DataController *instance() {
        if (_instance == nullptr) {
            _instance = new DataController;
        }
        return _instance;
    }

    ~DataController() = default;

    // Give JSon answer to a get request (== get ballance).
    void get(const utility::string_t &uriString, json::value &answer) const;

    // Give JSon answer to a put request (== do withdrawal).
    void put(const utility::string_t &uriString, const json::value &input, json::value &answer);

private:
    DataController() : _model(DataModel::factory()) {}
    static DataController *_instance;

    DataModel *_model;
};

