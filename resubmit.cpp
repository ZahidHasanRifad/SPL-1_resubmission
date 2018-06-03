#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<sstream>
#include<stack>

using namespace std;




vector<string> readFromFileGetOnlyLine(string filename)
{
    ifstream file;
    file.open(filename);
    string s;
    vector<string> line;
    //nint lines;
    if(file.is_open())
    {
        while(getline(file, s))
        {

            if(s=="")
                continue;
            else{
                //cout << s << endl;
                line.push_back(s);
            }

        }
    }

    else cout << "can't open the file." << endl;
    //cout << lines << endl;
    file.close();
    return line;
}


vector<string> getTotalLine(string filename)
{
    ifstream file;
    file.open(filename);
    vector<string> lines;
    string s;
    if(file.is_open())
    {
        while(getline(file, s))
        {
            lines.push_back(s);
        }
    }
    else cout << "trouble in getting total line of code" << endl;
    return lines;
}

int getNumberOfLine(string filename)
{
    ifstream file;
    file.open(filename);
    string s;
    //vector<string> line;
    int lines=0;
    if(file.is_open())
    {
        //cout << "file open" << endl;
        while( getline(file, s))
        {

            //cout << s << endl;
            lines++;
            //line.push_back(s);
        }
    }

    else cout << "can't open the file." << endl;
    file.close();
    return lines;
}

string removeBracket(string line)
{
    string lin;
    string hudai= "(";
    for(int i=0; i<hudai.size(); i++)
    {
        for(int j=0; j<line.size(); j++)
        {
            if(line[j] == hudai[i])
            {
                line[j] = ' ';
            }
        }
    }
    return line;
}


vector<pair<string, int> > getVariable(vector<string> line)
{
    string arr[] = {"int", "float", "double", "char","string","bool"};
    vector<pair<string, int> > variables;
    stack<string> bracket;
    string s,varname;
    int flag = 0, flag1 = 0;
    bool f = true;
    int countvar=0;
    for(int i=0; i<line.size(); i++)
    {
        for(int j=0; j<line[i].length(); j++)
        {
            if(line[i][j] != '[' && line[i][j] == '{')
            {
                bracket.push("{");
            }
            else if(line[i][j] == '}')
            {
                bracket.pop();
            }
        }

        if(!bracket.empty()&& bracket.top() == "{")
        {
            istringstream iss(line[i]);
            iss>> s;
            if(s=="int" || s=="float" || s=="double" || s=="char"|| s=="string" || s=="bool")
            {
                for(int j=0; j<line[i].length(); j++)
                {
                    if(line[i][j] == '(')
                    {
                        flag = j;
                    }
                    else if(line[i][j] == ')')
                    {
                        flag1 = j;
                    }
                }
                for(int k=flag; k<flag1; k++ )
                    {
                        if(line[i][k] == ',')
                            f = false;

                    }
                for(int j=0; j<line[i].length(); j++)
                {
                    if( f && line[i][j] == ',')
                        countvar++;
                }
                cout <<"in line " << i+1 << " " << s << " " << countvar+1 << endl;
                variables.push_back(make_pair(s,countvar+1));
                countvar =0;
            }
        }
        //cout << line[i] << endl;

    }
    return variables;
}


vector<pair<string, int> > getTotalVariable(vector<pair<string, int> > variables)
{
    vector<pair<string, int> > total;
    int countint=0, countfloat=0, countchar=0, countdouble=0, countbool=0, countstring =0;
    string sint = "int", sstring = "string", sfloat = "float", sdouble = "double", sbool = "bool", schar = "char";
    for(int i=0; i<variables.size(); i++)
    {
        string varname = variables[i].first;
        int countvar = variables[i].second;

        if(varname == sstring)
        {
            countstring += countvar;
        }
        else if(varname == sint)
        {
            countint += countvar;
        }
        else if(varname == sfloat)
        {
            countfloat += countvar;
        }
        else if(varname == sdouble)
        {
            countdouble += countvar;
        }
        else if(varname == sbool)
        {
            countbool += countvar;
        }
        else if(varname == schar)
        {
            countchar += countvar;
        }
    }
    total.push_back(make_pair(sint, countint));
    total.push_back(make_pair(sfloat, countfloat));
    total.push_back(make_pair(sdouble, countdouble));
    total.push_back(make_pair(sbool, countbool));
    total.push_back(make_pair(sstring, countstring));
    total.push_back(make_pair(schar, countchar));

    return total;
}

