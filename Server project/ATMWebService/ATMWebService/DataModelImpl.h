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
#include <assert.h>
#include "DataModel.h"
#include <unordered_map>


class DataModelImpl : public DataModel
{
public:
    static const int kNotFound = -1;

    DataModelImpl();
    ~DataModelImpl() = default;

    int ballance(const utility::string_t &cardId) const {
        auto it = _dictionary.find(cardId);
        if (it != _dictionary.end()) {
            return it->second;
        }
        return kNotFound;
    }

    void setBallance(const utility::string_t &cardId, int ballance) {
        assert(_dictionary.find(cardId) != _dictionary.end());
        _dictionary[cardId] = ballance;
    }

private:

    void _generateData();

    std::unordered_map<utility::string_t, int> _dictionary;
};
