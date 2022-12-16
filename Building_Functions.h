//
// Created by Professional on 11.12.2022.
//

#ifndef DISCRETE_MATH_BUILDING_FUNCTIONS_H
#define DISCRETE_MATH_BUILDING_FUNCTIONS_H
#include<string.h>
#include "Counting_Functions.h"
#include "Building_Functions.h"
#include<math.h>
using namespace std;

class Polynom {
public:
    vector<char> symbols;

    void push_symbols(const string &str);

    void swap(char &a, char &b);

    int find_order(char x);

    void sort();

    char *convert_to_bin(int x, int size);

    int *create_listOFvalues(const string &expr);

    string build_polynom(int *value, int N);

};

#endif //DISCRETE_MATH_BUILDING_FUNCTIONS_H
