#include <dirent.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
//#include<istringstream>
#include<bits/stdc++.h>

using namespace std;


int getnumberofline(ifstream &file)
{
    string line;
    int lines=0;
    while(getline(file, line))
    {
        lines++;
    }
    return lines;
}


string withoutPunc (string s)
{
    string p = ",.?;:!(){}[]\"";
    string ss;

    for(int i=0; i<p.length(); i++)
    {
        for(int j=0; j<s.length(); j++)
        {
            if(s[j] == p[i])
            {
                s[j] = ' ';

            }

        }

    }
    return s;
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


vector<string> getTotalWords(ifstream &file)
{
    vector<string> words;
    string word, str;

    while(file >> word)
    {
        //file >> word;
        word = withoutPunc(word);
        istringstream iss(word);
        iss >> str;
        words.push_back(str);
    }
    return words;
}


vector<string> uniquewords(vector<string> v)
{
    map<string, int> m;

    vector<string> word;
    m = wordFrequency(v);

    map<string, int>:: iterator it = m.begin();
    int i=0;
    for(it = m.begin(); it !=m.end(); it++)
    {
        word.push_back(it->first);
    }

    return word;
}


vector<string> getWithoutStopWords(vector<string> words)
{
    vector<string> word;
    vector<string> withoutStop;
    vector<string> v;
    map<string, bool> check;
    string s;

    for(int i=0; i<words.size(); i++)
    {
        string s = words[i];
        for(int j=0; j<s.length(); j++)
        {
            s[j] = tolower(s[j]);
        }
        word.push_back(s);
    }
    for(int i=0; i<words.size(); i++)
    {
        string s = words[i];
        for(int j=0; j<s.length(); j++)
        {
            s[j] = tolower(s[j]);
        }
        check[s] = true;
    }
    ifstream stopwordfile;
    stopwordfile.open("stop_words.txt");
    if(stopwordfile.is_open())
    {
        while(stopwordfile >> s)
        {
            if(check.find(s) != check.end())
            {
                check.erase(s);
            }
        }
    }
    else
        cout << "can't open the stopword file." << endl;

    for(map<string, bool> :: iterator it = check.begin(); it!=check.end(); it++)
    {
        withoutStop.push_back(it->first);
    }

    for(int i=0; i<words.size(); i++)
    {
        for(int j=0; j<withoutStop.size(); j++)
        {
            if(word[i] == withoutStop[j])
            {
                v.push_back(word[i]);
            }
        }
    }
    withoutStop.clear();
    check.clear();
    word.clear();
    return v;
}


double calculateTF(int numberOfTerms, int totalTerms)
{
    double result;
    result =(double) numberOfTerms/totalTerms;
    return result;
}


double caltulateIDF(int numberOfTerms, int numberOfDocuments)
{
    double result;
    double re=(double) numberOfDocuments/numberOfTerms;
    result =(double) (1+log2(re));
    return result;
}


double calculateWeight(double tf, double idf)
{
    double result;
    result = tf*idf;
    return result;
}


map<string, double> TF(vector<string> ttv)
{
    map<string, double> tfm;                         // term frequency map which contain term, and frequency.
    map<string, int> rowtfm;                        // term count map. which contain term and number of term.
    vector<string> tv;                              //term vector. which contain term and no stop words.

    tv = getWithoutStopWords(ttv);                    // getting fresh word.
    rowtfm = wordFrequency(tv);                        // getting term and number of term.
    int totalterm = tv.size();                      // total number of term of a document.
    //cout << "withoutstopwords total words is " << ttv.size() << endl;
    //cout << "Total Term is: " << totalterm << endl;
    //cout << "In row " << rowtfm.size() << endl;
    for(map<string, int> :: iterator it = rowtfm.begin(); it != rowtfm.end(); it++)
    {
        string term = it->first;
        int freq = it->second;

        double tf = (double) calculateTF(freq, totalterm);
        tfm[term] = tf;
        //cout << term << "   " << freq << "      " <<tf << endl;
    }

    tv.clear();
    rowtfm.clear();
    return tfm;

}


map<string, double> IDF2(vector<string> totalwordofdocuments, vector<string> *dtv, int numberOfDocuments)
{

    int countdf=0;
    vector<string> tv;
    vector<string> u;
    map<string, double> idfm;
    map<string, int> rowfrq[numberOfDocuments];

    vector<string> doct[numberOfDocuments];
    //vector<string> uniq[numberOfDocuments];

    tv = getWithoutStopWords(totalwordofdocuments);                 // get total words of documents.
    u = uniquewords(tv);                                            // get the unique words of documents.

    int totalword = u.size();

    for(int i=0; i<numberOfDocuments; i++)
    {
        doct[i] = getWithoutStopWords(dtv[i]);                      // get total word of a document.
        rowfrq[i] = wordFrequency(doct[i]);
        //uniq[i] = uniquewords(doct[i]);                         // get the rowcount of word of a document.
        //cout << "in IDF2 row count for file " << i+1 << "is" << rowfrq[i].size() << endl;
        //cout << "in IDF2 row count for file " << i+1 << "is" << uniq[i].size() << endl;
    }
    //cout << " IDF2 totalword is " << totalword << endl;

    for(int i=0; i<totalword; i++)
    {
        string t = u[i];
        for(int j=0; j<numberOfDocuments; j++)
        {

            for(map<string, int>:: iterator it = rowfrq[j].begin(); it!=rowfrq[j].end(); it++)
            //for(int k=0; k<uniq[i].size(); k++)
            {
                if(t == it->first)
            //    if(t==uniq[i][k])
                {
                    countdf++;
                }
            }
        }
        //cout << "count of word "<< t <<  " in document is : " << countdf << endl;
        double idfv = caltulateIDF(countdf, numberOfDocuments);
        //if(idfv == 1)
        	//cout << "Similar word is " << t << endl;
        idfm[t] = idfv;
        countdf = 0;
    }
    for(int i=0; i<numberOfDocuments; i++)
    {
        rowfrq[i].clear();
        //uniq[i].clear();
        doct[i].clear();
    }
    tv.clear();
    u.clear();
    return idfm;
}


map<string, double> getscore(map<string, double> tf, map<string, double> idf, int numberOfDocuments)
{
    map<string, double> s;

    map<string, double>:: iterator itf = tf.begin();
    map<string, double>:: iterator itdf = idf.begin();

    for(itf = tf.begin(); itf != tf.end(); itf++)
    {
        string stf = itf->first;

        for(itdf = idf.begin(); itdf!=idf.end(); itdf++)
        {
            string sdf = itdf->first;
            if(stf == sdf)
            {

                double sc = calculateWeight(itf->second, itdf->second);
                s[stf] = sc;

            }
        }
    }

    return s;
}


double* getScoreforFile(map<string, double> *totalscore, int numberOfDocuments)
{
    //int files = tf.size();
    double* score = new double[numberOfDocuments];
    double coutnscore = 0.0;
    for(int i=0; i<numberOfDocuments; i++)
    {
        //for(map<string, double>:: iterator itf = tf[i].begin(); itf != tf[i].end(); itf++)
        //{
            //string s = itf->first;
            for(map<string, double>:: iterator its = totalscore[i].begin(); its != totalscore[i].end(); its++)
            {
                //if(s == its->first)
                //{
                    coutnscore += its->second;
                //}
            }

        //}

        score[i] = coutnscore;
        coutnscore = 0.0;
    }

    return score;
}


map<string, double> wordVectorofDocument(map<string, double> tf, map<string, double> score)
{
	map<string, double> vec;

	for(map<string, double>:: iterator it = tf.begin(); it!=tf.end(); it++)
	{
		string s = it->first;
		for(map<string, double>:: iterator its = score.begin(); its!=score.end(); its++)
		{
			if(s == its->first)
			{
				vec[s] = its->second;
			}
		}
	}
	return vec;
}


map<string, double>* wordVectorofDocuments(map<string, double> *tf, map<string, double> score, int numberOfDocuments)
{
	map<string, double> vec[numberOfDocuments];
	for(int i=0; i<numberOfDocuments; i++)
	{
		for(map<string, double>:: iterator it = tf[i].begin(); it!=tf[i].end(); it++)
		{
			string s = it->first;
			for(map<string, double>:: iterator its = score.begin(); its!=score.end(); its++)
			{
				if(s == its->first)
				{
					vec[i][s] = its->second;
				}
			}
		}
	}

	return vec;
}


double dotproduct(map<string, double> vec1, map<string, double> vec2)
{
	double result = 0.0;
	map<string, double>:: iterator v2 = vec2.begin();
	for(map<string, double>:: iterator v1 = vec1.begin(); (v1 != vec1.end()) && (v2 != vec2.end()); v1++)
	{
		double value1 = v1->second;
		double value2 = v2->second;

		result += value1*value2;
		v2++;
	}
	return result;
}


double valueofVector(map<string, double> vec)
{
	double result = 0.0;
	double samplesum = 0.0;
	for(map<string, double>:: iterator v = vec.begin(); v != vec.end(); v++)
	{
		double value = v->second;
		samplesum += value*value;
	}

	result = sqrt(samplesum);
	return result;
}


double getCosineValue(map<string, double> vec1, map<string, double> vec2)
{
	double cosinevalue;

	cosinevalue = (double) dotproduct(vec1, vec2)/(valueofVector(vec1)*valueofVector(vec2));
	//cout << "dot Product " << dotproduct(vec1, vec2) << endl;
	//cout << "value of vector 1 " << valueofVector(vec1) << endl << "value of vector 2 " << valueofVector(vec2) << endl;
	//cout << "multiplication of two vector value " << valueofVector(vec1)*valueofVector(vec2) << endl;

	return cosinevalue;
}


void pritn(map<string, double> *tf, map<string, int> *rowfreq, map<string, double> idf, map<string, double> *score, double *filescore, int numberOfDocuments)
{

    ofstream file;
    file.open("SPL.csv");
    if(file.is_open())
    {
        file << "Term" << "," << "count" << "," << "Term Frequency" << "," << "IDF" << "," << "Score" <<endl;
        for(int i=0; i<numberOfDocuments; i++)
        {

            //cout << "File " << i+1 << endl;
            file<< "File" << i+1 << endl;

            map<string, int> :: iterator itr = rowfreq[i].begin();
            map<string, double>:: iterator its = score[i].begin();
            for(map<string, double>:: iterator itf = tf[i].begin(); (itf != tf[i].end() || itr != rowfreq[i].end() || its != score[i].end()); itf++)
            {
                //map<string, int>:: iterator itrw = rowfreq.begin();
                string s = itf->first;
                //int rc = itr->second;
                for(map<string, double>:: iterator itdf = idf.begin(); (itdf != idf.end()) ; itdf++)
                {
                    string sd = itdf->first;
                    string ss = its->first;
                    //string sr = itrw->first;
                    if((s==sd))
                    {
                        //cout << s << "|            " << itf->second << "|              " << itdf->second << "|             " << its->second <<endl;
                        //cout << s << "," << itr->second << "," << itf->second << "," << itdf->second << "," << its->second <<endl;
                        file << s << "," << itr->second << "," << itf->second << "," << itdf->second << "," << its->second <<endl;
                    }

                    //itrw++;
                }
                its++;
                itr++;
            }
           // cout << "File " << i+1 << "Score is " << filescore[i] <<endl;
            //cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            //cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
        }
    }

}


void makedoubelwordfile(vector<string> singlewords)
{
    ofstream bygramfile;
    bygramfile.open("doublewordfile.txt");

    for(int i=0; i<singlewords.size(); i++)
    {
        bygramfile << singlewords[i];
        if(i%2 != 0)
            bygramfile << " ";
    }
}

vector<string> open(string path)
{

    DIR* dir;
    dirent* pdir;
    vector<string> files;

    dir = opendir(path.c_str());

    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }

    return files;
}


