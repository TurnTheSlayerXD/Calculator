//
// Created by Professional on 11.12.2022.
//
#include "Building_Functions.h"
using namespace std;
void Polynom:: push_symbols(const string& str) {
    bool buf;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != '0' && str[i] != '1'
            && str[i] != '*' && str[i] != '+'
            && str[i] != '(' && str[i] != ')' && str[i] != '!' && str[i] != '=')
        {
            buf = false;
            for(int j = 0; j < symbols.size(); j++){
                if(symbols[j] == str[i]){
                    buf = true;
                    break;
                }
            }
            if(buf == false) {
                symbols.push_back(str[i]);
            }
        }
    }
}

void Polynom:: swap(char& a, char& b){
    char buf = a;
    a = b;
    b = a;
}

int Polynom::find_order(char x){
    for(int i = 0; i < symbols.size(); i++){
        if(symbols[i] == x){
            return i;
        }
    }
    return -1;
}

void Polynom:: sort(){
    for(int i = 1; i < symbols.size(); i++){
        for(int j = i; j > 0 && (symbols[j] - 'a' < symbols[j-1] - 'a'); j--){
            swap(symbols[j-1], symbols[j]);
        }
    }
}

char* Polynom::convert_to_bin(int x, int size){
    char* num = new char[size];
    memset(num,'0',size);
    for(int i = size - 1; x >= 1; x = x/2, i--){
        if(x % 2 == 1){
            num[i] = '1';
        }
    }
    return num;
}

int* Polynom::create_listOFvalues(const string& expr){
    string buf = expr;
    push_symbols(buf);
    sort();
    int size = symbols.size();
    int *res = new int[int(pow(2, size))];
    char* bin_num;
    for(int value = 0; value < pow(2, size); value++){
        bin_num = convert_to_bin(value, size);
        for(int i = 0; i < buf.length(); i++){
            if (buf[i] != '0' && buf[i] != '1'
                && buf[i] != '*' && buf[i] != '+'
                && buf[i] != '(' && buf[i] != ')' && buf[i] != '!' && buf[i] != '=')
            {
                buf[i] = bin_num[find_order(buf[i] )];
            }
        }
        res[value] = stoi(count(buf));
        buf = expr;
    }
    delete []bin_num;
    return res;
}

string Polynom::build_polynom(int* value, int N){
    int hor = N + 1;
    int ver = int( pow(2,N) );
    int** table = new int*[hor];
    for(int i = 0; i < hor; i++){
        table[i] = new int[ver];
    }

    for(int i = 0; i < hor; i++){
        for(int j = 0; j < ver; j++){
            table[i][j] = 0;
        }
    }

    for(int j = 0; j < ver; j++){
        table[0][j] = value[j];
    }

    for(int i = 1; i < hor; i++){
        for(int j = 0;  j < ver; j = j+int(pow(2,i)) ){
            for(int k = 0; k < int(pow(2,i))/2; k++){
                table[i][j+k] = table[i-1][j+k];
            }
            for(int k = 0; k < int(pow(2,i))/2; k++){
                if(table[i-1][j + int(pow(2,i))/2 + k] != table[i-1][j+k]){
                    table[i][j + int(pow(2,i))/2 + k] = 1;
                }
            }
        }
    }

    string polynom = "";
    if(table[hor-1][0] == 1){
        polynom += "1 XOR ";
    }

    char* bin_name = new char;
    string minterm;
    for(int i = 1; i < ver; i++){
        if(table[hor-1][i] == 1) {
            minterm = "";
            bin_name = convert_to_bin(i,N);
            for (int j = 0; j < N; j++) {
                if (bin_name[j] == '1') {
                    minterm += symbols[j];
                }
            }
            polynom += (minterm + " XOR ");
        }
    }

    polynom = polynom.substr(0,polynom.length()-4);

    delete[]bin_name;
    return polynom;
}
