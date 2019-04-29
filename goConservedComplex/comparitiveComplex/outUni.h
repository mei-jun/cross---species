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

class MapGeneSymbl2Uniprotkb {
public:
	multimap<string, string> m_map;
	MapGeneSymbl2Uniprotkb(const char* file) {
		ifstream ifs(file);
		if (!ifs)
		{
			cout << file << " not exist!" << endl;
			return;
		}
		string uniprotkb, genesymbl;
		while (!ifs.eof())	{				
			ifs >> uniprotkb >> genesymbl;
			m_map.insert(pair<string,string>(genesymbl, uniprotkb));
		}
		ifs.close();
	}
	~MapGeneSymbl2Uniprotkb() {
		m_map.clear();
	}
};


class ConservedComplex {
public:
	string id;
	vector<NodeEnsg*> nodes;	
	set<string> homeGeneMergeSet;//所有节点的同源基因集合

	ConservedComplex(string i){
		id = i;		
	}
	~ConservedComplex() {
		for (size_t i = 0;i < nodes.size();i++)
			delete nodes[i];
		nodes.clear();
		homeGeneMergeSet.clear();	
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
		for (size_t i = 0;i < ComplexList.size();i++) {
			for (size_t j = 0;j < ComplexList[i]->nodes.size();j++) {
				NodeEnsg *node = ComplexList[i]->nodes[j];		
				multimap<string, string>::iterator begin = mmap.lower_bound(node->name);
				multimap<string, string>::iterator end = mmap.upper_bound(node->name);		
				while (begin != end) {
					node->homogeneSet.insert(begin->second);
					ComplexList[i]->homeGeneMergeSet.insert(begin->second);
					begin++;
				}		
			}		
		}
	}
	~ConservedComplexList() { 
		for (size_t i = 0;i < ComplexList.size();i++)
			delete ComplexList[i];
		ComplexList.clear(); 
	}
};


class IDs {
public:
	set<string> m_IDs;
	IDs(const char* file) {
		ifstream f(file);
		if (!f)
		{
			cout << file << " does not exist!" << endl;
			return;
		}
		string id;
		while (!f.eof()) {
			f >> id;
			m_IDs.insert(id);
		}
		f.close();
	}
};

void outConservedUni(ConservedComplexList &conservedComplexList, MapGeneSymbl2Uniprotkb &map_Gsyb2unipro, const IDs &idset, const char* file) {
	ofstream ofile(file);
	if (!ofile)
	{
		cout << file << "not exist." << endl;
		return;
	}
	for (size_t i = 0;i < conservedComplexList.ComplexList.size();i++) {
		ConservedComplex *cc = conservedComplexList.ComplexList[i];
		if (idset.m_IDs.find(cc->id) == idset.m_IDs.end())
			continue;
		ofile << cc->id << "\t";
		multimap<string, string>::iterator lowb, upb;
		set<string>::iterator it = cc->homeGeneMergeSet.begin();
		while (it != cc->homeGeneMergeSet.end())
		{
			lowb = map_Gsyb2unipro.m_map.lower_bound(*it);
			upb = map_Gsyb2unipro.m_map.upper_bound(*it);
			it++;
			while (lowb != upb) {
				ofile << lowb->second << "\t";
				lowb++;
			}
		}
		ofile << endl;
	}
	
}