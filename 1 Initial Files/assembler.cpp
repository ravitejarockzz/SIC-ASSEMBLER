/*
Name : BORRA RAVI TEJA
Reg No : 22006
II M.Sc. Mathematics and Computer Science
This is the code for SIC ASSEMBLER
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "functions.h"
#include "pass1.h"
#include "pass2.h"

using namespace std;

int main()
{
    cout << "-----Welcome to the SIC ASSEMBLER-----" << endl;
    cout << "> The assembly code is given in the \"input.txt\" file." << endl;
    cout << "> Pass1 started..." << endl;
    pass1();
    cout << "> \"Intermediate_file.txt\" and SYMTAB are generated." << endl;
    cout << "> Pass2 started..." << endl;
    pass2();
    cout << "> Object Program is generated in the \"object-program.txt\"";
    return 0;
}