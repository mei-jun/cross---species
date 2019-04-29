#include "stdafx.h"
#include "head.h"
/*
int main()
{
	void compare(ConservedComplexList &conservedComplexList, SpeciesComplexList &speciesComplexList, MapUniprotkb2GeneSymbl &map_unipro2Gsyb,double tv);
	void output(const ConservedComplexList &conservedComplexList, const char* file,double tv);
	void outputALL(const ConservedComplexList &conservedComplexList1, const ConservedComplexList &conservedComplexList2,\
		const ConservedComplexList &conservedComplexList13,const char* file, double tv);

	const double tv=0.5;
	//MM
	ConservedComplexList conservedComplexList("data//1_seedGrow_conservedComplex(ENSG)_id.txt");
	conservedComplexList.setHomoGenes("data//MM//homoGene_HS(Ensg)2MM(geneSymbl).txt");
	MapUniprotkb2GeneSymbl map_unipro2Gsyb("data//MM//MM_uniprotkb2geneSysmbl.txt");
	SpeciesComplexList speciesComplexList("data//MM//MM_Complexes_IN_0.6_OUT_0.8.txt");
	compare(conservedComplexList, speciesComplexList, map_unipro2Gsyb,tv);
//	output(conservedComplexList, "data//result//MM_result.txt", tv);

	//HS
	ConservedComplexList conservedComplexList2("data//1_seedGrow_conservedComplex(ENSG)_id.txt");
	conservedComplexList2.setHomoGenes("data//HS//HS_EnsemblGeneId-HGNCsymbol.txt");
	MapUniprotkb2GeneSymbl map_unipro2Gsyb2("data//HS//HS_uniprotkb2geneSysmbl.txt");
	SpeciesComplexList speciesComplexList2("data//HS//HS_Complexes_IN_0.6_OUT_0.8.txt");
	compare(conservedComplexList2, speciesComplexList2, map_unipro2Gsyb2, tv);
//	output(conservedComplexList2, "data//result//HS_result.txt", tv);
	//
	//DM
	ConservedComplexList conservedComplexList3("data//1_seedGrow_conservedComplex(ENSG)_id.txt");
	conservedComplexList3.setHomoGenes("data//DM//homoGene_HS(Ensg)2DM(geneSymbl).txt");
	MapUniprotkb2GeneSymbl map_unipro2Gsyb3("data//DM//DM_uniprotkb2geneSysmbl.txt");
	SpeciesComplexList speciesComplexList3("data//DM//DM_Complexes_IN_0.6_OUT_0.8.txt");
	compare(conservedComplexList3, speciesComplexList3, map_unipro2Gsyb3, tv);
//	output(conservedComplexList3, "data//result//DM_result.txt", tv);
//	outputALL(conservedComplexList, conservedComplexList2, conservedComplexList3,"data//result_all.txt",tv);
	return 0;
}
*/


double getCommonNum(const ConservedComplex *cc, const SpeciesComplex *sc, MapUniprotkb2GeneSymbl &map_unipro2Gsyb) {	
	double n_cc = cc->nodes.size();
	double n_sc = sc->nodes.size();
	map<string, string>::iterator lowb, upb;
	double n_same_sc = 0, n_same_cc = 0, n_same = 0;
	if (n_cc > 0 && n_sc > 0) {
		for (size_t j = 0;j < n_sc;j++) {
			bool find = false;
			lowb = map_unipro2Gsyb.m_map.lower_bound(sc->nodes[j]);
			upb = map_unipro2Gsyb.m_map.upper_bound(sc->nodes[j]);
			while (lowb != upb) {
				if (cc->homeGeneMergeSet.find(lowb->second) != cc->homeGeneMergeSet.end()) {}
				{
					n_same_sc++;
					find = true;
					break;
				}
				lowb++;
			}
		}

		for (size_t i = 0; i < cc->nodes.size(); i++)
		{
			bool find = false;
			for (size_t k = 0; k < sc->nodes.size(); k++)
			{
				lowb = map_unipro2Gsyb.m_map.lower_bound(sc->nodes[k]);
				upb = map_unipro2Gsyb.m_map.upper_bound(sc->nodes[k]);
				while (lowb != upb) {
					if (cc->nodes[i]->homogeneSet.find(lowb->second) != cc->nodes[i]->homogeneSet.end()) {
						n_same_cc++;
						find = true;
						break;
					}
					lowb++;
				}
				if (find)
					break;
			}
		}
		n_same = (n_same_cc > n_same_sc ? n_same_sc : n_same_cc);
		return n_same;
	}
	else
		return 0;
}

