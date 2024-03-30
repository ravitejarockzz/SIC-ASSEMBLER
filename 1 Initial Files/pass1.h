void pass1()
{
    int locctr;
    int start_add;
    int prog_len;
    int len;
    string line;
    vector<string> inst_fields;
    map <string, string> OpTab;
    map <string, string> SymTab;

    //Construction of optab
    OpTab = const_optab();

    ifstream fin("input.txt");
    ofstream fout("intermediate_file.txt");

    getline(fin, line);
    inst_fields = split(line,' ');
    string label = inst_fields[0];
    string opcode = inst_fields[1];
    string operand = inst_fields[2];
    
    if(opcode == "START")
    {
        start_add =  stoi(operand);
        locctr = hextodec(to_string(start_add)); //here locctr is already in hex
        fout << dectohex(locctr) << " " << line << endl;
        getline(fin, line);
        inst_fields = split(line,' ');
        if(inst_fields[0]!="")
            label = inst_fields[0];
        if(inst_fields[1]!="")
            opcode = inst_fields[1];
        if(inst_fields[2]!="")
            operand = inst_fields[2];
    }
    else
    {locctr = 0;}
    

    while(opcode != "END")
    {
        if (label != "")
        {
            if(SymTab[label]!="")
            {cout << locctr <<  "Error : Duplicate Symbol " << label << endl;}
            else
            {SymTab[label] = dectohex(locctr);}
        }

        fout << dectohex(locctr) << " " << line << endl;
        
        if(OpTab[opcode]!="")
            locctr = locctr + 3;
        else if (opcode == "WORD")
            locctr = locctr + 3;
        else if (opcode == "RESW")
            locctr = locctr + (3*stoi(operand));
        else if (opcode == "RESB")
            locctr = locctr + stoi(operand);
        else if (opcode == "BYTE")
        {
            if(operand[0]=='C')
                len = operand.length() - 3; //removing the characters {c ' '}
            else if(operand[0]=='X')
                len = (operand.length() - 3)/2; //considering two characters as 1 byte
            
            locctr = locctr + len;

        }
        else
            cout << "Error : Invalid operation code" << endl;
        
        label = "";
        getline(fin, line);
        inst_fields = split(line,' ');
        int length = inst_fields.size();
        if(length-- &&  inst_fields[0]!="")
        label = inst_fields[0];
        if(length-- &&  inst_fields[1]!="")
        opcode = inst_fields[1];
        if(length-- &&  inst_fields[2]!="")
        operand = inst_fields[2];
    }
    fout << " " << line << endl;
    
    prog_len = locctr - hextodec(to_string(start_add));

    ofstream dout("data.txt");
    dout << dectohex(prog_len) << endl << "The above is Program Length" << endl;
    dout << start_add << endl << "The above is Start Address" <<  endl ;

    ofstream sout("SymbolTable.txt");
    for (auto i : SymTab) sout << i.first << "," << i.second << endl;
    sout.close();
    
    fin.close();
    fout.close();
    
}