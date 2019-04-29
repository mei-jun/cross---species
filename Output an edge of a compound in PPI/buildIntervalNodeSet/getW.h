void readPCTfile(NodeMatrix &complex,char PCTfile[100]){
	std::ifstream inFile;
	inFile.open(PCTfile);
	if(!inFile){
		cout<<"can not open the file "<<PCTfile<<endl;
		return;
	}
	const string strDelims="\t \n";
	vector<string> splitStrs;
	vector<string>::iterator iter; 
	char str[10000];
	char c='\0';
	int i=0;
	inFile>>noskipws;  
	string cliqueId;
	int proteinNum=0;
	char enter;
	while(!inFile.eof())  {		
		while(!inFile.eof() && c!='\n')
		{
			inFile>>c;
			str[i++]=c;
		}
		str[i]='\0';
		splitStrs.clear();
		int splitString(string &strSrc, const string &strDelims, vector<string>& strDest);
		string s(&str[0],&str[strlen(str)]);  
		splitString(s,strDelims,splitStrs);
		iter = splitStrs.begin(); 
		//		cliqueId=*iter;
		Clique* pClique = new Clique();
		//		++iter;
		while(iter != splitStrs.end()) {  
			s=(*iter);
			Node *node=new Node();
			node->setNodeName(s);
			pClique->m_CliqueNodes.push_back(node);
			++iter;
		}
		pClique->proteinNum=pClique->m_CliqueNodes.size();
		complex.CliqueVec.push_back(pClique);
		i=0;
		c='\0';
	}
	if(inFile)
		inFile.close();
	complex.cliqueNum=complex.CliqueVec.size();
}
void rebuildWeight(char fileName[],NodeMatrix complex,GraphLoader rawgraph){
	std::ofstream outFile;
	outFile.open(fileName);
	if(!outFile){
		cout<<"can not open the file "<<fileName<<endl;
		return;
	}
	bool isIncludeInComplex(string nodeA,string nodeB,Clique *acomplex);
	
	string proteinA;
	string proteinB;
	
	for(size_t i=0;i<rawgraph.m_RawGraph.size();i++)
	{	
	
		proteinA=rawgraph.m_RawGraph[i].m_szFrom;
		proteinB=rawgraph.m_RawGraph[i].m_szTo;
		for(int k=0;k<complex.CliqueVec.size();k++)
		{
			if(isIncludeInComplex(proteinA,proteinB,complex.CliqueVec[k])){
				outFile<<proteinA<<'\t'<<proteinB<<'\t'<<endl;
			}
		}
	
				
	}
	if(outFile)
		outFile.close();
}


int  splitString(string &strSrc, const string &strDelims, vector<string> &strDest)  
{	/*分割字符串strSrc,分隔符为strDelims中的各个字符，分割出来的各个分量存在strDest*/
	typedef string::size_type ST;  
	string delims = strDelims;  
	std::string STR;  
	if(delims.empty())
		delims = "|";  
	ST pos=0, LEN = strSrc.size();  
	while(pos < LEN ){  
		STR="";   
		while((pos < LEN) && (delims.find(strSrc[pos]) != std::string::npos)) 
			++pos;  
		if(pos==LEN) 
			return strDest.size();  
		while( (pos < LEN)&&(delims.find(strSrc[pos]) == std::string::npos)) 
			STR += strSrc[pos++];  
		if( ! STR.empty() ) 
			strDest.push_back(STR);  
	}  
	return strDest.size();  
}  


bool isIncludeInComplex(string nodeA,string nodeB,Clique *clique){
	/*判断2个节点是否包含在一个复合物中*/
	bool marka=false;
	bool markb=false;
	for(int k=0;k<clique->m_CliqueNodes.size();k++){
		if(nodeA==clique->m_CliqueNodes[k]->gName){
			marka=true;			
		}
		if(nodeB==clique->m_CliqueNodes[k]->gName){
			markb=true;			
		}
		if(marka&markb)break;
	}

	return marka&markb;
}


void LoadGraphFromRawGraph(Graph &graph,GraphLoader rawGraph)
{
	for(int i=0;i<rawGraph.m_nArcs;i++)	//从rawGraph中读取边的信息;
	{
		int j,k;
		bool bFoundFrom=false;
		bool bFoundTo=false;

		//刚开始时节点数组是为空的，是根据原始图信息来逐渐添加节点的;
		for(j=0;j<graph.m_NodeArray.size();j++)	 //查看边的起始节点是否存在，j保存了改边起始点的位置;
		{
			if(graph.m_NodeArray[j].gName==rawGraph.m_RawGraph[i].m_szFrom)//比较2个字符串的大小……;
			{
				bFoundFrom=true;
				break;
			}			
		}		
		for(k=0;k<graph.m_NodeArray.size();k++)					    //查看边的终止节点是否存在, k保存了改边起始点的位置;
		{
			if(graph.m_NodeArray[k].gName==rawGraph.m_RawGraph[i].m_szTo)
			{
				bFoundTo=true;
				break;
			}
		}
		if(bFoundFrom==false)									//如果不存在，则创建一个新的节点;
		{	Node pNode(graph.m_NodeArray.size(),rawGraph.m_RawGraph[i].m_szFrom);
		graph.m_NodeArray.push_back(pNode);
		j=graph.m_NodeArray.size()-1;												 //j保存了在m_NodeArray中的改边起始点的位置;
		}
		if(bFoundTo==false)											//如果不存在，则创建一个新的节点;
		{	Node pNode(graph.m_NodeArray.size(),rawGraph.m_RawGraph[i].m_szTo);
		graph.m_NodeArray.push_back(pNode);
		k=graph.m_NodeArray.size()-1;												 //k保存了改边终止点的位置;
		}
		graph.m_NodeArray[j].InsertArc(rawGraph.m_RawGraph[i].m_szTo,k,1.0); //在链表中添加一条边;
		graph.m_NodeArray[j].m_iDegree++;
		graph.m_NodeArray[k].InsertArc(rawGraph.m_RawGraph[i].m_szFrom,j,1.0);   //在链表中添加一条边;
		graph.m_NodeArray[k].m_iDegree++;		   		
	}
	graph.m_nNumEdges=rawGraph.m_nArcs;//关系的个数等价于边的个数;
}
