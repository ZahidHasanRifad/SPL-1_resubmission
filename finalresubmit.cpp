#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;


string makefileinstandardform(string filename, string outputfilename)
{
    ifstream file;
    string fullfile,s, onlychars;
    vector<string> line;
    file.open(filename);
    if(file.is_open())
    {
        while(file>>s)
        {
            istringstream iss(s);
            iss >> fullfile;
            onlychars += fullfile;
            //line.push_back(fullfile);
        }
    }
    else cout << "file could't be read." << endl;
    file.close();
    //cout << fullfile << endl;
    //istringstream iss(fullfile);
    //iss >> onlychars;
    //cout << onlychars <<endl;
    ofstream ofile;
    ofile.open(outputfilename);
    if(ofile.is_open())
    {
        for(int i=0; i<onlychars.length(); i++)
        {
            //if(onlychars[i] == '{' && onlychars[i] == ';' && onlychars[i] == '}')
            //{
                 ofile << onlychars[i];

            //}
            //else ofile << onlychars[i];
        }
    }
    else cout << "file could't be write" << endl;
    ofile.close();
    return onlychars;
}


vector<pair<string, int> > getVariable(string file)
{
    int counvar = 0;
    vector<pair<string, int> > var;
    stack<string> variables;
    for(int i=0;i<file.length(); i++)
    {
        if(file[i] == 'i' && file[i+1] == 'n' && file[i+2] == 't')
        {
            variables.push("int");
            i = i+2;
        }
        if(!variables.empty() && file[i] == '{')
        {
            variables.pop();
        }
        if(!variables.empty())
        {
            if(variables.top() == "int")
            {

                if(file[i] == ',')
                {
                    counvar++;
                }
                if(file[i] == ';')
                {
                    var.push_back(make_pair(variables.top(), counvar+1));
                    variables.pop();
                    counvar = 0;
                }
            }
        }
    }

    for(int i=0;i<file.length(); i++)
    {
        if(file[i] == 'f' && file[i+1] == 'l' && file[i+2] == 'o' && file[i+3] == 'a' && file[i+4] == 't')
        {
            variables.push("float");
            i = i+4;
        }

        if(!variables.empty() && file[i] == '{')
        {
            variables.pop();
        }
        if(!variables.empty())
        {
            if(variables.top() == "float")
            {
                if(file[i] == ',')
                {
                    counvar++;
                }
                if(file[i] == ';')
                {
                    var.push_back(make_pair(variables.top(), counvar+1));
                    variables.pop();
                    counvar = 0;
                }
            }
        }
    }

    for(int i=0;i<file.length(); i++)
    {
        if(file[i] == 'd' && file[i+1] == 'o' && file[i+2] == 'u' && file[i+3] == 'b' && file[i+4] == 'l' && file[i+5] == 'e')
        {
            variables.push("double");
            i = i+5;
        }

        if(!variables.empty() && file[i] == '{')
        {
            variables.pop();
        }
        if(!variables.empty())
        {
            if(variables.top() == "double")
            {
                if(file[i] == ',')
                {
                    counvar++;
                }
                if(file[i] == ';')
                {
                    var.push_back(make_pair(variables.top(), counvar+1));
                    variables.pop();
                    counvar = 0;
                }
            }
        }
    }

    for(int i=0;i<file.length(); i++)
    {
        if(file[i] == 's' && file[i+1] == 't' && file[i+2] == 'r' && file[i+3] == 'i' && file[i+4] == 'n' && file[i+5] == 'g')
        {
            variables.push("string");
            i = i+5;
        }

        if(!variables.empty() && file[i] == '{')
        {
            variables.pop();
        }
        if(!variables.empty())
        {
            if(variables.top() == "string")
            {
                if(file[i] == ',')
                {
                    counvar++;
                }
                if(file[i] == ';')
                {
                    var.push_back(make_pair(variables.top(), counvar+1));
                    variables.pop();
                    counvar = 0;
                }
            }
        }
    }

    for(int i=0;i<file.length(); i++)
    {
        if(file[i] == 'c' && file[i+1] == 'h' && file[i+2] == 'a' && file[i+3] == 'r')
        {
            variables.push("char");
            i = i+3;
        }

        if(!variables.empty() && file[i] == '{')
        {
            variables.pop();
        }
        if(!variables.empty())
        {
            if(variables.top() == "char")
            {
                if(file[i] == ',')
                {
                    counvar++;
                }
                if(file[i] == ';')
                {
                    var.push_back(make_pair(variables.top(), counvar+1));
                    variables.pop();
                    counvar = 0;
                }
            }
        }
    }

    for(int i=0;i<file.length(); i++)
    {
        if(file[i] == 'b' && file[i+1] == 'o' && file[i+2] == 'o' && file[i+3] == 'l')
        {
            variables.push("bool");
            i = i+3;
        }

        if(!variables.empty() && file[i] == '{')
        {
            variables.pop();
        }
        if(!variables.empty())
        {
            if(variables.top() == "bool")
            {
                if(file[i] == ',')
                {
                    counvar++;
                }
                if(file[i] == ';')
                {
                    var.push_back(make_pair(variables.top(), counvar+1));
                    variables.pop();
                    counvar = 0;
                }
            }
        }
    }

    return var;
}



