// 2017GetEvolvingComplex.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<sstream>
/*
Author:		Yi Li

��ȡ�ļ��������磨1Ϊ��Ȩ���磬0Ϊ����Ȩ��,�ļ�����Ƿ�Ϊ��û��Ҫ��
Graph igraph("", 0);
�Զ�ȥ���ظ��ߡ���ѭ����
*/

#include"graph.h"
#include "getos.h"
int main(int args, char* argv[]) {
	
	string tofile_whole = "C://Users//meijun//Desktop//���������ݣ�����ͼ//ʵ������//1_seedGrow_ConservedComplex_unipro.txt";
	string tofile_additional = "C://Users//meijun//Desktop//���������ݣ�����ͼ//ʵ������//mapDatadata//HS_uniprotkb2geneSysmbl.txt";
	double para = 0.1;
	for (para = 0.00;para <= 0.40;para += 0.05)
	{
		Graph graph3("C://Users//meijun//Desktop//���������ݣ�����ͼ//ʵ������//speciesPPI//data//PPI_final_HS.txt", 0);
		graph3.mapComplexToPPI("C://Users//meijun//Desktop//���������ݣ�����ͼ//ʵ������//mapDatadata//HS_EnsemblGeneId-HGNCsymbol.txt");
		graph3.getEvolvingComplex(para);
		graph3.FilterClique(1.0);
		graph3.outPutIntervalComplex(tofile_whole, tofile_additional);

		ComplexSet complexKnown;
		readComplexfile(complexKnown, "C://Users//meijun//Desktop//���������ݣ�����ͼ//ʵ������//data//CorrumComplex_human_unitprot.txt");
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



