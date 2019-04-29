

void LoadAndSetActive(char  fromFileName[100],ExpressionSet &expSet){
	std::ifstream InFile;
	InFile.open(fromFileName);
//	void SetActive1( Expression *p);
	void SetActive2( Expression *p);

	if (!InFile)
	{
		std::cout<<"can not open the file "<<fromFileName<<std::endl;
		return;
	}
	string at;
	while(!InFile.eof())  {
		Expression exp;
//		InFile>>at;
		InFile>>exp.protein;
		for(int n_interval=0;n_interval<n_subPINs;n_interval++){
			InFile>>exp.expValue[n_interval];		
		}	
		if(exp.protein!="Found"&&exp.protein!="non-annotated"&&exp.protein!="--Control")
		{	exp.mark=false;//默认设置为未激活
			SetActive2(&exp);
			expSet.ExpVex.push_back(exp);
		}
	}
	expSet.expNum=expSet.ExpVex.size();
	if(InFile)InFile.close();
}

//u+sigma
void SetActive1( Expression *p){
	//判断蛋白质P的表达值在时刻interval是否超过活性阈值
	int interval;
	double u=0,sigma=0;
	for(int i=0;i<n_subPINs;i++){
		u+=p->expValue[i];	
	}
	u/=n_subPINs;

	for(int i=0;i<n_subPINs;i++){
		sigma+=(p->expValue[i]-u)*(p->expValue[i]-u);
	}
	sigma/=(n_subPINs-1); //平方
	sigma=sqrt(sigma); //sigma	

	for(interval=1;interval<=n_subPINs;interval++){
			if(p->expValue[interval-1]-u>sigma) { 
				p->mark=true;
				p->isActive[interval-1]=true;
			}
			else 
				p->isActive[interval-1]=false;

	}
}


//3SIGMA
void SetActive2( Expression *p){
	//判断蛋白质P的表达值在时刻interval是否超过活性阈值
	//使用一个周期的表达数据，该周期每个时刻的表达值等于三个周期对应表达值的平均值
	//interval从1。。。n_subPINs
	int interval;
	double u=0,sigma=0,f=0,active_th;
	for(int i=0;i<n_subPINs;i++){
		u+=p->expValue[i];	
	}
	u/=n_subPINs;
	for(int i=0;i<n_subPINs;i++){
		sigma+=(p->expValue[i]-u)*(p->expValue[i]-u);
	}
	sigma/=(n_subPINs-1);
	f=1/(1+sigma); //sigma平方
	sigma=sqrt(sigma); //sigma	
	active_th=u+(3*sigma)*(1.0-f);
	double expV=0;
	for(interval=1;interval<=n_subPINs;interval++){
		//expV=(p->expValue[interval-1]+p->expValue[interval+11]+p->expValue[interval+23])/3;
		expV=p->expValue[interval-1];
		if(expV>=active_th)
		{   p->mark=true;
			p->isActive[interval-1]=true;
		}
		else 
			p->isActive[interval-1]=false;	
	}
}



void outPutActiveNodesToFile(char  fromFileName[100],ExpressionSet expSet){
	//输出活性的蛋白质集合到n_subPINs个文件
	//输出文件名格式：_NodeSet_atInterval_k
	char stt[5];
	char  toFileName[100];
	int num=0;//统计在任何时刻都没被表达的个数
	for(int k=1;k<=n_subPINs;k++){

		strcpy(toFileName,fromFileName);
		strcat(toFileName,"_NodesAtInterval_");
		itoa(k,stt,10);
		strcat(toFileName,stt);
		strcat(toFileName,".txt");
		std::ofstream OutFile;
		OutFile.open(toFileName);
		if(!OutFile)
		{
			std::cout<<"Can't Create Output File_"<<k<<"  "<<std::endl;
			return;
		}
		for(size_t j=0;j<expSet.ExpVex.size();j++)
		{	
			if(expSet.ExpVex[j].isActive[k-1]==true)
				{	
					OutFile<<expSet.ExpVex[j].protein<<std::endl;
			}
		}
		if(OutFile)
			OutFile.close();
	}
	return;
}

void outPutStaticProteinToFile(ExpressionSet expSet){
	//输出静态的组成蛋白集合到文件
	
	char  toFileName[100]="E://_dataTest//DPIN_V8//ppi//constituent_protein.txt";
//	char  toFileName[100]="E://_dataTest//DPIN_V9//ppi//constituent_protein.txt";

	std::ofstream OutFile;
	OutFile.open(toFileName);
	if(!OutFile)
	{
		std::cout<<"Can't Create Output File_"<<toFileName<<"  "<<std::endl;
		return;
	}
	for(size_t j=0;j<expSet.ExpVex.size();j++)
	{	
		if(expSet.ExpVex[j].mark==false)
		{	
			OutFile<<expSet.ExpVex[j].protein<<std::endl;
		}
	}
	if(OutFile)
		OutFile.close();
	return;
}

void countNonExpress(ExpressionSet expSet){
	//从未表达过的数量	
	int num=0;
		for(size_t j=0;j<expSet.ExpVex.size();j++){

			if(expSet.ExpVex[j].mark==false)num++;
		}
		cout<<num;
}