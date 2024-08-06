//41043201 黃柔語 
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
		float coef;//係數(使用float 有正有負) coefficient
		int exp;//次方 exponent
};

class Polynomial
{
	friend istream &operator>>(istream &s, Polynomial &p); 
    friend ostream &operator<<(ostream &s, Polynomial &p); 
	private:
		Term *termArray;//array of nonzero terms
		int capcaity;//size of termArray(空間)
		int terms;//number of nonozero terms
	public:
		Polynomial();//建構子
		Polynomial Add(Polynomial poly);//加法(+)
		Polynomial Mult(Polynomial poly);//乘法(*)
		Polynomial Sort();//排序
		float Eval(float x);////最後數值算出來的總和(使用float 有正有負) f(x)的x
		void NewTerm(const float theCoeff,const int theExp);//增加空間函式
};

Polynomial::Polynomial()
{
	terms=0;
	capcaity=2;//最初的空間 (初始化) 
	termArray=new Term[capcaity];
}


Polynomial Polynomial::Add(Polynomial b)//加法(p.91) 
{
	Polynomial c;//c方程式
	int aPos=0,bPos=0;//位置
	while((aPos<terms)&&(bPos<b.terms))
	{
		if(termArray[aPos].exp==b.termArray[bPos].exp)//如果次方相等
		{
			float t=termArray[aPos].coef+b.termArray[bPos].coef;//係數相加 
			if(t) c.NewTerm(t,termArray[aPos].exp);//新增至c裡 
			aPos++;
			bPos++;
		}
		else if(termArray[aPos].exp<b.termArray[bPos].exp)//如果b次方大，將此項丟入c 
		{
			c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
			bPos++;
		}
		else//如果a次方大，將此項丟入c 
		{
			c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
			aPos++;
		}
		for(;aPos<terms;aPos++)//a剩下的數，丟入c方程式
			c.NewTerm(termArray[aPos].coef,termArray[aPos].exp);
		for(;bPos<b.terms;bPos++)//b剩下的數，丟入c方程式
			c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
		return c.Sort();//排序後輸出c方程式 
	}
}

Polynomial Polynomial::Mult(Polynomial b)//乘法 
{
	Polynomial c;//c方程式
	float *newcoef=new float[terms*b.terms];//建立相乘後的係數空間 
	int *newexp=new int[terms*b.terms];//建立相加後的次方空間 
	int count=0,i,j;
	for(i=0;i<terms;i++)
	{
		for(j=0;j<b.terms;j++)
		{
			*(newcoef+count)=termArray[i].coef*b.termArray[j].coef;//係數相乘存入 newcoef
			*(newexp+count)=termArray[i].exp+b.termArray[j].exp;//次方相加存入 newexp
			count++;
		}
	}
	int maxexp=0;
	float sum=0;
	for(i=0;i<count;i++)
	{
		if(newexp[i]>maxexp)
			maxexp=newexp[i];//找出最大的exp(maxexp) 
	}
	for(i=maxexp;i>=0;i--)
	{
		for(j=0;j<count;j++)
		{
			if(i==newexp[j])
				sum+=newcoef[j];//係數加至 sum
		}
		c.NewTerm(sum,i);//建立NewTerm
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
		sum+=pow(x,termArray[i].exp)*termArray[i].coef;//pow帶入f(x) 
	}
	return sum;
}


void Polynomial::NewTerm(const float theCoeff,const int theExp)//當空間不夠，則需增加空間(p.92)
{
	if(terms==capcaity)
	{
		capcaity *=2;
		Term *temp=new Term[capcaity];//temp存入新空間 
		copy(termArray,termArray+terms,temp);//termArray至 termArray+terms,copy至temp 
		delete[]termArray;//刪除termArray空間 
		termArray=temp;//temp取代 termArray
	}
	if(theCoeff!=0)//削掉後面式子的0 
	{
		termArray[terms].coef=theCoeff;
		termArray[terms++].exp=theExp;
	}
}

Polynomial Polynomial::Sort()//排序 
{
	Polynomial temp;
	int maxexp=0,i,j;
	for(i=0;i<terms;i++)
	{
		if(termArray[i].exp>maxexp)
			maxexp=termArray[i].exp;//找出最大的exp(maxexp) 
	}
	int sum=0;
	for(i=maxexp;i>=0;i--)
	{
		for(j=0;j<terms;j++)
		{
			if(i==termArray[j].exp)
				sum+=termArray[j].coef;//係數加至 sum
		}
		temp.NewTerm(sum,i);//建立NewTerm
		sum=0;
	}
	return temp;
}

istream &operator>>(istream &s, Polynomial &p)//輸入的部分 
{
	int termterm,i;
	float coefcoef,expexp;
	cout<<"請輸入幾項多項式：";
	cin>>termterm;

	for(i=1;i<termterm+1;i++)//讓使用者知道目前輸入的文字是屬於次方還是係數 
	{
		cout<<i<<".係數：";
		cin>>coefcoef;
		cout<<i<<".次方：";
		cin>>expexp;
		p.NewTerm(coefcoef,expexp);
	}
	cout<<"-----------------------------------"<<endl;
	return s;
}

ostream &operator<<(ostream &s, Polynomial &p)//輸出的部分 
{
	int i;
	for(i=0;i<p.terms;i++)
	{
		if(i>0)
		{
			if(p.termArray[i].coef>=0)
				cout<<"+";//讓每一項後面加上"+"的符號(最後一個不加) 
		}
		if(p.termArray[i].exp==0)
			cout<<p.termArray[i].coef;//如果0次方的話不輸出"X^" 
		else
			cout<<p.termArray[i].coef<<"X^"<<p.termArray[i].exp;//讓每一項後面加上"X^"
	}
	cout<<endl;
	return s;
}

int main()
{
	int number; 
	Polynomial A,B,add,sub,mult;
	cout<<"請輸入A多項式："<<endl; 
	cin>>A;
	cout<<"請輸入B多項式："<<endl; 
	cin>>B;
	cout<<"選擇運算子："<<endl;
	cout<<"(1)A,B多項式\n(2)加法+\n(3)乘法*\n(4)f(x)\n(5)離開\n->"; 
	while(cin>>number)
	{
		cout<<"-----------------------------------"<<endl;
		switch(number)
		{
			case 1:
				cout<<"A多項式:"<<A;
				cout<<"B多項式:"<<B;
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
		cout<<"選擇運算子："<<endl;
		cout<<"(1)A,B多項式\n(2)加法+\n(3)乘法*\n(4)f(x)\n(5)離開\n->"; 
	}
}
