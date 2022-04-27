//
// Created by makmn on 3/25/2022.
//
#include "../headers/OutputManager.h"
#include "../headers/TypedPassRate.h"
#include "../headers/UserControl.h"

using namespace std;

void gradeRatesByCategories(map<vector<string>, vector<string>> &courseGrades) {
    TypedPassRate instructorPassRate;
    TypedPassRate coursePassRate;
    TypedPassRate termPassRate;

    CourseReporter report;

    bool userWantsAReport = true;

    while (userWantsAReport) {
        report.falsifyOptions();
        printf("\n\n-----------------BETA-----------------\n");
        printf("---Brooklyn College Course Reporter---\n");
        printf("Current Courses: CISC. 1115, CISC. 3115, CISC. 3130\n\n");

        printf("The following output are available:\n\n"
               "[1] Pass Rates By Instructor\n"
               "[2] Pass Rates By Course\n"
               "[3] Pass Rates By Course & Semester\n\n"
               "Type in the number corresponding to the report you want to generate.\n"
               "Make sure to separate numbers with a comma. "
               "Example: To generate output 1 and 3, type in 1, 3\n"
               "Your choices: ");


        string userInput;
        getline(cin, userInput);
        processUserInput(report, userInput);


        if (report.reportChosen()) {
            printf("\nType in the name of the output file you would like to generate\n"
                   "Output File Name: ");
            string outputFileName;
            getline(cin, outputFileName);
            cout << endl;

            // iterate through all sections (i.e. classes)
            for(auto kv : courseGrades) {
                auto& key = kv.first;
                auto& grades = kv.second;

                if (report.reportRatesByInstructor)
                    instructorPassRate.processClass(key, grades, 1);
                if (report.reportRatesByCourse)
                    coursePassRate.processClass(key, grades, 0);
                if (report.reportRatesByCourseAndSemester)
                    termPassRate.processClassByTwoTypes(key, grades, 0, 2); // this will give grades per term
            }

            TypedPassRate seasonPassRate;
            if (report.reportRatesByCourseAndSemester)
                seasonPassRate.passRateMap = termPassRate.termsToSeason();

            FILE *pFile = createOutputFile("./output/", outputFileName);
            if (report.reportRatesByInstructor)
                instructorPassRate.printRates({"Instructor ID"}, pFile);
            if (report.reportRatesByCourse)
                coursePassRate.printRates({"Course"}, pFile);

            //    printRates(termPassRate, {"Course", "Term"}, pFile);

            if (report.reportRatesByCourseAndSemester)
                seasonPassRate.printRates({"Course", "Semester"}, pFile);

            fclose(pFile);

            printf("Report successfully created!\nWould you like to generate more reports?\n"
                   "Enter yes or no:");
        } else {
            printf("No output chosen. Would you like to try selecting again?\nEnter yes or no:");
        }
        userWantsAReport = keepRunning();
    }

}


