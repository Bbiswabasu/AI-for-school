#include <bits/stdc++.h>
using namespace std;

int OR(int a,int b)
{return a|b;}
int AND(int a,int b)
{return a&b;}
int XOR(int a,int b)
{return a^b;}
int IMPLY(int a,int b)
{return (!a)|b;}
int BIIMPLY(int a,int b)
{return (a&b)|((!a)&(!b));}

int best;
vector<int> bestBits;
vector<string> moves,bestMoves;

int orc,andc,xorc,implyc,biimplyc;
void getBest(int i,int cur,vector<int> &bits)
{
	if(i==0){
		if(cur>best){
			best=cur;
			bestBits=bits;
			bestMoves=moves;
		}
		return;
	}
	if(orc>0)
	{
		bits[i]=OR(bits[2*i],bits[2*i+1]);
		orc--;
		moves[i]="OR";
		getBest(i-1,cur+bits[i],bits);
		orc++;
	}
	if(andc>0)
	{
		bits[i]=AND(bits[2*i],bits[2*i+1]);
		andc--;
		moves[i]="AND";
		getBest(i-1,cur+bits[i],bits);
		andc++;
	}
	if(xorc>0)
	{
		bits[i]=XOR(bits[2*i],bits[2*i+1]);
		xorc--;
		moves[i]="XOR";
		getBest(i-1,cur+bits[i],bits);
		xorc++;
	}
	if(implyc>0)
	{
		bits[i]=IMPLY(bits[2*i],bits[2*i+1]);
		implyc--;
		moves[i]="IMPLY";
		getBest(i-1,cur+bits[i],bits);
		implyc++;
	}
	if(biimplyc>0)
	{
		bits[i]=BIIMPLY(bits[2*i],bits[2*i+1]);
		biimplyc--;
		moves[i]="BIIMPLY";
		getBest(i-1,cur+bits[i],bits);
		biimplyc++;
	}
}
int main()
{
	int n;
	cout<<"Enter no of levels in tree: ";
	cin>>n;
	cout<<"Let the nodes be numbered levelwise from left to right as: \n";
	int i=1;
	for(int l=1;l<=n;l++)
	{
		for(int j=1;j<=(1<<(l-1));j++)
			cout<<i++<<" ";
		cout<<"\n";
	}
	int size=1<<n;
	vector<int> bits(size);
	srand((unsigned int)time(nullptr));

	cout<<"\n";
	for(int i=1<<(n-1);i<1<<n;i++){
		bits[i]=rand()%2;
		cout<<i<<" -> "<<bits[i]<<"\n";
	}
	cout<<"\n";
	
	int score=0;
	best=0;
	
	orc=0;
	andc=xorc=1<<(n-1);
	implyc=biimplyc=2;

	cout<<"OR -> "<<orc<<"\n";
	cout<<"AND -> "<<andc<<"\n";
	cout<<"XOR -> "<<xorc<<"\n";
	cout<<"IMPLY -> "<<implyc<<"\n";
	cout<<"BIIMPLY -> "<<biimplyc<<"\n";
	cout<<"\n";

	moves.resize((1<<(n-1)));
	getBest((1<<(n-1))-1,0,bits);
	for(int l=n-1;l>=1;l--)
	{
		for(int i=1<<(l-1);i<=(1<<l)-1;i++)
		{
			// while(1)
			// {
				cout<<i<<" -> ";
				string s;
				cin>>s;
				if(s=="or" && orc>0){
					bits[i]=OR(bits[2*i],bits[2*i+1]);
					orc--;
				}
				else if(s=="and" && andc>0){
					bits[i]=AND(bits[2*i],bits[2*i+1]);
					andc--;
				}
				else if(s=="xor" && xorc>0){
					bits[i]=XOR(bits[2*i],bits[2*i+1]);
					xorc--;
				}
				else if(s=="imply" && implyc>0){
					bits[i]=IMPLY(bits[2*i],bits[2*i+1]);
					implyc--;
				}
				else if(s=="biimply" && biimplyc>0){
					bits[i]=BIIMPLY(bits[2*i],bits[2*i+1]);
					biimplyc--;
				}
				else{
					cout<<"Invalid operator\n";
					i--;
					continue;
				}
				score+=bits[i];
			// 	if(bits[i]==1){
			// 		cout<<"Well done\n";
			// 		break;
			// 	}
			// 	else
			// 		cout<<"It can be made 1. Try once more\n";
			// }
		}
	}
	cout<<"\nYour Score: "<<score<<"\n";
	cout<<"Highest possible: "<<best<<"\n";
	cout<<"One of the optimal moves\n";
	for(int i=1;i<(1<<(n-1));i++)
		cout<<i<<" -> "<<bestMoves[i]<<"\n";
}