//导线求坐标
#include<bits/stdc++.h>
using namespace std;
double x[9],y[9],x2[9],y2[9],alpha[9][9],alpha2[9][9];
double s[10]={104.440000000000,99.1130327049259	,92.8325535116393	,95.1541549885133	,71.6351230146091	,90.8564579325665,	76.4852283115137	,71.3775269910896,	79.7685686063198,	73.5973076912815	};
double angle[13]={925457.924568797,	470769.504280082,	1185092.98717653,	761451.378594770,	259635.062607730,	901340.379216465,	767005.260007731,	876996.210918883,	1043481.53116387,	774518.350973435,	166485.320244988,	581568.800607233,	740787.713017660};
//double s[10]={104.440000000000,99.1102040002169,	92.8323520737871,	95.1559857587151,	71.6299138107364,	90.8550164940795	,76.4846660261143	,71.3771258854277,	79.7696306711981,	73.5950300853858	};//三角求坐标一次平差
//double angle[13]={925459.397360744,	470768.827574004,	1185094.37485952,	761452.219925693	,259634.977498781	,901340.220015100,	767004.420076669	,876995.197601604,	1043481.62248268,	774517.372594194,	166486.424881074	,581569.147456604	,740787.347542036};
//double s[10]={104.440,99.082,92.821,95.183,71.656,90.915,76.504,71.364,79.744,73.586};//初始
//double angle[13]={925468.2,470761.9,1185092.5,761451.1,259644.9,901339.1,767003.3,876993.2,1043482.5,774524.3,166477.5,581561.1,740779.3};
//double s[10]={103.711365867,75.038,95.276,89.885,81.607,79.163,76.929,75.054,75.879,62.15};//hc
//double angle[13]{254*3600+8*60+8.3,360*3600-228*3600-37*60,321*3600+18*60+39.9,210*3600+37*60+53,67*3600+10*60+18.2,245*3600+44*60+36.5,221*3600+60+54.4,360*3600-116*3600-10*60-51.4,280*3600+15*60+51.1,216*3600+1*60+18.3,36*3600+26*60+27.8,194*3600+51*60+33.6,174*3600*38*60+42.2};
void fix(){
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			alpha[i][j]-=2*M_PI*(alpha[i][j]>2*M_PI);
			alpha[i][j]+=2*M_PI*(alpha[i][j]<0);
			alpha2[i][j]-=2*M_PI*(alpha2[i][j]>2*M_PI);
			alpha2[i][j]+=2*M_PI*(alpha2[i][j]<0);
		}
}
int main(){
	x[0]=300.536,y[0]=189.482,x[1]=272.962,y[1]=290.216;
	if(x[1]>x[0]&&y[1]>y[0])
		alpha[0][1]=atan((y[1]-y[0])/(x[1]-x[0]));
	else if(x[0]>x[1]&&y[1]>y[0])
		alpha[0][1]=atan((x[0]-x[1])/(y[1]-y[0]))+M_PI/2;
	else if(x[0]>x[1]&&y[0]>y[1])
		alpha[0][1]=atan((y[0]-y[1])/(x[0]-x[1]))+M_PI;
	else if(x[1]>x[0]&&y[0]>y[1])
		alpha[0][1]=atan((x[1]-x[0])/(y[0]-y[1]))+M_PI*3/2;
	for(int i=0;i<13;i++)
		angle[i]*=M_PI/648000;
	alpha[1][2]=alpha[0][1]+angle[0]-M_PI;//alpha01+angle012-M_PI
	alpha[2][3]=alpha[1][2]+angle[3]-M_PI;//alpha12+angle123-M_PI
	alpha[3][4]=alpha[2][3]+angle[5]-M_PI;//alpha23+angle234-M_PI
	alpha[4][5]=alpha[3][4]+angle[6]-M_PI;//alpha34+angle345-M_PI
	alpha[5][6]=alpha[4][5]+angle[7]-M_PI;//alpha45+angle456-M_PI
	fix();
	for(int i=2;i<=6;i++){
		x[i]=x[i-1]+s[i-1]*cos(alpha[i-1][i]);
		y[i]=y[i-1]+s[i-1]*sin(alpha[i-1][i]);
	}
	alpha[6][0]=alpha[5][6]+angle[9]-M_PI;
	double x01=x[6]+s[6]*cos(alpha[6][0]),y01=y[6]+s[6]*sin(alpha[6][0]);
	cout<<fixed<<x01<<' '<<y01<<endl;
	x2[1]=x[1],y2[1]=y[1];
	alpha2[0][1]=alpha[0][1];
	alpha2[1][8]=alpha2[0][1]+angle[2]-M_PI;
	alpha2[8][7]=alpha2[1][8]+(2*M_PI-angle[12])-M_PI;
	alpha2[7][5]=alpha2[8][7]+(2*M_PI-angle[11])-M_PI;	
	alpha2[5][6]=alpha2[7][5]+(2*M_PI-angle[10])-M_PI;
	alpha2[6][0]=alpha2[5][6]+angle[9]-M_PI;
	//cout<<alpha2[1][8]*180/M_PI<<' '<<alpha2[8][7]*180/M_PI<<' '<<alpha2[7][5]*180/M_PI<<' '<<alpha2[5][6]*180/M_PI<<' '<<alpha2[6][0]*180/M_PI<<endl;
	fix();
	x2[8]=x2[1]+s[9]*cos(alpha2[1][8]),y2[8]=y2[1]+s[9]*sin(alpha2[1][8]);
	x2[7]=x2[8]+s[8]*cos(alpha2[8][7]),y2[7]=y2[8]+s[8]*sin(alpha2[8][7]);
	x2[5]=x2[7]+s[7]*cos(alpha2[7][5]),y2[5]=y2[7]+s[7]*sin(alpha2[7][5]);
	x2[6]=x2[5]+s[5]*cos(alpha2[5][6]),y2[6]=y2[5]+s[5]*sin(alpha2[5][6]);
	//cout<<x2[8]<<' '<<y2[8]<<endl<<x2[7]<<' '<<y2[7]<<endl<<x2[5]<<' '<<y2[5]<<endl<<x2[6]<<' '<<y2[6]<<endl;
	double x02=x2[6]+s[6]*cos(alpha2[6][0]),y02=y2[6]+s[6]*sin(alpha2[6][0]);
	cout<<fixed<<x02<<' '<<y02<<endl;
	for(int i=2;i<9;i++){
		if(x[i]&&x2[i]){
			x[i]=(x[i]+x2[i])/2;
			y[i]=(y[i]+y2[i])/2;
		}
		else{
			x[i]=!x2[i]?x[i]:x2[i];
			y[i]=!y2[i]?y[i]:y2[i];
		}
	}
	for(int i=0;i<9;i++){
		if(!i)cout<<"double x[9]={";
		cout<<x[i];
		if(i<8)cout<<',';
		if(i==8)cout<<"};\n";
	}
	for(int i=0;i<9;i++){
		if(!i)cout<<"double y[9]={";
		cout<<y[i];
		if(i<8)cout<<',';
		if(i==8)cout<<"};\n";
	}
	/*
	for(int i=0;i<9;i++)
		cout<<i<<':'<<x[i]<<' '<<y[i]<<endl;
	*/
	return 0;
}
/*
//三角求坐标
#include<bits/stdc++.h>
using namespace std;
double xa,xb,ya,yb,xc,yc,a,b,c,abc,cab,alpha_ab,alpha_ac;
int flag,side;
int main(){
	cin>>flag;//已知bc时,flag=1
	if(flag==1){
		double p,q,r;
		cin>>xa>>ya>>xb>>yb>>a>>p>>q>>r>>side;
		//b->a->c为顺时针时side=1,反之为0
		abc=(p+q/60.0+r/3600.0)*M_PI/180.0;
		c=sqrt(pow(xb-xa,2)+pow(yb-ya,2));
		b=sqrt(a*a+c*c-2*a*c*cos(abc));
		cab=acos((b*b+c*c-a*a)/(2*b*c));
	}
	else{
		double p,q,r;
		cin>>xa>>ya>>xb>>yb>>b>>p>>q>>r>>side;
		cab=(p+q/60.0+r/3600.0)*M_PI/180.0;
		c=sqrt(pow(xb-xa,2)+pow(yb-ya,2));
	}
	side-=(!side);
	alpha_ab=atan((yb-ya)/(xb-xa));
	alpha_ac=alpha_ab+side*cab;
	xc=xa+b*cos(alpha_ac);
	yc=ya+b*sin(alpha_ac);
	cout<<xc<<' '<<yc<<endl;
	return 0;
}
*/