vector<pair<string, string> > getFunctionFOR(string file)
{
    string functionname, insideparenthesis, contents;
    //int condfstpos, condlastpos, contentfstpos, contentlastpos;
    stack<string> func;
    stack<string> condition;
    stack<string> content;
    stack<string> flag;
    int j=0, k=0, numoffor = 0;
    vector<pair<string, string> > functions;
    for(int i=0; i<file.length(); i++)
    {
        if(file[i] == 'f' && file[i+1] == 'o' && file[i+2] == 'r' && file[i+3] == '(')
        {
            func.push("for");
            flag.push("for");
            numoffor++;
            //content.push("for");
            i = i+2;
            //cout << "pushed " << flag.top() << endl;
            //cout << "pushed " << func.top() << endl;
        }

        else if(file[i] == 'w' && file[i+1] == 'h' && file[i+2] == 'i' && file[i+3] == 'l' && file[i+4] == 'e' && file[i+5] == '(')
            flag.push("while");
        else if(file[i] == 'd' && file[i+1] == 'o' && file[i+2] == '{')
            flag.push("do");
        else if(file[i] == 'i' && file[i+1] == 'f')
            flag.push("if");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] == 'i' && file[i+5] == 'f')
            flag.push("elseif");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] != '(')
            flag.push("else");
        else if(file[i] == 's' && file[i+1] == 'w' && file[i+2] == 'i' && file[i+3] == 't' && file[i+4] == 'c' && file[i+5] == 'h')
            flag.push("switch");

        //cout << file[i] << endl;
        if(!func.empty() && !flag.empty())
        {



            if(func.top() == "for" && flag.top() == "for")
            {
                if(file[i-1] == '(')
                {
                    func.push("(");
                    //cout << "pushed " << func.top() << endl;

                }
            }

            if(func.top() == "(" && file[i] != ')')
            {
                insideparenthesis += file[i];
                //cout << insideparenthesis << endl ;

            }
            //cout << " cond " <<  insideparenthesis << endl;
            if(func.top() == "(" && file[i] == ')' && file[i+1] == '{')
            {
                func.pop();
                func.push("{");
                condition.push(insideparenthesis);
                insideparenthesis = "";
                //cout << " cond " <<  condition.top() << endl;

            }
            if(func.top() == "(" && file[i] == ')' && file[i+1] != '{')
                {
                func.pop();
                functionname = func.top();
                func.pop();
                condition.push(insideparenthesis);
                insideparenthesis = "";
                functions.push_back(make_pair(functionname, condition.top()));
                }
            /*
            if( flag.top() == "for" && file[i-1] == '{')
            {
                //if(content.top() != "{")
                    content.push("{");
            }
            if(!content.empty() && content.top() == "{" && file[i] !='}')
            {
                contents += file[i];

            }
            //cout << file[i] << endl;
            if(!content.empty() && flag.top() == "for" && content.top() == "{" && file[i] == '{')
            {
                content.push(contents);
                contents = "";
                k = 0;
            }
            */
            if(file[i] == '}')
            {
                if(flag.top() != "for")
                {
                    flag.pop();
                }
                else if(flag.top() == "for")
                {
                    content.push(contents);
                    if(func.top() == "{")
                    {

                        func.pop();
                        functionname = func.top();
                        insideparenthesis = condition.top();
                        condition.pop();
                        contents = content.top();
                        content.pop();
                        functions.push_back(make_pair(functionname, insideparenthesis));
                        //content.pop();
                        func.pop();
                        flag.pop();
                        insideparenthesis = "";
                        contents = "";
                    }
                }
            }
        }
    }

    return functions;
}


