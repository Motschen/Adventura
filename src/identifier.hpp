#pragma once
#include <string>

using std::string;

class Identifier {
public:
    std::string nameSpace;
    std::string path;

    Identifier(std::string nameSpace, std::string path) : nameSpace(nameSpace), path(path) {}

    std::ostream& operator<<(std::ostream& out) {
        out << nameSpace << ":" << path;
        return out;
    }
    std::istream& operator>>(std::istream& in) {
        string input;
        in >> input;
        nameSpace = input.substr(0, input.find(":"));
        path = input.substr(input.find(":") + 1, input.length());
        return in;
    }
    bool operator==(Identifier otherId) {
      return this->nameSpace == otherId.nameSpace && this->path == otherId.path;
    }
};
