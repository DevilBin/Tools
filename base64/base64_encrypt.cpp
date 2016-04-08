/*************************************************************************
	> File Name: base64_encrypt.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: 2016/4/8 21:18:31
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
#include <bitset>

using namespace std;

int main() {
    string input;
    string symbol = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    cout << "Input string to base64 encrypt:" << endl;
    while(cin >> input) {
        string result;
        for(int i = 0; i < static_cast<int>(input.size()); i += 3) {
            vector<int> bin;
            int flag = 0;
            for(int j = 0; j < 3; ++j) {
                if(i + j < static_cast<int>(input.size())) {
                    bitset<8> bit(input[i + j]);
                    for(int k = 7; k >= 0; --k) {
                        bin.push_back(bit[k]);
                    }
                }
                else {
                    ++flag;
                }
            }
            for(int j = 0; j < 24; j += 6) {
                int sum = 0;
                for(int k = 0; k < 6; ++k) {
                    if(bin[j + k] == 1) {
                        sum += pow(2, 5 - k);
                    }
                }
                result += symbol[sum];
            }
            while(flag > 0) {
                result[result.size() - flag] = '=';
                --flag;
            }
        }
        cout << result << endl;
    }
    return 0;
}
