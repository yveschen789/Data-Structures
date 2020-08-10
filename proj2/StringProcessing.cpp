// String Processing.cpp
// purpose: take an input and sanitize the string so alphanumeric numbers are
//kept on both ends
// name: Yves Chen
// date: 4/11

#include <iostream>
#include <string>

using namespace std;

int main(){
    string input;
    

while (!cin.eof()){

    cin >> input;

    while (! isalnum(input[0])){
        input = input.erase(0,1);
    }

    while(! isalnum(input[input.size()-1])){
            input.erase(input.size()-1, input.size());
    }

    cout << input << endl;
}

    return 0;

}