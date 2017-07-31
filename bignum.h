#include<stdlib.h>
class BIG_NUM{
	static int length;
	char num[500];
protected:
	int head_addr(char*);
	BIG_NUM shift();
	BIG_NUM shift(int);
	bool bigger(BIG_NUM&);
public:
	BIG_NUM();
	BIG_NUM(char*);
	BIG_NUM(const BIG_NUM&);
	BIG_NUM operator+(BIG_NUM);
	BIG_NUM operator-(BIG_NUM);
	BIG_NUM operator*(BIG_NUM);
	BIG_NUM operator/(BIG_NUM);
	BIG_NUM operator%(BIG_NUM);
	void print();
};
int BIG_NUM::length=500;
BIG_NUM::BIG_NUM(){
	for(int i=0;i<length;i++)
		num[i]='0';
}
BIG_NUM::BIG_NUM(char* input){
	int len=length-strlen(input);
	for(int i=0;i<len;i++)
		num[i]='0';
	for(int i=len;i<length;i++)
		num[i]=input[i-len];
}
BIG_NUM::BIG_NUM(const BIG_NUM& input){
	for(int i=0;i<length;i++)
		num[i]=input.num[i];
}
BIG_NUM BIG_NUM::operator+(BIG_NUM a){
	int c=0;
	for(int i=length-1;i>=0;i--){
		a.num[i]=num[i]+a.num[i]+c-'0';
		c=0;
		if(a.num[i]>'9'){
			a.num[i]-=10;
			c=1;
		}
	}
	return a;
}
BIG_NUM BIG_NUM::operator-(BIG_NUM a){
	int c=0;
	if(this->bigger(a)){
		for(int i=length-1;i>=0;i--){
			a.num[i]=num[i]-a.num[i]-c+'0';
			c=0;
			if(a.num[i]<'0'){
				a.num[i]+=10;
				c=1;
			}
		}
		return a;
	}else{
		a=a-(*this);
		a.num[head_addr(a.num)-1]='-';
		return a;
	}
}
void BIG_NUM::print(){
	for(int i=head_addr(num);i<length;i++)
		printf("%c",num[i]);
	printf("\n");
}



int BIG_NUM::head_addr(char* num){
	int temp=0;
	for(int i=0;i<length-1;i++){
		if(num[i]!='0')
			break;
		temp++;
	}
	return temp;
}
BIG_NUM BIG_NUM::shift(){
	BIG_NUM temp;
	int addr=head_addr(num);
	for(int i=addr;i<length;i++)
		temp.num[i-addr]=num[i];
	return temp;
}
BIG_NUM BIG_NUM::shift(int x){
	BIG_NUM temp;
	int addr=head_addr(num);
	for(int i=addr;i<length;i++)
		temp.num[i-x]=num[i];
	return temp;
}
bool BIG_NUM::bigger(BIG_NUM& a){
	int t_addr=head_addr(num);
	int a_addr=head_addr(a.num);
	if(t_addr>a_addr)
		return false;
	if(num[t_addr]<a.num[t_addr])
		return false;
	else
		return true;
}
