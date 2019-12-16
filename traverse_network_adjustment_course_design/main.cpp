#include<bits/stdc++.h>
#include<Eigen/Eigen>
#define r 180*3600/M_PI
using namespace std;
using namespace Eigen;
double a[9][9],b[9][9],s0[10],alpha[9][9];
double s[10]={104.440,99.082,92.821,95.183,71.656,90.915,76.504,71.364,79.744,73.586};
double x[9]={300.536,272.962,173.966,96.921,120.313,172.923,257.839,200.697,253.298};//三角求坐标
double y[9]={189.482,290.216,286.096,234.329,142.091,93.524,126.001,159.371,219.306};
//double x[9]={300.536,272.962,173.966,96.9207,130.381,173.044,257.956,200.697,253.298};//导线求坐标
//double y[9]={189.482,290.216,286.096,234.329,142.083,93.5513,126.04,159.371,219.306};
double angle[13]={925468.2,470761.9,1185092.5,761451.1,259644.9,901339.1,767003.3,876993.2,1043482.5,774524.3,166477.5,581561.1,740779.3};
MatrixXd v(22,1),B(22,14),dx(14,1),l(22,1),xx(14,1),p=MatrixXd::Identity(22,22);
void init();
int main(){
	init();
	dx=((B.transpose()*p*B).inverse())*B.transpose()*p*l;
	v=B*dx-l;
	xx+=dx;
	cout<<"l1=\n"<<l<<endl;
	cout<<"p1=\n"<<p<<endl;
	cout<<"dx1=\n"<<dx<<"\nv1=\n"<<v<<endl;
	double ans=(v.transpose()*p*v)(0,0);
	cout<<"error1="<<sqrt(ans/8)<<endl;
	for(int i=0;i<14;i++){
		if(i%2)y[(i-1)/2+2]+=dx(i,0);
		else x[i/2+2]+=dx(i,0);
	}
	/*
	for(int i=0;i<22;i++)
		i<13?angle[i]+=v(i,0):s[i-12]+=v(i,0);
	for(int i=0;i<9;i++)
		cout<<x[i]<<' '<<y[i]<<endl;
	for(int i=0;i<13;i++)
		cout<<fixed<<angle[i]<<' ';
	cout<<endl;
	for(int i=0;i<9;i++)
		cout<<s[i]<<' ';
	cout<<endl;
	*/
	int cnt=2;
	while(1){//迭代
		MatrixXd temp(14,1);
		temp=dx;
		init();
		dx=((B.transpose()*p*B).inverse())*B.transpose()*p*l;
		v=B*dx-l;
		xx+=dx;
		//cout<<"dx"<<cnt<<"=\n"<<dx<<endl<<'v'<<cnt<<"=\n"<<v<<endl;
		ans=(v.transpose()*p*v)(0,0);
		cout<<fixed<<"error"<<cnt<<"="<<sqrt(ans/8)<<endl;
		for(int i=0;i<14;i++){
			if(i%2)y[(i-1)/2+2]+=dx(i,0);
			else x[i/2+2]+=dx(i,0);
		}
		int flag=0;
		for(int i=0;i<14;i++)
			flag+=(temp(i,0)-dx(i,0)<pow(10,-6));
		if(flag==14)
			break;
		cnt++;
	}
	for(int i=0;i<22;i++)
		i<13?angle[i]+=v(i,0):s[i-12]+=v(i,0);
	for(int i=0;i<13;i++)
		cout<<(int)(angle[i]/3600)<<' '<<(int)((angle[i]-(int)(angle[i]/3600)*3600)/60)<<' '<<(angle[i]-(int)(angle[i]/60)*60)<<endl;
	cout<<endl;
	for(int i=0;i<=9;i++)
		cout<<s[i]<<' ';
	cout<<endl;
	cout<<v<<endl;
	cout<<dx<<endl;
	for(int i=0;i<9;i++)
		cout<<x[i]<<' '<<y[i]<<endl;
	cout<<xx<<endl;
	double anss[14];
	//for(int i=0;i<14;i++)
	//	cout<<fixed<<setprecision(100)<<(B.transpose()*p*B).inverse()(i,i)*1000000<<endl;
	for(int i=0;i<14;i++)
		anss[i]=(B.transpose()*p*B).inverse()(i,i)*1000000;
	for(int i=0;i<7;i++)
		cout<<sqrt(ans/8)*sqrt(anss[2*i]+anss[2*i+1])<<endl;
	MatrixXd QLL(22,22);
	QLL=B*(B.transpose()*p*B).inverse()*B.transpose();
	double qll[9];
	for(int i=0;i<9;i++){
		qll[i]=QLL(i+13,i+13);
		cout<<fixed<<sqrt(ans/8)*sqrt(qll[i])/s[i+1]<<endl;
	}
	return 0;
}
void init(){
	s0[1]=sqrt(pow(x[1]-x[2],2)+pow(y[1]-y[2],2));
	s0[2]=sqrt(pow(x[2]-x[3],2)+pow(y[2]-y[3],2));
	s0[3]=sqrt(pow(x[3]-x[4],2)+pow(y[3]-y[4],2));
	s0[4]=sqrt(pow(x[4]-x[5],2)+pow(y[4]-y[5],2));
	s0[5]=sqrt(pow(x[5]-x[6],2)+pow(y[5]-y[6],2));
	s0[6]=sqrt(pow(x[6]-x[0],2)+pow(y[6]-y[0],2));
	s0[7]=sqrt(pow(x[5]-x[7],2)+pow(y[5]-y[7],2));
	s0[8]=sqrt(pow(x[7]-x[8],2)+pow(y[7]-y[8],2));
	s0[9]=sqrt(pow(x[8]-x[1],2)+pow(y[8]-y[1],2));
	a[1][2]=r*(y[2]-y[1])/(s0[1]*s0[1]);
	b[1][2]=-r*(x[2]-x[1])/(s0[1]*s0[1]);
	a[2][3]=r*(y[3]-y[2])/(s0[2]*s0[2]);
	b[2][3]=-r*(x[3]-x[2])/(s0[2]*s0[2]);
	a[3][4]=r*(y[4]-y[3])/(s0[3]*s0[3]);
	b[3][4]=-r*(x[4]-x[3])/(s0[3]*s0[3]);
	a[4][5]=r*(y[5]-y[4])/(s0[4]*s0[4]);
	b[4][5]=-r*(x[5]-x[4])/(s0[4]*s0[4]);
	a[5][6]=r*(y[6]-y[5])/(s0[5]*s0[5]);
	b[5][6]=-r*(x[6]-x[5])/(s0[5]*s0[5]);
	a[6][0]=r*(y[0]-y[6])/(s0[6]*s0[6]);
	b[6][0]=-r*(x[0]-x[6])/(s0[6]*s0[6]);
	a[5][7]=r*(y[7]-y[5])/(s0[7]*s0[7]);
	b[5][7]=-r*(x[7]-x[5])/(s0[7]*s0[7]);
	a[7][8]=r*(y[8]-y[7])/(s0[8]*s0[8]);
	b[7][8]=-r*(x[8]-x[7])/(s0[8]*s0[8]);
	a[8][1]=r*(y[1]-y[8])/(s0[9]*s0[9]);
	b[8][1]=-r*(x[1]-x[8])/(s0[9]*s0[9]);
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
				a[j][i]+=!a[j][i]?-a[i][j]:0;
				b[j][i]+=!b[j][i]?-b[i][j]:0;
		}
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			if(x[j]>x[i]&&y[j]>y[i])
				alpha[i][j]=atan((y[j]-y[i])/(x[j]-x[i]));
			else if(x[i]>x[j]&&y[j]>y[i])
				alpha[i][j]=atan((x[i]-x[j])/(y[j]-y[i]))+M_PI/2;
			else if(x[i]>x[j]&&y[i]>y[j])
				alpha[i][j]=atan((y[i]-y[j])/(x[i]-x[j]))+M_PI;
			else if(x[j]>x[i]&&y[i]>y[j])
				alpha[i][j]=atan((x[j]-x[i])/(y[i]-y[j]))+M_PI*3/2;
			alpha[i][j]*=648000/M_PI;
		}
	l(0,0)=angle[0]-(1296000+alpha[1][2]-alpha[1][0]);
	l(1,0)=angle[1]-(alpha[0][6]-alpha[0][1]);
	l(2,0)=angle[2]-(1296000+alpha[1][8]-alpha[1][0]);
	l(3,0)=angle[3]-(alpha[2][3]-alpha[2][1]);
	l(4,0)=angle[4]-(alpha[1][8]-alpha[1][2]);
	l(5,0)=angle[5]-(alpha[3][4]-alpha[3][2]);
	l(6,0)=angle[6]-(alpha[4][5]-alpha[4][3]);
	l(7,0)=angle[7]-(1296000+alpha[5][6]-alpha[5][4]);
	l(8,0)=angle[8]-(1296000+alpha[5][7]-alpha[5][4]);
	l(9,0)=angle[9]-(1296000+alpha[6][0]-alpha[6][5]);
	l(10,0)=angle[10]-(alpha[5][7]-alpha[5][6]);
	l(11,0)=angle[11]-(1296000+alpha[7][8]-alpha[7][5]);
	l(12,0)=angle[12]-(1296000+alpha[8][1]-alpha[8][7]);
	l(13,0)=s[1]-s0[1];
	l(14,0)=s[2]-s0[2];
	l(15,0)=s[3]-s0[3];
	l(16,0)=s[4]-s0[4];
	l(17,0)=s[5]-s0[5];
	l(18,0)=s[6]-s0[6];
	l(19,0)=s[7]-s0[7];
	l(20,0)=s[8]-s0[8];
	l(21,0)=s[9]-s0[9];
	for(int i=13;i<22;i++)
		p(i,i)=144/pow(s[i-12]/2000,2);
	B(1-1,2*1-2)=-a[1][2];
	B(1-1,2*1-1)=-b[1][2];//v012=-a12x2-b12y2-l1
	B(2-1,2*5-2)=-a[0][6];
	B(2-1,2*5-1)=-b[0][6];//v106=-a06x6-b06y6-l2
	B(3-1,2*7-2)=-a[1][8];
	B(3-1,2*7-1)=-b[1][8];//v018=-a18x8-b18y8-l3
	B(4-1,2*1-2)=a[2][3]-a[2][1];
	B(4-1,2*1-1)=b[2][3]-b[2][1];
	B(4-1,2*2-2)=-a[2][3];
	B(4-1,2*2-1)=-b[2][3];//v123=(a23-a21)x2+(b23-b21)y2-a23x3-b23y3-l4
	B(5-1,2*1-2)=a[1][2];
	B(5-1,2*1-1)=b[1][2];
	B(5-1,2*7-2)=-a[1][8];
	B(5-1,2*7-1)=-b[1][8];//v218=-a18x8-b18y8+a12x2+b12y2-l5
	B(6-1,2*1-2)=a[3][2];
	B(6-1,2*1-1)=b[3][2];
	B(6-1,2*2-2)=a[3][4]-a[3][2];
	B(6-1,2*2-1)=b[3][4]-b[3][2];
	B(6-1,2*3-2)=-a[3][4];
	B(6-1,2*3-1)=-b[3][4];//v234=(a34-a32)x3+(b34-b32)y3-a34x4-b34y4+a32x2+b32y2-l6
	B(7-1,2*2-2)=a[4][3];
	B(7-1,2*2-1)=b[4][3];
	B(7-1,2*3-2)=a[4][5]-a[4][3];
	B(7-1,2*3-1)=b[4][5]-b[4][3];
	B(7-1,2*4-2)=-a[4][5];
	B(7-1,2*4-1)=-b[4][5];//v345=(a45-a43)x4+(b45-b43)y4-a45x5-b45y5+a43x3+b43y3-l7
	B(8-1,2*3-2)=a[5][4];
	B(8-1,2*3-1)=b[5][4];
	B(8-1,2*4-2)=a[5][6]-a[5][4];
	B(8-1,2*4-1)=b[5][6]-b[5][4];
	B(8-1,2*5-2)=-a[5][6];
	B(8-1,2*5-1)=-b[5][6];//v456=(a56-a54)x5+(b56-b54)y5-a56x6-b56y6+a54x4+b54y4-l8
	B(9-1,2*3-2)=a[5][4];
	B(9-1,2*3-1)=b[5][4];
	B(9-1,2*4-2)=a[5][7]-a[5][4];
	B(9-1,2*4-1)=b[5][7]-b[5][4];
	B(9-1,2*6-2)=-a[5][7];
	B(9-1,2*6-1)=-b[5][7];//v457=(a57-a54)x5+(b57-b54)y5-a57x7-b57y7+a54x4+b54y4-l19
	B(10-1,2*4-2)=a[6][5];
	B(10-1,2*4-1)=b[6][5];
	B(10-1,2*5-2)=a[6][0]-a[6][5];
	B(10-1,2*5-1)=b[6][0]-b[6][5];//v560=(a60-a65)x6+(b60-b65)y6+a65x5+b65y5-l10
	B(11-1,2*4-2)=a[5][7]-a[5][6];
	B(11-1,2*4-1)=b[5][7]-b[5][6];
	B(11-1,2*5-2)=a[5][6];
	B(11-1,2*5-1)=b[5][6];
	B(11-1,2*6-2)=-a[5][7];
	B(11-1,2*6-1)=-b[5][7];//v657=(a57-a56)x5+(b57-b56)y5-a57x7-b57y7+a56x6+b56y6-l11
	B(12-1,2*4-2)=a[7][5];
	B(12-1,2*4-1)=b[7][5];
	B(12-1,2*6-2)=a[7][8]-a[7][5];
	B(12-1,2*6-1)=b[7][8]-b[7][5];
	B(12-1,2*7-2)=-a[7][8];
	B(12-1,2*7-1)=-b[7][8];//v578=(a78-a75)x7+(b78-b75)y7-a78x8-b78y8+a75x5+b75y5-l12
	B(13-1,2*6-2)=a[8][7];
	B(13-1,2*6-1)=b[8][7];
	B(13-1,2*7-2)=a[8][1]-a[8][7];
	B(13-1,2*7-1)=b[8][1]-b[8][7];//v781=(a81-a87)x8+(b81-b87)y8+a87x7+b87y7-l13
	B(14-1,2*1-2)=(x[2]-x[1])/s0[1];
	B(14-1,2*1-1)=(y[2]-y[1])/s0[1];//v12=(x2-x1)/s0(12)*x2+(y2-y1)/s0(12)*y2-l14
	B(15-1,2*1-2)=-(x[3]-x[2])/s0[2];
	B(15-1,2*1-1)=-(y[3]-y[2])/s0[2];
	B(15-1,2*2-2)=(x[3]-x[2])/s0[2];
	B(15-1,2*2-1)=(y[3]-y[2])/s0[2];//v23=-(x3-x2)/s0(23)*x2-(y3-y2)/s0(23)*y2+(x3-x2)/s0(23)*x3+(x3-x2)/s0(23)*y3-l15
	B(16-1,2*2-2)=-(x[4]-x[3])/s0[3];
	B(16-1,2*2-1)=-(y[4]-y[3])/s0[3];
	B(16-1,2*3-2)=(x[4]-x[3])/s0[3];
	B(16-1,2*3-1)=(y[4]-y[3])/s0[3];//v34=-(x4-x3)/s0(34)*x3-(y4-y3)/s0(34)*y3+(x4-x3)/s0(34)*x4+(x4-x3)/s0(34)*y4-l16
	B(17-1,2*3-2)=-(x[5]-x[4])/s0[4];
	B(17-1,2*3-1)=-(y[5]-y[4])/s0[4];
	B(17-1,2*4-2)=(x[5]-x[4])/s0[4];
	B(17-1,2*4-1)=(y[5]-y[4])/s0[4];//v45=-(x5-x4)/s0(45)*x4-(y5-y4)/s0(45)*y4+(x5-x4)/s0(45)*x5+(x5-x4)/s0(45)*y5-l17
	B(18-1,2*4-2)=-(x[6]-x[5])/s0[5];
	B(18-1,2*4-1)=-(y[6]-y[5])/s0[5];
	B(18-1,2*5-2)=(x[6]-x[5])/s0[5];
	B(18-1,2*5-1)=(y[6]-y[5])/s0[5];//v56=-(x6-x5)/s0(56)*x5-(y6-y5)/s0(56)*y5+(x6-x5)/s0(56)*x6+(x6-x5)/s0(56)*y6-l18
	B(19-1,2*5-2)=-(x[0]-x[6])/s0[6];
	B(19-1,2*5-1)=-(y[0]-y[6])/s0[6];//v60=-(x0-x6)/s0(60)*x6-(y0-y6)/s0(60)*y6-l19
	B(20-1,2*4-2)=-(x[7]-x[5])/s0[7];
	B(20-1,2*4-1)=-(y[7]-y[5])/s0[7];
	B(20-1,2*6-2)=(x[7]-x[5])/s0[7];
	B(20-1,2*6-1)=(y[7]-y[5])/s0[7];//v57=-(x7-x5)/s0(57)*x5-(y7-y5)/s0(57)*y5+(x7-x5)/s0(57)*x7+(x7-x5)/s0(57)*y7-l20
	B(21-1,2*6-2)=-(x[8]-x[7])/s0[8];
	B(21-1,2*6-1)=-(y[8]-y[7])/s0[8];
	B(21-1,2*7-2)=(x[8]-x[7])/s0[8];
	B(21-1,2*7-1)=(y[8]-y[7])/s0[8];//v78=-(x8-x7)/s0(78)*x7-(y8-y7)/s0(78)*y7+(x8-x7)/s0(78)*x8+(x8-x7)/s0(78)*y8-l21
	B(22-1,2*7-2)=-(x[1]-x[8])/s0[9];
	B(22-1,2*7-1)=-(y[1]-y[8])/s0[9];//v81=-(x1-x8)/s0(81)*x8-(y1-y8)/s0(81)*y8-l22
}