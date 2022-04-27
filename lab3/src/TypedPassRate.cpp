#include "../headers/TypedPassRate.h"

TypedPassRate::TypedPassRate() = default;

// Non-Static Definitions
void TypedPassRate::processClass(const vector<basic_string<char>> &key, vector<basic_string<char>> &grades,
                                 int keyIndex) {
    auto itCategory = this->passRateMap.find({key[keyIndex]});
    if (itCategory != this->passRateMap.end()) {
        vector<double> rates = gradeRatesByInstructorMapHelper(grades);
        for (int i = 0; i < rates.size(); i++) {
            itCategory->second[i] += rates[i];
        }
    } else {
        vector<double> rates = gradeRatesByInstructorMapHelper(grades);
        this->passRateMap[{key[keyIndex]}] = rates;
    }
}

void TypedPassRate::processClassByTwoTypes(const vector<basic_string<char>> &key, vector<basic_string<char>> &grades,
                                           int keyIndex1, int keyIndex2) {
    auto itInstructor = this->passRateMap.find({key[keyIndex1], key[keyIndex2]});
    if (itInstructor != this->passRateMap.end()) {
        vector<double> rates = gradeRatesByInstructorMapHelper(grades);
        for (int i = 0; i < rates.size(); i++) {
            itInstructor->second[i] += rates[i];
        }
    } else {
        vector<double> rates = gradeRatesByInstructorMapHelper(grades);
        this->passRateMap[{key[keyIndex1], key[keyIndex2]}] = rates;
    }
}

map<vector<string>, vector<double>> TypedPassRate::termsToSeason() {
    map<vector<string>, vector<double>> seasonPassRate;

    vector<string> springTerms = {"T04", "T08", "T12", "T16", "T20", "T23"};
//    vector<string> fallTerms = {"T02", "T06", "T10", "T14", "T18", "T21"}; // these do not exist

    // these are probably summer and winter, but I'll use it for testing now
    vector<string> fallTerms = {"T11", "T13", "T15", "T17", "T19", "T05", "T07", "T09"};

    for (auto kv : this->passRateMap) {
        auto &key = kv.first;
        auto &rates = kv.second;

        // this iterator is used to find if the term is part of Spring
        auto itSpring = find(springTerms.begin(), springTerms.end(), key[1]);

        if (itSpring != springTerms.end()) {
            auto itCourseSeason = seasonPassRate.find({key[0], "Spring"});

            if (itCourseSeason != seasonPassRate.end()) {
                for (int i = 0; i < rates.size(); i++) {
                    itCourseSeason->second[i] += rates[i];
                }
            } else {
                seasonPassRate[{key[0], "Spring"}] = rates;
            }
            continue;
        }

        // this iterator is used to find if the term is part of Fall
        auto itFall = find(fallTerms.begin(), fallTerms.end(), key[1]);

        if (itFall != fallTerms.end()) {
            auto itCourseSeason = seasonPassRate.find({key[0], "Fall"});

            if (itCourseSeason != seasonPassRate.end()) {
                for (int i = 0; i < rates.size(); i++) {
                    itCourseSeason->second[i] += rates[i];
                }
            } else {
                seasonPassRate[{key[0], "Fall"}] = rates;
            }
        } else {
            cout << "Could not match term " << key[1] << endl;
            continue;
        }
    }
    return seasonPassRate;
}

void TypedPassRate::printRates(vector<string> reportType, FILE *pFile) {
    double totalStudentsProcessed = 0;

    string reportHeading;
    int types = 0;
    while (types != reportType.size()) {
        reportHeading += reportType[types];
        types++;
        if (types != reportType.size())
            reportHeading += ", ";
    }

    // Output File Headings
    vector<char const *> headings = {reportHeading.c_str(), "Passed", "Failed", "Total Withdrawal", "INC", "FIN", "AUD", "||", "WD", "W", "WN", "WU\n"};

    fprintf(pFile, "%-30s\t%12s\t%12s\t%20s\t%6s\t%6s\t%6s\t%6s\t%6s\t%6s\t%6s\t%6s", headings[0], headings[1], headings[2],
            headings[3], headings[4], headings[5], headings[6], headings[7], headings[8], headings[9], headings[10], headings[11], headings[12]);

    for (auto kv : this->passRateMap) {
        auto& key = kv.first;
        auto& value = kv.second;
        totalStudentsProcessed += value[0];

        types = 0;
        string cellName;
        while (types != reportType.size()) {
//            printf("---%s: %s---\n", reportType[types].c_str(), key[types].c_str());
            cellName += key[types];
            types++;
            if (types != reportType.size())
                cellName += ", ";
        }

        fprintf(pFile, "%-30s\t", cellName.c_str());

        double passedPercentage = (value[1]/value[0])*100;
        double failedPercentage = (value[2]/value[0])*100;
        double INCPercentage = (value[7]/value[0])*100;
        double FINPercentage = (value[8]/value[0])*100;
        double AUDPercentage = (value[9]/value[0])*100;
        double WDPercentage = (value[3]/value[0])*100;
        double WPercentage = (value[4]/value[0])*100;
        double WNPercentage = (value[5]/value[0])*100;
        double WUPercentage = (value[6]/value[0])*100;
        double withdrawalPercentage = WDPercentage + WPercentage + WNPercentage + WUPercentage;

       printf("Students Taught: %.2f\n"
               "Pass Rate: %.2f%\n"
               "Fail Rate: %.2f%\n"
               "Total Withdrawal Rate: %.2f%\n"
               "INC Rate: %.2f%\n"
               "FIN Rate: %.2f%\n"
               "AUD Rate: %.2f%\n\n"
               "---Withdrawal Rate Breakdown---\n"
               "WD Rate: %.2f%\n"
              "W Rate: %.2f%\n"
               "WN Rate: %.2f%\n"
               "WU Rate: %.2f%\n\n\n",
               value[0], passedPercentage, failedPercentage, withdrawalPercentage,
               INCPercentage, FINPercentage, AUDPercentage, WDPercentage, WPercentage, WNPercentage, WUPercentage);

        fprintf(pFile, "%11.2f%%\t%11.2f%%\t%19.2f%%\t%5.2f%%\t%5.2f%%\t%5.2f%%\t%6s\t%5.2f%%\t%5.2f%%\t%5.2f%%\t%5.2f%%\t",
                passedPercentage, failedPercentage, withdrawalPercentage,
                INCPercentage, FINPercentage, AUDPercentage, headings[7], WDPercentage, WPercentage, WNPercentage, WUPercentage);

        fprintf(pFile, "\n");
    }
    fprintf(pFile, "\n");
    printf("Total Students Processed: %.0f\n\n\n\n", totalStudentsProcessed);
}

