// p-value.cpp : 定义控制台应用程序的入口点。
//

#include<math.h>
#include<iostream>
#include"head.h"
using namespace::std;

void swap(int &a,int &b) {
	int t = a;
	a = b;
	b = t;
}
long long C(int n, int m) {
	//C(n,m),从n中选择m个组合
	long long result = 1;
	double a = n - m,b=m;
	if(a > b)swap(a, b);
	int i = 1;
	for (;i <= a;i++) {
		result *= ((b + i) / i);
	}
	return result;
	//return (jiecheng(n)) / (jiecheng(m)*jiecheng(n - m));

}
long double pvalue(int n, int x,double p,string term) {

	if(x==0)
		return 1;
	long double pvalue=0;
	int j = x;
	for (;j <= n;j++) {
		long long t=C(n, j);
		if(t<0)
		{
			cout<<term<<"\t"<<n<<"\t"<<x<<"\t"<<p<<endl;
			break;
		}
		pvalue += t*pow(p, j)*pow(1 - p, n -j);	
	}
	return pvalue;
}

void countPvalue(const char* backNodeGOfile,const char* proteinsfile,const char* outfile) {	
	BackgroundNodeGOlist Nodearray = *new BackgroundNodeGOlist(backNodeGOfile);
	set<string> uniset;
	GOTermlist Termfreq = *new GOTermlist(Nodearray,uniset);
	wantedTerms wantterms = *new wantedTerms(uniset);
	AnalizedClique Protein = *new AnalizedClique(proteinsfile);	
	int x = 0;
	vector<string>::iterator it_p = Protein.m_ProteinArray.begin();
	vector<GOterm>::iterator it_w = wantterms.m_Terms.begin(), it_all, it_be = Termfreq.m_GOTermArray.begin(), it_en = Termfreq.m_GOTermArray.end();
	//背景频率
	for (;it_w != wantterms.m_Terms.end();it_w++) {
		it_all = find(it_be, it_en, *it_w);
		if (it_all != it_en) {
			it_w->m_back_f = it_all->m_back_f;
		}
	}
	//x
	it_w = wantterms.m_Terms.begin();
	for (;it_w != wantterms.m_Terms.end();it_w++) {
		int x = 0;
		for (it_p = Protein.m_ProteinArray.begin();it_p != Protein.m_ProteinArray.end();it_p++) {
			Node node = *new Node(*it_p);
			vector<Node>::iterator it_n = find(Nodearray.m_NodeArray.begin(), Nodearray.m_NodeArray.end(), node);
			if (it_n != Nodearray.m_NodeArray.end()) {
				if (it_n->findGo(it_w->m_term)) {
					x++;
				}
			}
		}
		it_w->m_x = x;
	}
	it_w = wantterms.m_Terms.begin();
	ofstream ofil(outfile);
	for (;it_w != wantterms.m_Terms.end();it_w++) {
		ofil << it_w->m_term << "\t" << pvalue(Protein.m_ProteinArray.size(), it_w->m_x, it_w->m_back_f,it_w->m_term) << endl;
		//cout << it_w->m_term << "\t\t\n";
		//cout << pvalue(Protein.m_ProteinArray.size(), it_w->m_x, it_w->m_back_f) << endl;
	}
	ofil.close();
}



int main()
{
	cout<<"DM:"<<endl<<endl;
//	countPvalue("data//DM_GO.txt","data//proteins_DM.txt","data//p_value_DM.txt");
//	cout<<"HS:"<<endl<<endl;
	countPvalue("data//HS_GO.txt", "data//proteins_HS.txt", "data//p_value_HS.txt");
	cout<<"MM:"<<endl<<endl;
//	countPvalue("data//MM_GO.txt", "data//proteins_MM.txt", "data//p_value_MM.txt");
	
    return 0;
}

