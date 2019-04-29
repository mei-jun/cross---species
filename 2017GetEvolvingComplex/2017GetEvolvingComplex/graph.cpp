#include "stdafx.h"
#include "graph.h"

/*
void Graph::getEdgeECC(double alpha) {//边和节点的加权		
		
		double mNum = 0;
		double ecc = 0;
		double nodew = 0;
		double dx = 0, dy = 0, mindeg;
		//	double maxecc = -1, minecc = 100;
		for (size_t i = 0;i < m_NodeArray.size();i++) {
			//对于节点x
			nodew = 0;
			Node *nodex = m_NodeArray[i];
			dx = nodex->m_iDegree;
			Arc *arcxy = nodex->m_pFirst;
			while (arcxy != NULL) {//对于x的所有邻居节点Y：
				mNum = 0;
				Node *nodey = m_NodeArray[arcxy->m_iNodeTo];//与x相连的节点y
				dy = nodey->m_iDegree;
				Arc *arcxm = nodex->m_pFirst;//与x相连的节点m
				for (;arcxm != NULL;arcxm = arcxm->m_pNextArc) {//对于x的所有邻居（除了Y外）M：
					if (arcxm != arcxy) {
						Node *nodem = m_NodeArray[arcxm->m_iNodeTo];
						Arc *arcmy = nodem->m_pFirst;
						while (arcmy != NULL) {//遍历与M相连的节点，若与Y与M相连：
							if (arcmy->m_iNodeTo == nodey->m_iNode)
							{
								mNum++;
								break;
							}
							arcmy = arcmy->m_pNextArc;
						}
					}
				}
				if (dx < 2 || dy < 2)
					ecc = 0;
				else {
					mindeg = (dx < dy ? dx - 1 : dy - 1);
					ecc = mNum / mindeg;
				}
				double edgew=alpha*ecc+(1-alpha)*arcxy->m_fWeight;
				arcxy->m_fWeight =edgew; 
				arcxy = arcxy->m_pNextArc;
				nodew += edgew;
			}
//			nodex->weight = nodew;
		}

	}

	*/
bool Graph::IsIncludedInClique(int inode, Clique *clique) {
	for (int i = 0; i < clique->m_CliqueNodes.size(); i++) {
		if (inode == clique->m_CliqueNodes[i]) {
			return true;
		}
	}
	return false;
}
double Graph::getWeightOfNode2Clique(const Node* node, Clique *clique) {
	//团内的所有节点对另一个节点node的权值所做的贡献值,ecc之和加suvtime
	if (node->m_iDegree <= 1)
	{
		return 0;
	}
	double ecc = 0;
	Clique *neighborInClique = new Clique(0);
	Arc *arc = node->m_pFirst;
	while (arc&&IsIncludedInClique(arc->m_iNodeTo, clique)) {
		neighborInClique->m_CliqueNodes.push_back(arc->m_iNodeTo);
		ecc += arc->m_fWeight;
		arc = arc->m_pNextArc;
	}
	double neighborNum = neighborInClique->m_CliqueNodes.size();
	if (neighborNum == 0) {
		delete neighborInClique;
		return 0;
	}
	delete neighborInClique;
	return ecc/(double)clique->m_CliqueNodes.size();
}
/*
void Graph::getEvolvingComplex(double para) {	
	for (size_t i = 0;i < m_CliqueArray.size();i++) {
		std::vector<int> ExtendNodes;
		for (int j = 0; j < m_CliqueArray[i]->m_CliqueNodes.size(); j++)
		{
			Arc* pArc = m_NodeArray[m_CliqueArray[i]->m_CliqueNodes[j]]->m_pFirst;
			while (pArc != NULL)
			{
				std::vector<int>::iterator begin = ExtendNodes.begin();
				std::vector<int>::iterator end = ExtendNodes.end();
				std::vector<int>::iterator result = find(begin, end, pArc->m_iNodeTo);

				if (!IsIncludedInClique(pArc->m_iNodeTo, m_CliqueArray[i]) && result == ExtendNodes.end())
				{
					ExtendNodes.push_back(pArc->m_iNodeTo);
				}
				pArc = pArc->m_pNextArc;
			}
		}
		for (int m = 0; m < ExtendNodes.size(); m++)
		{
			if (getWeightOfNode2Clique(m_NodeArray[ExtendNodes[m]], m_CliqueArray[i]) > para)
				m_CliqueArray[i]->m_CliqueNodes.push_back(ExtendNodes[m]);
		}
	}
}
*/

