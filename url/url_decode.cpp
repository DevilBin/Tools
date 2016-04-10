/*************************************************************************
	> File Name: url_decode.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: 2016/4/10 15:39:46
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
    string s = "http://lab1.xseclab.com/sqli4_9b5a929e00e122784e44eddf2b6aa1a0/index.php?id=2%df'%20union%20select%204,database%28%29,user%28%29%23";
    unsigned index = 0;
    while(index < s.size()) {
        switch(s[index]) {
            case '%': {
                if(s[index + 1] == '2' && s[index + 2] == '0') {
                    temp += ' ';
                }
                else if(s[index + 1] == '2' && s[index + 2] == '8') {
                    temp += '(';
                }
                else if(s[index + 1] == '2' && s[index + 2] == '9') {
                    temp += ')';
                }
                else if(s[index + 1] == '2' && s[index + 2] == '3') {
                    temp += '#';
                }
                index += 3;
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
