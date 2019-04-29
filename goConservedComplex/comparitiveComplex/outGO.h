
#include "stdafx.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include"outUni.h"
const int Num_conservedComplex = 81;

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
	GOterm() {}
	GOterm(string term, string des) {
		m_term = term;
		m_description = des;
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
		else return false;
	}
};

class NodeArray4GO {
public:
	vector<Node> m_NodeArray;

	NodeArray4GO(const char* file2) {
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
	~NodeArray4GO() {
		//	for (int i = 0; i < m_NodeArray.size(); i++) {
		//		delete m_NodeArray[i];
		//	}
	}
};



class Clique {
public:
	string id;
	set<Node> m_CliqueNodes;

	Clique(string i) {
		id = i;
	}
	bool operator<(const Clique &c)const {
		if (id < c.id)
			return true;
		else
			return false;
	}
};

class CliqueArray {
public:
	vector<Clique> m_CliqueArray;
	CliqueArray() {};
	CliqueArray(const char* file, const IDs &idset) {
		//read additional protein file
		ifstream f(file);
		if (!f)
		{
			cout << file << " does not exist!" << endl;
			return;
		}
		stringstream istr;
		string line;
		string id;
		string protein;
		while (!f.eof()) {
			getline(f, line, '\n');
			istr.clear();
			istr.str(line);
			if (!istr.eof()) {
				istr >> id;
				if (idset.m_IDs.find(id) == idset.m_IDs.end())
					continue;
				string useless;
				//				istr >> useless;istr >> useless;istr >> useless;istr >> useless;istr >> useless;
				Clique *clique = new Clique(id);
				while (!istr.eof())
				{
					istr >> protein;
					Node *node = new Node(protein);
					clique->m_CliqueNodes.insert(*node);
				}
				m_CliqueArray.push_back(*clique);
			}
		}
		f.close();
		sort(m_CliqueArray.begin(), m_CliqueArray.end());
	}

	~CliqueArray() {
		//		for (int i = 0; i < Num_conservedComplex; i++) {
		//			delete m_CliqueArray[i];
		//		}
	}
};

void outputAspecies(const CliqueArray &addArray, const NodeArray4GO &NodeArrOfGO, ofstream &of, int k, string species) {
	of << addArray.m_CliqueArray[k].id << "[" << species << "]\t";
	if (addArray.m_CliqueArray[k].m_CliqueNodes.size() == 0)
		of << "\n";
	else {
		multiset<string> TermVec;
		set<Node>::iterator it = addArray.m_CliqueArray[k].m_CliqueNodes.begin();
		while (it != addArray.m_CliqueArray[k].m_CliqueNodes.end()) {
			const Node *node = &(*it);
			const vector<Node>::const_iterator begin = NodeArrOfGO.m_NodeArray.begin();
			const vector<Node>::const_iterator end = NodeArrOfGO.m_NodeArray.end();
			vector<Node>::const_iterator iter;
			for (iter = begin; iter < end; iter++) {
				if ((*iter) == *node) {
					for (size_t n = 0; n < (*iter).m_gotermArray.size(); n++)
						TermVec.insert((*iter).m_gotermArray[n].m_term);
					break;
				}
			}
			it++;
		}
		multiset<string>::const_iterator iter = TermVec.begin();
		while (iter != TermVec.end()) {
			of << (*iter) << "{" << TermVec.count(*iter) << "}|";
			iter = TermVec.upper_bound(*iter);
		}
		of << "\n";
	}
}


void out3speciesAdditionGO(const char *file3, \
	const CliqueArray &addArray_DM, const NodeArray4GO &NodeArrOfGO_DM, \
	const CliqueArray &addArray_HS, const NodeArray4GO &NodeArrOfGO_HS, \
	const CliqueArray &addArray_MM, const NodeArray4GO &NodeArrOfGO_MM) {

	ofstream of(file3);
	of << "complexID\t" << "DM_GOterms\t" << "HS_GOterms\t" << "MM_GOterms\t" << endl;
	for (int k = 0; k < Num_conservedComplex; k++) {
		outputAspecies(addArray_DM, NodeArrOfGO_DM, of, k, "DM");
		outputAspecies(addArray_HS, NodeArrOfGO_HS, of, k, "HS");
		outputAspecies(addArray_MM, NodeArrOfGO_MM, of, k, "MM");
		of << endl;
	}
	of.close();
}










#pragma once
