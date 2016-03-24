/*************************************************************************
	> File Name: des.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: 2016/3/21 20:32:27
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

int pc_1[56] = {
    57, 49, 41, 33, 25, 17,  9,  1, 58, 50,
    42, 34, 26, 18, 10,  2, 59, 51, 43, 35,
    27, 19, 11,  3, 60, 52, 44, 36, 63, 55,
    47, 39, 31, 23, 15,  7, 62, 54, 46, 38,
    30, 22, 14,  6, 61, 53, 45, 37, 29, 21,
    13,  5, 28, 20, 12,  4
};
int pc_2[48] = { 
    14, 17, 11, 24,  1,  5,  3, 28, 15,  6,
    21, 10, 23, 19, 12,  4, 26,  8, 16,  7,
    27, 20, 13,  2, 41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};
int pc_2_shift[16] = {
     1,  1,  2,  2,  2,  2,  2,  2,  1,  2,
     2,  2,  2,  2,  2,  1
};
int ip[64] = {
    58, 50, 42, 34, 26, 18, 10,  2, 60, 52,
    44, 36, 28, 20, 12,  4, 62, 54, 46, 38, 
    30, 22, 14,  6, 64, 56, 48, 40, 32, 24, 
    16,  8, 57, 49, 41, 33, 25, 17,  9,  1, 
    59, 51, 43, 35, 27, 19, 11,  3, 61, 53, 
    45, 37, 29, 21, 13,  5, 63, 55, 47, 39, 
    31, 23, 15,  7
};
int ip_[64] = {
    40,  8, 48, 16, 56, 24, 64, 32, 39,  7,
    47, 15, 55, 23, 63, 31, 38,  6, 46, 14,
    54, 22, 62, 30, 37,  5, 45, 13, 53, 21,
    61, 29, 36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27, 34,  2,
    42, 10, 50, 18, 58, 26, 33,  1, 41,  9,
    49, 17, 57, 25
};
int e[48] = {
    32,  1,  2,  3,  4,  5,  4,  5,  6,  7,
     8,  9,  8,  9, 10, 11, 12, 13, 12, 13,
    14, 15, 16, 17, 16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25, 24, 25, 26, 27,
    28, 29, 28, 29, 30, 31, 32, 1
};
int s[8][64] = {{
    14,  4, 13,  1,  2, 15, 11,  8,  3, 10,
     6, 12,  5,  9,  0,  7,  0, 15,  7,  4,
    14,  2, 13,  1, 10,  6, 12, 11,  9,  5,
     3,  8,  4,  1, 14,  8, 13,  6,  2, 11,
    15, 12,  9,  7,  3, 10,  5,  0, 15, 12,
     8,  2,  4,  9,  1,  7,  5, 11,  3, 14,
    10,  0,  6, 13
}, {
    15,  1,  8, 14,  6, 11,  3,  4,  9,  7,
     2, 13, 12,  0,  5, 10,  3, 13,  4,  7,
    15,  2,  8, 14, 12,  0,  1, 10,  6,  9,
    11,  5,  0, 14,  7, 11, 10,  4, 13,  1,
     5,  8, 12,  6,  9,  3,  2, 15, 13,  8,
    10,  1,  3, 15,  4,  2, 11,  6,  7, 12,
     0,  5, 14,  9
}, {
    10,  0,  9, 14,  6,  3, 15,  5,  1, 13,
    12,  7, 11,  4,  2,  8, 13,  7,  0,  9,
     3,  4,  6, 10,  2,  8,  5, 14, 12, 11,
    15,  1, 13,  6,  4,  9,  8, 15,  3,  0,
    11,  1,  2, 12,  5, 10, 14,  7,  1, 10,
    13,  0,  6,  9,  8,  7,  4, 15, 14,  3,
    11,  5,  2, 12
}, {
     7, 13, 14,  3,  0,  6,  9, 10,  1,  2,
     8,  5, 11, 12,  4, 15, 13,  8, 11,  5,
     6, 15,  0,  3,  4,  7,  2, 12,  1, 10,
    14,  9, 10,  6,  9,  0, 12, 11,  7, 13,
    15,  1,  3, 14,  5,  2,  8,  4,  3, 15,
     0,  6, 10,  1, 13,  8,  9,  4,  5, 11,
    12,  7,  2, 14
}, {
     2, 12,  4,  1,  7, 10, 11,  6,  8,  5,
     3, 15, 13,  0, 14,  9, 14, 11,  2, 12,
     4,  7, 13,  1,  5,  0, 15, 10,  3,  9,
     8,  6,  4,  2,  1, 11, 10, 13,  7,  8,
    15,  9, 12,  5,  6,  3,  0, 14, 11,  8,
    12,  7,  1, 14,  2, 13,  6, 15,  0,  9,
    10,  4,  5,  3
}, {
    12,  1, 10, 15,  9,  2,  6,  8,  0, 13,
     3,  4, 14,  7,  5, 11, 10, 15,  4,  2,
     7, 12,  9,  5,  6,  1, 13, 14,  0, 11,
     3,  8,  9, 14, 15,  5,  2,  8, 12,  3,
     7,  0,  4, 10,  1, 13, 11,  6,  4,  3,
     2, 12,  9,  5, 15, 10, 11, 14,  1,  7,
     6,  0,  8, 13
}, {
     4, 11,  2, 14, 15,  0,  8, 13,  3, 12,
     9,  7,  5, 10,  6,  1, 13,  0, 11,  7,
     4,  9,  1, 10, 14,  3,  5, 12,  2, 15,
     8,  6,  1,  4, 11, 13, 12,  3,  7, 14,
    10, 15,  6,  8,  0,  5,  9,  2,  6, 11,
    13,  8,  1,  4, 10,  7,  9,  5,  0, 15,
    14,  2,  3, 12
}, {
    13,  2,  8,  4,  6, 15, 11,  1, 10,  9,
     3, 14,  5,  0, 12,  7,  1, 15, 13,  8,
    10,  3,  7,  4, 12,  5,  6, 11,  0, 14,
     9,  2,  7, 11,  4,  1,  9, 12, 14,  2,
     0,  6, 10, 13, 15,  3,  5,  8,  2,  1,
    14,  7,  4, 10,  8, 13, 15, 12,  9,  0,
     3,  5,  6, 11
}};
int p[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,  1, 15,
    23, 26,  5, 18, 31, 10,  2,  8, 24, 14,
    32, 27,  3,  9, 19, 13, 30,  6, 22, 11,
     4, 25
};

class Key_class {
public:
    deque<unsigned char> init_keys(const string & keys) {
        deque<unsigned char> keys_to_number;
        if(keys.size() != 8) {
            cout << "[E]: You should input 8 character as keys." << endl;
            return keys_to_number;
        }
        for(int i = 0; i < static_cast<int>(keys.size()); ++i) {
            bitset<8> bit(keys[i]);
            for(int j = 7; j >= 0; --j) {
                keys_to_number.push_back(bit[j] + '0');
            }
        }
        return keys_to_number;
    }

    deque<unsigned char> pc_1_keys(deque<unsigned char> & keys_to_number) {
        deque<unsigned char> pc_1_keys_result;
        for(unsigned i = 0; i < sizeof(pc_1) / sizeof(pc_1[0]); ++i) {
            pc_1_keys_result.push_back(keys_to_number[pc_1[i] - 1]);
        }
        return pc_1_keys_result;
    }

    deque<deque<unsigned char>> pc_2_keys(deque<unsigned char> & pc_1_keys_result) {
        deque<deque<unsigned char>> keys;
        deque<unsigned char> keys_left;
        deque<unsigned char> keys_right;
        for(int j = 0; j < 28; ++j) {
            keys_left.push_back(pc_1_keys_result[j]);
            keys_right.push_back(pc_1_keys_result[j + 28]);
        }
        for(int i = 0; i < 16; ++i) {
            int left_right = pc_2_shift[i];
            deque<unsigned char> keys_left_right_pc_2;
            deque<unsigned char> pc_2_keys_left_right_pc_2;
            while(left_right > 0) { // pc_2 shift left & right
                keys_left.push_back(keys_left[0]);
                keys_left.pop_front();
                keys_right.push_back(keys_right[0]);
                keys_right.pop_front();
                --left_right;
            }
            for(int j = 0; j < 28; ++j) {
                keys_left_right_pc_2.push_back(keys_left[j]);
            }
            for(int j = 0; j < 28; ++j) {
                keys_left_right_pc_2.push_back(keys_right[j]);
            }
            for(int j = 0; j < 48; ++j) {
                pc_2_keys_left_right_pc_2.push_back(keys_left_right_pc_2[pc_2[j] - 1]);
            }
            keys.push_back(pc_2_keys_left_right_pc_2); 
        }
        return keys;
    }

    deque<deque<unsigned char>> init(string & keys) {
        cout << "[I]: The current keys is \"" << keys << "\"." << endl;
        deque<unsigned char> keys_to_number = init_keys(keys);
        if(keys_to_number.size()) 
            cout << "[I]: Changing keys to number...(OK)" << endl;
        else {
            cout << "[E]: Changing keys to number...(Failed)" << endl;
            exit(0);
        }
        deque<unsigned char> pc_1_keys_result = pc_1_keys(keys_to_number);
        if(pc_1_keys_result.size()) 
            cout << "[I]: Operate keys in pc 1...(OK)" << endl;
        else {
            cout << "[E]: Operate keys in pc 1...(Failed)" << endl;
            exit(0);
        }
        deque<deque<unsigned char>> keys_arry = pc_2_keys(pc_1_keys_result);
        if(keys_arry.size()) 
            cout << "[I]: Creating keys...(OK)" << endl;
        else {
            cout << "[E]: Creating keys...(Failed)" << endl;
            exit(0);
        }
        return keys_arry;
    }
};

class File_class {
public:
    deque<unsigned char> init_file_data_encrypt(unsigned char buffer[]) {
        deque<unsigned char> buffer_to_number;
        for(int i = 0; i < 8; ++i) {
            bitset<8> bit(buffer[i]);
            for(int j = 7; j >= 0; --j) {
                buffer_to_number.push_back(bit[j] + '0');
            }
        }
        return buffer_to_number;
    }

    deque<unsigned char> init_file_data_decrypt(unsigned char buffer[]) {
        deque<unsigned char> buffer_to_number;
        for(int i = 0; i < 64; ++i) {
            buffer_to_number.push_back(buffer[i]);
        }
        return buffer_to_number;
    }

    deque<unsigned char> ultimate_file_data_decrypt(deque<unsigned char> decrypt_result) {
        deque<unsigned char> ultimate_decrypt_data;
        for(int i = 0; i < 8; ++i) {
            int sum = 0;
            for(int j = 0; j < 8; ++j) {
                if(decrypt_result[i * 8 + j] == '1') {
                    sum += pow(2, 7 - j);
                }
            }
            unsigned char c = sum;
            ultimate_decrypt_data.push_back(c); 
        }
        return ultimate_decrypt_data;
    }

    deque<unsigned char> ip_file_data(deque<unsigned char> & buffer_to_number) {
        deque<unsigned char> ip_buffer_to_number;
        for(int i = 0; i < 64; ++i) {
            ip_buffer_to_number.push_back(buffer_to_number[ip[i] - 1]);
        }
        return ip_buffer_to_number; // buffer to char
    }
    
    deque<unsigned char> encrypt(deque<unsigned char> & ip_buffer_to_number, deque<deque<unsigned char>> & keys_arry) {
        deque<unsigned char> e_ip_buffer_to_number;
        deque<unsigned char> s_e_ip_buffer_to_number;
        deque<unsigned char> p_s_e_ip_buffer_to_number;
        deque<unsigned char> _ip_s_e_ip_buffer_to_number;

        for(int i = 0; i < 16; ++i) {
            deque<unsigned char> temp_ip_buffer_to_number(64, '0');
            e_ip_buffer_to_number = {}; // Empty e_ip_buffer_to_number
            for(int j = 0; j < 48; ++j) {
                e_ip_buffer_to_number.push_back(ip_buffer_to_number[e[j] + 31]); // E operate
            }
            for(int j = 0; j < 48; ++j) { // key ^ e
                if(e_ip_buffer_to_number[j] == keys_arry[i][j])
                    e_ip_buffer_to_number[j] = '0';
                else 
                    e_ip_buffer_to_number[j] = '1';
            }
            s_e_ip_buffer_to_number = {}; // Empty s_e_ip_buffer_to_number
            for(int j = 0; j < 8; ++j) { // s
                int x = (e_ip_buffer_to_number[j * 6] - '0') * 2 
                    + e_ip_buffer_to_number[j * 6 + 5] - '0';
                int y = (e_ip_buffer_to_number[j * 6 + 1] - '0') * 8 
                    + (e_ip_buffer_to_number[j * 6 + 2] - '0') * 4
                    + (e_ip_buffer_to_number[j * 6 + 3] - '0') * 2
                    + e_ip_buffer_to_number[j * 6 + 4] - '0';
                bitset<4> bit(s[j][x * 16 + y]);
                for(int k = 3; k >= 0; --k) {
                    s_e_ip_buffer_to_number.push_back(bit[k] + '0');
                }
            }
            p_s_e_ip_buffer_to_number = {}; // Empty p_s_e_ip_buffer_to_number
            for(int j = 0; j < 32; ++j) { // p
                p_s_e_ip_buffer_to_number.push_back(s_e_ip_buffer_to_number[p[j] - 1]);
            }
            for(int j = 0; j < 32; ++j) {
                if(ip_buffer_to_number[j] == p_s_e_ip_buffer_to_number[j])
                    temp_ip_buffer_to_number[j + 32] = '0';
                else
                    temp_ip_buffer_to_number[j + 32] = '1';
                temp_ip_buffer_to_number[j] = ip_buffer_to_number[j + 32];
            }
            ip_buffer_to_number = temp_ip_buffer_to_number;
        }
        for(int i = 0; i < 32; ++i) {
            swap(ip_buffer_to_number[i], ip_buffer_to_number[i + 32]);
        }
        for(int i = 0; i < 64; ++i) { // ip_
            _ip_s_e_ip_buffer_to_number.push_back(ip_buffer_to_number[ip_[i] - 1]);
        }
        return _ip_s_e_ip_buffer_to_number;
    }

    deque<unsigned char> decrpyt(deque<unsigned char> & ip_buffer_to_number, deque<deque<unsigned char>> & keys_arry) {
        deque<unsigned char> e_ip_buffer_to_number;
        deque<unsigned char> s_e_ip_buffer_to_number;
        deque<unsigned char> p_s_e_ip_buffer_to_number;
        deque<unsigned char> _ip_s_e_ip_buffer_to_number;

        for(int i = 15; i >= 0; --i) {
            deque<unsigned char> temp_ip_buffer_to_number(64, '0');
            e_ip_buffer_to_number = {}; // Empty e_ip_buffer_to_number
            for(int j = 0; j < 48; ++j) {
                e_ip_buffer_to_number.push_back(ip_buffer_to_number[e[j] + 31]); // E operate
            }
            for(int j = 0; j < 48; ++j) { // key ^ e
                if(e_ip_buffer_to_number[j] == keys_arry[i][j])
                    e_ip_buffer_to_number[j] = '0';
                else 
                    e_ip_buffer_to_number[j] = '1';
            }
            s_e_ip_buffer_to_number = {}; // Empty s_e_ip_buffer_to_number
            for(int j = 0; j < 8; ++j) { // s
                int x = (e_ip_buffer_to_number[j * 6] - '0') * 2 
                    + e_ip_buffer_to_number[j * 6 + 5] - '0';
                int y = (e_ip_buffer_to_number[j * 6 + 1] - '0') * 8 
                    + (e_ip_buffer_to_number[j * 6 + 2] - '0') * 4
                    + (e_ip_buffer_to_number[j * 6 + 3] - '0') * 2
                    + e_ip_buffer_to_number[j * 6 + 4] - '0';
                bitset<4> bit(s[j][x * 16 + y]);
                for(int k = 3; k >= 0; --k) {
                    s_e_ip_buffer_to_number.push_back(bit[k] + '0');
                }
            }
            p_s_e_ip_buffer_to_number = {}; // Empty p_s_e_ip_buffer_to_number
            for(int j = 0; j < 32; ++j) { // p
                p_s_e_ip_buffer_to_number.push_back(s_e_ip_buffer_to_number[p[j] - 1]);
            }
            for(int j = 0; j < 32; ++j) {
                if(ip_buffer_to_number[j] == p_s_e_ip_buffer_to_number[j])
                    temp_ip_buffer_to_number[j + 32] = '0';
                else
                    temp_ip_buffer_to_number[j + 32] = '1';
                temp_ip_buffer_to_number[j] = ip_buffer_to_number[j + 32];
            }
            ip_buffer_to_number = temp_ip_buffer_to_number;
        }
        for(int i = 0; i < 32; ++i) {
            swap(ip_buffer_to_number[i], ip_buffer_to_number[i + 32]);
        }
        for(int i = 0; i < 64; ++i) { // ip_
            _ip_s_e_ip_buffer_to_number.push_back(ip_buffer_to_number[ip_[i] - 1]);
        }
        return _ip_s_e_ip_buffer_to_number;
    }

    deque<unsigned char> init_encrypt(unsigned char buffer[], deque<deque<unsigned char>> keys_arry) {
        deque<unsigned char> buffer_to_number = init_file_data_encrypt(buffer);
        deque<unsigned char> ip_buffer_to_number = ip_file_data(buffer_to_number);
        deque<unsigned char> encrypt_result = encrypt(ip_buffer_to_number, keys_arry);
        return encrypt_result;
    }

    deque<unsigned char> init_decrypt(unsigned char buffer[], deque<deque<unsigned char>> keys_arry) {
        deque<unsigned char> buffer_to_number = init_file_data_decrypt(buffer);
        deque<unsigned char> ip_buffer_to_number = ip_file_data(buffer_to_number);
        deque<unsigned char> decrypt_result = decrpyt(ip_buffer_to_number, keys_arry);
        deque<unsigned char> ultimate_decrypt_data = ultimate_file_data_decrypt(decrypt_result);
        return ultimate_decrypt_data;
    }
};

void encrypt(string origin_filename, string keys) {
    int index = 0;
    char buffer_c;
    unsigned char buffer[8];
    string encrypt_filename;

    encrypt_filename = origin_filename + ".des";
    ifstream fin(origin_filename.c_str());
    ofstream fout(encrypt_filename.c_str());
    if(fin.fail() || fout.fail()) {
        cout << "[E]: Open file failed." << endl;
        exit(0);
    }
    Key_class test;
    deque<deque<unsigned char>> keys_arry = test.init(keys);
    File_class test_file;
    deque<unsigned char> result;
    
    while(fin.get(buffer_c)) {
        buffer[index] = buffer_c;
        if(index == 7) {
            result = test_file.init_encrypt(buffer, keys_arry);
            for(int i = 0; i < 64; ++i) {
                fout << result[i];
            }
        }
        index++;
        index %= 8;
    }
    while(index < 8) {
        buffer[index] = 0x0a;
        index++;
    }
    result = test_file.init_encrypt(buffer, keys_arry);
    for(int i = 0; i < 64; ++i) {
        fout << result[i];
    }
    fin.close();
    fout.close();
}

void decrypt(string encrypt_filename, string keys) {
    int index = 0;
    char buffer_c;
    unsigned char buffer[64];
    string filename_out = "__";

    for(unsigned i = 0; i < encrypt_filename.size() - 4; ++i) {
        filename_out += encrypt_filename[i];
    }
    ifstream fin(encrypt_filename.c_str());
    ofstream fout(filename_out.c_str());
    if(fin.fail() || fout.fail()) {
        cout << "[E]: Open file failed." << endl;
        exit(0);
    }
    Key_class test;
    deque<deque<unsigned char>> keys_arry = test.init(keys);
    File_class test_file;
    deque<unsigned char> result;
    
    while(fin.get(buffer_c)) {
        buffer[index] = buffer_c;
        if(index == 63) {
            result = test_file.init_decrypt(buffer, keys_arry);
            for(int i = 0; i < 8; ++i) {
                fout << result[i];
            }
        }
        index++;
        index %= 64;
    }
    fin.close();
    fout.close();
}

int main(int argc, char * argv[]) {
    string filename;
    string keys = "abcdefgh";

    if(argc != 5) {
        cout << "Usage:" << endl;
        cout << "\t-e [] file name for encryption" << endl;
        cout << "\t-d [] file name for decryption" << endl;
        cout << "\t-p [] password" << endl;
        cout << "eg: des -d a.txt -p \"hahahaha\"" << endl;
        return 0;
    } 
    string op1 = argv[1];
    string op2 = argv[3];
    if((op1 == "-e" || op1 == "-d") && op2 == "-p") {
        filename = argv[2];
        keys = argv[4];
        if(op1 == "-e")
            encrypt(filename, keys);
        else
            decrypt(filename, keys);
    }
    else if(op1 == "-p" && (op2 == "-d" || op2 == "-e")) {
        filename = argv[4];
        keys = argv[2];
        if(op1 == "-e")
            encrypt(filename, keys);
        else
            decrypt(filename, keys);
    }
    else {
        cout << "You input is error!" << endl;
        return -1;
    }
    return 0;
}
