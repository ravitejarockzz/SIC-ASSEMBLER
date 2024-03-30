Name : Borra Ravi Teja
Reg No : 22006
II M.Sc. Mathematics and Computer Science
Mail : ravitejarockzz5@gmail.com
--------------------------------------------------------------------------------------------
Input is sic code
Fields of the instructions are separated by space
LABEL OPCODE OPERAND

-------------------------------

Algorithm :

Pass 1
--> Generate intermediate file
* Maintain LOCCTR
* Read SIC instruction from code(input.txt)
* Assign addresses for each instruction and process the assembly directives like RESB, RESW, BYTE, WORD if occured
* Populate symtab with labels and their addresses
* Write the SIC instructions to the intermediate file(intermediate.txt) and "data.txt"
* Generate "intermediate_file.txt" for Pass 2

Pass 2
--> Generate HEADER, TEXT(s), END records
* Read input line from "intermediate_file.txt"
* Assemble instructions(HEX): Translate opcodes and looking up for label's addresses in SYMTAB
* Generate constants/literals
* Assemble the object code(HEX) into records and generate "object-code.txt"
* Write these records to "object-program.txt"

----------------------------------------------------------------------------------------------

Files (before execution):

input.txt
OpTable.txt
functions.h
pass1.h
pass2.h
assembler.cpp

Files (generated after execution):

pass1() -> intermediate_file.txt, SymbolTable.txt, data.txt
pass2() -> object-code.txt, object-program.txt

----------------------------------------------------------------------------------------------