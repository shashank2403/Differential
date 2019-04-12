#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<ctype.h>
class term
{
 int coeff;
 int pow;
 public:
 void tremy (char term[30]);
};
class exp
{
 char equation[30];
 int termno;
 term oreo[25];
 public:
 exp(char eq[30])
 {
  strcpy(equation,eq);
 }

};

 void foo::tremy(char term[30])
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
 }
};
void main()
{
 clrscr();
 char eq[30];
 cout<<"Enter: ";
 gets(eq);
 getch();
}


