//
// Created by makmn on 3/27/2022.
//
#include "../headers/OutputManager.h"


FILE* createOutputFile(string path, string outputFileName) {
    auto currentChronoTime = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(currentChronoTime);
    string time = ctime(&currentTime);
    time = regex_replace(time, regex(":"), ".");
    time = regex_replace(time, regex(" "), "-");
    time = regex_replace(time, regex("\n"), "");

    string outputFileAbsolutePath;
    outputFileAbsolutePath.append(path);
    outputFileAbsolutePath.append(outputFileName);
    outputFileAbsolutePath.append("_");
    outputFileAbsolutePath.append(time);
    outputFileAbsolutePath.append(".txt");

    char const *out = outputFileAbsolutePath.c_str();
    FILE *pFile = fopen(out, "w");
    return pFile;
}