#include <iostream>
#include <cmath>
using namespace std;

enum class perform_operation {Addition,Subtraction,Division,Multiplication,SquareRoot};


struct Basic_Calculator {
perform_operation po ;
Basic_Calculator(perform_operation Perform_Operation) { po = Perform_Operation;}

int perform(int x , int y) {
switch(po) {
case perform_operation::Addition: {
return x + y;
}break;
case perform_operation::Subtraction: {
return x - y;
}break;
case perform_operation::Division: {
return x/y;
}break;
case perform_operation::Multiplication: {
return x * y;
}break;
case perform_operation::SquareRoot: {
return sqrt(x);
}
default: {
cout<<" Invalid operation ";
return 0;
}
}
}
};
int main() {
int p,q ;
string Perform_Operation;
cout<<" Enter First Number:  ";
cin>>p;
cout<<" Enter Second Number: ";
cin>>q;
cout<< " \n\nOperations are Addition,Subtraction,Division,Multiplication,SquareRoot \n\n";
cout<<"Operation to be performed : ";
cin>>Perform_Operation;

perform_operation po{ };

if (Perform_Operation == "Addition") {
po = perform_operation::Addition;}
else if (Perform_Operation == "Subtraction") {
po = perform_operation::Subtraction;}
else if(Perform_Operation == "Division") {
po = perform_operation::Division;}
else if(Perform_Operation == "Multiplication") {
po = perform_operation::Multiplication;}
else if(Perform_Operation == "SquareRoot") {
po = perform_operation::SquareRoot;}

Basic_Calculator bc(po);
auto result= bc.perform(p,q);
cout<< "After Performing Operation Answer is : "<<result;
}

