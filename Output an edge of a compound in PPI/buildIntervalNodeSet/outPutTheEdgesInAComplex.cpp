#include "stdafx.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
#include<stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#define n_subPINs 50 //û�õ�
using namespace std;  

#include "datastruct.h"
#include "graph.h"
#include"getW.h"
int main(int argc, _TCHAR* argv[])
{
	void rebuildWeight(char fileName[],NodeMatrix complex,GraphLoader rawgraph);
	NodeMatrix complex;
	char complexfile[100]="data//MM_31.txt";//����֪ʶ
	//ע�⵼����Ǽ�Ȩͼ������Ȩͼ �޸�
	
	readPCTfile(complex, complexfile);

	char ppi[100]="data//PPI_final_MM.txt";		
	char w[100]="data//MM_31_edges.txt";		

	GraphLoader rawgraph(ppi);
	rebuildWeight(w,complex,rawgraph);

}

