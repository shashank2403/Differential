#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<stdio.h>
#include<ctype.h>
using namespace std;

class term
{
	char ti[10];
	int coeff;
	int pow;
public:
	void assign(char[30], int , int);
	int getcoeff()
	{
		return coeff;
	}
	int getpow()
	{
		return pow;
	}
	void getterm(char t[10])
	{
		int i;
		for (i = 0;ti[i] != '\0';i++)
			t[i] = ti[i];
		t[i] = '\0';
	}
	void setcoeff(int k)
	{
		coeff = k;
	}
	void setpow(int k)
	{
		pow = k;
	}
	void setterm()
	{
		_itoa_s(coeff,ti, 10);
		if (coeff < 0)
		{
			for (int i = strlen(ti) - 1;i > 0;i++)
				ti[i] = ti[i - 1];
			ti[0] == '-';
		}
		if (pow)
			strcat_s(ti, "x");
		if (pow > 1)
		{
			strcat_s(ti, "^");
			char p[5];
			_itoa_s(pow, p, 10);
			strcat_s(ti, p);
		}
	}
};
class expression
{
	char equation[30];
	int termno;
	term terms[25];
public:
	expression(char[30]);	
	expression(expression&);
	void output();
	int gettermno()
	{
		return termno;
	}
	int getcoeff(int i)
	{
		return terms[i].getcoeff();
	}
	int getpow(int i)
	{
		return terms[i].getpow();
	}
	void setcoeff(int i, int k)
	{
		terms[i].setcoeff(k);
	}
	void setpow(int i, int k)
	{
		terms[i].setpow(k);
	}
};

int main()
{
	system("CLS");
	char eq[30];
	cout << "Enter: ";
	cin >> eq;
	expression equation(eq);
	expression derivative(equation);
	derivative.output();
	cin.get();
	cin.get();
	return 0;
}

void term::assign(char eq[30], int L, int U)
{
	int len = U - L;
	int i;
	for (i = 0; i < len; i++)
		ti[i] = eq[i + L];
	ti[i] = '\0';
	int chk_coeff = 1;
	for (i = 1;ti[i] != '\0' && chk_coeff;i++)
		if (!isdigit(ti[i]))
			chk_coeff = 0;
	i--;
	if (i == 1)		
			coeff = 1;
	else
	{
		coeff = 0;
		for (int j = i-1; j > 0; j--)
			coeff = ((int(ti[j])-'0')*10);
		if (ti[0] == '-')
			coeff *= -1;		
	}
	int cons = 1;
	for (i=0;i<len && cons;i++)
		if (ti[i]=='x')
			cons = 0;
	if (cons)
	{
		coeff = 0;
		for (i = len - 1;i > 0;i--)
			coeff = (coeff*10)+(int(ti[i])-'0');
		if (ti[0] == '-')
			coeff *= -1;
	}
	pow = 0;
	if (!chk_coeff)
	{
		if (isdigit(ti[len - 1]))
			for (i = len - 1;i > 0 && ti[i] != '^';i--)
				pow = (pow*10)+(int(ti[i])-'0');
		else
			pow = 1;
	}
}

expression::expression(char eq[30])
{
	strcpy_s(equation, eq);
	int i;
	termno = 0;
	for (i = 0; equation[i] != '\0'; i++)
		if (equation[i] == '+' || equation[i] == '-')
			termno++;
	int L = 0, t_idx = 0;
	strcat_s(equation, "+");

	for (i = 0; equation[i] != '\0'; i++)
		if (equation[i] == '+' || equation[i] == '-')
		{
			if (i!=0)
				terms[t_idx++].assign(equation, L, i);
			L = i;
		}
	//terms[t_idx].assign(equation, L, strlen(equation),1);
	for (i = 0;equation[i] != '\0';i++);
	equation[i - 1] = '\0';
}

expression::expression(expression &equation)
{
	termno = 0;
	int i;
	for (i = 0;i < equation.gettermno();i++)
	{
		int c, p;
		if (equation.getpow(i))
		{
			int p_ = equation.getcoeff(i);
			p_ = equation.getpow(i);
			c = equation.getcoeff(i)*equation.getpow(i);
			p = equation.getpow(i) - 1;
		}
		else
		{
			c = 0;
			p = 0;
		}
		terms[termno].setcoeff(c);
		terms[termno].setpow(p);
		if (c)
			terms[termno++].setterm();
	}
}

void expression::output()
{
	for (int i = 0;i < termno;i++)
	{
		char term[10];
		terms[i].getterm(term);
		cout << term;
	}
}