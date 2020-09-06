#include<bits/stdc++.h>
#include <fstream>
#define ll long long
#define  vi vector<int>
#define vvi vector<vector<int>>
#define si set<int>
#define pb push_back
//#define int long long
#define boost ios_base::sync_with_stdio(false);	cin.tie(0);	cout.tie(0)
#define pi pair<int,int>
#define F first
#define S second
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORE(i, m, n) for(int i=m; i<=n; i++)
#define endl '\n'
#include "functions.h"
using namespace std;
ll max(ll a, ll b) {if(a<b) return b; else return a;}
ll min(ll a, ll b) {if(a<b) return a; else return b;}
//int mod=(int)(1e9+7);

void solve()
{   
	string str1;
	string str2;
	cin>>str1>>str2;
	fstream out;
	out.open("output.txt", ios::in | ios::out | ios::app);
	if(str1.size() != 32)
	{
		out<<"Input1 is not 32-bit long\n";
		out<<"Total cycles : "<<0<<endl;
		return;
	}
	if(str2.size() != 32)
	{
		out<<"Input2 is not 32-bit long\n";
		out<<"Total cycles : "<<0<<endl;
		return;
	}

	// FILE *fp;
	// fp = fopen("output.txt", "a");
	// cout<<"str1 is : "<<str1<<endl;
	// cout<<"str2 is : "<<str2<<endl;
	char s1 = str1[0];
	char s2 = str2[0];
	string expstr1 = str1.substr(1, 8);
	string expstr2 = str2.substr(1, 8);
	string frac1 = str1.substr(9, 23);
	string frac2 = str2.substr(9, 23);
	int cycles=0;
	string significand1 = "1."+frac1;
	string significand2 = "1."+frac2;

	//WE WILL TAKE str1 WITH LARGER EXPONENT AND str2 WITH LESSER EXPONENT
		////INPUT DONE/////
	// str1 has larger exponent and str2 has lesser exponent
	
/////////////PHASE 1/////////////////
	cycles++;
	int exp1 = stoi(expstr1, 0, 2);
	// cout<<exp1<<endl;
	int exp2 = stoi(expstr2, 0, 2);
	if(exp1 == 0)
	{
		significand1[0] = '0';
		exp1 = 1;
	}
	if(exp2 == 0)
	{
		significand2[0] = '0';
		exp2 = 1;
	}
	if(exp1 == 255 || exp2 == 255)
	{
		out<<"Exception : infinity or NaN\n";
		out<<"cycles : "<<cycles<<endl;
		return;
	}
	//CHECKING FOR VALIDANCE
	// if(expstr1 == "11111111" || expstr1 == "00000000")
	// {
	// 	out<<"Value of number 1 is ";
	// 	if(frac1 == "00000000000000000000000")
	// 	{
	// 		if(s1 == '0')
	// 			out<<"+";
	// 		else out<<"-";
	// 		out<<"infinite.\n";
	// 	}
	// 	else out<<"NaN\n";
	// 	out<<"Total cycles : "<<cycles<<endl;
	// 	return;
	// }
	// if(expstr2 == "11111111" || expstr2 == "00000000")
	// {
	// 	out<<"Value of number 2 is ";
	// 	if(frac2 == "00000000000000000000000")
	// 	{
	// 		if(s2 == '0')
	// 			out<<"+";
	// 		else out<<"-";
	// 		out<<"infinite.\n";
	// 	}
	// 	else out<<"NaN\n";
	// 	out<<"Total cycles : "<<cycles<<endl;
	// 	return;
	// }

	// cout<<exp2<<endl;
	if(exp1 < exp2)
	{
		swap(str1, str2);
		swap(s1, s2);
		swap(expstr1, expstr2);
		swap(frac1, frac2);
		swap(exp1, exp2);
		swap(significand1, significand2);
	}
	shift1((exp1-exp2), significand2);
	// cout<<"significand1 : "<<significand1<<endl;
	// cout<<"significand2 : "<<significand2<<endl;
///////////PHASE 1 COMPLETE//////////

//////////PHASE 2///////////////////
	cycles++;
	pair<string, int> resultant;
	int ressign; //1 for - and 0 for +
	if(s1==s2)
	{
		// cout<<"Addition\n";
		resultant = add(significand1, significand2);
		if(s1=='1')
			ressign = 1;
		else ressign = 0;
	}
	else {
		// cout<<"substraction\n";
		resultant = sub(significand1, significand2);
		if((s1 == '0' && resultant.second == 0)||(s1 == '1' && resultant.second == 1))
			ressign = 0;
		if((s1 == '1' && resultant.second == 0)||(s1 == '0' && resultant.second == 1))
			ressign = 1;
	}
/////////PHASE 2 COMPLETE//////////////

//////////PHASE 3///////////////////
	//final sign fixed = ressign
	//final value fixed = resultant.second
	bool isNormal= false;
	while(!isNormal)
	{
		bool temp = normalizationtotal(resultant.first, exp1); cycles++;
		if(temp == false)
		{
			out<<"00000000000000000000000000000000\n";
			out<<"Total cycles : "<<cycles<<endl;
			return;
		}
		// bool flow = checkflow(exp1);
		if(exp1 >254)
		{
			out<<"Error : OVERFLOW\n";
			out<<"Total cycles : "<<cycles<<endl;
			return;
		}
		if(exp1<1)
		{
			out<<"Error : UNDERFLOW\n";
			out<<"Total cycles : "<<cycles<<endl;
			return;
		}
		rounding(resultant.first, exp1); cycles++;
		isNormal = isNormalize(resultant.first);
	}
	string finalBinary = "";
	if(ressign == 0)
		finalBinary = "0";
	else finalBinary = "1";

	string exponent = toBinary(exp1);
	finalBinary += exponent;
	finalBinary += resultant.first.substr(2, 23);
	// cout<<"\n\nFINAL RESULT IS : ";
	out<<finalBinary<<endl;
	out<<"TOTAL cycles : "<<cycles<<endl;
}
 
signed main()
{ 
	// boost;
 //cout<<fixed<<setprecision(14 );
  int t;cin>>t;
  ofstream outf;
  outf.open("output.txt");
  outf<<"";
  outf.close();
  for(int i=1;i<=t;i++)
  	solve();
 // cout<<"Case #"<<i<<": "<<solve()<<endl;
 
return 0;
}