vector<string> getfunctions(vector<string> line)
{
    string arr1[] = {"for", "while", "do","if", "else if", "switch", "else"};

    vector<string> functions;
    string ss;
    //stack<string> l;
    for(int i=0; i<line.size(); i++)
    {
        line[i] = removeBracket(line[i]);

        istringstream iss(line[i]);
        iss>>ss;

        for(int j=0; j<sizeof(arr1)/sizeof(arr1[0]); j++)
        {
            if(ss == arr1[j])
            {
                //cout << ss << endl;
                functions.push_back(ss);

            }
        }

    }
    return functions;
    //for(int i=0; i<)
}
/*
vector<string> getTotalWords(string filename)
{
    vector<string> words;
    string word, str;
    ifstream file;
    file.open(filename);

    while(file >> word)
    {
        //file >> word;
        word = removeBracket(word);
        istringstream iss(word);
        iss >> str;
        words.push_back(str);
    }
    return words;
}
*/
map<string, int> wordFrequency(vector<string> s)
{
    map<string, int> frequency;
    int countword;
    string word;

    //cout << "in word frequency " << s.size() <<  endl;

    if(s.size() == 0)
    {
        cout << "no words" << endl;
    }
    sort(s.begin(), s.end());

    s.push_back(" ");
    word = s[0];
    countword = 1;

    for(int i=1; i<s.size(); i++)
    {

        if(word != s[i])
        {
            frequency[word] = countword;
            countword = 0;
            word = s[i];
        }
        countword++;
    }

    return frequency;
}


vector<pair<string, pair<int, int> > > getLineOfEachFunction(vector<string> line)
{
    vector<pair<string, pair<int, int> > > linenumber;
    int startLine, endLine;
    stack<string> brackets;
    stack<int> lines;
    string s,ss,str,sss;
    for(int i=0; i<line.size(); i++)
    {
        //cout << brackets.size() << endl;
        //cout << "line " << i+1 << " " << line[i] << endl;
        line[i] = removeBracket(line[i]);
        //cout << "line " << i+1 << " " << line[i] << endl;
        istringstream iss(line[i]);
        iss >> s;
        if(line[i] == "")
            s ="som";
        //cout << "line " << i+1 << " " << s << endl;
        if(s== "else{")
            s = "else";
        if(s == "do{")
            s = "do";

        if(brackets.empty() && ( s == "for" || s == "while" || s == "do" || s== "if" ||s == "else" || s == "switch"))
        {
            lines.push(i+1);
            brackets.push(s);
            //cout << "pushed " << brackets.top()  << endl;
        }
        else if(!brackets.empty() && ( s == "for" || s == "while" || s == "do" || s== "if" ||s == "else" || s == "switch"))
        {
            lines.push(i+1);
            brackets.push(s);
            //cout << "pushed " << brackets.top()  << endl;
        }
/*
        if(line[i] == "{")
        {
            if(!brackets.empty())
            {
                cout << "get { next line" << endl;
                brackets.push(line[i]);
                cout << "pushed " << line[i] << endl;
            }
        }
*/
        for(int j=0; j<line[i].length(); j++)
        {

            if(line[i][j] == '{')
            {
                if(!brackets.empty())
                {
                    //cout << "get { in the same line" << endl;
                    brackets.push("{");
                    //cout << "pushed " << brackets.top() << endl;
                }
            }
        }
        //cout << "after top" << endl;
/*
        if(line[i] == "}" && !brackets.empty())
        {
            if(brackets.top() == "{")
            {
                //cout << "after top" << endl;
                //ss = "{";
                lines.push(i+1);
                brackets.pop();
                if((brackets.top() == "for" )|| (brackets.top()== "while") || (brackets.top() == "do") ||
                (brackets.top() == "if") || (brackets.top() == "else") || brackets.top() == "switch")
                {
                        ss = brackets.top();
                        cout<< " ss " << ss << endl;
                        brackets.pop();
                        endLine = lines.top();
                        cout << "endline " << endLine << endl;
                        lines.pop();
                        startLine = lines.top();
                        cout << "startline " << startLine << endl;
                        lines.pop();
                        linenumber.push_back(make_pair(ss, make_pair(startLine, endLine)));
                }
            }
        }
*/
        for(int j=0; j<line[i].length(); j++)
        {
            if(line[i][j] == '}' && !brackets.empty())
            {
                //cout << "pop korar age top e ase " << brackets.top() << endl;
                if(brackets.top() == "{")
                {
                    lines.push(i+1);
                    //ss = "{";
                    //cout << "will be popped " << brackets.top() << endl;
                    brackets.pop();
                    if((brackets.top() == "for" )|| (brackets.top()== "while") || (brackets.top() == "do") ||
                    (brackets.top() == "if") || (brackets.top() == "else") || brackets.top() == "switch")
                    {
                        ss = brackets.top();
                        //cout << "ss " << ss << endl;
                        brackets.pop();
                        endLine = lines.top();
                        //cout << "endline " << endLine << endl;
                        lines.pop();
                        startLine = lines.top();
                        //cout << "startline " << startLine << endl;
                        lines.pop();
                        linenumber.push_back(make_pair(ss, make_pair(startLine, endLine)));
                    }
                }
            }
        }
        //cout << "after top" << endl;
        /*
        if(!brackets.empty()){
            if((brackets.top() == "for" && !brackets.empty())|| (brackets.top()== "while" && !brackets.empty()) || (brackets.top() == "do" && !brackets.empty()) ||
            (brackets.top() == "if" && !brackets.empty()) || (brackets.top() == "else" && !brackets.empty()) || brackets.top() == "switch")
            {
                cout << "inside" << endl;
                ss = brackets.top();
                brackets.pop();
                endLine = lines.top();
                lines.pop();
                startLine = lines.top();
                lines.pop();
                linenumber.push_back(make_pair(ss, make_pair(startLine, endLine)));

            }
        }
        */

        //cout << "after top" << endl;


    }
    return linenumber;


}


