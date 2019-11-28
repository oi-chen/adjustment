#include<bits/stdc++.h>
#include<Eigen/Eigen>
using namespace Eigen;
using namespace std;
int main(){
	MatrixXd a(4,8),b(4,3),w(4,1),x(3,1),dx(3,1),l(8,1),li(8,1),v(8,1),temp(3,1),q=MatrixXd::Identity(8,8);
	int cnt=1;
	l<<120,0,80,80,50,100,0,120;
	x<<0,0,120;
	while(1){
		li=l+v;
		x+=dx;
		for(int i=0;i<4;i++){
			a(i,2*i)=2*(li(2*i,0)-x(0,0));
			a(i,2*i+1)=2*(li(2*i+1,0)-x(1,0));
			b(i,0)=-2*(li(2*i,0)-x(0,0));
			b(i,1)=-2*(li(2*i+1,0)-x(1,0));
			b(i,2)=-2*x(2,0);
			w(i,0)=pow((li(2*i,0)-x(0,0)),2)+pow((li(2*i+1,0)-x(1,0)),2)-x(2,0)*x(2,0);
		}
		w-=a*v;
		dx=-1*(b.transpose()*(a*q*a.transpose()).inverse()*b).inverse()*b.transpose()*(a*q*a.transpose()).inverse()*w;
		v=-1*q*a.transpose()*(a*q*a.transpose()).inverse()*(b*dx+w);
		int flag=0;
		for(int i=0;i<3;i++)
			flag+=(temp(i,0)-dx(i,0)<=pow(10,-6));
		if(flag==3)
			break;
		temp=dx;
		cnt++;
	}
	cout<<"count="<<cnt<<"\npoints:\n";
	for(int i=0;i<4;i++)
		cout<<i+1<<':'<<li(2*i,0)<<','<<li(2*i+1,0)<<'\n';
	cout<<"center:"<<x(0,0)<<','<<x(1,0)<<"\nr="<<x(2,0)<<'\n';
	cout<<"error="<<(v.transpose()*q.inverse()*v)/1<<'\n';
	return 0;
}
/*
1.初始观测圆心赋给x,四个点赋给l
2.li=l+v,li为此次迭代时的各点
3.x+=dx,x为此次圆心信息，dx为上次迭代后对x的修正量
(v用完即弃,参数x需累加保留)
4.对a,b,w赋值
5.计算dx,v并判断是否应停止迭代
6.重复2~5
*/