vector<pair<string, string> > getFunctionWHILE(string file)
{
    string functionname, insideparenthesis, contents;
    //int condfstpos, condlastpos, contentfstpos, contentlastpos;
    stack<string> func;
    stack<string> condition;
    stack<string> content;
    stack<string> flag;
    int j=0, k=0, numoffor = 0;
    vector<pair<string, string> > functions;
    for(int i=0; i<file.length(); i++)
    {
        if(file[i] == 'w' && file[i+1] == 'h' && file[i+2] == 'i' && file[i+3] == 'l' && file[i+4] == 'e' && file[i+5] == '(')
        {
            func.push("while");
            flag.push("while");
            numoffor++;
            //content.push("for");
            i = i+2;
            //cout << "pushed " << flag.top() << endl;
            //cout << "pushed " << func.top() << endl;
        }

        else if(file[i] == 'f' && file[i+1] == 'o' && file[i+2] == 'r' && file[i+3] == '(')
            flag.push("for");
        else if(file[i] == 'd' && file[i+1] == 'o' && file[i+2] == '{')
            flag.push("do");
        else if(file[i] == 'i' && file[i+1] == 'f')
            flag.push("if");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] == 'i' && file[i+5] == 'f')
            flag.push("elseif");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] != '(')
            flag.push("else");
        else if(file[i] == 's' && file[i+1] == 'w' && file[i+2] == 'i' && file[i+3] == 't' && file[i+4] == 'c' && file[i+5] == 'h')
            flag.push("switch");

        //cout << file[i] << endl;
        if(!func.empty() && !flag.empty())
        {



            if(func.top() == "while" && flag.top() == "while")
            {
                if(file[i-1] == '(')
                {
                    func.push("(");
                    //cout << "pushed " << func.top() << endl;

                }
            }

            if(func.top() == "(" && file[i] != ')')
            {
                insideparenthesis += file[i];
                //cout << insideparenthesis << endl ;

            }
            //cout << " cond " <<  insideparenthesis << endl;
            if(func.top() == "(" && file[i] == ')' && file[i+1] == '{')
            {
                func.pop();
                func.push("{");
                condition.push(insideparenthesis);
                insideparenthesis = "";
                //cout << " cond " <<  condition.top() << endl;

            }
            if(func.top() == "(" && file[i] == ')' && file[i+1] != '{')
                {
                func.pop();
                functionname = func.top();
                func.pop();
                condition.push(insideparenthesis);
                insideparenthesis = "";
                functions.push_back(make_pair(functionname, condition.top()));
                }
            /*
            if( flag.top() == "for" && file[i-1] == '{')
            {
                //if(content.top() != "{")
                    content.push("{");
            }
            if(!content.empty() && content.top() == "{" && file[i] !='}')
            {
                contents += file[i];

            }
            //cout << file[i] << endl;
            if(!content.empty() && flag.top() == "for" && content.top() == "{" && file[i] == '{')
            {
                content.push(contents);
                contents = "";
                k = 0;
            }
            */
            if(file[i] == '}')
            {
                if(flag.top() != "while")
                {
                    flag.pop();
                }
                else if(flag.top() == "while")
                {
                    content.push(contents);
                    if(func.top() == "{")
                    {

                        func.pop();
                        functionname = func.top();
                        insideparenthesis = condition.top();
                        condition.pop();
                        contents = content.top();
                        content.pop();
                        functions.push_back(make_pair(functionname, insideparenthesis));
                        //content.pop();
                        func.pop();
                        flag.pop();
                        insideparenthesis = "";
                        contents = "";
                    }
                }
            }
        }
    }

    return functions;

}



