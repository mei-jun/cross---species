
void readIntervalNodeSetFile(char filename[][100],std::vector<Nodeset> &ns){
	std::ifstream inFile[n_subPINs];
	for(int i=0;i<n_subPINs;i++){
		inFile[i].open(filename[i]);
		if(!inFile[i]){
			cout<<"can not open the file "<<filename[i]<<endl;
			return;
		}
	}
	string protein;
	for(int i=0;i<n_subPINs;i++){
		Nodeset nodeset;
		while(!inFile[i].eof()){
			inFile[i]>>protein;	
			nodeset.nodeVec.push_back(protein);
		}
		ns.push_back(nodeset);
	}
	for(int i=0;i<n_subPINs;i++){

		if(inFile[i])
			inFile[i].close();
	}

}

void buildIntervalPPI(char *scfileName ,std::vector<Nodeset> &ns,char szfilename[n_subPINs][100]){
	std::ifstream inFile;
	inFile.open(scfileName);
	if(!inFile){
		cout<<"can not open the file "<<scfileName<<endl;
		return;
	}
	std::ofstream outFile[n_subPINs];
	for(int i=0;i<n_subPINs;i++){
		outFile[i].open(szfilename[i]);
		if(!outFile[i])
		{	
			cout<<"can not open the out file "<<szfilename[i]<<endl;
			return;
		}
	}

	vector <string>::iterator nodeIter;
	string proteinA;
	string proteinB;

	while(!inFile.eof()){
		inFile>>proteinA;
		inFile>>proteinB;

		for(int i=0;i<n_subPINs;i++){
			bool markA=false;
			bool markB=false;
			for(nodeIter=ns[i].nodeVec.begin();nodeIter!=ns[i].nodeVec.end();nodeIter++){

				if((*nodeIter)==proteinA)
				{
					markA=true;		
				}
				if((*nodeIter)==proteinB)
				{
					markB=true;		
				}
				if(markA&&markB){
					outFile[i]<<proteinA<<'\t'<<proteinB<<endl;
					break;
				}
			}
		}
	}
	for(int i=0;i<n_subPINs;i++){
		if(outFile[i])
			outFile[i].close();
	}
	if(inFile)
		inFile.close();
}
