
#include "../headers/UserControl.h"


void printValidInputs(CourseReporter &report, vector<int> validInputs) {
    cout << endl;
    for (int input : validInputs) {
        switch (input) {
            case 1:
                cout << "[" << input << "]: Pass Rate By Instructor Report Chosen" << endl;
                report.reportRatesByInstructor = true;
                break;
            case 2:
                cout << "[" << input << "]: Pass Rate By Course Report Chosen" << endl;
                report.reportRatesByCourse = true;
                break;
            case 3:
                cout << "[" << input << "]: Pass Rate By Course & Semester Report Chosen" << endl;
                report.reportRatesByCourseAndSemester = true;
                break;
            default:
                cout << "[" << input << "]: This option is not supported." << endl;
                break;
        }
    }
    cout << endl;
}

void printInvalidInputs(vector<char> invalidInputs) {
    if (!invalidInputs.empty()) {
        cout << "The following inputs are invalid: " << endl;
        string invalidStuff;
        for (char input : invalidInputs) {
            invalidStuff.push_back(input);
            invalidStuff.push_back(',');
            invalidStuff.push_back(' ');
        }
        invalidStuff[invalidStuff.size() - 2] = ' ';
        cout << invalidStuff << endl;
    }
}

void processUserInput(CourseReporter &report, string userInput) {
    vector<int> validInputs;
    queue<int> longerDigits;
    vector<char> invalidInputs;

    for (char character : userInput) {
        if (isdigit(character)) {
            int digit = character - 48;
            longerDigits.push(digit);
        } else if (character == ',' && !longerDigits.empty()) {
            int fullNumber = longerDigits.front();
            longerDigits.pop();
            while (!longerDigits.empty()) {
                fullNumber = fullNumber*10 + longerDigits.front();
                longerDigits.pop();
            }
            auto it = find(validInputs.begin(), validInputs.end(), fullNumber);
            // if the iterator does not find the value fullNumber in the vector, then push it on
            if (it == validInputs.end())
                validInputs.emplace_back(fullNumber);
        } else if (character != ' ' && character != ','){
            auto it = find(invalidInputs.begin(), invalidInputs.end(), character);
            // if the iterator does not find the value character in the vector, then push it on
            if (it == invalidInputs.end())
                invalidInputs.emplace_back(character);
        }
    }

    // check for last number
    if (!longerDigits.empty()) {
        int fullNumber = longerDigits.front();
        longerDigits.pop();
        while (!longerDigits.empty()) {
            fullNumber = fullNumber*10 + longerDigits.front();
            longerDigits.pop();
        }
        auto it = find(validInputs.begin(), validInputs.end(), fullNumber);
        // if the iterator does not find the value fullNumber in the vector, then push it on
        if (it == validInputs.end())
            validInputs.emplace_back(fullNumber);

    }

    printValidInputs(report, validInputs);
    printInvalidInputs(invalidInputs);

}

bool keepRunning() {

    bool userWantsAnotherReport;

    string userResponse;

    getline(cin, userResponse);

    size_t pos = string::npos;

    while ((pos = userResponse.find(" ")) != std::string::npos) {
        userResponse.erase(pos, 1);
    }

    if (userResponse[0] == 'Y' || userResponse[0] == 'y') {
        userWantsAnotherReport = true;
    } else if (userResponse[0] == 'N' || userResponse[0] == 'n') {
        userWantsAnotherReport = false;
        cout << "Closing program" << endl;
    } else {
        cout << "Unknown response. Terminating Program" << endl;
        exit(1);
        userWantsAnotherReport = false;
    }
    return userWantsAnotherReport;
}