vector<pair<string, string> > getFunctionIF(string file)
{
    string functionname, insideparenthesis, contents;
    //int condfstpos, condlastpos, contentfstpos, contentlastpos;
    stack<string> func;
    stack<string> condition;
    stack<string> content;
    stack<string> flag;
    int j=0, k=0, numoffor = 0;
    vector<pair<string, string> > functions;
    for(int i=0; i<file.length(); i++)
    {
        if(file[i] == 'i' && file[i+1] == 'f')
        {
            func.push("if");
            flag.push("if");
            numoffor++;
            //content.push("for");
            i = i+2;
            //cout << "pushed " << flag.top() << endl;
            //cout << "pushed " << func.top() << endl;
        }

        else if(file[i] == 'w' && file[i+1] == 'h' && file[i+2] == 'i' && file[i+3] == 'l' && file[i+4] == 'e' && file[i+5] == '(')
            flag.push("while");
        else if(file[i] == 'd' && file[i+1] == 'o' && file[i+2] == '{')
            flag.push("do");
        else if(file[i] == 'f' && file[i+1] == 'o' && file[i+2] == 'r' && file[i+3] == '(')
            flag.push("for");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] == 'i' && file[i+5] == 'f')
            flag.push("elseif");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] != '(')
            flag.push("else");
        else if(file[i] == 's' && file[i+1] == 'w' && file[i+2] == 'i' && file[i+3] == 't' && file[i+4] == 'c' && file[i+5] == 'h')
            flag.push("switch");

        //cout << file[i] << endl;
        if(!func.empty() && !flag.empty())
        {



            if(func.top() == "if" && flag.top() == "if")
            {
                if(file[i-1] == '(')
                {
                    func.push("(");
                    //cout << "pushed " << func.top() << endl;

                }
            }

            if(func.top() == "(" && file[i] != ')')
            {
                insideparenthesis += file[i];
                //cout << insideparenthesis << endl ;

            }
            //cout << " cond " <<  insideparenthesis << endl;
            if(func.top() == "(" && file[i] == ')' && file[i+1] == '{')
            {
                func.pop();
                func.push("{");
                condition.push(insideparenthesis);
                insideparenthesis = "";
                //cout << " cond " <<  condition.top() << endl;

            }
            if(func.top() == "(" && file[i] == ')' && file[i+1] != '{')
                {
                func.pop();
                functionname = func.top();
                func.pop();
                condition.push(insideparenthesis);
                insideparenthesis = "";
                functions.push_back(make_pair(functionname, condition.top()));
                }
            /*
            if( flag.top() == "for" && file[i-1] == '{')
            {
                //if(content.top() != "{")
                    content.push("{");
            }
            if(!content.empty() && content.top() == "{" && file[i] !='}')
            {
                contents += file[i];

            }
            //cout << file[i] << endl;
            if(!content.empty() && flag.top() == "for" && content.top() == "{" && file[i] == '{')
            {
                content.push(contents);
                contents = "";
                k = 0;
            }
            */
            if(file[i] == '}')
            {
                if(flag.top() != "if")
                {
                    flag.pop();
                }
                else if(flag.top() == "if")
                {
                    content.push(contents);
                    if(func.top() == "{")
                    {

                        func.pop();
                        functionname = func.top();
                        insideparenthesis = condition.top();
                        condition.pop();
                        contents = content.top();
                        content.pop();
                        functions.push_back(make_pair(functionname, insideparenthesis));
                        //content.pop();
                        func.pop();
                        flag.pop();
                        insideparenthesis = "";
                        contents = "";
                    }
                }
            }
        }
    }

    return functions;
}


vector<pair<string, string> > getFunctionELSEIF(string file)
{
    string functionname, insideparenthesis, contents;
    //int condfstpos, condlastpos, contentfstpos, contentlastpos;
    stack<string> func;
    stack<string> condition;
    stack<string> content;
    stack<string> flag;
    int j=0, k=0, numoffor = 0;
    vector<pair<string, string> > functions;
    for(int i=0; i<file.length(); i++)
    {
        if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] == 'i' && file[i+5] == 'f')
        {
            func.push("elseif");
            flag.push("elseif");
            numoffor++;
            //content.push("for");
            i = i+2;
            //cout << "pushed " << flag.top() << endl;
            //cout << "pushed " << func.top() << endl;
        }

        else if(file[i] == 'w' && file[i+1] == 'h' && file[i+2] == 'i' && file[i+3] == 'l' && file[i+4] == 'e' && file[i+5] == '(')
            flag.push("while");
        else if(file[i] == 'd' && file[i+1] == 'o' && file[i+2] == '{')
            flag.push("do");
        else if(file[i] == 'i' && file[i+1] == 'f')
            flag.push("if");
        else if(file[i] == 'f' && file[i+1] == 'o' && file[i+2] == 'r' && file[i+3] == '(')
            flag.push("for");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] != '(')
            flag.push("else");
        else if(file[i] == 's' && file[i+1] == 'w' && file[i+2] == 'i' && file[i+3] == 't' && file[i+4] == 'c' && file[i+5] == 'h')
            flag.push("switch");

        //cout << file[i] << endl;
        if(!func.empty() && !flag.empty())
        {



            if(func.top() == "elseif" && flag.top() == "elseif")
            {
                if(file[i-1] == '(')
                {
                    func.push("(");
                    //cout << "pushed " << func.top() << endl;

                }
            }

            if(func.top() == "(" && file[i] != ')')
            {
                insideparenthesis += file[i];
                //cout << insideparenthesis << endl ;

            }
            //cout << " cond " <<  insideparenthesis << endl;
            if(func.top() == "(" && file[i] == ')' && file[i+1] == '{')
            {
                func.pop();
                func.push("{");
                condition.push(insideparenthesis);
                insideparenthesis = "";
                //cout << " cond " <<  condition.top() << endl;

            }
            if(func.top() == "(" && file[i] == ')' && file[i+1] != '{')
                {
                func.pop();
                functionname = func.top();
                func.pop();
                condition.push(insideparenthesis);
                insideparenthesis = "";
                functions.push_back(make_pair(functionname, condition.top()));
                }
            /*
            if( flag.top() == "for" && file[i-1] == '{')
            {
                //if(content.top() != "{")
                    content.push("{");
            }
            if(!content.empty() && content.top() == "{" && file[i] !='}')
            {
                contents += file[i];

            }
            //cout << file[i] << endl;
            if(!content.empty() && flag.top() == "for" && content.top() == "{" && file[i] == '{')
            {
                content.push(contents);
                contents = "";
                k = 0;
            }
            */
            if(file[i] == '}')
            {
                if(flag.top() != "elseif")
                {
                    flag.pop();
                }
                else if(flag.top() == "elseif")
                {
                    content.push(contents);
                    if(func.top() == "{")
                    {

                        func.pop();
                        functionname = func.top();
                        insideparenthesis = condition.top();
                        condition.pop();
                        contents = content.top();
                        content.pop();
                        functions.push_back(make_pair(functionname, insideparenthesis));
                        //content.pop();
                        func.pop();
                        flag.pop();
                        insideparenthesis = "";
                        contents = "";
                    }
                }
            }
        }
    }

    return functions;
}


