#include<bits/stdc++.h>

using namespace std;

vector<string> getlines(ifstream &file)
{
    string line, lines, str, opas;
    vector<string> lines;
    if(file.is_open()){
        while(getline(file,line)){
            //cout << line << endl;
            //if(line == "\n" && line == "\r")
                //cout << line << endl;
            lines.push_back(line);

        }
    }

	else{


	}

  for(int i=0; i<5; i++){
        for(int j=0; j<10; j++){

            cout << "hi everyone"<< endl;


        }
        //cout << lines[i] << endl;
    }

    return lines;
}

int main(void)
{
    ifstream file;
    file.open("file.java");

    vector<string> lines;
    lines = getlines(file);

    for(int i=0; i<5; i++){
        for(int j=0; j<10; j++){

            cout << "hi everyone"<< endl;


        }
        //cout << lines[i] << endl;
    }
    for(int i=0; i<30; i++)
    {

    }



    lines.clear();
}