// Static Definitions (Helper Functions)
double TypedPassRate::convertLetterGradeToNumber(const string &grade) {
    if (grade == "A+" || grade == "A")
        return 4.0;
    else if (grade == "A-")
        return 3.7;
    else if (grade == "B+")
        return 3.3;
    else if (grade == "B")
        return 3.0;
    else if (grade == "B-")
        return 2.7;
    else if (grade == "C+")
        return 2.3;
    else if (grade == "C")
        return 2.0;
    else if (grade == "C-")
        return 1.7;
    else if (grade == "D+")
        return 1.3;
    else if (grade == "D")
        return 1.0;
    else if (grade == "D-")
        return 0.7;
    else if (grade == "F")
        return 0.0;
    else if (grade == "WD")
        return -1;
    else if (grade == "W")
        return -2;
    else if (grade == "WN")
        return -3;
    else if (grade == "WU")
        return -4;
    else if (grade == "INC")
        return -5;
    else if (grade == "FIN")
        return -6;
    else if (grade == "CR" || grade == "P")
        return -7;
    else if (grade == "NC")
        return -8;
    else if (grade == "AUD")
        return (-9);
    else {
        cout << grade << endl;
        if (grade.empty()) cout << "No grade";
        return -10;
    }
}

vector<double> TypedPassRate::gradeRatesByInstructorMapHelper(vector<basic_string<char>> &grades) {
    double numberGrade;
    double passRate = convertLetterGradeToNumber("D-");
    double count = 0;
    double passed = 0; // assigned to students with a grade equal to or above pass rate
    double failed = 0; // assigned to students with a grade below pass rate
    double gradeWD = 0; // assigned to students who officially drop during the drop period. Not counted, unknown if shown on transcript.
    double gradeWN = 0; // assigned to students who never participated in any academically related activity and did not officially withdraw. Not shown on transcript.
    double gradeW = 0; // assigned to students who officially drop after the drop period. Not counted, shown on transcript.
    double gradeWU = 0; // assigned to students who stop attending courses but do not officially withdraw. Counted as an F.
    double gradeINC = 0; // assigned to students who do not complete full course work. Not counted, shown on transcript.
    double gradeFIN = 0; // assigned to students who do not complete full course work and the deadline has passed. Counted as an F.
    double gradeAUD = 0; // assigned to students who only audit a course (i.e. learning for fun)

    for (const string &grade: grades) {
        count += 1;
        numberGrade = convertLetterGradeToNumber(grade);
        if (numberGrade >= passRate)
            passed++;
        else if (numberGrade >= 0 && numberGrade < passRate)
            failed++;
        else if (numberGrade < 0) {
            switch ((int) numberGrade) {
                case -1:
                    gradeWD++;
                    break;
                case -2:
                    gradeW++;
                    break;
                case -3:
                    gradeWN++;
                    break;
                case -4:
                    gradeWU++;
                    break;
                case -5:
                    gradeINC++;
                    break;
                case -6:
                    gradeFIN++;
                    break;
                case -7:
                    passed++;
                    break;
                case -8:
                    failed++;
                    break;
                case -9:
                    gradeAUD++;
                    break;
                case -10:
                    if (numberGrade == -10) exit(-10);
                    break;
            }
        }
    }
    return {count, passed, failed, gradeWD, gradeW, gradeWN, gradeWU, gradeINC, gradeFIN, gradeAUD};
}
