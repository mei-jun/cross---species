#include "stdafx.h"
#pragma once

/*
�������ݽṹ����
*/
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include<sstream>
#include<algorithm>
using namespace std;

class Arc		    //�߽ṹ
{
public:
	int m_iNodeTo; //��ָ��Ľڵ���
	double m_fWeight;//�ߵ�Ȩ��
	Arc* m_pNextArc;//�ߵ�ָ��
public:
	Arc()
	{
		m_iNodeTo = 0;
		m_fWeight = 1;
		m_pNextArc = NULL;
	}
	Arc(int iNodeTo, double fWeight, Arc* pNextArc)
	{
		m_iNodeTo = iNodeTo;
		m_fWeight = fWeight;
		m_pNextArc = pNextArc;
	}
	~Arc()
	{
		if (m_pNextArc)
			delete m_pNextArc;
	}
};

class Node           //����ṹ
{
public:
	int		m_iNode;//�ڵ���
	string	m_szName;//�ڵ�����
	int		m_iDegree;//�ڵ��
	Arc*	m_pFirst;//��ڵ������ĵ�һ����
	bool	m_bMarked;//�ڵ��־
	int		m_iClique;//��ǰ����Clique

public:
	Node() {
		m_iNode = 0;
		m_szName="";
		m_iDegree = 0;
		m_pFirst = 0;
		m_bMarked = false;
		m_iClique = -1;
	}
	Node(string szName) {
		m_szName = szName;
	}
	Node(int iNode, string szName)
	{
		m_szName = szName;
		m_iNode = iNode;
		m_iDegree = 0;
		m_pFirst = 0;
		m_bMarked = false;
		m_iClique = -1;
	}
	~Node() {
		if (m_pFirst)
			delete m_pFirst;
	}
	void InsertArc(int iTo, double fWeight)
	{
		Arc* newArc = new Arc(iTo, fWeight, m_pFirst);
		m_pFirst = newArc;
	}
	bool operator == (const Node &node) const {
		if (m_szName == node.m_szName)
			return true;
		else
			return false;
	}
};

class Clique		//�Žṹ
{
public:
	int					m_iCliqueNo;//���ŵı��
	std::vector<int>	m_CliqueNodes;//�����ڵĽڵ�����
	bool mark;

public:
	Clique(int iCliqueNo)
	{
		m_iCliqueNo = iCliqueNo;
	}
	size_t m_size() {
		return m_CliqueNodes.size();
	}

};

class GraphArc {
public:
	string m_szFrom;
	string m_szTo;
	double m_fWeight;
public:
	GraphArc()
	{
		m_fWeight = 1.0f;
	}
	GraphArc(string szFrom, string szTo, double fWeight)
	{
		m_szFrom = szFrom;
		m_szTo = szTo;
		m_fWeight = fWeight;
	}
	bool operator<(const GraphArc &arc) const {
		if (m_szFrom < arc.m_szFrom)
			return true;
		else if (m_szFrom == arc.m_szFrom) {
			if (m_szTo < arc.m_szTo)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	bool operator==(const GraphArc &arc) const {
		if (m_szFrom == arc.m_szFrom&&m_szTo == arc.m_szTo)
			return true;
		else
			return false;
	}
};

class GraphLoader
{
public:
	std::vector<GraphArc>	m_RawGraph;
public:
	GraphLoader() {}
	GraphLoader(const char* szFileName, const bool &weight)
	{
		m_RawGraph.clear();
		GraphArc arc, temparc;
		if (szFileName != "") {
			//���ļ���ȡͼ	
			std::ifstream InFile(szFileName);
			if (!InFile)
			{
				std::cout << "Can't Open The Input File!" << std::endl;
				return;
			}
			for (;;)
			{
				if (!InFile)
					break;
				if (weight)
					InFile >> arc.m_szFrom >> arc.m_szTo >> arc.m_fWeight;
				else
					InFile >> arc.m_szFrom >> arc.m_szTo;
				if (arc.m_szFrom != arc.m_szTo) {
					if (arc.m_szFrom > arc.m_szTo)
					{
						temparc.m_szFrom = arc.m_szTo;
						temparc.m_szTo = arc.m_szFrom;
					}
					else {
						temparc.m_szFrom = arc.m_szFrom;
						temparc.m_szTo = arc.m_szTo;
					}
					temparc.m_fWeight = arc.m_fWeight;
					m_RawGraph.push_back(temparc);
				}
			}
			InFile.close();
		}
		else {
			//������������
			do {
				if (weight)
					cin >> arc.m_szFrom >> arc.m_szTo >> arc.m_fWeight;
				else
					cin >> arc.m_szFrom >> arc.m_szTo;
				if (arc.m_szFrom != arc.m_szTo) {
					if (arc.m_szFrom > arc.m_szTo)
					{
						temparc.m_szFrom = arc.m_szTo;
						temparc.m_szTo = arc.m_szFrom;
					}
					else {
						temparc.m_szFrom = arc.m_szFrom;
						temparc.m_szTo = arc.m_szTo;
					}
					temparc.m_fWeight = arc.m_fWeight;
					m_RawGraph.push_back(temparc);
				}
			} while ((arc.m_szFrom != "#") && (arc.m_szTo != "#"));
		}
		m_RawGraph.pop_back();
	}

	size_t m_nArcs() {
		return m_RawGraph.size();
	}
};