vector<pair<string, string> > getFunctionSWITCH(string file)
{
    string functionname, insideparenthesis, contents;
    //int condfstpos, condlastpos, contentfstpos, contentlastpos;
    stack<string> func;
    stack<string> condition;
    stack<string> content;
    stack<string> flag;
    int j=0, k=0, numoffor = 0;
    vector<pair<string, string> > functions;
    for(int i=0; i<file.length(); i++)
    {
        if(file[i] == 's' && file[i+1] == 'w' && file[i+2] == 'i' && file[i+3] == 't' && file[i+4] == 'c' && file[i+5] == 'h')
        {
            func.push("switch");
            flag.push("switch");
            numoffor++;
            //content.push("for");
            i = i+2;
            //cout << "pushed " << flag.top() << endl;
            //cout << "pushed " << func.top() << endl;
        }

        else if(file[i] == 'w' && file[i+1] == 'h' && file[i+2] == 'i' && file[i+3] == 'l' && file[i+4] == 'e' && file[i+5] == '(')
            flag.push("while");
        else if(file[i] == 'd' && file[i+1] == 'o' && file[i+2] == '{')
            flag.push("do");
        else if(file[i] == 'i' && file[i+1] == 'f')
            flag.push("if");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] == 'i' && file[i+5] == 'f')
            flag.push("elseif");
        else if(file[i] == 'e' && file[i+1] == 'l' && file[i+2] == 's' && file[i+3] == 'e' && file[i+4] != '(')
            flag.push("else");
        else if(file[i] == 'f' && file[i+1] == 'o' && file[i+2] == 'r' && file[i+3] == '(')
            flag.push("for");

        //cout << file[i] << endl;
        if(!func.empty() && !flag.empty())
        {



            if(func.top() == "switch" && flag.top() == "switch")
            {
                if(file[i-1] == '(')
                {
                    func.push("(");
                    //cout << "pushed " << func.top() << endl;

                }
            }

            if(func.top() == "(" && file[i] != ')')
            {
                insideparenthesis += file[i];
                //cout << insideparenthesis << endl ;

            }
            //cout << " cond " <<  insideparenthesis << endl;
            if(func.top() == "(" && file[i] == ')' && file[i+1] == '{')
            {
                func.pop();
                func.push("{");
                condition.push(insideparenthesis);
                insideparenthesis = "";
                //cout << " cond " <<  condition.top() << endl;

            }
            if(func.top() == "(" && file[i] == ')' && file[i+1] != '{')
            {
                func.pop();
                functionname = func.top();
                func.pop();
                condition.push(insideparenthesis);
                insideparenthesis = "";
                functions.push_back(make_pair(functionname, condition.top()));
            }
            /*
            if( flag.top() == "for" && file[i-1] == '{')
            {
                //if(content.top() != "{")
                    content.push("{");
            }
            if(!content.empty() && content.top() == "{" && file[i] !='}')
            {
                contents += file[i];

            }
            //cout << file[i] << endl;
            if(!content.empty() && flag.top() == "for" && content.top() == "{" && file[i] == '{')
            {
                content.push(contents);
                contents = "";
                k = 0;
            }
            */
            if(file[i] == '}')
            {
                if(flag.top() != "switch")
                {
                    flag.pop();
                }
                else if(flag.top() == "switch")
                {
                    content.push(contents);
                    if(func.top() == "{")
                    {

                        func.pop();
                        functionname = func.top();
                        insideparenthesis = condition.top();
                        condition.pop();
                        contents = content.top();
                        content.pop();
                        functions.push_back(make_pair(functionname, insideparenthesis));
                        //content.pop();
                        func.pop();
                        flag.pop();
                        insideparenthesis = "";
                        contents = "";
                    }
                }
            }
        }
    }

    return functions;
}


