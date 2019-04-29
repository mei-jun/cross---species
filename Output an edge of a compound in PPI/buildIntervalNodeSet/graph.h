

class Arc
{
public:
	string m_iNodeToName;
	int m_iNodeTo;
	double m_fWeight;
	double m_ecc;
	double m_cac;


	Arc* m_pNextArc;
public:
	Arc()
	{m_ecc=0;
	m_cac=0;
		m_pNextArc = NULL;
	}
	Arc(string iNodeToName,int  iNodeTo, double fWeight, Arc* pNextArc)
	{
		m_iNodeToName=iNodeToName;
		m_iNodeTo = iNodeTo;
		m_fWeight = fWeight;
		m_pNextArc = pNextArc;
	}
};

class Node
{
public:
	string	gName;//�ڵ�����;
	bool	m_bMarked;//�ڵ��־;
	int		m_iNode;//�ڵ���;
	int		m_iDegree;//�ڵ��;
	Arc*	m_pFirst;//��ڵ������ĵ�һ����;
	int		m_iComplex;//��ǰ����Complex;
public:
	Node()
	{	m_iNode=0;
		m_pFirst=0;
		m_iDegree=0;
		gName="";
		
	}
	
	Node(int iNode,string szName)
	{
		gName=szName;
		m_iNode=iNode;
		m_pFirst=0;
		m_iDegree=0;
		m_bMarked=false;
		m_iComplex=0;
	}

	void setNodeName(string s)
	{
		gName=s;
		
	}
	void InsertArc(string iNodeToName,int iNodeTo,double fWeight)
	{
		Arc* newArc=new Arc(iNodeToName,iNodeTo,fWeight,m_pFirst);//����������ͷ���뷨
		m_pFirst=newArc;
	}
};

class Clique//����;
{
public:
	std::vector<Node*>	m_CliqueNodes;//�ŵĽڵ�����;
	bool	mark ;
	string	m_CliqueNodesID;  //�ű��
	int		NumEdges;
	string  cliqueName;
	int		proteinNum;
public:
	Clique(){
		proteinNum=0;
		NumEdges=0;
	}
	Clique(string CliqueNodesID)
	{
		m_CliqueNodesID = CliqueNodesID;
		NumEdges=0;
		proteinNum=0;
		mark = false;
	}

	void setCliqueName(string name)
	{
		cliqueName =name;
	}
};

class NodeMatrix
{
public:
	std::vector<Clique*>  CliqueVec;
	int cliqueNum;
public:
	NodeMatrix()
	{	cliqueNum=0;	
	}
};


class GraphArc
{
public:
	string m_szFrom;//
	string m_szTo;//
	double m_fWeight;//
	bool arcMark;
public:
	GraphArc()
	{
		m_fWeight = 1.0f;
		arcMark = false;
	}
	GraphArc(string szFrom,string szTo,double fWeight,bool Arcmark)
	{
		m_szFrom=szFrom;
		m_szTo=szTo;
		m_fWeight = fWeight;
		arcMark = Arcmark;
	}
};

class GraphLoader
{
public:
	std::vector<GraphArc>  m_RawGraph;//��ʼ�ıߵ����ݱ���������;
	int m_nArcs;
public:
	GraphLoader()
	{	m_nArcs = 0;
	}
	GraphLoader(char szFileName[100])
	{
		LoadGraphFromFile(szFileName);
	}
	void LoadGraphFromFile(string szFileName)
	{
		m_RawGraph.clear();
		std::ifstream InFile(szFileName);	
		if (!InFile)
		{
			std::cout<<"can not open the file szFileName!"<<std::endl;
			return;
		}
		GraphArc arc;
		int i=0;
		while(!InFile.eof())  {

			InFile>>arc.m_szFrom>>arc.m_szTo;
		//	InFile>>arc.m_szFrom>>arc.m_szTo>>arc.m_fWeight;

			m_RawGraph.push_back(arc); //�ں������
		}
		m_nArcs = (int)m_RawGraph.size();			
		if (InFile)
			InFile.close();		
	}
};

class Graph
{
public:
	std::vector<Node>	 m_NodeArray;             //�ڵ�����;
	int					 m_nNumEdges;
	std::vector<Clique*>	 m_CliqueArray;//�˴����������֪�ĸ�����
	int m_NumClique;
public:
	Graph(){
		 m_nNumEdges=0;
		 m_NumClique=0;
	}	
};

