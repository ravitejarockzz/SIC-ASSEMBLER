void pass2()
{
    ifstream fin("intermediate_file.txt");
    ofstream fout("object-code.txt");

    string opcode_hex, oper_add, object_code;
    ofstream out("object-program.txt");
    string H_rec,T_rec,E_rec;

    map <string, string> OpTab;
    map <string, string> SymTab;

    OpTab = const_optab();  //OpTab construction
    
    SymTab = const_symtab();    //SymTab construction

    vector<string> inst_fields;
    string line;

    getline(fin, line);
    
    inst_fields = split(line, ' ');
    string locctr = inst_fields[0];
    string label = inst_fields[1];
    string opcode = inst_fields[2];
    string operand = inst_fields[3];

    string ProgName, startaddr, proglen;

    if (opcode == "START")
    {
        ProgName = label;
        startaddr = operand;
        fout << line << endl;

        getline(fin, line);
        inst_fields = split(line, ' ');
        if(inst_fields[0]!="")
            locctr = inst_fields[0];
        if(inst_fields[1]!="")
            label = inst_fields[1];
        if(inst_fields[2]!="")
            opcode = inst_fields[2];
        if(inst_fields[3]!="")
            operand = inst_fields[3];
    }
    

//  write Header Record H^COPY  ^001000^00107A
    while(ProgName.length()<6)
    {   ProgName = ProgName + " ";  }
    while(startaddr.length()<6)
    {   startaddr = "0" + startaddr;    }
    ifstream din("data.txt");
    getline(din, proglen);
    while(proglen.length()<6)
    {   proglen = "0" + proglen;    }

    H_rec = "H" + ProgName + startaddr + proglen;

    out << H_rec << endl;
//  Initialize text record
    T_rec = "T" + startaddr;
    int lenTR = 0;
    string objcodestr;
    while(opcode!="END")
    {
        oper_add = "";
        if (OpTab[opcode]!="")
        {
            opcode_hex = OpTab[opcode];
            if (operand!="")    //if there is a symbol in operand field
            {//operand processing for index mode should be done (X)
                int pos = operand.find(',');
                if (pos != -1)  // , exists
                {
                    operand = operand.substr(0, pos);
                    if(SymTab[operand]!="")
                    {
                        oper_add=indexedAddr(SymTab[operand]);
                    }
                    else
                    {
                        oper_add = "8000";  //X bit is set to 1
                        cout << "Error : Undefined Symbol " << operand << endl;
                    }
                }
                else
                {
                    if(SymTab[operand]!="")
                    {
                        oper_add=SymTab[operand];
                    }
                    else
                    {
                        oper_add = "0000";
                        cout << "Error : Undefined Symbol " << operand << endl;
                    }
                }
                object_code = opcode_hex + oper_add;
            }
            else
            {   oper_add="0000";    }
            
            object_code = opcode_hex + oper_add;
        }
        else if (opcode == "BYTE")
        {
            if (operand[0] == 'C')
            {
                for(int i=2; i<(operand.length()-1); i++)
                {
                    oper_add = oper_add + dectohex(int(operand[i]));
                }
            }
            else if (operand[0] == 'X')
            {
                for(int i=2; i<(operand.length()-1); i++)
                {
                    oper_add = oper_add + operand[i];
                }
            }
            object_code = oper_add;
        }
        else if (opcode == "WORD")
        {
            oper_add = objcode(stoi(operand));
            object_code = oper_add;
        }
        else if (opcode == "RESW" || opcode == "RESB")
        {
            object_code = "";
            fout << line << endl;
            out << T_rec << dectohex(lenTR) << objcodestr << endl;
            objcodestr = "";
            lenTR=0;
            while (opcode == "RESW" || opcode == "RESB")
            {
                getline(fin, line);
                
                inst_fields = split(line, ' ');
                int length = inst_fields.size();
                if(length-- && inst_fields[0]!="")
                    locctr = inst_fields[0];
                if(length-- && inst_fields[1]!="")
                    label = inst_fields[1];
                if(length-- && inst_fields[2]!="")
                    opcode = inst_fields[2];
                if(length-- && inst_fields[3]!="")
                    operand = inst_fields[3];
                else operand = "";
                if (opcode == "RESW" || opcode == "RESB")
                {fout << line << endl;}//
            }
            string loc = locctr;
            while(loc.length()<6)
            {   loc = "0" + loc;    }
            T_rec = "T" + loc;
            continue;
        }
            
        fout << line << " " << object_code << endl;
        
        if ((objcodestr.length() + object_code.length()) > 60)
        {
            out << T_rec << dectohex(lenTR) << objcodestr << endl;
            objcodestr = "";
            lenTR=0;

            string loc = locctr;
            while(loc.length()<6)
            {   loc = "0" + loc;    }
            T_rec = "T" + loc;
        }
        objcodestr = objcodestr + object_code;
        lenTR = lenTR + (object_code.length()/2);

        getline(fin, line);
        inst_fields = split(line, ' ');
        int length = inst_fields.size();
        if(length-- && inst_fields[0]!="")
            locctr = inst_fields[0];
        if(length-- && inst_fields[1]!="")
            label = inst_fields[1];
        if(length-- && inst_fields[2]!="")
            opcode = inst_fields[2];
        if(length-- && inst_fields[3]!="")
            operand = inst_fields[3];
        else operand = "";  //if operand doesnt exist then the operand variable containing prev operand should be set to null

    }
    fout << line << endl;
    out << T_rec << dectohex(lenTR) << objcodestr << endl;

//  write END record
    E_rec = "E" + startaddr;
    out << E_rec << endl;
    
    fin.close();
    fout.close();

}