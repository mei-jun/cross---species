// 2017GetEvolvingComplex.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<sstream>
/*
Author:		Yi Li

读取文件构建网络（1为加权网络，0为不加权）,文件最后是否为空没有要求
Graph igraph("", 0);
自动去除重复边、自循环边
*/

#include"graph.h"
#include "getos.h"
int main(int args, char* argv[]) {
	
	string tofile_whole = "C://Users//meijun//Desktop//第五章数据，程序，图//实验数据//1_seedGrow_ConservedComplex_unipro.txt";
	string tofile_additional = "C://Users//meijun//Desktop//第五章数据，程序，图//实验数据//mapDatadata//HS_uniprotkb2geneSysmbl.txt";
	double para = 0.1;
	for (para = 0.00;para <= 0.40;para += 0.05)
	{
		Graph graph3("C://Users//meijun//Desktop//第五章数据，程序，图//实验数据//speciesPPI//data//PPI_final_HS.txt", 0);
		graph3.mapComplexToPPI("C://Users//meijun//Desktop//第五章数据，程序，图//实验数据//mapDatadata//HS_EnsemblGeneId-HGNCsymbol.txt");
		graph3.getEvolvingComplex(para);
		graph3.FilterClique(1.0);
		graph3.outPutIntervalComplex(tofile_whole, tofile_additional);

		ComplexSet complexKnown;
		readComplexfile(complexKnown, "C://Users//meijun//Desktop//第五章数据，程序，图//实验数据//data//CorrumComplex_human_unitprot.txt");
		int numKC = complexKnown.osCliqueNum;
		ComplexSet complexPredict;
		readComplexfile(complexPredict, tofile_whole.c_str());
		int numPC = complexPredict.osCliqueNum;
		int tp = getPredictComplexOS(complexPredict, complexKnown, "", "", "");
		int tn = getKnownComplexOS(complexKnown, complexPredict, "", "", "");
		int fn = numKC - tn;
		int fp = numPC - tp;
		double sn = (double)tp / ((double)tp + (double)fn);
		double sp = (double)tp / ((double)tp + (double)fp);
		double f_measure = ((2 * sn*sp) / (sn + sp));
		cout << para << "\t" << sn << '\t' << sp << "\t" << f_measure << endl;
	}

	/*
	string tofile_whole = "data//dca_evolutionary_whole_complex_HS.txt";
	string tofile_additional = "data//dca_evolutionary_aditional_complex_HS.txt";
	double para = 0.1;
	for (para = 0.00;para <= 0.40;para += 0.05)
	{
	Graph graph3("data//PPI_final_HS.txt", 0);
	graph3.mapComplexToPPI("data//ConservedComplex_final_HS.txt");
	graph3.getEvolvingComplex(para);
	graph3.FilterClique(1.0);
	graph3.outPutIntervalComplex(tofile_whole, tofile_additional);

	ComplexSet complexKnown;
	readComplexfile(complexKnown, "data//CorrumComplex_human_unitprot.txt");
	int numKC = complexKnown.osCliqueNum;
	ComplexSet complexPredict;
	readComplexfile(complexPredict, tofile_whole.c_str());
	int numPC = complexPredict.osCliqueNum;
	int tp = getPredictComplexOS(complexPredict, complexKnown, "", "", "");
	int tn = getKnownComplexOS(complexKnown, complexPredict, "", "", "");
	int fn = numKC - tn;
	int fp = numPC - tp;
	double sn = (double)tp / ((double)tp + (double)fn);
	double sp = (double)tp / ((double)tp + (double)fp);
	double f_measure = ((2 * sn*sp) / (sn + sp));
	cout << para << "\t" << sn << '\t' << sp << "\t" << f_measure << endl;



	Graph graph2("data//PPI_final_DM.txt", 0);
	tofile_whole = "data//dca_evolutionary_whole_complex_DM.txt";
	tofile_additional = "data//dca_evolutionary_aditional_complex_DM.txt";
	mapComplexToPPI("data//ConservedComplex_final_DM.txt", graph2, "");
	graph2.getEvolvingComplex(para);
	graph2.FilterClique(1.0);
	graph2.outPutIntervalComplex(tofile_whole, tofile_additional);

	Graph graph4("data//PPI_final_MM.txt", 0);
	tofile_whole = "data//dca_evolutionary_whole_complex_MM.txt";
	tofile_additional = "data//dca_evolutionary_aditional_complex_MM.txt";
	mapComplexToPPI("data//ConservedComplex_final_MM.txt", graph4, "");
	graph4.getEvolvingComplex(para);
	graph4.FilterClique(1.0);
	graph4.outPutIntervalComplex(tofile_whole, tofile_additional);
	*/
	return 0;
}



