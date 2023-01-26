#include <iostream>
#include <vector>
class BaseCodec {
public:
    virtual ~BaseCodec() {}
    virtual std::string encode(const std::string&) = 0;
};

BaseCodec* getCodec(const std::string& name);
//#include "function.h"
class Reverse : public BaseCodec {
	public:
	Reverse() {}
	std::string encode(const std::string& input) override {
		std::string ans = "";
		for (int i = input.length() - 1 ; i >= 0 ; i--) {
			ans += input.at(i);
		}
		return ans;
	}
};
class Compress : public BaseCodec {
	public:
	Compress() {}
	std::string encode(const std::string& input) override {
		char prev = '\0';
		int cnt = 0;
		std::string ans = "";
		for (int i = 0 ; i < input.length() ; i++) {
			if (prev != input.at(i)) {
				if (cnt > 0) {
					if (cnt == 1) {
						ans += prev;
					}
					else if (cnt == 2) {
						ans = ans + prev + prev;
					}
					else {
						std::string num_str = "";
						while (cnt != 0) {
							num_str = (char)(cnt % 10 + '0') + num_str;
							cnt = cnt / 10;
						}
						ans = ans + num_str + prev;
					}
				}
				prev = input.at(i);
				cnt = 1;
			}
			else {
				cnt++;
			}
		}
		if (cnt == 1) {
			ans += prev;
		}
		else if (cnt == 2) {
			ans = ans + prev + prev;
		}
		else {
			std::string num_str = "";
			while (cnt != 0) {
				num_str = (char)(cnt % 10 + '0') + num_str;
				cnt = cnt / 10;
			}
			ans = ans + num_str + prev;
		}
		return ans;
	}
};
class Delay : public BaseCodec {
	public:
	Delay() {}
	std::string encode(const std::string& input) override {
		std::string tmp = input;
		std::swap(tmp, memory);
		return tmp;
	}
	private:
	std::string memory = "None";
};
BaseCodec* getCodec(const std::string& name) {
	if (name == "Reverse") {
		return new Reverse;
	}
	else if (name == "Compress") {
		return new Compress;
	}
	else if (name == "Delay") {
		return new Delay;
	}
}
//
int main() {
	int Codec_num, Q;
	std::cin >> Codec_num;
	BaseCodec** Codec = new BaseCodec*[Codec_num];
	for (int i = 0; i < Codec_num; i++) {
		std::string op; std::cin >> op;
		Codec[i] = getCodec(op);
	}
	std::cin >> Q;
	while (Q--) {
		int Codec_id;
		std::string input;
		std::cin >> Codec_id >> input;
		std::cout << Codec[Codec_id]->encode(input) << '\n';
	}
	delete[] Codec;
	return 0;
}