void compare(ConservedComplexList &conservedComplexList, SpeciesComplexList &speciesComplexList, MapUniprotkb2GeneSymbl &map_unipro2Gsyb,double tv) {
	for (size_t i = 0;i < conservedComplexList.ComplexList.size();i++) {
		ConservedComplex *cc = conservedComplexList.ComplexList[i];
		double bestOS = 0;
		size_t bestj = 0;
		double commonNum = 0,tempNum=0;
		for (size_t j = 0;j < speciesComplexList.ComplexList.size();j++) {
			SpeciesComplex *sc = speciesComplexList.ComplexList[j];
			tempNum = getCommonNum(cc, sc, map_unipro2Gsyb);
			double os = tempNum / cc->nodes.size();
			if (os > bestOS)
			{
				bestOS = os;
				bestj = j;
				commonNum = tempNum;
			}
		}
		cc->spc_os = bestOS;		
		if (bestOS >= tv) {
			cc->commonNum = commonNum;			
			const SpeciesComplex *bestSc = speciesComplexList.ComplexList[bestj];
			cc->spc = bestSc;
			map<string, string>::iterator lowb, upb;
			for (size_t k = 0;k < bestSc->nodes.size();k++) {
				bool find = false;
				lowb = map_unipro2Gsyb.m_map.lower_bound(bestSc->nodes[k]);
				upb = map_unipro2Gsyb.m_map.upper_bound(bestSc->nodes[k]);
				while (lowb != upb) {
					if (cc->homeGeneMergeSet.find(lowb->second) != cc->homeGeneMergeSet.end()) {
						find = true;
						break;
					}
					lowb++;
				}
				if (find == false) {
					cc->extraGenes.insert(bestSc->nodes[k]);
				}
			}
		}
	}
}


void output(const ConservedComplexList &conservedComplexList, const char* file,double tv) {
	ofstream ofile(file);
	if (!ofile)
	{
		cout << file << "not exist" << endl;
	}
	ofile << "CC_ID\tOS\tCommonNum\tCC_SIZE\tSPC_SIZE\tSPC_ID\tComplex" << endl;
	for (size_t i = 0;i < conservedComplexList.ComplexList.size();i++) {
		ConservedComplex *c = conservedComplexList.ComplexList[i];
		if (c->spc_os >= tv)
		{
			ofile << c->id << "\t" << c->spc_os << "\t" << c->commonNum << "\t" << c->nodes.size()\
				<< "\t" << c->spc->nodes.size() << "\t" << c->spc->id << "\t";
			set<string>::iterator it = c->extraGenes.begin();
			while (it != c->extraGenes.end()) {
				ofile << *it << "\t";
				it++;
			}		
			ofile << endl;
		}
	}
	ofile.close();
}

void outputALL(const ConservedComplexList &conservedComplexList1, const ConservedComplexList &conservedComplexList2, \
	const ConservedComplexList &conservedComplexList3, const char* file, double tv) {
	//MM  HS  DM
	ofstream ofile(file);
	if (!ofile)
	{
		cout << file << "not exist" << endl;
	}
	ofile << "CC_ID\tOS(MM)\tOS(HS)\tOS(DM)" << endl;
	for (size_t i = 0;i < conservedComplexList1.ComplexList.size();i++) {
		int n = 0;
		ConservedComplex *c_MM = conservedComplexList1.ComplexList[i];
		ConservedComplex *c_HS = conservedComplexList2.ComplexList[i];
		ConservedComplex *c_DM = conservedComplexList3.ComplexList[i];		
		ofile << i << "\t";
		if (c_MM->spc_os >= tv)
		{
			n++;
			ofile << c_MM->spc_os << "\t";
		}
		else		
			ofile << " \t";		
		if (c_HS->spc_os >= tv) {
			n++;
			ofile << c_HS->spc_os << "\t";
		}
		else
			ofile << " \t";
		if (c_DM->spc_os >= tv) {
			n++;
			ofile << c_DM->spc_os<<"\t";
		}
		else
			ofile << " \t";
		ofile << n << endl;
	}
	ofile.close();

}