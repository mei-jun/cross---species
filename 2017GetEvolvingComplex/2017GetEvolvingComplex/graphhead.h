#include "stdafx.h"
#pragma once

/*
基本数据结构定义
*/
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include<sstream>
#include<algorithm>
using namespace std;

class Arc		    //边结构
{
public:
	int m_iNodeTo; //边指向的节点编号
	double m_fWeight;//边的权重
	Arc* m_pNextArc;//边的指针
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

class Node           //顶点结构
{
public:
	int		m_iNode;//节点编号
	string	m_szName;//节点名称
	int		m_iDegree;//节点度
	Arc*	m_pFirst;//与节点相连的第一条边
	bool	m_bMarked;//节点标志
	int		m_iClique;//当前所属Clique

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

class Clique		//团结构
{
public:
	int					m_iCliqueNo;//此团的编号
	std::vector<int>	m_CliqueNodes;//此团内的节点向量
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
			//从文件读取图	
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
			//从命令行输入
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

