#pragma once
#include <string>

using std::string;

class Identifier {
public:
    std::string nameSpace_;
    std::string path_;


    /**
     * Construct a new Identifier.
     * Identifiers are used to uniquely identify blocks, regardless of their encoding.
     * 
     * @param nameSpace The namespace of the Identifier.
     * @param path The path of the Identifier.
     */
    Identifier(std::string nameSpace, std::string path) : nameSpace_(nameSpace), path_(path) {}

    std::ostream& operator<<(std::ostream& out) {
        out << nameSpace_ << ":" << path_;
        return out;
    }
    std::istream& operator>>(std::istream& in) {
        string input;
        in >> input;
        nameSpace_ = input.substr(0, input.find(":"));
        path_ = input.substr(input.find(":") + 1, input.length());
        return in;
    }
    bool operator==(Identifier otherId) {
      return this->nameSpace_ == otherId.nameSpace_ && this->path_ == otherId.path_;
    }
};
