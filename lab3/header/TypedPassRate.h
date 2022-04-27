//
// Created by makmn on 3/27/2022.
//

#ifndef CISC_3142_LAB_3_TYPEDPASSRATE_H
#define CISC_3142_LAB_3_TYPEDPASSRATE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class TypedPassRate {
    public:
        TypedPassRate();

    void processClass(const vector<basic_string<char>> &key, vector<basic_string<char>> &grades, int keyIndex);

    void processClassByTwoTypes(const vector<basic_string<char>> &key, vector<basic_string<char>> &grades, int keyIndex1, int keyIndex2);

    map<vector<string>, vector<double>> termsToSeason();

    void printRates(vector<string> reportType, FILE *pFile);

    map<vector<string>, vector<double>> passRateMap;

    static vector<double> gradeRatesByInstructorMapHelper(vector<basic_string<char>> &grades);

    static double convertLetterGradeToNumber(const string &grade);
};

#endif //CISC_3142_LAB_3_TYPEDPASSRATE_H
