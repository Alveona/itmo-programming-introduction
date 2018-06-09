#include<stdio.h>
#include<string.h>
#include<math.h>
#define printsf(s) printf("%s", s);
#define printcf(c) printf("%c", c);
#define printff(f) printf("%.1f", f);
#define endl() printf("\n");
//#define DEBUG
typedef unsigned int uint;
int isDigit(char tmp)
{
	return (tmp >= '0' && tmp <= '9') ? 1 : 0;
}
void stPush_c(char *stack_op, char c, int *st_op)
{
	(*st_op)++;
	stack_op[*st_op] = c;	
}
void stPop_c(char *stack_op, int *st_op)
{
	stack_op[*st_op] = 0;
	(*st_op)--;		
}
void stPush_f(float *stack_out, float f, int *st_out)
{
	(*st_out)++;
	stack_out[*st_out] = f;	
}
void stPop_f(float *stack_out, int *st_out)
{
	stack_out[*st_out] = 0;
	(*st_out)--;		
}
void calculate(float *stack_out, int *st_out, char operation)
{
	switch(operation)
	{
		case 's':
			stack_out[(*st_out)] = sqrt(stack_out[*st_out]);
			break;
		case 'a':
			stack_out[(*st_out)] = abs(stack_out[*st_out]);
			break;
		case '+':
			stack_out[(*st_out)-1] = stack_out[(*st_out)-1] + stack_out[*st_out];
			stack_out[*st_out] = 0;
			(*st_out)--;
			break;
		case '-':
			stack_out[(*st_out)-1] = stack_out[(*st_out)-1] - stack_out[*st_out];
			stack_out[*st_out] = 0;
			(*st_out)--;
			break;
		case '*':
			stack_out[(*st_out)-1] = stack_out[(*st_out)-1] * stack_out[*st_out];
			stack_out[*st_out] = 0;
			(*st_out)--;
			break;
		case '/':
			stack_out[(*st_out)-1] = stack_out[(*st_out)-1] / stack_out[*st_out];
			stack_out[*st_out] = 0;
			(*st_out)--;
			break;
	}
}
char getP(char c)
{
	switch (c)
	{
		case 's': return 3;
		case 'a': return 3;
		case '*': return 2;
		case '/': return 2;
		case '+': return 1;
		case '-': return 1;
	}
}
char *inputString(FILE* f, uint size, uint *len){
    char *str;
    int ch;
    //uint len = 0;
    str = realloc(NULL, sizeof(char)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(f)) && ch != '\n'){
        str[(*len)++]=ch;
        if(*len==size){
            str = realloc(str, sizeof(char)*(size*=2));
            if(!str) return str;
        }
    }
    str[(*len)++]='\0';
	
    return realloc(str, sizeof(char)*(*len));
}
int main(int argc, char** argv)
{
	FILE *fin = fopen(argv[1], "r");
	FILE *fout = fopen(argv[2], "w");
	//size_t buffer = UINT_MAX;
	//char a[1000];
	char *a;
	uint a_len = 0;
	//fgets(a, 998, fin);
	a = inputString(fin, 2, &a_len);
	char stack_op[a_len];
	int st_op = 0;
	float stack_out[a_len];
	int st_out = 0;
	#ifdef DEBUG
		printf("String length: %d\n", a_len);
		printsf(a);
		endl();
		char *test = "-3.0+";
		float x = 3.05;
		//printf("x length len: %d", *strlen(x));
		float test_;
		char test__;
		//sscanf(test, "%f%c", &test_, &test__);
		//printf("\nTest: %f, %c\n", test_, test__);
	#endif
	char tmp = 'P';
	int index = 0;
	float ftmp;
	while(a[index] != '\0')
	{
		sscanf(a+index, "%c", &tmp);
		//if(tmp >= '0' && tmp <= '9')
		if(isDigit(tmp)  && a[index-1] != '-')
		{
			sscanf(a+index, "%f", &ftmp);
			#ifdef DEBUG
				printf("float: %f\n", ftmp);
			#endif
			stPush_f(stack_out, ftmp, &st_out);
		}
		else if (tmp  != ' ')
		{
			
			if(tmp == '.')
			{
				index++;
				while(isDigit(a[index+1]))
					index++;
			}
			else
			{
				if(tmp == '-')
				{
					if(!(a[index-1] == ' ' ? isDigit(a[index-2]) : isDigit(a[index-1])) || index == 0)
					{
						 sscanf(a+index, "%f", &ftmp);
						 #ifdef DEBUG
							 printf("temp: %c\n", tmp);
							 printf("minusfloat: %f\n", ftmp);
						 #endif
						 stPush_f(stack_out, ftmp, &st_out);
						 index+=2;
						 continue;
					}
				}
				if (tmp == 's' || tmp == 'a')
				{
				switch(tmp)
					{
					case 's':
						index+=3;
						break;
					case 'a':
						index+=2;
						break;
					}
				}
				#ifdef DEBUG
					printf("char: %c\n", tmp);
				#endif
				if(getP(tmp) > getP(stack_op[st_op]) || tmp == '(' || tmp == ')')
				{
					if(tmp == ')')
					{
						while(stack_op[st_op] != '(')
						{
						calculate(stack_out, &st_out, stack_op[st_op]);
						stPop_c(stack_op, &st_op);
						}
						stPop_c(stack_op, &st_op);
					}
					else
					{
						stPush_c(stack_op, tmp, &st_op);
					}
				}
				else
				{
					if (stack_op[st_op] != 's' && stack_op[st_op] != 'a')
					{
						while(st_op > 0)
						{
							if(stack_op[st_op] == '(')
							{
								//stPop_c(stack_op, &st_op);
								break;
							}
							else
							{
							calculate(stack_out, &st_out, stack_op[st_op]);
							stPop_c(stack_op, &st_op);
							}
						}
					}
					else
					{
						//printsf("trying SQRT or ABS\n");
						calculate(stack_out, &st_out, stack_op[st_op]);
						stPop_c(stack_op, &st_op);
					}
					stPush_c(stack_op, tmp, &st_op);
				}
					#ifdef DEBUG
						endl();
						printsf("stack_op: ");
						for (int i = st_op; i > 0; i--)
							printf("%c ", stack_op[i]);
						endl();
						printsf("stack_out: ");
						for (int i = st_out; i > 0; i--)
							printf("%f ", stack_out[i]);
						endl();
					#endif
			}
		}
		index++;
	}
	while(st_op != 0)
	{
		calculate(stack_out, &st_out, stack_op[st_op]);
		stPop_c(stack_op, &st_op);
	}
	#ifdef DEBUG
		endl();
		printf("\nprinting\n");
		for (int i = st_op; i > 0; i--)
			printf("%c ", stack_op[i]);	
		endl();
		for (int i = st_out; i > 0; i--)
			printf("Answer: %f ", stack_out[i]);
	#else
		for (int i = st_out; i > 0; i--)
			fprintf(fout, "%f", stack_out[i]);
	#endif
	free(a);
	fclose(fin);
	fclose(fout);
	return 0;
}
