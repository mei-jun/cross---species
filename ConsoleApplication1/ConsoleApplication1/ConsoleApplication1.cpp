// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<set>
#include<map>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace::std;

class termFrequency {
public:
	string term;
	string f_species;
	string f_background;
	string f_third;
	bool mark;
	termFrequency() {
		f_species = "0";
		f_background = "0";
		f_third = "0";
		mark = false;
	}
	bool operator==(const termFrequency& other) const{
		if (term == other.term)
			return true;
		else
			return false;	
	}
};

int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)
{	/*分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest*/
	typedef string::size_type ST;
	string delims = strDelims;
	std::string STR;
	if (delims.empty())
		delims = "\t";
	ST pos = 0, LEN = strSrc.size();
	while (pos < LEN) {
		STR = "";
		while ((pos < LEN) && (delims.find(strSrc[pos]) != std::string::npos))
			++pos;
		if (pos == LEN)
			return strDest.size();
		while ((pos < LEN) && (delims.find(strSrc[pos]) == std::string::npos))
			STR += strSrc[pos++];
		if (!STR.empty())
			strDest.push_back(STR);
	}
	return strDest.size();
}

void readfile(const char* file1,const char* file2,const char* tofile) {
	//file1: species
	//file2: background
	//2个的比较
	vector<termFrequency> termfreq1;
	vector<termFrequency> termfreq2;
	vector<termFrequency> termfreq;
	ifstream ifs1(file1);
	if (!ifs1)
	{
		cout << file1 << " not exist!" << endl;
		return;
	}	
	string term;
	vector<string> vecline;
	string f;
	string line;
	while (!ifs1.eof()) {
		getline(ifs1,line,'\n');
		vecline.clear();
		size_t linesize = splitString(line, "\t", vecline);
		if (linesize ==2) {
			term = vecline[0];
			f = vecline[1];
		}		
		termFrequency t = *new termFrequency();
		t.term = term;t.f_species = f;
		termfreq1.push_back(t);
	}
	ifs1.close();

	ifstream ifs2(file2);
	if (!ifs2)
	{
		cout << file2 << " not exist!" << endl;
		return;
	}
	while (!ifs2.eof()) {
		getline(ifs2, line, '\n');
		vecline.clear();
		size_t linesize = splitString(line, "\t", vecline);
		if (linesize == 2) {
			term = vecline[0];
			f = vecline[1];
		}
		termFrequency t = *new termFrequency();
		t.term = term;t.f_background = f;
		termfreq2.push_back(t);
	}
	ifs2.close();

	vector<termFrequency>::iterator it = termfreq2.begin();
	for (size_t i = 0;i < termfreq1.size();i++) {
		it = find(termfreq2.begin(), termfreq2.end(), termfreq1[i]);
		if (it!= termfreq2.end()) {
			termfreq1[i].f_background = it->f_background;
			termfreq.push_back(termfreq1[i]);
			it->mark = true;//找到了重复的
		}
		else
			termfreq.push_back(termfreq1[i]);
	}	
	for (size_t i = 0;i < termfreq2.size();i++) {
		if (termfreq2[i].mark == true)
			continue;
		termfreq.push_back(termfreq2[i]);
	}

	//OUTPUT
	ofstream ifs3(tofile);
	if (!ifs3)
	{
		cout << tofile << " not exist!" << endl;
		return;
	}
	for (size_t i = 0;i < termfreq.size();i++) {
		ifs3 << termfreq[i].term << "\t" << termfreq[i].f_species << "\t" << termfreq[i].f_background << endl;
		
	}

	ifs3.close();
	
}


double stringToNum(const string& str)
{
	istringstream iss(str);
	double num;
	iss >> num;
	return num;
}

