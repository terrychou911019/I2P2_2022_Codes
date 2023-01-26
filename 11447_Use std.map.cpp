#include<cassert>
#include<iostream>
#include<map>
#include<ostream>
#include<string>
#include<cstddef>
//#include<map>
//#include<string>

namespace oj
{
	struct String
	{
		std::string str;
		String(const std::string &);
		String(const String &);
		String& operator=(const String &);
	};

	std::ostream& operator<<(std::ostream &,const String &);

	void insert(std::map<int,String> &ma,int key,const std::string &str);
	void output(const std::map<int,String> &ma,int begin,int end);
	void erase(std::map<int,String> &ma,int begin,int end);

	std::ostream& operator<<(std::ostream &,const std::map<int,String> &);
}
//#include"function.h"
//#include <iostream>
#include <set>
using namespace std;
namespace oj {
	void insert(std::map<int,String> &ma,int key,const std::string &str) {
		if (ma.find(key) != ma.end()) {
			String n(str + ma.find(key)->second.str);
			ma.erase(key);
			ma.insert(pair<int, String>(key, n));
		}
		else {
			String n(str);
			ma.insert(pair<int, String>(key, n));
		}
	}
	void output(const std::map<int,String> &ma,int begin,int end) {
		for (auto it = ma.begin() ; it != ma.end() ; it++) {
			if ((it->first >= begin && it->first <= end)) {
				cout << it->second << " ";
			}
		}
	}
	/*int flag = 0;
	void erase(std::map<int,String> &ma,int begin,int end) {
		for (auto it = ma.begin() ; it != ma.end() ; flag == 1 ? it = it : it++) {
			flag = 0;
			if ((it->first >= begin && it->first <= end)) {
				auto tmp = it++;
				ma.erase(tmp->first);
				flag = 1;
			}
		}
	}*/
	void erase(std::map<int,String> &ma,int begin,int end) {
		set<int> e;
		for (auto it : ma) {
			if (it.first >= begin && it.first <= end) {
				e.insert(it.first);
			}
		}
		for (auto it : e) {
			ma.erase(it);
		}
	}
	std::ostream& operator<<(std::ostream &os,const std::map<int,String> &m) {
		for (auto it = m.begin() ; it != m.end() ; it++) {
			os << it->second << " ";
		}
		return os;
	}
}
//

namespace oj
{
	String::String(const std::string &str_)
		:str(str_){}

	String::String(const String &rhs)
		:str(rhs.str){}

	String& String::operator=(const String &rhs)
	{
		str=rhs.str;
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const String &str)
	{
		return os<<str.str;
	}
}

int main()
{
	using namespace std;
	using namespace oj;
	map<int,String> ma;
	for(string cmd;cin>>cmd;)
	{
		if(cmd=="insert")
		{
			int key;
			cin>>key>>cmd;
			insert(ma,key,cmd);
		}
		else
			if(cmd=="range")
			{
				int begin,end;
				cin>>cmd>>begin>>end;
				if(cmd=="output")
					output(ma,begin,end);
				else
					if(cmd=="erase")
						erase(ma,begin,end);
					else
						assert(false);
			}
			else
				assert(false);
		cout<<ma<<endl;
	}
}