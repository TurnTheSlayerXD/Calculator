//
// Created by Professional on 11.12.2022.
//
#include "Counting_Functions.h"
using namespace std;
int find_multiply(const string &expr, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (expr[i] == '*') {
            return i;
        }
    }
    return -1;
}
int find_plus(const string& expr, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (expr[i] == '+') {
            return i;
        }
    }
    return -1;
}

int find_deny(const string& expr, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (expr[i] == '!') {
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
string count(string expr) {
    cout<<expr<<"\n";
    int l = 0, r = expr.length() - 1;
    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == '(') {
            l = i;
        }
        else if (expr[i] == ')') {
            r = i;
            break;
        }
    }
    //deleting useless brackets
    for(int i = 0; i < expr.length(); i++){
        if(i < expr.length() - 1 && i > 0){
            if(expr[i-1] == '(' && expr[i+1] == ')'){
                return count(expr.substr(0, i-1) + expr[i] + expr.substr(i + 2, expr.length() - i - 2));
            }
        }
    }

    int pos;
    if(expr.length() == 1){
        return expr;
    }

    else if(expr.length() == 3 || expr.length() == 2){
        if( (pos = find_multiply(expr, l, r)) != -1){
            if (expr[pos - 1] == '0' || expr[pos + 1] == '0') {
                return "0";
            }
            else {
                return "1";
            }
        }
        else if( (pos = find_plus(expr, l, r)) != -1){
            if (expr[pos - 1] == '1' || expr[pos + 1] == '1') {
                return "1";
            }
            else {
                return "0";
            }
        }
        else if( (pos = find_deny(expr, l, r)) != -1){
            if(expr[pos+1] == '0'){
                return "1";
            }
            else{
                return "0";
            }
        }
        else if( (pos = find_equal(expr, l, r)) != -1){
            if ( (expr[pos - 1] == '0' && '0' == expr[pos + 1]) || (expr[pos - 1] == '1' && '1' == expr[pos + 1])) {
                return "1";
            }
            else {
                return "0";
            }
        }
    }
    else if ((pos = find_deny(expr, l, r)) != -1) {
        if (expr[pos + 1] == '1') {
            return count(expr.substr(0, pos) + '0' + expr.substr(pos + 2, expr.length() - pos - 2));
        }
        if (expr[pos + 1] == '0') {
            return count(expr.substr(0, pos) + '1' + expr.substr(pos + 2, expr.length() - pos - 2));
        }
    }
    else if ((pos = find_equal(expr, l, r)) != -1) {
        if ( (expr[pos - 1] == '0' && '0' == expr[pos + 1]) || (expr[pos - 1] == '1' && '1' == expr[pos + 1])) {
            return count(expr.substr(0, pos-1) + '1' + expr.substr(pos + 2, expr.length() - pos - 2));
        }
        else{
            return count(expr.substr(0, pos-1) + '0' + expr.substr(pos + 2, expr.length() - pos - 2));
        }
    }
    else if ((pos = find_multiply(expr, l, r)) != -1) {
        if (expr[pos - 1] == '0' || expr[pos + 1] == '0') {
            return count(expr.substr(0, pos - 1) + '0' + expr.substr(pos + 2, expr.length() - pos - 2) );
        }
        else {
            return count(expr.substr(0, pos - 1) + '1' + expr.substr(pos + 2, expr.length() - pos - 2) );
        }
    }
    else if ((pos = find_plus(expr, l, r)) != -1) {
        if (expr[pos - 1] == '1' || expr[pos + 1] == '1') {
            return count(expr.substr(0, pos - 1) + '1' + expr.substr(pos + 2, expr.length() - pos - 2) );
        }
        else {
            return count(expr.substr(0, pos - 1) + '0' + expr.substr(pos + 2, expr.length() - pos - 2) );
        }
    }
    return "0";
}