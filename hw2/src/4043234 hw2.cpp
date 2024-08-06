//41043201 ���X�y 
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;
class Term
{
	friend istream &operator>>(istream &s, Polynomial &p); 
    friend ostream &operator<<(ostream &s, Polynomial &p); 
	friend Polynomial;
	private:
		float coef;//�Y��(�ϥ�float �������t) coefficient
		int exp;//���� exponent
};

class Polynomial
{
	friend istream &operator>>(istream &s, Polynomial &p); 
    friend ostream &operator<<(ostream &s, Polynomial &p); 
	private:
		Term *termArray;//array of nonzero terms
		int capcaity;//size of termArray(�Ŷ�)
		int terms;//number of nonozero terms
	public:
		Polynomial();//�غc�l
		Polynomial Add(Polynomial poly);//�[�k(+)
		Polynomial Mult(Polynomial poly);//���k(*)
		Polynomial Sort();//�Ƨ�
		float Eval(float x);////�̫�ƭȺ�X�Ӫ��`�M(�ϥ�float �������t) f(x)��x
		void NewTerm(const float theCoeff,const int theExp);//�W�[�Ŷ��禡
};

Polynomial::Polynomial()
{
	terms=0;
	capcaity=2;//�̪쪺�Ŷ� (��l��) 
	termArray=new Term[capcaity];
}


Polynomial Polynomial::Add(Polynomial b)//�[�k(p.91) 
{
	Polynomial c;//c��{��
	int aPos=0,bPos=0;//��m
	while((aPos<terms)&&(bPos<b.terms))
	{
		if(termArray[aPos].exp==b.termArray[bPos].exp)//�p�G����۵�
		{
			float t=termArray[aPos].coef+b.termArray[bPos].coef;//�Y�Ƭۥ[ 
			if(t) c.NewTerm(t,termArray[aPos].exp);//�s�W��c�� 
			aPos++;
			bPos++;
		}
		else if(termArray[aPos].exp<b.termArray[bPos].exp)//�p�Gb����j�A�N������Jc 
		{
			c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
			bPos++;
		}
		else//�p�Ga����j�A�N������Jc 
		{
			c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
			aPos++;
		}
		for(;aPos<terms;aPos++)//a�ѤU���ơA��Jc��{��
			c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
		for(;bPos<b.terms;bPos++)//b�ѤU���ơA��Jc��{��
			c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
		return c.Sort();//�Ƨǫ��Xc��{�� 
	}
}

Polynomial Polynomial::Mult(Polynomial b)//���k 
{
	Polynomial c;//c��{��
	float *newcoef=new float[terms*b.terms];//�إۭ߬��᪺�Y�ƪŶ� 
	int *newexp=new int[terms*b.terms];//�إ߬ۥ[�᪺����Ŷ� 
	int count=0,i,j;
	for(i=0;i<terms;i++)
	{
		for(j=0;j<b.terms;j++)
		{
			*(newcoef+count)=termArray[i].coef*b.termArray[j].coef;//�Y�Ƭۭ��s�J newcoef
			*(newexp+count)=termArray[i].exp+b.termArray[j].exp;//����ۥ[�s�J newexp
			count++;
		}
	}
	int maxexp=0;
	float sum=0;
	for(i=0;i<count;i++)
	{
		if(newexp[i]>maxexp)
			maxexp=newexp[i];//��X�̤j��exp(maxexp) 
	}
	for(i=maxexp;i>=0;i--)
	{
		for(j=0;j<count;j++)
		{
			if(i==newexp[j])
				sum+=newcoef[j];//�Y�ƥ[�� sum
		}
		c.NewTerm(sum,i);//�إ�NewTerm
		sum=0;
	}
	return c;
}

float Polynomial::Eval(float x)//f(x)
{
	float sum=0;
	int i;
	for(i=0;i<terms;i++)
	{
		sum+=pow(x,termArray[i].exp)*termArray[i].coef;//pow�a�Jf(x) 
	}
	return sum;
}


