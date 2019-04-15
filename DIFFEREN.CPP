#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>

class term
{
 char ti[10];
 int coeff;
 int pow;
 public:
 void assign(char eq[30], int L, int U);
 int ret()
 {
  return coeff;
 }
};

class exp
{
 char equation[30];
 int termno;
 term oreo[25];
 public:
 exp(char eq[30]);
 void output()
 {
  for (int i = 0; i<2; i++)
   cout<<oreo[i].ret()<<endl;
 }
};
 exp::exp(char eq[30])
 {
  strcpy(equation,eq);

  int c = 0;
  for (int i =0; equation[i]!='\0'; i++)
   if (equation[i] == '+' || equation [i] == '-')
    c++;
  termno=c+1;
  int b = 0, t = 0;

  for (i = 0; equation[i]!='\0'; i++)
   if (equation[i]=='+' || equation[i]=='-')
    oreo[t++].assign(equation, b, i);
 }
/*void term::termy(char term[30])
{
 char c = '1';
 int chk=1;
 coeff=0;
 pow=0;
 for (int i = 0; term[i]!='+' && term[i] != '-';i++)
 {
  if(term[i]=='x')
  {
   chk=0;
   i+=2;
  }
  if(chk==1)
  {
    coeff*=10;
    coeff+=term[i]-'0';
  }
  else if(chk==0)
  {
    pow*=10;
    pow+=term[i]-'0';
  }
 }
 for (int j = 0; j<i; j++)
  term[j] = term[j+i];
}; */
void term::assign(char eq[30], int L, int U)
{
 for (int i=0; i<U-L+1; i++)
  ti[i]=eq[i+L];
 ti[i]='\0';
 int chk_coeff=1;
 for (i=0;ti[i]!='\0' && chk_coeff;i++)
  if (!isdigit(ti[i]))
   chk_coeff=0;
 i--;
 if (i==0)
  coeff=1;
 else
 {
  int c=0;
  for (int j = i; j>=0; j--)
  {
   c*=10;
   c+=int(ti[j])-'0';
  }
  coeff=c;
 }
 int p=0;

 for(i=U-L;i>=0&&ti[i-1]!='^';i--)
 {
  p*=10;
  p+=int(ti[i])-'0';
 }
 if (i<0)
  pow=1;
 else pow=p;
}

void main()
{
 clrscr();
 char eq[30];
 cout<<"Enter: ";
 gets(eq);
 exp equation(eq);
 equation.output();
 getch();
}


