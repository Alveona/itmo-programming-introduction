#include<stdio.h>
#include<math.h>
#define log(s) printf("\n\nLOG: %s\n", s)
#define logint(num) printf("\n\nLOG: %d\n", num);
#define logfloat(num) printf("\n\nLOG: %f\n", num);
#define DBL_EPSILON 0.0001
#define M(i,j) M[i*(N+1)+j]
#define false 0
#define true 1
#define NOERROR 0
#define FILEOPENERR 1
#define ZEROBY_Y 2
#define ZEROBY_X 3
#define EXIT free(M);\
		fclose(fin);\
		fclose(fout);\
		return 0;
char errortype = NOERROR; 
void swap(float *a, float *b)
{
	float t = *a;
	*a = *b;
	*b = t;
}
int main(int argc, char **argv)
{
FILE *fin = fopen(argv[1], "r");
FILE *fout = fopen(argv[2], "w");
int N;
int i = 0;
int j = 0;
if (fin == NULL || fout == NULL)
{
	errortype = FILEOPENERR;
	goto erroroccured;
}
fscanf(fin, "%d", &N); 
float *M = malloc(N * (N+1) * sizeof(float));
while (i < N){			
	if (j < N + 1){
	fscanf(fin, "%f", &M(i,j));
	//printf("%.3f ", M(i,j));
	j++;
	}
	else if (j == N + 1)
	{
		//printf("\n");
		i++;
		j = 0;
	}
}
int iter = 0;
int in = 0;
char backflag = 0;
float max;
float tmp;
//printf("abs: %f", abs(5.0f));

for(iter = 0; iter < N; iter++)
{
	max = fabs(M(iter, iter));
	in = iter;
	for (i = iter + 1; i < N; i++)
	{
	//test = _abs(M(i, iter));
	if (fabs(M(i, iter)) > max)
	{
		max = fabs(M(i, iter));
		in = i;
		//printf("dadw");
	}
	}
	if (max < DBL_EPSILON)
	{
		//errortype = ZEROBY_Y;
		//goto erroroccured;
	}
	//printf("\nCurrent max: %f\n", max);
	for(j = 0; j < N + 1; j++)
		swap(&M(iter, j), &M(in, j));
	for (i = iter; i < N; i++)
	{
		tmp = M(i, iter);
		if (fabs(tmp) < DBL_EPSILON) continue;
		for (j = 0; j < N + 1; j ++)
			M(i, j) /= tmp;
		if (i == iter) continue;
		for (j = 0; j < N + 1; j++)
			M(i, j) -= M(iter, j);
		
	}
}
char iszero;
char zeroindex;
for (i = 0; i < N; i++)
{
	iszero = true;
	zeroindex = i;
	for(j = 0; j < N; j++)
	{
		if(fabs(M(i, j)) > DBL_EPSILON)
		{
			iszero = false;
			break;
		}
	}
	if(iszero)
	{
	 errortype = ZEROBY_X;
	 goto erroroccured;
	}
}
erroroccured:
switch(errortype)
{
case NOERROR: break;
case ZEROBY_X:
	if(fabs(M(zeroindex, N)) < DBL_EPSILON)
	 {
		//printf("\nunexp sol ind strig %d\n", zeroindex);
		fprintf(fout, "Many solutions");
		EXIT
	 }
	 else
	 {
	 	//printf("\nunexp sol in strig %d\n", zeroindex);
		fprintf(fout, "No solution");
		EXIT
	 } 
	 //return 0;
case ZEROBY_Y:
	fprintf(fout, "Many solutions_y");
	EXIT
	//return 0;
case FILEOPENERR:
	printf("Error occured while opening file");
	return 255;
}
float answers[N];
answers[N - 1] = M((N - 1), N);
for( i = N - 1; i >= 0; i--)
{
	answers[i] = M(i, N);
	for ( j = 0; j < i; j++)
		M(j, N) -= M(j, i) * answers[i];
}
/*printf("\nfinal:\n");
for (i = 0; i < N; i++)
{
	for(j = 0; j < N + 1; j++)
		{
			printf("%.3f ",  M(i, j));
		}
	printf("\n");
}
printf("\n");*/
for(i = 0; i < N; i++)
	fprintf(fout, "%f\n", answers[i]);
free(M);
fclose(fin);
fclose(fout);
return 0;
}
