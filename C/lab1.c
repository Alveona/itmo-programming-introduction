#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define log(s) printf("\n\nLOG: %s\n", s)
typedef long long int llint;
typedef	struct {
		char _1n[21];
		char _2n[21];
		char _3n[21];
		llint _t;
	} List;
int cmp(List list1, List list2)
{
	if (strcmp(list1._1n, list2._1n) == 0)
	{
		if (strcmp(list1._2n, list2._2n) == 0) 
		{
			if (strcmp(list1._3n, list2._3n) != 0)
				return strcmp(list1._3n, list2._3n);
		}
		else {return strcmp(list1._2n, list2._2n);}
	}
	else {return strcmp(list1._1n, list2._1n);}
}
void _qsortList(List *a, int n)
{
	int i = 0; List t;
	int j = n;
	List p = a[n >> 1];
	iteration:
		if( n < 1 ) return;
		j = n;
		i = 0;
		p = a[n >> 1];
	while (i <= j){
		while (cmp(a[i], p) < 0) i++;
		while (cmp(a[j], p) > 0) j--;
		if (i <= j) {	
			t = a[i];
			a[i] = a[j];
			a[j] = t;
			i++; 
			j--;
		}
	} 
	if (j < n+i)
	{
		_qsortList(a, j);
		a = a + i;
		n = n - i;
		goto iteration;
	}
	else
	{
		_qsortList(a+i, n - i);
	}
}
int main(int argc, char **argv)
{	
	FILE *fin = fopen(argv[1], "r");
	FILE *fout = fopen(argv[2], "w");
	 List l1;
	 List lempty;
	int size = 2;
	int i = 0;
	int j = 0;
	 List *larr = malloc(size*sizeof(List));
	 List *larr_temp;
	char temp[1000];
	while (1){		
		if(i+1 == size){
			size*=2;
			if (larr_temp = realloc(larr, size*sizeof(lempty)))
			{
				larr = larr_temp;	
			}
			else
			{
				log("realloc_failed");
			}	
		}	    
		if(fscanf(fin, "%20s %20s %20s %lld", larr[i]._1n, larr[i]._2n, larr[i]._3n, &larr[i]._t) != 4) break;
				i++;
	}
	_qsortList(larr, i - 1);
	for(j = 0; j < i; j++)
		fprintf(fout, "%s %s %s %lld\n", larr[j]._1n, larr[j]._2n, larr[j]._3n, larr[j]._t);	
	fclose(fin);
	fclose(fout);
	free(larr);
	return 0;
}
