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

class NodeEnsg {
public:
	string name;
	set<string> homogeneSet;
	NodeEnsg(string n){
		name = n;
	}
	~NodeEnsg() {
		homogeneSet.clear();
	}
};

class MapUniprotkb2GeneSymbl {
public:
	multimap<string, string> m_map;
	MapUniprotkb2GeneSymbl(const char* file) {
		ifstream ifs(file);
		if (!ifs)
		{
			cout << file << " not exist!" << endl;
			return;
		}
		string uniprotkb, genesymbl;
		while (!ifs.eof())	{				
			ifs >> uniprotkb >> genesymbl;
			m_map.insert(pair<string,string>(uniprotkb,genesymbl));
		}
		ifs.close();
	}
	~MapUniprotkb2GeneSymbl() {
		m_map.clear();
	}
};
class SpeciesComplex;

class ConservedComplex {
public:
	string id;
	vector<NodeEnsg*> nodes;
	double spc_os;  //spc_id与本complex的os
	const SpeciesComplex*	spc;//species complex中与本complex最匹配的那个
	set<string> homeGeneMergeSet;//所有节点的同源基因集合
	set<string> extraGenes; //在species complex中增加的基因
	int commonNum;
	ConservedComplex(string i){
		id = i;
		spc_os = 0;
		commonNum = 0;
		spc = 0;
	}
	~ConservedComplex() {
		for (size_t i = 0;i < nodes.size();i++)
			delete nodes[i];
		nodes.clear();
		homeGeneMergeSet.clear();
		extraGenes.clear();
		spc = 0;
	}
};

class ConservedComplexList {
public:
	vector<ConservedComplex*> ComplexList;

	ConservedComplexList(const char* file){
		ifstream ifs(file);
		if (!ifs)
		{
			cout << file << " not exist!" << endl;
			return;
		}
		string line,id,protein;		
		while (!ifs.eof()) {
			getline(ifs, line, '\n');
			stringstream strs(line.c_str());
			strs >> id;
			ConservedComplex *c=new ConservedComplex(id);
			while (!strs.eof()) {
				strs >> protein;
				c->nodes.push_back(new NodeEnsg(protein));
			}
			ComplexList.push_back(c);
		}
		ifs.close();
	}
	void setHomoGenes(const char* homofile) {
		ifstream ifs(homofile);
		if (!ifs)
		{
			cout << homofile << " not exist!" << endl;
			return;
		}
		string ensg, genesymbl;
		multimap<string, string> mmap;
		while (!ifs.eof()) {
			ifs >> ensg >> genesymbl;
			mmap.insert(pair<string,string>(ensg,genesymbl));
		}
		ifs.close();
//		double total = 0,ok = 0;
		for (size_t i = 0;i < ComplexList.size();i++) {
			for (size_t j = 0;j < ComplexList[i]->nodes.size();j++) {
				NodeEnsg *node = ComplexList[i]->nodes[j];
//				total++;
				multimap<string, string>::iterator begin = mmap.lower_bound(node->name);
				multimap<string, string>::iterator end = mmap.upper_bound(node->name);
//				if (begin != end)ok++;
				while (begin != end) {
					node->homogeneSet.insert(begin->second);
					ComplexList[i]->homeGeneMergeSet.insert(begin->second);
					begin++;
				}
//				if (node->homogeneSet.size()>1)
//					cout << node->name << "  " << node->homogeneSet.size() << endl;
			}		
		}
//		cout <<endl<<"ok rate is "<< ok / total<<endl<<endl;
	}
	~ConservedComplexList() { 
		for (size_t i = 0;i < ComplexList.size();i++)
			delete ComplexList[i];
		ComplexList.clear(); 
	}
};


class SpeciesComplex {
public:
	string id;
	vector<string> nodes;
	SpeciesComplex(string i){
		id = i;
	}
	~SpeciesComplex() {
		nodes.clear();
	}
};

class SpeciesComplexList{
public:
	vector<SpeciesComplex*> ComplexList;

	SpeciesComplexList(const char* file) {
		ifstream ifs(file);
		if (!ifs)
		{
			cout << file << " not exist!" << endl;
			return;
		}
		string line, id, protein;
		while (!ifs.eof()) {
			getline(ifs, line, '\n');
			stringstream strs(line.c_str());
			strs >> id;
			SpeciesComplex *c = new SpeciesComplex(id);
			while (!strs.eof()) {
				strs >> protein;
				c->nodes.push_back(protein);
			}
			ComplexList.push_back(c);			
		}
		ifs.close();
	}
	~SpeciesComplexList() {
		for (size_t i = 0; i < ComplexList.size(); i++)
		{
			delete ComplexList[i];
		}
		ComplexList.clear();
	}
};