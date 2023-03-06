/*
  Inroads
*/

#include <istream>
#include <string>
#include <utility>

#include "formatError.h"
#include "inroadsDataReader.h"

using namespace std;

InroadsDataReader::InroadsDataReader(std::istream& input, bool debug)
    : DataReader(input, debug) {
}

pair<string, string> InroadsDataReader::readEdge() {
    return readPair<string, string>([&]() { return this->readString(); },
                                    [&]() { return this->readString(); });
}

vector<string> InroadsDataReader::readMessage() {
    requireCharFromStream('M', "Expected message");
    string messageType = readString();
    vector<string> message = {messageType};
    if (messageType == "edge") {
        pair<string, string> edge = readEdge();
        message.push_back(edge.first);
        message.push_back(edge.second);
    } else if (messageType == "error") {
        message.push_back(readString());
    } else if (messageType == "close") {
        // There's nothing else to read.
    }
    requireCharFromStream('$', "Expected message terminator");
    return message;
}
