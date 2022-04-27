//
// Created by makmn on 3/27/2022.
//

struct CourseReporter {
    CourseReporter();
    CourseReporter(bool instructor, bool course, bool courseBySemester);

    bool reportChosen();
    void falsifyOptions();

    bool reportRatesByInstructor = false;
    bool reportRatesByCourse = false;
    bool reportRatesByCourseAndSemester = false;

};