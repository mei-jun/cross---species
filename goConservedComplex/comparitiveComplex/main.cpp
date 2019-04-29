#include "stdafx.h"

#include "outGO.h"

int main()
{
	void outConservedUni(ConservedComplexList &conservedComplexList, MapGeneSymbl2Uniprotkb &map_Gsyb2unipro, const IDs &idset, const char* file);

	IDs idset("data//cc_idlist.txt");
	//MM
	ConservedComplexList conservedComplexList("data//1_seedGrow_conservedComplex(ENSG)_id.txt");
	conservedComplexList.setHomoGenes("data//MM//homoGene_HS(Ensg)2MM(geneSymbl).txt");
	MapGeneSymbl2Uniprotkb map_unipro2Gsyb("data//MM//MM_uniprotkb2geneSysmbl.txt");
	outConservedUni(conservedComplexList, map_unipro2Gsyb, idset,"data//MM_ConservedComplex_uni.txt");

	//HS
	ConservedComplexList conservedComplexList2("data//1_seedGrow_conservedComplex(ENSG)_id.txt");
	conservedComplexList2.setHomoGenes("data//HS//HS_EnsemblGeneId-HGNCsymbol.txt");
	MapGeneSymbl2Uniprotkb map_unipro2Gsyb2("data//HS//HS_uniprotkb2geneSysmbl.txt");
	outConservedUni(conservedComplexList2, map_unipro2Gsyb2, idset, "data//HS_ConservedComplex_uni.txt");
	
	//DM
	ConservedComplexList conservedComplexList3("data//1_seedGrow_conservedComplex(ENSG)_id.txt");
	conservedComplexList3.setHomoGenes("data//DM//homoGene_HS(Ensg)2DM(geneSymbl).txt");
	MapGeneSymbl2Uniprotkb map_unipro2Gsyb3("data//DM//DM_uniprotkb2geneSysmbl.txt");
	outConservedUni(conservedComplexList3, map_unipro2Gsyb3, idset, "data//DM_ConservedComplex_uni.txt");

	CliqueArray cl1("data//DM_ConservedComplex_uni.txt", idset);
	CliqueArray cl2("data//HS_ConservedComplex_uni.txt", idset);
	CliqueArray cl3("data//MM_ConservedComplex_uni.txt", idset);

	cout << "read addition protein file over!" << endl;

	NodeArray4GO NodeArrGO1("data//DM_GO.txt");
	cout << "read DM GO file over!" << endl;
	NodeArray4GO NodeArrGO2("data//HS_GO.txt");
	cout << "read HS GO file over!" << endl;
	NodeArray4GO NodeArrGO3("data//MM_GO.txt");
	cout << "read all GO file over!" << endl;

	out3speciesAdditionGO("data//GO_3SpeciesConservedComponent.txt", cl1, NodeArrGO1, cl2, NodeArrGO2, cl3, NodeArrGO3);
	return 0;
}





