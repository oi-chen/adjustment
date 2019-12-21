#include<bits/stdc++.h>
#include<Eigen/Eigen>
using namespace std;
using namespace Eigen;
const double r=180*3600/M_PI;
MatrixXd L(8,1),v(8,1),B(8,7),dx(7,1),l(8,1),xx(7,1),temp(7,1),p=MatrixXd::Identity(8,8);
void init();
int main(){
	L<<120,0,80,80,50,100,0,120;
	xx<<0,0,120,0,0,0,0;
	for(int i=0;i<8;i++)
		B(i,i%2)=1;
	while(1){
		temp=dx;
		for(int i=0;i<4;i++){
			if(L(2*i,0)==xx(0,0))
				xx(i+3,0)=M_PI/2;
			else if(L(2*i+1,0)==xx(1,0))
				xx(i+3,0)=0;
			else
				xx(i+3,0)=atan((L(2*i+1,0)-xx(1,0))/(L(2*i,0)-xx(0,0)));
			B(2*i,2)=cos(xx(i+3,0));
			B(2*i+1,2)=sin(xx(i+3,0));
			B(2*i,i+3)=-xx(2,0)*sin(xx(i+3,0))/r;
			B(2*i+1,i+3)=xx(2,0)*cos(xx(i+3,0))/r;
			l(2*i,0)=L(2*i,0)-(xx(0,0)+xx(2,0)*cos(xx(i+3,0)));
			l(2*i+1,0)=L(2*i+1,0)-(xx(1,0)+xx(2,0)*sin(xx(i+3,0)));
			xx(i+3,0)*=648000/M_PI;
		}
		dx=((B.transpose()*p*B).inverse())*B.transpose()*p*l;
		v=B*dx-l;
		xx+=dx;
		int flag=0;
		for(int i=0;i<7;i++)
			flag+=temp(i,0)-dx(i,0)<pow(10,-6);
		if(flag==7)
			break;
	}
	L+=v;
	cout<<"center:"<<xx(0,0)<<','<<xx(1,0)<<"\nr="<<xx(2,0)<<endl<<"points:\n";
	for(int i=0;i<4;i++)
		cout<<i+1<<':'<<L(2*i,0)<<','<<L(2*i+1,0)<<endl;
	cout<<"error="<<sqrt((v.transpose()*p*v)(0,0))<<endl;
	return 0;
}