void makefilewithvariable(string filename, string dstfilename)
{
    vector<string> lines;
    vector<pair<string, int> > variables;
    vector<pair<string, int> > totalvariables;
    lines = getTotalLine(filename);
    variables = getVariable(lines);
    totalvariables = getTotalVariable(variables);
    ofstream ofile;
    ofile.open(dstfilename);
    if(ofile.is_open())
    {
        for(int i=0; i<totalvariables.size(); i++)
        {
            ofile << totalvariables[i].first << "," << totalvariables[i].second << endl;
        }
    }
    else cout << "can't write to variable file" << endl;
    lines.clear();
    variables.clear();
    totalvariables.clear();
}


void makefilewithfunction(string filename, string dstfilename)
{
    vector<string> lines;
    vector<string> functions;
    map<string, int> fcounts;
    vector<pair<string, pair<int, int> > > lineofeachfunction;
    lines = getTotalLine(filename);
    lineofeachfunction = getLineOfEachFunction(lines);
    for(int i=0; i<lineofeachfunction.size(); i++)
    {
        functions.push_back(lineofeachfunction[i].first);
    }
    fcounts = wordFrequency(functions);
    ofstream ofile;
    ofile.open(dstfilename);
    if(ofile.is_open())
    {
        for(map<string, int>:: iterator it = fcounts.begin(); it!=fcounts.end(); it++)
        {
            ofile << it->first << "," << it->second << endl;
        }
    }
    else cout << "can't write to functions file." << endl;


}

int main (void)
{
    string filename1 = "similarity.cpp";
    string filename2 = "spl1.cpp";
    makefilewithvariable(filename1, "file1var.txt");
    makefilewithvariable(filename2, "file2var.txt");
    makefilewithfunction(filename1, "file1func.txt");
    makefilewithfunction(filename2, "file2func.txt");
/*
    vector<string> lines;
    vector<string> functions;
    vector<string> words;
    map<string, int> fcounts;
    vector<pair<string, int> > variables;
    vector<pair<string, int> > totalvariables;
    //map<string, int> vcounts;
    vector<pair<string, pair<int, int> > > lineofeachfunction;
    int numberOfLine;
    numberOfLine = getNumberOfLine(filename);
    lines = getTotalLine(filename);
    //functions = getfunctions(lines);
    //words = getTotalWords(filename);
    //fcounts = wordFrequency(functions);
    variables = getVariable(lines);
    totalvariables = getTotalVariable(variables);
    //vcounts = wordFrequency(variables);
    //cout << "kaj hoy" << endl;
    lineofeachfunction = getLineOfEachFunction(lines);
    //cout << " na " << endl;

    for(int i=0; i<totalvariables.size(); i++)
    {
        int varcount;
        string varname;
        varname = totalvariables[i].first;
        varcount = totalvariables[i].second;
        cout << "variable name-> " << varname << " count " << varcount << endl;
        //cout << variables[i] << endl;
    }

    //for(map<string, int>:: iterator it = vcounts.begin(); it!= vcounts.end(); it++)
    //{
        //cout << it->first << "  " << it->second << endl;
    //}

    for(int i=0; i<lineofeachfunction.size(); i++)
    {
        int a,b;
        string str;
        str = lineofeachfunction[i].first;
        a = lineofeachfunction[i].second.first;
        b = lineofeachfunction[i].second.second;

        cout << "str is " <<  str << endl << "Start= " << a << " End= " << b << endl;
        //cout << endl;
    }
    cout << "number of line of this code= " << numberOfLine << endl;
    //cout << "number " << l.size() << endl;
*/
}
