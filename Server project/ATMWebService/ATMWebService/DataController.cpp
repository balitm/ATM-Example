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

#include "DataController.h"
#include <assert.h>
#include <cpprest\asyncrt_utils.h>
#include <cpprest\http_msg.h>
#include <iostream>

using namespace std;
using namespace web::http;


// Constants
const utility::string_t DataController::kUrlString = U("http://*");
const utility::string_t DataController::kBaseTag = U("/atm");

// Instance
DataController *DataController::_instance = nullptr;

static const utility::string_t kKeyBallance= L"ballance";
static const utility::string_t kKeyAmount= L"amount";
static const utility::string_t kKeyPicture = L"picture";


void DataController::get(const utility::string_t &uriString, json::value &answer) const
{
    try {
        wcout << L"URI: " << uriString << '\n';
        if (uriString.length() >= kBaseTag.length() + 1) {
            utility::string_t cardId = uriString.substr(kBaseTag.length() + 1);
            wcout << L"Card ID: " << cardId << endl;
            int ballance = _model->ballance(cardId);
            wcout << L"ballance: " << ballance << endl;
            answer[kKeyBallance] = ballance;
        }
    } catch (http_exception const &e) {
        wcout << e.what() << endl;
    }
}

void DataController::put(const utility::string_t &uriString, const json::value &input, json::value &answer)
{
    assert(input.is_object());
    try {
        wcout << L"URI: " << uriString << '\n';
        if (uriString.length() >= kBaseTag.length() + 1) {
            utility::string_t cardId = uriString.substr(kBaseTag.length() + 1);
            wcout << L"Card ID: " << cardId << endl;
            int amount = input.at(kKeyAmount).as_integer();
            int ballance = _model->ballance(cardId);
            wcout << L"ballance: " << ballance << L", amount: " << amount << endl;
            if (input.at(kKeyPicture).is_string()) {
                wcout << L"picture data arrived\n";
            }
            json::value result(amount < ballance ? ballance - amount : DataModel::kNotFound);
            wcout << L"result: " << result.as_integer() << endl;
            answer[kKeyBallance] = result;
        }
    } catch (http_exception const &e) {
        wcout << e.what() << endl;
    }
}