vector<pair<string, int> > variablefrequency(vector<pair<string, int> > variables)
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


void comparevariable(vector<pair<string, int> > file1, vector<pair<string, int> > file2)
{
    vector<pair<string, int> > v1;
    vector<pair<string, int> > v2;
    v1 = variablefrequency(file1);
    v2 = variablefrequency(file2);
    vector<pair<string, int> > v3;
    string name;
    int counts, sub;
    for(int i=0; i<v1.size(); i++)
    {
        name = v1[i].first;
        counts = v1[i].second;
        if(name == v2[i].first)
        {
            sub = fabs(counts-v2[i].second);
            v3.push_back(make_pair(name, sub));
        }
    }

    for(int i=0; i<v3.size(); i++)
    {
        name = v3[i].first;
        counts = v3[i].second;
        if(counts == 0)
        {
            cout << name << " type variables are same number of occurrences " << endl;
        }
        else
            cout << name << " type variables are not same number of occurrences " << endl;
    }

}


vector<string> getTotalfunctions(string file)
{
    vector<pair<string,string> > forcount;
    vector<pair<string,string> > whilecount;
    vector<pair<string,string> > ifcount;
    vector<pair<string,string> > elseifcount;
    vector<pair<string,string> > switchcount;
    forcount = getFunctionFOR(file);
    whilecount = getFunctionWHILE(file);
    ifcount = getFunctionIF(file);
    elseifcount = getFunctionELSEIF(file);
    switchcount = getFunctionSWITCH(file);
    vector<string> func;

    for(int i=0; i<forcount.size(); i++)
    {
        func.push_back(forcount[i].first);
    }
    for(int i=0; i<whilecount.size(); i++)
    {
        func.push_back(whilecount[i].first);
    }
    for(int i=0; i<ifcount.size(); i++)
    {
        func.push_back(ifcount[i].first);
    }
    for(int i=0; i<elseifcount.size(); i++)
    {
        func.push_back(elseifcount[i].first);
    }
    for(int i=0; i<switchcount.size(); i++)
    {
        func.push_back(switchcount[i].first);
    }
    return func;
}


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


void comparefunctionoccurrences(vector<string> functionsfile1, vector<string> functionsfile2)
{
    map<string, int> f1;
    map<string, int> f2;
    f1 = wordFrequency(functionsfile1);
    f2 = wordFrequency(functionsfile2);
    vector<pair<string, int> > v;

    map<string, int>:: iterator itf1 = f1.begin();
    for(map<string, int>:: iterator itf2 = f2.begin(); (itf2 != f2.end() && itf1 != f1.end()); itf2++)
    {
        if(itf1->first == itf2->first)
        {
            v.push_back(make_pair(itf1->first, fabs(itf1->second - itf2->second)));
        }
        itf1++;
    }

    for(int i=0; i<v.size(); i++)
    {
        string name;
        int sub;
        name = v[i].first;
        sub = v[i].second;
        if(sub == 0)
        {
            cout << name << " same number of occurrences " << endl;
        }

        else
            cout << name << " not same number of occurrences " <<endl;
    }
}


vector<pair<string, string> > generateforloopcondition(vector<pair<string, string> > forcount)
{
    vector<pair<string, string> > frc;
        for(int i=0; i<forcount.size(); i++)
        {
            string name = forcount[i].first;
            string condition1 = forcount[i].second;
            string actualcon1,ini1, increm1, total;
            stack<char> check;
            stack<char> act;
            stack<char> ini;
            for(int j=0;j<condition1.length(); j++)
            {
                if(condition1[j] == ';')
                {
                    check.push(condition1[j]);
                }

                if(check.empty() && condition1[j] == '=')
                {
                    //cout << "check " << condition1[j] << endl;
                    ini.push(condition1[j]);

                }
                if(!ini.empty() && ini.top() == '=' && check.empty())
                {
                    ini1 += condition1[j];
                }
                if((condition1[j] == '<' || condition1[j] == '>' || condition1[j] =='!' || condition1[j] == '=')
                   && check.size() == 1)
                {
                    act.push(condition1[j]);
                }
                if(!act.empty() && check.size() == 1 && (act.top() == '<' || act.top() == '>' || act.top() == '!'
                                                         || act.top() == '='))
                {
                    actualcon1 += condition1[j];
                }
                if(!check.empty() && check.size() == 2 && condition1[j] != '\n' &&
                   ((condition1[j] == '+'&& condition1[j+1] == '+') || (condition1[j]== '+' && condition1[j+1] == '1')))
                {
                    increm1 = "++";
                    check.pop();
                    check.pop();
                }

            }
            total = ini1+actualcon1+increm1;
            //cout << "total is " << total << endl;
            frc.push_back(make_pair(name, total));
        }
        return frc;
}


