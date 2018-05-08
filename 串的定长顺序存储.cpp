/*
串定长顺序存储表示
*/

#include<stdio.h>
#include<stdlib.h>

#define OK 0
#define ERROR 1
#define OVERFLOW -1
#define MAXSTRLEN 255

int next[MAXSTRLEN];

// 0号单元存放串的长度
typedef unsigned char SString[MAXSTRLEN+1];
typedef int Status;

// 返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0
int Index(SString S, SString T, int pos){
	int i = pos;
	int j = 1;
	while (i <= S[0] && j <= T[0]){
		if (S[i] == T[j]){
			++i;
			++j;
		}
		else{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T[0]){
		return i - T[0];
	}
	else{
		return 0;
	}
}

// 利用模式串T的next函数求T在主串S中第pos个字符之后的位置
int Index_KMP(SString S, SString T, int pos){
	int i=pos;
	int j = 1;
	while (i <= S[0] && j <= T[0]){
		if (j == 0 || S[i] == T[j]){
			++i; 
			++j;
		}
		else{
			j = next[j];
		}
	}
	if (j > T[0]){
		return i - T[0];
	}
	else{
		return 0;
	}
}

// 求模式串T的next函数值并存入数组next
void get_next(SString T, int next[]){
	int i = 1;
	next[1] = 0;
	int j = 0;
	while (i < T[0]){
		if (j == 0 || T[i] == T[j]){
			++i;
			++j;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

// 求模式串T的next函数修正值并存入数组nextval
void get_nextval(SString T, int nextval[]){
	int i = 1;
	nextval[1] = 0;
	int j = 0;
	while (i < T[0]){
		if (j == 0 || T[i] == T[j]){
			++i;
			++j;
			if (T[i] != T[j]){
				nextval[i] = j;
			}
			else{
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}
	printf("\n");
}

int main(){

	SString S1 = "8abaabcac";
	SString S2 = "1acabaabaabcacaabc";
	S1[0] = 8;
	S2[0] = 17;
	get_next(S1, next);
	for (int i = 1; i <= S1[0]; i++){
        printf("%4d",next[i]);
	}
    printf("\n");
	if (Index_KMP(S2, S1, 1) != 0){
		printf("Success\n");
	}
	return 0;
}



  