void Graph::getEvolvingComplex(double para) {
	for (size_t i = 0;i < m_CliqueArray.size();i++) {
		std::vector<int> ExtendNodes;
		for (int j = 0; j < m_CliqueArray[i]->m_CliqueNodes.size(); j++)
		{
			Arc* pArc = m_NodeArray[m_CliqueArray[i]->m_CliqueNodes[j]]->m_pFirst;
			while (pArc != NULL)
			{
				std::vector<int>::iterator begin = ExtendNodes.begin();
				std::vector<int>::iterator end = ExtendNodes.end();
				std::vector<int>::iterator result = find(begin, end, pArc->m_iNodeTo);

				if (!IsIncludedInClique(pArc->m_iNodeTo, m_CliqueArray[i]) && result == ExtendNodes.end())
				{
					ExtendNodes.push_back(pArc->m_iNodeTo);
				}
				pArc = pArc->m_pNextArc;
			}
		}
		for (int m = 0; m < ExtendNodes.size(); m++)
		{
			if (getWeightOfNode2Clique(m_NodeArray[ExtendNodes[m]], m_CliqueArray[i]) > para)
				m_CliqueArray[i]->m_CliqueNodes.push_back(ExtendNodes[m]);
		}
	}
}


void  Graph::FilterClique(double  tvOverlap)
{
	sort(m_CliqueArray.begin(), m_CliqueArray.end(), CompCliqueSizeDecend_CliqueNodes());

	int findNum;
	int mi;
	int mj;
	double overlap;
	std::vector<int>::iterator iter;
	for (int i = 0; i < m_CliqueArray.size(); i++) {
		m_CliqueArray[i]->mark = true;
	}
	for (int i = 0; i < (int)m_CliqueArray.size() - 1; i++) {
		if (m_CliqueArray[i]->mark == false)
			continue;
		for (int j = i + 1; j < m_CliqueArray.size(); j++) {
			if (m_CliqueArray[j]->mark == false)
				continue;
			findNum = 0;
			mi = m_CliqueArray[i]->m_CliqueNodes.size();
			mj = m_CliqueArray[j]->m_CliqueNodes.size();
			for (int jd = 0; jd < mj; jd++)
			{
				for (iter = m_CliqueArray[i]->m_CliqueNodes.begin(); iter != m_CliqueArray[i]->m_CliqueNodes.end(); iter++)
				{	//?????
					if (*iter == m_CliqueArray[j]->m_CliqueNodes[jd])
					{
						findNum++;
						break;
					}
				}
			}
			if ((mi != 0) && (mj != 0))
			{
				overlap = (double)(findNum*findNum) / (mi*mj);
			}
			if (findNum == mj || (overlap - tvOverlap >= 0)) {
				m_CliqueArray[j]->mark = false;
			}
		}
	}
}

void Graph::outPutIntervalComplex(const string tofile, const string tofile_additionalProtein)
{
	std::ofstream OutFile;
	OutFile.open(tofile.c_str(), ios::out);
	if (!OutFile)
	{
		std::cout << "Can't create OutPut file COMPLEX!" << std::endl;
	}
	for (int i = 0; i < m_CliqueArray.size(); i++)
	{
		if (m_CliqueArray[i]->mark == true) {
			int j;
			OutFile<<m_CliqueArray[i]->m_iCliqueNo<<"\t";
			for (j = 0; j < m_CliqueArray[i]->m_CliqueNodes.size()-1; j++)
			{
				OutFile << m_NodeArray[m_CliqueArray[i]->m_CliqueNodes[j]]->m_szName << '\t';

			}
			OutFile << m_NodeArray[m_CliqueArray[i]->m_CliqueNodes[j]]->m_szName;
			OutFile << std::endl;
		}
	}
	if (OutFile)
		OutFile.close();	
}

void Graph::mapComplexToPPI(const string file) {
	ifstream ifile(file.c_str());
	if (!ifile)
		cout << "file not exist!" << endl;
	string line;
	stringstream istr;
	string protein;
	int nodeIndex;
	int cliqueNo = 0;
	while (!ifile.eof()) {
		getline(ifile, line, '\n');
		istr.clear();
		istr.str(line);
		if (!istr.eof())
			istr >> cliqueNo;
		Clique *clique = new Clique(cliqueNo);
		while (!istr.eof()) {
			istr >> protein;
			nodeIndex = -1;
			for (size_t k = 0;k < m_NodeArray.size();k++) {
				if (m_NodeArray[k]->m_szName == protein)
				{
					nodeIndex = k;
					break;
				}
			}
			if (nodeIndex != -1) {
				clique->m_CliqueNodes.push_back(nodeIndex);
			}
		}
		sort(clique->m_CliqueNodes.begin(), clique->m_CliqueNodes.end());
		vector<int>::iterator iter = unique(clique->m_CliqueNodes.begin(), clique->m_CliqueNodes.end());
		clique->m_CliqueNodes.erase(iter, clique->m_CliqueNodes.end());
		if (clique->m_CliqueNodes.size()>1)
			m_CliqueArray.push_back(clique);
	}
	ifile.close();
}