void readfile2(const char* file1, const char* file2,const char* file3,const char* file4, const char* tofile) {
	//file1: species
	//file2: background
	//3个的比较
	vector<termFrequency> termfreq1;
	vector<termFrequency> termfreq2;
	vector<termFrequency> termfreq3;
	vector<termFrequency> termfreq;
	string term;
	vector<string> vecline;
	string f;
	string line;

	ifstream ifs1(file1);
	if (!ifs1)
	{
		cout << file1 << " not exist!" << endl;
		return;
	}	
	while (!ifs1.eof()) {
		getline(ifs1, line, '\n');
		vecline.clear();
		size_t linesize = splitString(line, "\t", vecline);
		if (linesize == 2) {
			term = vecline[0];
			f = vecline[1];
		}
		termFrequency t = *new termFrequency();
		t.term = term;t.f_species = f;
		termfreq1.push_back(t);
	}
	ifs1.close();

	ifstream ifs2(file2);
	if (!ifs2)
	{
		cout << file2 << " not exist!" << endl;
		return;
	}
	while (!ifs2.eof()) {
		getline(ifs2, line, '\n');
		vecline.clear();
		size_t linesize = splitString(line, "\t", vecline);
		if (linesize == 2) {
			term = vecline[0];
			f = vecline[1];
		}
		termFrequency t = *new termFrequency();
		t.term = term;t.f_background = f;
		termfreq2.push_back(t);
	}
	ifs2.close();

	ifstream ifs3(file3);
	if (!ifs3)
	{
		cout << file3 << " not exist!" << endl;
		return;
	}
	while (!ifs3.eof()) {
		getline(ifs3, line, '\n');
		vecline.clear();
		size_t linesize = splitString(line, "\t", vecline);
		if (linesize == 2) {
			term = vecline[0];
			f = vecline[1];
		}
		termFrequency t = *new termFrequency();
		t.term = term;t.f_third = f;
		termfreq3.push_back(t);
	}
	ifs3.close();



	vector<termFrequency>::iterator it2 = termfreq2.begin(),it3=termfreq3.begin();
	for (size_t i = 0;i < termfreq1.size();i++) {
		it2 = find(termfreq2.begin(), termfreq2.end(), termfreq1[i]);
		it3 = find(termfreq3.begin(), termfreq3.end(), termfreq1[i]);

		if (it2 != termfreq2.end()&&it3 != termfreq3.end()) {
			//第二个、第三个中都找到了重复的
			termfreq1[i].f_background = it2->f_background;
			termfreq1[i].f_third = it3->f_third;
			termfreq.push_back(termfreq1[i]);
			it2->mark = true;//
			it3->mark = true;//
		}
		else if (it2 != termfreq2.end() && it3 == termfreq3.end()) {
			//只在第二个找到，第三个没找到
			termfreq1[i].f_background = it2->f_background;
			termfreq.push_back(termfreq1[i]);
			it2->mark = true;//
		}
		else if (it2 == termfreq2.end() && it3 != termfreq3.end()) {
			//只在第三个找到，第二个没找到
			termfreq1[i].f_third = it3->f_third;
			termfreq.push_back(termfreq1[i]);
			it3->mark = true;//
		}
		else
		{
			//都没找到
			termfreq.push_back(termfreq1[i]);
		}
	}

	//第二个没有找到的部分
	for (size_t i = 0;i < termfreq2.size();i++) {
		if (termfreq2[i].mark == true)
			continue;
		it3 = find(termfreq3.begin(), termfreq3.end(), termfreq2[i]);
		if (it3 != termfreq3.end()) {
			//找到了
			termfreq2[i].f_third = it3->f_third;
			termfreq.push_back(termfreq2[i]);
			it3->mark = true;
		}
		else
			termfreq.push_back(termfreq2[i]);
	}

	//第三个没有找到的部分
	for (size_t i = 0;i < termfreq3.size();i++) {
		if (termfreq3[i].mark == true)
			continue;
		termfreq.push_back(termfreq3[i]);
	}


	//conserved
	vector<termFrequency> termfreqConserved;
	ifstream ifs4(file4);
	if (!ifs4)
	{
		cout << file4 << " not exist!" << endl;
		return;
	}
	while (!ifs4.eof()) {
		getline(ifs4, line, '\n');
		vecline.clear();
		size_t linesize = splitString(line, "\t", vecline);
		if (linesize == 2) {
			term = vecline[0];
			f = vecline[1];
		}
		termFrequency t = *new termFrequency();
		t.term = term;t.f_third = f;
		termfreqConserved.push_back(t);
	}
	ifs4.close();


	//OUTPUT
	ofstream outf(tofile);
	if (!outf)
	{
		cout << tofile << " not exist!" << endl;
		return;
	}
	outf << "GOterms\tDM比例差值\tHS比例差值\tMM比例差值" << endl;
	vector<termFrequency>::iterator itcon = termfreqConserved.begin();
	for (size_t i = 0;i < termfreq.size();i++) {
		itcon = find(termfreqConserved.begin(), termfreqConserved.end(),termfreq[i]);
		if (itcon != termfreqConserved.end()) {
			outf << termfreq[i].term << "\t" << stringToNum( termfreq[i].f_species )- stringToNum(itcon->f_third) << "\t" <<\
				stringToNum(termfreq[i].f_background)- stringToNum(itcon->f_third) << "\t" << stringToNum(termfreq[i].f_third)- stringToNum(itcon->f_third) << endl;
		}
		else 
			outf << termfreq[i].term << "\t" << termfreq[i].f_species << "\t" << termfreq[i].f_background <<"\t"<<termfreq[i].f_third<< endl;

	}

	outf.close();

}





int main()
{
	
	readfile2( "background_DM.txt","background_HS.txt","background_MM.txt","rate_conserved.txt","termFreq_DM_3物种差值.txt");


    return 0;
}

