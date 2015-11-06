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

// ATMWebService.cpp : Defines the entry point for the console application.
//

#include <cpprest/http_listener.h>
#include "DataController.h"
#include <iostream>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#define TRACE(msg)            wcout << msg


// Handle get requests.
static void handle_get(http_request request)
{
    TRACE(L"\nhandle GET\n");
    json::value answer = json::value::object();

    DataController::instance()->get(request.request_uri().to_string(), answer);
    request.reply(status_codes::OK, answer);
}


// Handle post requests.
static void handle_post(http_request request)
{
    TRACE("\nhandle POST\n");

    json::value answer;

    request
        .extract_json()
        .then([&answer, request](pplx::task<json::value> task) {
        try {
            auto &jvalue = task.get();
            if (!jvalue.is_null()) {
                DataController::instance()->put(request.request_uri().to_string(), jvalue, answer);
            }
        } catch (http_exception const & e) {
            wcout << e.what() << endl;
        }
    })
        .wait();

    request.reply(status_codes::OK, answer);
}


int main()
{
    http_listener listener(DataController::kUriString());
    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);

    // Handle incoming requests.
    try {
        listener
            .open()
            .then([&listener]() {TRACE(L"\nstarting to listen\n");})
            .wait();

        while (true);
    }
    catch (exception const & e) {
        wcout << e.what() << endl;

    }

    return 0;
}