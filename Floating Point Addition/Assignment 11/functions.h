#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<bits/stdc++.h>
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
using namespace std;

void swap(string &s1, string &s2)
{
	string temp = s1;
	s1 = s2;
	s2 = temp;
}

void swap(char &ch1, char &ch2)
{
	char temp = ch1;
	ch1 = ch2;
	ch2 = temp;
}

void swap(int *a, int *b)
{
	int* temp = a;
	a = b;
	b = temp;
}

void shift1(int diff, string &significand2)
{
	if(diff < 0)
	{
		cout<<"IMPOSSIBLE\n\n";
		exit(1);
	}
	if(diff == 0)
		return;
	
	string fs2 = "0.";
	FOR(i, diff-1)
		fs2 += '0';
	//removing point
	significand2.erase(significand2.begin()+1);
	significand2 = fs2+significand2;
}

pair<string, string> parsePoint(string &str)
{
	string ret1 = "";
	string ret2 = "";
	bool done = false;
	for(int i=0; i<str.length(); i++)
	{
		if(str[i] == '.')
		{
			done = true;
			continue;
		}
		if(done)
		{
			ret2 += str[i];
		}
		else ret1 += str[i];
	}
	pair<string, string> ret;
	ret.first = ret1;
	ret.second = ret2;
	return ret;
}


pair<string, int> decimalSub(string s1, string s2)
{
	int diff = s2.length()-s1.length();
	for(int i=0; i<diff; i++)
		s1 = s1+'0';

	int carry = 0;
	vector<char> v;
	for(int i=s1.size()-1; i>=0; i--)
	{
		if(s1[i] == '0' && s2[i] == '0')
		{
			if(carry == 0)
				v.push_back('0');
			else
			{
				v.push_back('1');
				carry = 1;
			}
			continue;
		}
		if(s1[i] == '1' && s2[i] == '0')
		{
			if(carry==0)
			{
				v.push_back('1');
			}
			else
			{
				v.push_back('0');
				carry = 0;
			}
			continue;
		}
		if(s1[i] == '0' && s2[i] == '1')
		{
			if(carry == 0)
			{
				v.push_back('1');
				carry = 1;
			}
			else
			{
				v.push_back('0');
			}
			continue;
		}

		if(s1[i] == '1' && s2[i] == '1')
		{
			if(carry == 0)
				v.push_back('0');
			else
			{
				carry = 1;
				v.push_back('1');
			}
			continue;
		}
	}

	string postPoint = "";
	for(int i=v.size()-1; i>=0; i--)
		postPoint += v[i];
	pair<string, int> ret = {postPoint, carry};
	return ret;
}
pair<string, int> decimalAdd(string s1, string s2) //postPoint string and carry
{

	int diff = s2.length() - s1.length();
	for(int i=0; i<diff; i++)
	{
		s1 = s1 + '0';
	}
	int carry = 0;
	vector<char> v;
	for(int i=s1.size()-1; i>=0; i--)
	{
		if(s1[i] == '0' && s2[i] == '0')
		{
			if(carry == 0)
				v.push_back('0');
			else{
				v.push_back('1');
				carry = 0;
			}
			continue;
		} 
		if(s1[i] == '0' && s2[i] == '1')
		{
			if(carry == 0)
				v.push_back('1');
			else v.push_back('0');
			continue;
		}
		if(s2[i] == '0' && s1[i] == '1')
		{
			if(carry == 0)
				v.push_back('1');
			else v.push_back('0');
			continue;
		}
		if(s1[i] == '1' && s2[i] == '1')
		{
			if(carry == 0)
			{
				v.push_back('0');
				carry = 1;
			}
			else
			{
				v.push_back('1');
			}
		}
	}

	string postPoint = "";
	for(int i=v.size()-1; i>=0; i--)
		postPoint += v[i];
	pair<string, int> ret = {postPoint, carry};
	return ret;
}