void compareConditions(string file1, string file2)
{
    vector<pair<string,string> > forcount1;
    vector<pair<string,string> > whilecount1;
    vector<pair<string,string> > ifcount1;
    vector<pair<string,string> > elseifcount1;
    vector<pair<string,string> > switchcount1;
    forcount1 = getFunctionFOR(file1);
    whilecount1 = getFunctionWHILE(file1);
    ifcount1 = getFunctionIF(file1);
    elseifcount1 = getFunctionELSEIF(file1);
    switchcount1 = getFunctionSWITCH(file1);

    vector<pair<string,string> > forcount2;
    vector<pair<string,string> > whilecount2;
    vector<pair<string,string> > ifcount2;
    vector<pair<string,string> > elseifcount2;
    vector<pair<string,string> > switchcount2;
    forcount2 = getFunctionFOR(file2);
    whilecount2 = getFunctionWHILE(file2);
    ifcount2 = getFunctionIF(file2);
    elseifcount2 = getFunctionELSEIF(file2);
    switchcount2 = getFunctionSWITCH(file2);
    //for loop
    int forcnt=0, whilecnt=0, ifcnt=0, elseifcnt=0, switchcnt=0;

    vector<pair<string,string> > accurateconditionoffor1;
    vector<pair<string,string> > accurateconditionoffor2;
    accurateconditionoffor1 = generateforloopcondition(forcount1);
    accurateconditionoffor2 = generateforloopcondition(forcount2);

    if(accurateconditionoffor1.size()<=accurateconditionoffor2.size())
    {
        for(int i=0;i<accurateconditionoffor1.size(); i++)
        {
            string condition1 = accurateconditionoffor1[i].second;
            string condition2 = accurateconditionoffor2[i].second;

            if(condition1 == condition2)
            {
                forcnt++;
            }
        }
        cout << "for loop match " << forcnt << " times " << endl;
        if(accurateconditionoffor1.size() == forcnt)
        {
            cout << "all for of file1 matched to file2 " << endl;
        }
    }

    if(accurateconditionoffor2.size()<accurateconditionoffor1.size())
    {
        for(int i=0;i<accurateconditionoffor2.size(); i++)
        {
            string condition1 = accurateconditionoffor1[i].second;
            string condition2 = accurateconditionoffor2[i].second;

            if(condition1 == condition2)
            {
                forcnt++;
            }
        }
        cout << "for loop match " << forcnt << " times " << endl;
        if(accurateconditionoffor2.size() == forcnt)
        {
            cout << "all for of file2 matched to file1 " << endl;
        }
    }

    if(whilecount1.size()<=whilecount2.size())
    {
        for(int i=0;i<whilecount1.size(); i++)
        {
            string condition1 = whilecount1[i].second;
            string condition2 = whilecount2[i].second;

            if(condition1 == condition2)
            {
                whilecnt++;
            }
        }
        cout << "while loop match " << whilecnt << " times " << endl;
        if(whilecount1.size() == whilecnt)
        {
            cout << "all while of file1 matched to file2 " << endl;
        }
    }

    if(whilecount2.size()<whilecount1.size())
    {
        for(int i=0;i<whilecount2.size(); i++)
        {
            string condition1 = whilecount1[i].second;
            string condition2 = whilecount2[i].second;

            if(condition1 == condition2)
            {
                whilecnt++;
            }
        }
        cout << "while loop match " << whilecnt << " times " << endl;
        if(whilecount2.size() == whilecnt)
        {
            cout << "all while of file2 matched to file1 " << endl;
        }
    }

    if(ifcount1.size()<=ifcount2.size())
    {
        for(int i=0;i<ifcount1.size(); i++)
        {
            string condition1 = ifcount1[i].second;
            string condition2 = ifcount2[i].second;

            if(condition1 == condition2)
            {
                ifcnt++;
            }
        }
        cout << "if match " << ifcnt << " times " << endl;
        if(ifcount1.size() == ifcnt)
        {
            cout << "all if of file1 matched to file2 " << endl;
        }
    }

    if(ifcount2.size()<ifcount1.size())
    {
        for(int i=0;i<ifcount2.size(); i++)
        {
            string condition1 = ifcount1[i].second;
            string condition2 = ifcount2[i].second;

            if(condition1 == condition2)
            {
                ifcnt++;
            }
        }
        cout << "if match " << ifcnt << " times " << endl;
        if(ifcount2.size() == ifcnt)
        {
            cout << "all if of file2 matched to file1 " << endl;
        }
    }

    if(elseifcount1.size()<=elseifcount2.size())
    {
        for(int i=0;i<elseifcount1.size(); i++)
        {
            string condition1 = elseifcount1[i].second;
            string condition2 = elseifcount2[i].second;

            if(condition1 == condition2)
            {
                elseifcnt++;
            }
        }
        cout << "else if match " << elseifcnt << " times " << endl;
        if(elseifcount1.size() == elseifcnt)
        {
            cout << "all else if of file1 matched to file2 " << endl;
        }
    }

    if(elseifcount2.size()<elseifcount1.size())
    {
        for(int i=0;i<elseifcount2.size(); i++)
        {
            string condition1 = elseifcount1[i].second;
            string condition2 = elseifcount2[i].second;

            if(condition1 == condition2)
            {
                elseifcnt++;
            }
        }
        cout << "else if match " << elseifcnt << " times " << endl;
        if(elseifcount2.size() == elseifcnt)
        {
            cout << "all else if of file2 matched to file1 " << endl;
        }
    }

    if(switchcount1.size()<=switchcount2.size())
    {
        for(int i=0;i<switchcount1.size(); i++)
        {
            string condition1 = switchcount1[i].second;
            string condition2 = switchcount2[i].second;

            if(condition1 == condition2)
            {
                switchcnt++;
            }
        }
        cout << "switch match " << switchcnt << " times " << endl;
        if(switchcount1.size() == switchcnt)
        {
            cout << "all switch of file1 matched to file2 " << endl;
        }
    }

    if(switchcount2.size()<switchcount1.size())
    {
        for(int i=0;i<switchcount2.size(); i++)
        {
            string condition1 = switchcount1[i].second;
            string condition2 = switchcount2[i].second;

            if(condition1 == condition2)
            {
                switchcnt++;
            }
        }
        cout << "switch match " << switchcnt << " times " << endl;
        if(switchcount2.size() == switchcnt)
        {
            cout << "all switch of file2 matched to file1 " << endl;
        }
    }
}


