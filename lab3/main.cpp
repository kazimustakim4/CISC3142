#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

//#include "headers/InputFileManager.h"
//#include "headers/GradeRatesByCategory.h"

using namespace std;

int main() {

    int inputFilesProcessed = 0;

    vector<string> inputFilePaths = getInputFiles();

    ifstream in_stream;

    in_stream.open(inputFilePaths[0]);

    if (in_stream.fail()) {
        cout << "Can't open input file" << endl;
        exit(1);
    }

    map<vector<string>, vector<string>> courseGrades;

    string emplid;
    string courseno;
    string instructorid;
    string termid;
    string sectionid;

    string grade;

    getline(in_stream, emplid, '\n'); // skip first line

    // read cells one by one
    while(inputFilesProcessed != inputFilePaths.size()) {

        getline(in_stream, emplid, ',');
        getline(in_stream, courseno, ',');
        getline(in_stream, instructorid, ',');
        getline(in_stream, termid, ',');
        getline(in_stream, sectionid, ',');
        getline(in_stream, grade, '\n');

        /*
         * use map::find to check if the key exists.
         * If so, just update the grade vector.
         * If not, create a new key-value pair.
        */
        auto it = courseGrades.find({courseno, instructorid, termid, sectionid});
        if (it != courseGrades.end()) {
            it->second.push_back(grade);
        } else {
            courseGrades[{courseno, instructorid, termid, sectionid}] = {grade};
        }

        if (in_stream.eof()) {
            in_stream.close();
            inputFilesProcessed++;
            if (inputFilesProcessed != inputFilePaths.size()) {
                in_stream.open(inputFilePaths[inputFilesProcessed]);
                if (in_stream.fail()) {
                    cout << "Can't open input file" << endl;
                    exit(1);
                }
                getline(in_stream, emplid, '\n'); // skip first line
            }
        }
    }
    gradeRatesByCategories(courseGrades);
}

