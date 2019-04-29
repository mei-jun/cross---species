void FromIntervalPPIToDpin(char fromfile[n_subPINs][100],std::vector<PPI> &PPISet,char *toFile){
	std::ifstream inFile[n_subPINs];
	for(int i=0;i<n_subPINs;i++){
		inFile[i].open(fromfile[i]);
		if(!inFile[i])
		{	
			cout<<"can not open the out file "<<fromfile[i]<<endl;
			return;
		}
	}
	bool markA=false;
	bool markB=false;
	for(int timepoint=0;timepoint<n_subPINs;timepoint++){
		while(!inFile[timepoint].eof()){
			PPI ppi;

			inFile[timepoint]>>ppi.proteinA;
			inFile[timepoint]>>ppi.proteinB;

			if(PPISet.size() ==0)
			{
				PPISet.push_back(ppi);
				PPISet[0].Num_Point++;
				PPISet[0].ActivePoint[timepoint]=1;
				continue;
			}

			for(int ppi_k =0;ppi_k<PPISet.size();ppi_k++){
				markA=false;
				markB=false;
				if(PPISet[ppi_k].proteinA==ppi.proteinA)
				{
					markA=true;		
				}
				if(PPISet[ppi_k].proteinB==ppi.proteinB)
				{
					markB=true;		
				}
				if(markA&&markB){
					PPISet[ppi_k].Num_Point++;
					PPISet[ppi_k].ActivePoint[timepoint]=1;
					break;
				}

			}
			if(markA==false||markB==false){
				ppi.Num_Point++;
				ppi.ActivePoint[timepoint]=1;
				PPISet.push_back(ppi);

			}
		}
	}
	for(int timepoint=0;timepoint<n_subPINs;timepoint++){

		if(inFile[timepoint])
			inFile[timepoint].close();
	}
	/***************************************************************/

	std::ofstream oFile;
	oFile.open(toFile);
	if(!oFile){
		cout<<"can not open the file "<<toFile<<endl;
		return;
	}
	int s=0;

	for(size_t ppi_k =0;ppi_k<PPISet.size();ppi_k++){
		oFile<<PPISet[ppi_k].proteinA<<'\t'<<PPISet[ppi_k].proteinB<<'\t'<<PPISet[ppi_k].Num_Point<<'\t';
		
		for(int timepoint=0;timepoint<n_subPINs;timepoint++){
			if(PPISet[ppi_k].ActivePoint[timepoint]==1)
			{
				oFile<<timepoint+1<<" ,";  
				s++;
			}
		}

		oFile<<endl;

	}
	oFile<<s;

	if(oFile){
		oFile.close();
		return;
	}
}