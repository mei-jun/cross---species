
//ãÐÖµÎª0.7
/*
void readExpress(char  fromFileName[100],ExpressionSet &expSet){
	std::ifstream InFile;
	InFile.open(fromFileName);
	if (!InFile)
	{
		std::cout<<"can not open the file "<<fromFileName<<std::endl;
		return;
	}
	string at;
	while(!InFile.eof())  {
		Expression exp;
		InFile>>at;
		InFile>>exp.protein;
		for(int n_interval=0;n_interval<36;n_interval++){
			InFile>>exp.expValue[n_interval];
		
		}	
		if(exp.protein!="Found"&&exp.protein!="non-annotated"&&exp.protein!="--Control"){
			expSet.ExpVex.push_back(exp);
		}
	}
	expSet.expNum=expSet.ExpVex.size();
	if(InFile)InFile.close();
}



void outPutToAllIntervalNodeSetFile(char  fromFileName[100],ExpressionSet expSet){
	char stt[5];
	char  toFileName[100];
	double aveValue;
	for(int k=1;k<=n_subPINs;k++){
		strcpy(toFileName,fromFileName);
		strcat(toFileName,"_NodesAtInterval_");
		itoa(k,stt,10);
		strcat(toFileName,stt);
		strcat(toFileName,".txt");

		aveValue=0;
		std::ofstream OutFile;
		OutFile.open(toFileName);
		if(!OutFile)
		{
			std::cout<<"Can't Create Output File_"<<k<<"  "<<std::endl;
			return;
		}
		for(size_t j=0;j<expSet.ExpVex.size();j++)
		{	aveValue=(expSet.ExpVex[j].expValue[k-1]+expSet.ExpVex[j].expValue[k+11]+expSet.ExpVex[j].expValue[k+23])/3;

		if(aveValue-ts>eps)
			OutFile<<expSet.ExpVex[j].protein<<std::endl;
		}
		if(OutFile)
			OutFile.close();
	}
	return;
}
*/