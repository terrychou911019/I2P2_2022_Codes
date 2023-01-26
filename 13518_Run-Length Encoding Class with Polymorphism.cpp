#include <iostream>
#include <string>

class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }


    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};
//#include "function.h"
#include <sstream>
void RleCodec::encode()
{
    // Your code here
    std::stringstream ss;
    char prev = '\0';
    int cnt = 0;
    for (auto c : code_str) {
        if (c != prev) {
            if (cnt > 0) {
                if (cnt == 1) ss << prev;
                else if (cnt == 2) ss << prev << prev;
                else ss << cnt << prev;
            }
            prev = c;
            cnt = 1;
        }
        else {
            cnt++;
        }
    }
    if (cnt > 0) {
        if (cnt == 1) ss << prev;
        else if (cnt == 2) ss << prev << prev;
        else ss << cnt << prev;
    }
    code_str = ss.str();
    encoded = true;
}

void RleCodec::decode()
{
    std::stringstream os;
    std::string int_str;
    for (auto c : code_str) {
        if (std::isdigit(c)) {
            int_str.push_back(c);
        } else {
            int cnt = 0;
            std::stringstream is{int_str};
            is >> cnt;
            if (cnt==0) {
                os << c;
            } else {
                for (int i=0; i<cnt; ++i)
                    os << c;
            }
            int_str.clear();
        }
    }

    code_str = os.str();
    encoded = false;

}
//

std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}


int main()
{
    std::string input_string;
    std::cin >> input_string;

    DummyCodec dummy{input_string};
    encode_decode(dummy);
    std::cout << "Dummy encoding: ";
    std::cout << dummy << std::endl;
    encode_decode(dummy);
    std::cout << "Dummy decoding: ";
    std::cout << dummy << std::endl;

    RleCodec rle{input_string};
    encode_decode(rle);
    std::cout << "RLE encoding: ";
    std::cout << rle << std::endl;
    encode_decode(rle);
    std::cout << "RLE decoding: ";
    std::cout << rle << std::endl;
}
