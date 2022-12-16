//
// Created by Professional on 16.12.2022.
//

#ifndef CALCULATOR_FUNCTIONS_H
#define CALCULATOR_FUNCTIONS_H
#include <iostream>
#include <vector>
using namespace std;
bool check_BKT(const string& str, int l, int r);

int find_multiply(const string &expr, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (expr[i] == '*' && check_BKT(expr,i,r)) {
            return i;
        }
    }
    return -1;
}
int find_plus(const string& expr, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (expr[i] == '+' && check_BKT(expr,i,r)) {
            return i;
        }
    }
    return -1;
}

int find_deny(const string& expr, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (expr[i] == '!' && check_BKT(expr,i,r)) {
            return i;
        }
    }
    return -1;
}
int find_equal(const string& expr, int l, int r){
    for(int i = l; i <= r; i++){
        if(expr[i] == '='){
            return i;
        }
    }
    return -1;
}

bool check_BKT(const string& str, int l, int r){
    vector<char> BKT;
    for(int i = l; i <= r; i++){
        if(str[i] == '('){
            BKT.push_back('(');
        }
        if(str[i] == ')'){
            if(BKT.size() < 1){
                return false;
            }
            BKT.pop_back();
        }
    }
    if(BKT.empty()){
        return true;
    }
    return false;
}

int count(string expr) {
    cout<<expr<<"\n";
    int l = 0, r = expr.length() - 1;
    if(expr[0] == '(' && expr[expr.length()-1] == ')' && check_BKT(expr,1,expr.length()-2) == true){
        return count(expr.substr(1,expr.length()-2));
    }
    //deleting useless brackets
    int pos;
    if ((pos = find_plus(expr, l, r)) != -1) {
        return count(expr.substr(l, pos)) + count(expr.substr(pos + 1,r - pos));
    }
    else if ((pos = find_multiply(expr, l, r)) != -1) {
        return count(expr.substr(l, pos)) * count(expr.substr(pos + 1,r - pos));
    }
    else if ((pos = find_deny(expr, l, r)) != -1) {
        return !count(expr.substr(l, pos));
    }
    else{
        return stoi(expr);
    }
}
#endif //CALCULATOR_FUNCTIONS_H
