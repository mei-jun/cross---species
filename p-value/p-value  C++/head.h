
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>


using namespace::std;

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

class GOterm {
public:
	string m_term;
	string m_description;
	double m_back_f;
	int m_x;

	GOterm() {}
	GOterm(string term) {
		m_term = term;
	}
	GOterm(string term, string des) {
		m_term = term;
		m_description = des;
	}
	bool operator==(const GOterm &other) const {
		return m_term == other.m_term;
	}
};

class Node {
public:
	string m_name;
	vector<GOterm> m_gotermArray;
	Node() {
	}
	Node(string n) {
		m_name = n;
	}
	bool operator==(const Node& other)const {
		if (m_name == other.m_name)
			return true;
		else return false;
	}
	bool operator<(const Node& other)const {
		if (m_name < other.m_name)
			return true;
		else
			return false;
	}
	bool findGo(string go) {
		for (size_t i = 0;i < m_gotermArray.size();i++)
		{
			if (m_gotermArray[i].m_term == go)
				return true;
		}
		return false;
	}
};

class BackgroundNodeGOlist {
public:
	vector<Node> m_NodeArray;

	BackgroundNodeGOlist(const char* file2) {
		//read GOterm file
		ifstream f(file2);
		if (!f)
		{
			cout << file2 << " does not exist!" << endl;
			return;
		}
		vector<string> vecline;
		string term, descrip;
		string currentname = "";
		Node currentNode;
		string line;
		while (!f.eof()) {
			getline(f, line, '\n');
			vecline.clear();
			size_t linesize = splitString(line, "\t", vecline);
			if (linesize == 3) {
				if (currentname != vecline[0]) {
					currentname = vecline[0];
					m_NodeArray.push_back(currentNode);
					currentNode = *(new Node(vecline[0]));
					GOterm *term = new GOterm(vecline[1], vecline[2]);
					currentNode.m_gotermArray.push_back(*term);
				}
				else {
					GOterm *term = new GOterm(vecline[1], vecline[2]);
					currentNode.m_gotermArray.push_back(*term);
				}

			}
		}
		f.close();
		m_NodeArray.erase(m_NodeArray.begin());
	}
	~BackgroundNodeGOlist() {
		//	for (int i = 0; i < m_NodeArray.size(); i++) {
		//		delete m_NodeArray[i];
		//	}
	}
};

class AnalizedClique {
public:
	vector<string> m_ProteinArray;
	AnalizedClique(const char *file) {
		ifstream f(file);
		if (!f)
		{
			cout << file << " does not exist!" << endl;
			return;
		}
		string line;
		while (!f.eof()) {
			getline(f, line, '\n');
			m_ProteinArray.push_back(line);		
		}
		f.close();
	}
};

class wantedTerms {
	//要求的对每个term的富集度
public:
	vector<GOterm> m_Terms;
	wantedTerms(set<string> &uniset) {
		set<string>::iterator it = uniset.begin();
		while (it != uniset.end()) {
		//	if (*it != "dna binding")
		//		continue;
			GOterm *term = new GOterm(*it);
			m_Terms.push_back(*term);
			it++;
		}
		
	}
};

class GOTermlist {
public:
	vector<GOterm> m_GOTermArray;

	GOTermlist(const BackgroundNodeGOlist &nodeArray, set<string> &uniset) {
		multiset<string> mset;
		
		vector<Node>::const_iterator it = nodeArray.m_NodeArray.begin();
		while (it != nodeArray.m_NodeArray.end()) {
			vector<GOterm>::const_iterator itgo = it->m_gotermArray.begin();
			while (itgo != it->m_gotermArray.end()) {
				string term = itgo->m_term;
				mset.insert(term);
				uniset.insert(term);
				itgo++;
			}
			it++;
		}
		
		multiset<string>::iterator sit = mset.begin(),upb;
		while (sit != mset.end()) {
			upb = mset.upper_bound(*sit);
			GOterm *term = new GOterm(*sit);
			term->m_back_f = (double)mset.count(*sit) / uniset.size();
			m_GOTermArray.push_back(*term);
			sit = upb;		
		}
	}
};