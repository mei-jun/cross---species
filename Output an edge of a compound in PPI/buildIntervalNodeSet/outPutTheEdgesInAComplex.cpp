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
#define n_subPINs 50 //没用到
using namespace std;  

#include "datastruct.h"
#include "graph.h"
#include"getW.h"
int main(int argc, _TCHAR* argv[])
{
	void rebuildWeight(char fileName[],NodeMatrix complex,GraphLoader rawgraph);
	NodeMatrix complex;
	char complexfile[100]="data//MM_31.txt";//先验知识
	//注意导入的是加权图还是无权图 修改
	
	readPCTfile(complex, complexfile);

	char ppi[100]="data//PPI_final_MM.txt";		
	char w[100]="data//MM_31_edges.txt";		

	GraphLoader rawgraph(ppi);
	rebuildWeight(w,complex,rawgraph);

}

