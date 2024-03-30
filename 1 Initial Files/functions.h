#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
using namespace std;

vector<string> split(string str, char del)
{
      vector<string> v;
      string temp = "";
   
      for(int i=0; i<str.size(); i++)
        {
            if(str[i] != del)
            {
                temp += str[i];
            }
            else
            {
                v.push_back(temp);
                temp = "";
            }
        }
       
      v.push_back(temp);
      return v;
}

map <string, string> const_optab()
{
    map <string, string> optab;

    vector<string> vec;
    string line;
    ifstream opin("OpTable.txt");
    getline(opin,line);
    
    while(line!="")
    {
        vec = split(line,',');
        optab[vec[0]] = vec[1];    //OpTab construction
        getline(opin,line);
    }
    opin.close();

    return optab;
}

map <string, string> const_symtab()
{
    map <string, string> symtab;
    vector<string> vec;
    string line;
    ifstream sin("SymbolTable.txt");
    getline(sin,line);
    
    while(line!="")
    {
        vec = split(line,',');
        symtab[vec[0]] = vec[1];    //SymTab construction
        getline(sin,line);
    }
    sin.close();
    return symtab;
}

int dec(char c)
{
    switch (c)
    {
        case 'A':
        return 10;
        case 'B':
        return 11;
        case 'C':
        return 12;
        case 'D':
        return 13;
        case 'E':
        return 14;
        case 'F':
        return 15;
        default:
        return stoi(to_string(c))-48;   //ascii value to magnitude
    }
}

int hextodec(string hex)
{
    int len = hex.length();
    int base = 1;
    int dec_num = 0;
    for (int i = len-1; i>=0; i--)
    {
        dec_num += dec(hex[i])*base;
        base = base*16;
    }
    return dec_num;
}

string hex(int d)
{
    switch (d)
    {
        case 10:
        return "A";
        case 11:
        return "B";
        case 12:
        return "C";
        case 13:
        return "D";
        case 14:
        return "E";
        case 15:
        return "F";
        default:
        return to_string(d);
    }
}

string dectohex(int dec_num)
{
    string hex_str = "";
    stack<int> stack;

    int div, rem;
    div = dec_num;
    rem = div % 16;
    //cout << "rem:" << rem << endl;
    stack.push(rem);
    div = (div)/16;
    //cout << "div:" << div << endl;
    while(div > 15)
    {
        rem = div % 16;
        //cout << "rem:" << rem << endl;
        stack.push(rem);
        div = (div)/16;
        //cout << "div:" << div << endl;
    }
    stack.push(div);
    while(!stack.empty())
    {
        //cout << stack.top();
        
        hex_str = hex_str + hex(stack.top());
        stack.pop();
    }
    return hex_str;

}

string objcode(int con)
{
    //for generation of constants
    string res = "";
    res = dectohex(con);
    while(res.length()<6)
    {
        res = "0" + res;
    }
    return res;
}

string indexedAddr(string addr)
{
    //24 bit instruction format
    //opxode(8)-X(1)-address(15)
    //here X bit should be set to 1 i.e. 0xxx -> 1xxx
    switch (addr[0])
    {
        case '0':
        addr[0] = '8';
        break;
        case '1':
        addr[0] = '9';
        break;
        case '2':
        addr[0] = 'A';
        break;
        case '3':
        addr[0] = 'B';
        break;
        case '4':
        addr[0] = 'C';
        break;
        case '5':
        addr[0] = 'D';
        break;
        case '6':
        addr[0] = 'E';
        break;
        case '7':
        addr[0] = 'F';
        break;
    }
    
    return addr;
}

/*
int main()
{
    int dec = 1234;
    string hex_str = "";
    stack<int> stack;

    int div, rem;
    div = dec;
    rem = div % 16;
    cout << "rem:" << rem << endl;
    stack.push(rem);
    div = (div)/16;
    cout << "div:" << div << endl;
    while(div > 15)
    {
        rem = div % 16;
        cout << "rem:" << rem << endl;
        stack.push(rem);
        div = (div)/16;
        cout << "div:" << div << endl;
    }
    stack.push(div);
    while(!stack.empty())
    {
        cout << stack.top();
        
        hex_str = hex_str + hex(stack.top());
        stack.pop();
    }
    cout << "Hex String : " << hex_str << endl; 
    
    return 0;
}
*/
