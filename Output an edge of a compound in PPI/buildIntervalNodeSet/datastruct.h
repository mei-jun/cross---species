class Expression
{
public:
	string protein;	
	double expValue[n_subPINs];
	bool isActive[n_subPINs];
	bool mark;//����ͳ�����κ�ʱ�̶�û���ĸ���
public:
	Expression()
	{ 
		mark=false;
	}
};

class ExpressionSet{
public:
	std::vector<Expression>	ExpVex;
	int expNum;
public:
	ExpressionSet(){
	expNum=0;
	}
};

class Nodeset{
public:
	std::vector<string>	nodeVec;
	int numEdges;
public:
	Nodeset(){numEdges=0;}
};


class ComplexSet{
public:
	std::vector<Nodeset>  complexVec;
public:
	ComplexSet(){
	}
};


class PPI{
public:
	string proteinA;
	string proteinB;
	int	Num_Point;
	int ActivePoint[n_subPINs];
public:
	PPI(){
	Num_Point=0;
	for(int i=0;i<n_subPINs;i++){
		ActivePoint[i]=-1;
		//-1��û����
		//1������
	}
	}
};

