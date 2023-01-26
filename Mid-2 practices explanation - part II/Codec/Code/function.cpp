#include <sstream>
#include <cassert>
#include "function.h"

class ReverseCodec: public BaseCodec {
    std::string encode(const std::string& in) override {
        return std::string(in.rbegin(), in.rend());
    }
};

class CompressCodec: public BaseCodec {
	std::string encode(const std::string& in) override {
		std::stringstream ss;
		int count = 0;
		char ch = in.front();
		for (size_t i = 0; i < in.size(); i++) {
			if (in[i] == ch) count++;
			else {
				if (count == 1) ss << ch;
				else if (count == 2) ss << ch << ch;
				else ss << count << ch;
				count = 1, ch = in[i];
			}
			if (i == in.size() - 1) {
				if (count == 1) ss << ch;
				else if (count == 2) ss << ch << ch;
				else ss << count << ch;
			}
		}
		return ss.str();
	}
};

class DelayCodec: public BaseCodec {
    std::string memory = "None";
public:
    std::string encode(const std::string& in) override {
		std::string tmp = in;
        std::swap(tmp, memory);
        return tmp;
    }
};

BaseCodec* getCodec(const std::string& type) {
    if (type == "Reverse") {
        return new ReverseCodec;
	} else if (type == "Compress") {
		return new CompressCodec;
    } else if (type == "Delay") {
        return new DelayCodec;
    } else assert(false);
}

