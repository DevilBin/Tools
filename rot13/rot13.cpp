/*************************************************************************
	> File Name: rot13.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: 2016/4/8 20:42:33
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
    string key = "xrlvf23xfqwsxsqf";
    cout << "Input rot13 string:" << endl;
    while(cin >> key) {
        for(unsigned i = 0; i < key.size(); ++i) {
            if((key[i] >= 'A' && key[i] <= 'M') || (key[i] >= 'a' && key[i] <= 'm')) {
                key[i] += 13;
            }
            else if((key[i] >= 'N' && key[i] <= 'Z') || (key[i] >= 'n' && key[i] <= 'z')) {
                key[i] -= 13;
            }
        }
        cout << key << endl;
    }
    return 0;
}
