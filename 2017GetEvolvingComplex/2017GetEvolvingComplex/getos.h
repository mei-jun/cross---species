#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include<algorithm>
using namespace std;

class osClique
{
public:
	vector<string>			m_osCliqueNodes;
	int					m_iosCliqueNo;
	double os;
	int nodeNum;
	bool mark;
public:
	osClique()
	{
		m_iosCliqueNo = -1;
		mark = true;
		os = 0;
		nodeNum = 0;

	}
	osClique(int iosCliqueNo)
	{
		m_iosCliqueNo = iosCliqueNo;
		mark = true;
		os = 0;
		nodeNum = 0;

	}
	osClique& operator=(osClique &c) {
		m_osCliqueNodes = c.m_osCliqueNodes;
		m_iosCliqueNo = c.m_iosCliqueNo;
		os = c.os;
		nodeNum = c.nodeNum;
		mark = c.mark;
		return *this;
	}
};



class ComplexSet {

public:
	vector<osClique> osCliqueVex;
	int osCliqueNum;
public:
	ComplexSet() {
		osCliqueNum = 0;
	}
};



void readComplexfile(ComplexSet &complexset, const char* file) {
	std::ifstream inFile;
	inFile.open(file);
	if (!inFile) {
		cout << "can not open the file " << file << endl;
		return;
	}
	int splitString(string &strSrc, const string &strDelims, vector<string>& strDest);
	const string strDelims = "\t, \n";
	vector<string> splitStrs;
	vector<string>::iterator iter;
	string str;
	int cliqueId = 0;
	while (!inFile.eof()) {
		getline(inFile, str, '\n');
		osClique pClique;
		splitStrs.clear();
		splitString(str, strDelims, splitStrs);
		for (iter = splitStrs.begin(); iter != splitStrs.end(); ++iter) {
			pClique.m_osCliqueNodes.push_back(*iter);
		}
		complexset.osCliqueVex.push_back(pClique);
	}
	if (inFile)
		inFile.close();
	complexset.osCliqueNum=complexset.osCliqueVex.size();
}

double OS(osClique pc, osClique kc) {
	//与已知复合物比较 匹配程度
	std::vector<string>::iterator iterk;
	std::vector<string>::iterator iterp;
	double num = 0;
	double os = 0;
	for (iterk = kc.m_osCliqueNodes.begin();iterk != kc.m_osCliqueNodes.end();iterk++) {
		for (iterp = pc.m_osCliqueNodes.begin();iterp != pc.m_osCliqueNodes.end();iterp++)
		{
			if ((*iterp) == (*iterk))
				num++;
		}
	}
	os = (double)(num*num) / ((double)pc.m_osCliqueNodes.size()*(double)kc.m_osCliqueNodes.size());
	return os;
}
int getPredictComplexOS(ComplexSet &complexPredit, ComplexSet &complexKC, const char* identify, const char* PCinformationFile, const char* osFile) {
	//PC与KC匹配
	double os;
	for (int i = 0;i<complexPredit.osCliqueVex.size();i++) {
		complexPredit.osCliqueVex[i].os = 0;
	}

	double TP = 0, numPC = 0;
	numPC = complexPredit.osCliqueNum;
	double avesize = 0;
	int maxsize = 0;
	for (int i = 0;i<complexPredit.osCliqueVex.size();i++) {
		//对于标准复合物测试集中的每个复合物：求得它与预测的蛋白质复合物的最大的匹配值OS
		os = 0;
		for (int j = 0;j<complexKC.osCliqueVex.size();j++) {
			os = OS(complexPredit.osCliqueVex[i], complexKC.osCliqueVex[j]);
			if (os>complexPredit.osCliqueVex[i].os)
			{
				complexPredit.osCliqueVex[i].os = os;
			}
		}

		if (complexPredit.osCliqueVex[i].m_osCliqueNodes.size()>maxsize)
			maxsize = complexPredit.osCliqueVex[i].m_osCliqueNodes.size();
		avesize += complexPredit.osCliqueVex[i].m_osCliqueNodes.size();
		if (complexPredit.osCliqueVex[i].os >= 0.2) {
			TP++;
		}
	}
	return TP;
}
int getKnownComplexOS(ComplexSet &ComplexKC, ComplexSet &ComplexPC, const char* identify, const char* KCinformationFile, const char* osFile) {
	//KC被PC识别
	double os;
	for (int i = 0;i<ComplexKC.osCliqueVex.size();i++) {
		ComplexKC.osCliqueVex[i].os = 0;
	}

	double numMatchedKC = 0;
	int a_1 = 0, a_2 = 0, a_3 = 0, a_4 = 0, a_5 = 0, a_6 = 0, a_7 = 0, a_8 = 0, a_9 = 0, a_10 = 0;
	for (int i = 0;i<ComplexKC.osCliqueVex.size();i++) {
		//对于标准复合物测试集中的每个复合物：求得它与预测的蛋白质复合物的最大的匹配值OS
		os = 0;
		for (int j = 0;j<ComplexPC.osCliqueVex.size();j++) {
			os = OS(ComplexKC.osCliqueVex[i], ComplexPC.osCliqueVex[j]);
			if (os>ComplexKC.osCliqueVex[i].os)
				ComplexKC.osCliqueVex[i].os = os;
		}

		if (ComplexKC.osCliqueVex[i].os == 1.0) {
			a_10++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.9) {
			a_9++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.8) {
			a_8++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.7) {
			a_7++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.6) {
			a_6++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.5) {
			a_5++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.4) {
			a_4++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.3) {
			a_3++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.2) {
			a_2++;
		}

		if (ComplexKC.osCliqueVex[i].os >= 0.1) {
			a_1++;
		}
	}
	numMatchedKC = a_2;
	return numMatchedKC;
}
int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)
{	//分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest
	typedef string::size_type ST;
	string delims = strDelims;
	std::string STR;
	if (delims.empty())
		delims = "|";
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