void Polynomial::NewTerm(const float theCoeff,const int theExp)//��Ŷ������A�h�ݼW�[�Ŷ�(p.92)
{
	if(terms==capcaity)
	{
		capcaity *=2;
		Term *temp=new Term[capcaity];//temp�s�J�s�Ŷ� 
		copy(termArray,termArray+terms,temp);//termArray�� termArray+terms,copy��temp 
		delete[]termArray;//�R��termArray�Ŷ� 
		termArray=temp;//temp���N termArray
	}
	if(theCoeff!=0)//�d���᭱���l��0 
	{
		termArray[terms].coef=theCoeff;
		termArray[terms++].exp=theExp;
	}
}

Polynomial Polynomial::Sort()//�Ƨ� 
{
	Polynomial temp;
	int maxexp=0,i,j;
	for(i=0;i<terms;i++)
	{
		if(termArray[i].exp>maxexp)
			maxexp=termArray[i].exp;//��X�̤j��exp(maxexp) 
	}
	int sum=0;
	for(i=maxexp;i>=0;i--)
	{
		for(j=0;j<terms;j++)
		{
			if(i==termArray[j].exp)
				sum+=termArray[j].coef;//�Y�ƥ[�� sum
		}
		temp.NewTerm(sum,i);//�إ�NewTerm
		sum=0;
	}
	return temp;
}

istream &operator>>(istream &s, Polynomial &p)//��J������ 
{
	int termterm,i;
	float coefcoef,expexp;
	cout<<"�п�J�X���h�����G";
	cin>>termterm;

	for(i=1;i<termterm+1;i++)//���ϥΪ̪��D�ثe��J����r�O�ݩ󦸤��٬O�Y�� 
	{
		cout<<i<<".�Y�ơG";
		cin>>coefcoef;
		cout<<i<<".����G";
		cin>>expexp;
		p.NewTerm(coefcoef,expexp);
	}
	cout<<"-----------------------------------"<<endl;
	return s;
}

ostream &operator<<(ostream &s, Polynomial &p)//��X������ 
{
	int i;
	for(i=0;i<p.terms;i++)
	{
		if(i>0)
		{
			if(p.termArray[i].coef>=0)
				cout<<"+";//���C�@���᭱�[�W"+"���Ÿ�(�̫�@�Ӥ��[) 
		}
		if(p.termArray[i].exp==0)
			cout<<p.termArray[i].coef;//�p�G0���誺�ܤ���X"X^" 
		else
			cout<<p.termArray[i].coef<<"X^"<<p.termArray[i].exp;//���C�@���᭱�[�W"X^"
	}
	cout<<endl;
	return s;
}

int main()
{
	int number; 
	Polynomial A,B,add,sub,mult;
	cout<<"�п�JA�h�����G"<<endl; 
	cin>>A;
	cout<<"�п�JB�h�����G"<<endl; 
	cin>>B;
	cout<<"��ܹB��l�G"<<endl;
	cout<<"(1)A,B�h����\n(2)�[�k+\n(3)���k*\n(4)f(x)\n(5)���}\n->"; 
	while(cin>>number)
	{
		cout<<"-----------------------------------"<<endl;
		switch(number)
		{
			case 1:
				cout<<"A�h����:"<<A;
				cout<<"B�h����:"<<B;
				cout<<"-----------------------------------"<<endl;
				break;
			case 2:
				add=A.Add(B);
				cout<<"A+B="<<add;
				cout<<"-----------------------------------"<<endl;
				break;
			case 3:
				mult=A.Mult(B);
				cout<<"A*B="<<mult;
				cout<<"-----------------------------------"<<endl;
				break;
			case 4:
				float x;
				cout<<"x=";
				cin>>x;
				cout<<"A("<<x<<")="<<A.Eval(x)<<endl;
				cout<<"B("<<x<<")="<<B.Eval(x)<<endl;
				cout<<"-----------------------------------"<<endl;
				break;
			case 5:
				return 0;
		}
		cout<<"��ܹB��l�G"<<endl;
		cout<<"(1)A,B�h����\n(2)�[�k+\n(3)���k*\n(4)f(x)\n(5)���}\n->"; 
	}
}