int main(void)
{
    string filename1, filename2, file1,file2;
    filename1 = "spl1.cpp";
    filename2 = "spl1.cpp";
    file1 = makefileinstandardform(filename1, "stan1.txt");
    file2 = makefileinstandardform(filename2, "stan2.txt");

    vector<pair<string, int> > variables1;
    vector<pair<string, int> > variables2;
    variables1 = getVariable(file1);
    variables2 = getVariable(file2);

    comparevariable(variables1,variables2);

    vector<string> functions1;
    vector<string> functions2;
    functions1 = getTotalfunctions(file1);
    functions2 = getTotalfunctions(file2);

    comparefunctionoccurrences(functions1, functions2);

    compareConditions(file1, file2);
/*
    for(int i=0; i<variables.size(); i++)
    {
        cout << variables[i].first << " " << variables[i].second << endl;
    }

    vector<pair<string,string> > forcount;
    vector<pair<string,string> > whilecount;
    vector<pair<string,string> > ifcount;
    vector<pair<string,string> > elseifcount;
    vector<pair<string,string> > switchcount;
    forcount = getFunctionFOR(file1);
    whilecount = getFunctionWHILE(file1);
    ifcount = getFunctionIF(file1);
    elseifcount = getFunctionELSEIF(file1);
    switchcount = getFunctionSWITCH(file1);

    for(int i=0; i<forcount.size(); i++)
    {
        string name, condition, content;
        name = forcount[i].first;
        condition = forcount[i].second;
        //content = forcount[i].second.second;

        cout << name << " " << condition  << endl;
    }

    vector<pair<string, string> > geforloop;
    geforloop = generateforloopcondition(forcount);

    for(int i=0;i <geforloop.size(); i++)
    {
        string name = geforloop[i].first;
        string con = geforloop[i].second;

        cout << name << " accurate condition " << con << endl;
    }
    */

    variables1.clear();
    variables2.clear();
    functions1.clear();
    functions2.clear();

    return 0;
}
