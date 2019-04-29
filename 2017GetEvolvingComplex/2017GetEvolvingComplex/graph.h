#include "stdafx.h"
#include "graphhead.h"

class Graph          //用邻接列表表示的图结构
{
public:
	std::vector<Node*>	m_NodeArray;             //节点数组
	int					m_nNumEdges;
	std::vector<Clique*> m_CliqueArray;
public:
	Graph() {
	}
	Graph(const char* scFileName, const bool weight) {//载入初始的图信息
		GraphLoader	rawGraph(scFileName, weight);
		sort(rawGraph.m_RawGraph.begin(), rawGraph.m_RawGraph.end());
		std::vector<GraphArc>::iterator enditer = unique(rawGraph.m_RawGraph.begin(), rawGraph.m_RawGraph.end());
		rawGraph.m_RawGraph.erase(enditer, rawGraph.m_RawGraph.end());

		for (size_t i = 0;i < rawGraph.m_nArcs();i++)	//从rawGraph中读取边的信息
		{
			size_t j, k;
			bool bFoundFrom = false;
			bool bFoundTo = false;

			//刚开始时节点节点数组是为空的，是根据原始图信息来逐渐添加节点的。
			for (j = 0;j < m_NodeArray.size();j++)	 //查看边的起始节点是否存在，j保存了改边起始点的位置
			{
				if (m_NodeArray[j]->m_szName == rawGraph.m_RawGraph[i].m_szFrom)
				{
					bFoundFrom = true;
					break;
				}

			}
			for (k = 0;k < m_NodeArray.size();k++)					    //查看边的终止节点是否存在, k保存了改边起始点的位置
			{
				if (m_NodeArray[k]->m_szName == rawGraph.m_RawGraph[i].m_szTo)
				{
					bFoundTo = true;
					break;
				}
			}
			if (bFoundFrom == false)									//如果不存在，则创建一个新的节点
			{
				Node* pNode = new Node(m_NodeArray.size(), rawGraph.m_RawGraph[i].m_szFrom);
				m_NodeArray.push_back(pNode);
				j = m_NodeArray.size() - 1;												 //j保存了改边起始点的位置
			}
			if (bFoundTo == false)											//如果不存在，则创建一个新的节点
			{
				Node* pNode = new Node(m_NodeArray.size(), rawGraph.m_RawGraph[i].m_szTo);
				m_NodeArray.push_back(pNode);
				k = m_NodeArray.size() - 1;												 //k保存了改边终止点的位置
			}

			m_NodeArray[j]->InsertArc(k, rawGraph.m_RawGraph[i].m_fWeight); //在链表中添加一条边
			m_NodeArray[j]->m_iDegree++;
			m_NodeArray[k]->InsertArc(j, rawGraph.m_RawGraph[i].m_fWeight);   //在链表中添加一条边
			m_NodeArray[k]->m_iDegree++;

		}
		m_nNumEdges = rawGraph.m_nArcs();//关系的个数等价于边的个数。
	}
	void ClearNodes()
	{
		for (size_t i = 0;i < m_NodeArray.size();++i)
		{
			if (m_NodeArray[i] != 0)
				delete m_NodeArray[i];
			m_NodeArray[i] = 0;
		}
		m_NodeArray.clear();
	}
	void ClearClique()
	{
		for (size_t i = 0;i < m_CliqueArray.size();++i)
		{
			if (m_CliqueArray[i] != 0)
				delete m_CliqueArray[i];
			m_CliqueArray[i] = 0;
		}
		m_CliqueArray.clear();
	}
	~Graph()
	{
		ClearNodes();
		ClearClique();
	}
	
	void getEvolvingComplex(double para);
	bool IsIncludedInClique(int inode, Clique *clique);
	double getWeightOfNode2Clique(const Node* node, Clique *clique);
	void FilterClique(double  tvOverlap);
	void outPutIntervalComplex(const string tofile, const string tofile_additionalProtein);
//	void getEdgeECC(double alpha);
	void mapComplexToPPI(const string file);  //将file中的complex载入m_CliqueArray

	double getCliDensity(Clique* c) {
		double e, n, d;
		n = c->m_CliqueNodes.size();
		for (size_t nodeid = 0;nodeid < n; nodeid++) {
			Arc* pArc = m_NodeArray[c->m_CliqueNodes[nodeid]]->m_pFirst;
			while (pArc != NULL)
			{
				if (IsIncludedInClique(pArc->m_iNodeTo, c))
				{
					e++;
				}
				pArc = pArc->m_pNextArc;
			}
		}
		e /= 2;
		d = e / (n*(n - 1) / 2);
		return d;
	}
};

class CompCliqueSizeDecend_CliqueNodes
{
public:
	bool operator ()(const Clique *stItem1, const Clique *stItem2) {
		return stItem1->m_CliqueNodes.size() > stItem2->m_CliqueNodes.size();
	}
};