int isTextFile(string filename)
{
    for(int j=0; j<filename.length(); j++)
    {
        if(filename[j] == '.' && filename[j+1] == 't' && filename[j+2] == 'x' && filename[j+3] == 't')
        {
            //cout << filename << endl;
            return 1;
            break;
        }


    }
    return 0;
}


vector<string> getTextFiles(string path)
{
    vector<string> f;
    //string path;
    vector<string> files;
   // path = "C:\\Users\\HP\\Desktop";
    f = open(path); // or pass which dir to open

    ifstream file;
    for(int i=0; i<f.size(); i++)
    {
        string filename = f[i];
        if(isTextFile(filename))
        {
            files.push_back(f[i]);
        }


    }

    return files;
}


void findSingleWordSimilarity(string dirname)
{
    vector<string> files;
    files = getTextFiles(dirname);
    int numberofDocument = files.size();



    ofstream frequencyFile,cosinFile;
    vector<string> words[numberofDocument];
    vector<string> uniqueword;
    vector<string> withoutstopwords;
    vector<string> fresh;
    vector<string> withoutforeach[numberofDocument];
    map<string, double> tf[numberofDocument];
    map<string, double> idf;
    map<string, double> score[numberofDocument];
    map<string, int> rowfreq;
    map<string, int> rowcou[numberofDocument];

    vector<string> totalwords;

    for(int i=0; i<numberofDocument; i++)
    {
        files[i] = dirname+"/"+files[i];
    }


    for(int i=0; i<numberofDocument; i++)
    {
        ifstream file;
        file.open(files[i]);
        if(file.is_open())
        {
            words[i] = getTotalWords(file);
        }
        else
            cout << "can't open " << files[i] << " " << endl;
        file.close();

    }

    int numberOfDocuments = numberofDocument;
    for(int i=0; i<numberOfDocuments; i++)
    {
        withoutforeach[i] = getWithoutStopWords(words[i]);
        rowcou[i] = wordFrequency(withoutforeach[i]);

        int len = words[i].size();
        for(int j=0; j<len; j++)
        {
            string str = words[i][j];
            totalwords.push_back(str);
        }
    }

    withoutstopwords = getWithoutStopWords(totalwords);
    rowfreq = wordFrequency(withoutstopwords);


    for(int i=0; i<numberOfDocuments; i++)
    {
        tf[i] = TF(words[i]);
//        tfdoubleword[i] = TF(doublewords[i]);
    }

    idf = IDF2(totalwords,words, numberOfDocuments);
    //idfdoubleword = IDF2(totaldoublewords, doublewords, numberOfDocuments);
    //rowfreq = wordFrequency(withoutstopwords);
    for(int i=0; i<numberOfDocuments; i++)
    {
        score[i] = getscore(tf[i], idf, numberOfDocuments);
    }


    double* scores = new double[numberOfDocuments];
    scores = getScoreforFile(score,numberOfDocuments);
    pritn(tf, rowcou, idf, score, scores, numberOfDocuments);
    //pritn(tfdoubleword, rowcou, idf, score, scores, numberOfDocuments);
    //cout << "total words is: idf " << idf.size() << endl;
    //cout << "total words is: score " << score.size() << endl;
    //cout << "total words in: rowfreq " << rowfreq.size() << endl;

    cosinFile.open("Cosine.csv");
    map<string, double> wordVectorofDocuments[numberOfDocuments];
    double cosinevalues[numberOfDocuments][numberOfDocuments];
    for(int i=0; i<numberOfDocuments; i++)
    {
    	wordVectorofDocuments[i] = wordVectorofDocument(tf[i], score[i]);
    }
    //cout << "the cosine values are "<< endl;
    cosinFile << " " ;
    for(int i=0; i<numberOfDocuments; i++)
    {
        cosinFile << "," <<  "File" << i+1;
    }
    cosinFile << endl;
    for(int i=0; i<numberOfDocuments; i++)
    {
        cosinFile << "file" << i+1 << ",";
    	for(int j=0; j<numberOfDocuments; j++)
    	{
    		cosinevalues[i][j] = getCosineValue(wordVectorofDocuments[i], wordVectorofDocuments[j]);
    		//cout << cosinevalues[i][j] << " ";
    		cosinFile << cosinevalues[i][j] << ",";
    		if(i!=j && cosinevalues[i][j]>0.80)
                cout << "File" << i+1 << " is similar to " << "File" << j+1 << endl;
            else if(cosinevalues[i][j]<0.80)
                cout << "File" << i+1 << " is not similar to " << "File" << j+1 << endl;

    	}
    	cout << endl;
    	cosinFile << endl;
    }
    fresh.clear();
    uniqueword.clear();
    files.clear();
    for(int i=0; i<numberofDocument; i++)
    {
        words[i].clear();
        tf[i].clear();
        //tfdoubleword[i].clear();
        rowcou[i].clear();
        withoutforeach[i].clear();
        //doublewords[i].clear();
        score[i].clear();


    }
    totalwords.clear();
    withoutstopwords.clear();
    idf.clear();
    //idfdoubleword.clear();
    //score.clear();
    //scoredoubleword.clear();
    rowfreq.clear();
}


