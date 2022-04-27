## Lab3
## What is this lab?
This is a program that pulls the data and gives the grades of the student on different terms.
## How to Run this Program
Clone the repository with the recursive flag (the recursive flag is necessary in order to clone the data submodule): 

``git clone https://github.com/kazimustakim4/CISC3142.git``

If you forget to include the --recursive flag, you can update the cloned repository with the submodule by running: 

`git submodule update --init`

Next, move into the lab3 directory:

`cd lab3`

You can also add your own data files by following the [Input File Format](https://github.com/kazimustakim4/CISC3142/edit/main/lab3/README.md) section below.

Build the program using the provided Makefile by running: 

`make lab3`

After the program finishes building, it will automatically execute the program. 
You can execute the program again in the future by running: 

`./a.out`


## Report Publication
### 3 Types of report
The following types of reports are available:

1. Rates by Instructor
2. Rates by Course
3. Rates by Course & Semester

Data files are included in the data directory of the repository as a submodule.

### Input File Format

The input file must have the following types of headings in the same order:
- EMPLID : Student Identification Number. This is not used anywhere in the program.
- COURSENO : A string representing a course.
- INSTRUCTORID : A string representing an instructor.
- TERMID: A string representing a term.
- SECTIONID: A string representing a section.
- GRADE*: A string representing a grade.

Note that the names of these headings can be anything, but it is important they show up in the same order as above.


*Only the following grades are allowed:
- A+
- A
- A-
- B+
- B
- B-
- C+
- C
- C-
- D+
- D
- D-
- F
- WD
- W
- WN
- WU
- INC
- FIN
- CR
- P
- NC
- AUD