pair<string, int> add(string str1, string str2)
{
	pair<string, string> p1 = parsePoint(str1); 
	pair<string, string> p2 = parsePoint(str2); 
	pair<string, int> p3 = decimalAdd(p1.S, p2.S);
	string postPoint = p3.first;
	int carry = p3.second;
	char ch1 = p1.first[0];
	char ch2 = p2.first[0];

	string prePoint = "";
	if(ch1 == '0')
	{
		if(ch2 == '0')
		{
			if(carry == 1)
				prePoint = "1";
			else prePoint = "0";		
		}
		else 
		{
			if(carry == 1)
				prePoint = "10";
			else prePoint = "1";		
		}	
	}
	if(ch1=='1')
	{
		if(ch2 == '0')
		{
			if(carry == 0)
				prePoint = "1";
			else
				prePoint = "10";
		}
		else
		{
			if(carry==0)
				prePoint = "10";
			else prePoint = "11";
		}
	}
	string ret = prePoint;
	ret = ret + ".";
	ret = ret + postPoint;
	pair<string, int> retp = {ret, 0};
	//cout<<ret<<endl;
	return retp;
}
pair<string, int> sub(string str1, string str2) //second 0 mtlb positive
{
	pair<string, string> p1 = parsePoint(str1);
	pair<string, string> p2 = parsePoint(str2);
	if(str1 == str2)
	{
		string r1 = "0.00000000000000000000000";
		pair<string, int> p = {r1, 0};
		return p;
	}
	if(p1.first[0] < p2.first[0])
	{
		pair<string, int> ret = sub(str2, str1);
		ret.second = 1;
		return ret;
	}
	if(p1.first[0] == p2.first[0])
	{
		for(int i=0; i<p1.second.length(); i++)
		{
				if(p1.second[i] == p2.second[i])
				{
					continue;
				}
				else
				{
					if(p1.second[i] == '1')
					{
						break;
					}
					else {	
						pair<string, int> ret = sub(str2, str1);
						ret.second = 1;
						return ret;
					}
				}
			}
	}
		pair<string, int> p3 = decimalSub(p1.second, p2.second);
		string postPoint = p3.first;
		int carry = p3.second;
		char ch1 = p1.first[0];
		char ch2 = p2.first[0];
		string prePoint = "";

		if(carry == 1 && ch1 == '0')
		{
			cout<<"IMPOSSIBLE2\n";
			exit(1);	
		}
		if(carry == 1 && ch1 == '1')
		{
			if(ch2 == '0')
			{
				prePoint = "0";
			}
			else
			{
				cout<<"IMPOSSIBLE3\n";
				exit(1);		
			}
		}
		else {
			if(ch1 == '0' && ch2 == '0')
				prePoint = "0";
			else if(ch1 == '1' && ch2 == '1')
				prePoint = "0";
			else if(ch1 == '1' && ch2 == '0')
				prePoint = "1";
		}
		string ret = prePoint;
		ret = ret + ".";
		ret = ret + postPoint;
		//cout<<"Result without normalize : "<<ret<<endl;
		pair<string, int> retp = {ret, 0};
		return retp;
}

bool normalizationtotal(string &str, int &exp1)
{
	int firstOne=-1;
	int firstPoint=-1;
	for(int i=str.size()-1; i>=0; i--)
	{
		if(str[i] == '1')
			firstOne = i;
		else if(str[i] == '.')
			firstPoint = i;
	}
	if(firstOne == -1)
	{
		return false;
	}
	if(firstOne > firstPoint) //left shift and decrement of exponent
	{
		// cout<<"firtOne : "<<firstOne<<endl;
		// cout<<"firstPoint : "<<firstPoint<<endl;
		exp1 = exp1-(firstOne-1);
		str.erase(str.begin()+0, str.begin()+firstOne);
		str.insert(1, ".");
		return true;
	}
	else //right shift and increment of exponent
	{
		if(str[0] == '0')
		{
			str.erase(0, 1);
		}
		if(str[1] == '.')
		{
			return true;
		}

		if(str[2] == '.')
		{
			str.erase(2, 1);
			str.insert(1, ".");
			exp1++;
			return true;
		}

		cout<<"IMPOSSIBLE normalization\n";
		exit(1);
	}
}

void rounding(string &str, int exp1)
{
	int pointIndex = -1;
	for(int i=0; i<str.size(); i++)
	{
		if(str[i] == '.')
		{
			pointIndex = i;
			break;
		}
	}
	int fracSize = str.size()-pointIndex-1;
	if(fracSize == 23)
	{
		return;
	}
	if(fracSize < 23)
	{
		int reqzeros = 23 - fracSize;
		for(int i=0; i<reqzeros; i++)
			str = str + '0';
	}
	if(fracSize > 23)
	{
		if(str[pointIndex+24] == '0')
		{
			str.erase(pointIndex+24);
			return;
		}
		if(str[pointIndex+24] == '1')
		{
			str.erase(pointIndex+24);
			int carry = 1;
			for(int i=str.size()-1; i>=0; i--)
			{
				if(str[i] == '0')
				{
					str[i] = '1';
					return;
				}
				else if(str[i] == '1')
				{
					str[i] = '0';
				}
				else if(str[i] == '.')
				{
					continue;
				}
			}
			if(carry == 1)
			{
				str.insert(0, "1");
				return;
			}
		}
	}
}

bool isNormalize(string &str)
{
	if(str[0] == '1' && str[1] == '.')
	{
		return true;
	}
	return false;
}

string toBinary(int a)
{
	string ret = "00000000";
	int i=7;
	while(a>0)
	{
		int rem = a%2;
		if(rem==1)
			ret[i] = '1';
		else ret[i] = '0';
		a = a/2;
		i--;
	}
	return ret;
}
#endif
