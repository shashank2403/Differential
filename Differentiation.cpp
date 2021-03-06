#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<stdio.h>
#include<ctype.h>
using namespace std;

int extract(char[], int, int);

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
		_itoa_s(coeff, ti, 10);
		int len = strlen(ti);		
		if (coeff > 0)
		{
			for (int i = len;i > 0;i--)
				ti[i] = ti[i - 1];
			ti[0] = '+';
		}
		ti[len+1] = '\0';
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
	cout << "Enter the polynomial expression: ";
	cin >> eq;
	expression equation(eq);
	expression derivative(equation);
	derivative.output();
	cin.get();
	cin.get();
	return 0;
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
	cout << "Derivative of the expression = ";
	if (termno == 0)
		cout << 0;
	else
		for (int i = 0;i < termno;i++)
		{
			char term[10];
			terms[i].getterm(term);
			cout << term;
		}
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
		coeff = extract(ti, 1, i - 1);
		if (ti[0] == '-')
			coeff *= -1;
	}
	int cons = 1;
	for (i = 0;i<len && cons;i++)
		if (ti[i] == 'x')
			cons = 0;
	if (cons)
	{
		coeff = extract(ti, 1, len - 1);
		if (ti[0] == '-')
			coeff *= -1;
	}
	pow = 0;
	if (!chk_coeff)
	{
		if (isdigit(ti[len - 1]))
		{
			for (i = len - 1;i > 0 && ti[i] != '^';i--);
			for (int j = i + 1;j < len;j++)
				pow = (pow * 10) + (int(ti[j]) - '0');
		}
		else
			pow = 1;
	}
}

int extract(char eq[], int L, int U)
{
	int R = 0;
	for (int i = L;i <= U;i++)
	{
		R *= 10;
		R += int(eq[i]) - '0';
	}
	return R;
}