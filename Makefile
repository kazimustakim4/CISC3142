lab3: execute

execute : program
	@./a.out

program:
	@echo "Please wait while program builds..."
	@g++ main.cpp cpp/GradeRatesByCategory.cpp headers/GradeRatesByCategory.h cpp/CourseReporter.cpp headers/CourseReporter.h cpp/TypedPassRate.cpp headers/TypedPassRate.h cpp/UserControl.cpp headers/UserControl.h cpp/OutputManager.cpp headers/OutputManager.h cpp/InputFileManager.cpp headers/InputFileManager.h