void findPairWordSimilarity(string dirname)
{
    vector<string> files;
    files = getTextFiles(dirname);
    int numberofDocument = files.size();



    ofstream frequencyFile,cosinFile;
    vector<string> words[numberofDocument];
    vector<string> uniqueword;
    vector<string> withoutstopwords;
    vector<string> fresh;
    vector<string> withoutforeach[numberofDocument];
    map<string, double> tf[numberofDocument];
    map<string, double> idf;
    map<string, double> score[numberofDocument];
    map<string, int> rowfreq;
    map<string, int> rowcou[numberofDocument];

    vector<string> totalwords;

    for(int i=0; i<numberofDocument; i++)
    {
        files[i] = dirname+"/"+files[i];
    }


    for(int i=0; i<numberofDocument; i++)
    {
        ifstream file;
        file.open(files[i]);
        if(file.is_open())
        {
            words[i] = getTotalWords(file);
        }
        else
            cout << "can't open " << files[i] << " " << endl;
        file.close();

    }

    int numberOfDocuments = numberofDocument;
    for(int i=0; i<numberOfDocuments; i++)
    {
        withoutforeach[i] = getWithoutStopWords(words[i]);
        //rowcou[i] = wordFrequency(withoutforeach[i]);

        int len = words[i].size();
        for(int j=0; j<len; j++)
        {
            string str = words[i][j];
            totalwords.push_back(str);
        }
    }

    //withoutstopwords = getWithoutStopWords(totalwords);
    //rowfreq = wordFrequency(withoutstopwords);

    vector<string>doublewords[numberOfDocuments];
    vector<string>totaldoublewords;
    for(int i=0; i<numberOfDocuments; i++)
    {
        ifstream doublewordfile;
        makedoubelwordfile(withoutforeach[i]);
        doublewordfile.open("doublewordfile.txt");
        doublewords[i] = getTotalWords(doublewordfile);

        doublewordfile.close();
        int a = remove("doublewordfile.txt");
       /* if(a == 0)
            cout << "file deleted" << endl;
        else
            cout << "error in deleting" << endl;
*/
    }
    //cout << "before" << endl;
    for(int i=0; i<numberOfDocuments; i++)
    {

        for(int j=0; j<doublewords[i].size(); j++)
        {
            string s = doublewords[i][j];
            totaldoublewords.push_back(s);
            //cout << s << endl;
        }
    }




    //cout << "after" << endl;
    //map<string, double> tfdoubleword[numberofDocument];
    //map<string, double> idfdoubleword;
    //map<string, double> scoredoubleword;

    for(int i=0; i<numberOfDocuments; i++)
    {
        tf[i] = TF(doublewords[i]);
        rowcou[i] = wordFrequency(doublewords[i]);
//        tfdoubleword[i] = TF(doublewords[i]);
    }

    idf = IDF2(totaldoublewords,doublewords, numberOfDocuments);
    //idfdoubleword = IDF2(totaldoublewords, doublewords, numberOfDocuments);
    //rowfreq = wordFrequency(withoutstopwords);
    for(int i=0; i<numberOfDocuments; i++)
    {
        score[i] = getscore(tf[i], idf, numberOfDocuments);
    }


    double* scores = new double[numberOfDocuments];
    scores = getScoreforFile(score,numberOfDocuments);
    pritn(tf, rowcou, idf, score, scores, numberOfDocuments);
    //pritn(tfdoubleword, rowcou, idf, score, scores, numberOfDocuments);
    //cout << "total words is: idf " << idf.size() << endl;
    //cout << "total words is: score " << score.size() << endl;
    //cout << "total words in: rowfreq " << rowfreq.size() << endl;

    cosinFile.open("Cosine.csv");
    map<string, double> wordVectorofDocuments[numberOfDocuments];
    double cosinevalues[numberOfDocuments][numberOfDocuments];
    for(int i=0; i<numberOfDocuments; i++)
    {
    	wordVectorofDocuments[i] = wordVectorofDocument(tf[i], score[i]);
    	for(map<string, double>:: iterator it = wordVectorofDocuments[i].begin(); it != wordVectorofDocuments[i].end(); it++)
        {
            //cout << it->first << "  " << it->second << endl;
        }
    }
    //cout << "the cosine values are "<< endl;
    cosinFile << " " ;
    for(int i=0; i<numberOfDocuments; i++)
    {
        cosinFile << "," <<  "File" << i+1;
    }
    cosinFile << endl;
    for(int i=0; i<numberOfDocuments; i++)
    {
        cosinFile << "file" << i+1 << ",";
    	for(int j=0; j<numberOfDocuments; j++)
    	{
    		cosinevalues[i][j] = getCosineValue(wordVectorofDocuments[i], wordVectorofDocuments[j]);
    		//cout << cosinevalues[i][j] << " ";
    		cosinFile << cosinevalues[i][j] << ",";
    		if(i!=j && cosinevalues[i][j]>0.80)
                cout << "File" << i+1 << " is similar to " << "File" << j+1 << endl;

    	}
    	cout << endl;
    	cosinFile << endl;
    }
    fresh.clear();
    uniqueword.clear();
    files.clear();
    for(int i=0; i<numberofDocument; i++)
    {
        words[i].clear();
        tf[i].clear();
       // tfdoubleword[i].clear();
        rowcou[i].clear();
        withoutforeach[i].clear();
        //doublewords[i].clear();
        score[i].clear();


    }
    totalwords.clear();
    withoutstopwords.clear();
    idf.clear();
    //idfdoubleword.clear();
    //score.clear();
    //scoredoubleword.clear();
    rowfreq.clear();
}


int main(void)
{
    //vector<string> files;
    string dirname = "../SE305 SPL-I/FileArchive";
    //cin >> dirname;
    findSingleWordSimilarity(dirname);
    //findPairWordSimilarity(dirname);

}
