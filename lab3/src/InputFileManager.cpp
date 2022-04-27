#include "../headers/InputFileManager.h"

vector<string> getInputFiles() {
    vector<string> inputFilePaths;
    bool addInputFiles = true;
    string inputFileRelativePath = "./data/";
    string fileNameGivenByUser;


    printf("Please follow the README.md file for input\n"
           "Type in the name of the input files you would like to use.\n"
           "The program will look in the 'data' folder in the current directory for the files you list.\n");

    while (addInputFiles) {
        printf("Input File Name (do not include the extension):");
        cin >> fileNameGivenByUser;
        cin.ignore();
        inputFileRelativePath.append(fileNameGivenByUser);

        size_t pos = string::npos;
        while ((pos = fileNameGivenByUser.find(" ")) != std::string::npos) {
            fileNameGivenByUser.erase(pos, 1);
        }

        inputFileRelativePath.append(".csv");
        inputFilePaths.emplace_back(inputFileRelativePath);
        printf("You currently have the following input file paths:\n");
        for (string file : inputFilePaths) {
            printf("%s\n", file.c_str());
        }
        printf("Would you like to add another input file?\n"
               "Enter 'yes' or 'no':");
        addInputFiles = keepRunning();
        inputFileRelativePath = "./data/";
    }

    return inputFilePaths;
}
