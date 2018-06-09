#include<stdio.h>
#define LIMINF 99999999
#define numfield(i,j) numfield[(i)*W+j]
#define N H*W
#define false 0
#define true 1
#define WALL -1
#define NOTWALL -2
#define SHAREWAVE if(nexty >= 0 && nexty < H && nextx >= 0 && nextx < W && numfield(nexty, nextx) == NOTWALL)\
					{\
						flag = false;\
						numfield(nexty, nextx) = d + 1;\
					}
/*
#define SHAREBACK if (curry+nexty >= 0 && curry+nexty < H && currx+nextx >= 0 && currx+nextx < W && numfield((curry+nexty),(currx+nextx)) == d)\
	      		{\
	         		currx += nextx;\
					curry += nexty;\
					break;\
				}*/
//#define DEBUG
int main(int argc, char** argv)
{
	FILE* fin = fopen(argv[1], "r");
	FILE* fout = fopen(argv[2], "w");
	int W, H;
	int x, y;
	int coords;
	int exitX = 0;
	int exitY = 0;
	fscanf(fin, "%d %d%*c", &W, &H);
	#ifdef DEBUG
	printf("W = %d H = %d\n", W, H);
	#endif
	//char field[H][W];
	if (fin == NULL || fout == NULL){
		perror("file could not be open");
		return 255;
	}
	char field[H][W+2];
	int *numfield = malloc(H * W * sizeof(int));
	for (int i = 0; i < H; i++)
	{
		if (fgets(field[i], W+2, fin) != NULL)
		{
			#ifdef DEBUG
			printf("%s", field[i]);
			#endif
		}
	}
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{

				if(field[i][j] == '-' || field[i][j] == '|' || field[i][j] == '+' )
					numfield(i, j) = -1;
				if(field[i][j] == ' ')
					numfield(i, j) = -2;
				if(field[i][j] == '*')
				{
					numfield(i, j) = -3;
					y = i;
					x = j;
				}
			}	
	}
	#ifdef DEBUG
		printf("\n PRINTING \n");
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				printf("%2d ",numfield(i, j));
			}
		printf("\n");
	}
		printf("\nPointCoords: (%d, %d)\nExitCoords: (%d, %d)\n", y, x, exitY, exitX);
	#endif
		//printf(" %d", numfield(y,x));
	//lee
	int d = 0;
	int k;
	int currx, curry;
	char flag;
	numfield(y, x) = 0;
	int nexty, nextx;
	while(!flag)
	{
	flag = true;
	for(curry = 0; curry < H; curry++)
	{
		for(currx = 0; currx < W; currx++)
		{
			if(numfield(curry, currx) == d)
			{
				nexty = curry;
				nextx = currx + 1;
				SHAREWAVE
				nexty = curry + 1;
				nextx = currx;
				SHAREWAVE
				nexty = curry;
				nextx = currx - 1;
				SHAREWAVE
				nexty = curry - 1;
				nextx = currx;
				SHAREWAVE
				if(((curry == H - 1) || (curry == 0) || (currx == 0) || (currx == W-1)) && field[curry][currx] == ' ')
				{
					#ifdef DEBUG
					printf("\nExit found: coords(%d, %d)", curry, currx);
					#endif
					goto out;
				}
			}
			
		}
	}
	d++;
	#ifdef DEBUG
	printf("\n PRINTING \n");
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				printf("%2d ",numfield(i, j));
			}
		printf("\n");
	}
	#endif
	};
	#ifdef DEBUG
	printf("Path hasn't been found");
	return 0;
	#endif
	fprintf(fout, "Path hasn't been found");
	free(numfield);
	fclose(fin);
	fclose(fout);
	return 0;
	//out:
	//#ifdef DEBUG
	//printf("\nPath has been found\n");
	//#endif
	out:;	
	int pathlength = numfield(curry, currx);
	int pathX[N];
	int pathY[N];
	d = pathlength;
	#ifdef DEBUG
	printf("d = %d, curry = %d, currx = %d", d, curry, currx);
	#endif
	int deltax[4] = {1, 0, -1, 0};  
  	int deltay[4] = {0, 1, 0, -1};
	while(d > 0)
	{
		pathX[d] = currx;
		pathY[d] = curry;
		d--;
		/*nextx = 1;
		nexty = 0;
		SHAREBACK
		nextx = 0;
		nexty = 1;
		SHAREBACK
		nextx = -1;
		nexty = 0;
		SHAREBACK
		nextx = 0;
		nexty = -1;
		SHAREBACK
		//nextx = 
		/**/
		for (k = 0; k < 4; ++k)
	    {
	       nexty = curry + deltay[k];
		   nextx = currx + deltax[k];		   
	       if (nexty >= 0 && nexty < H && nextx >= 0 && nextx < W &&
	            numfield(nexty,nextx) == d)
	      	{
	         	currx += deltax[k];
				curry += deltay[k];		          
				break;
	      	}
	    }
	}
	pathX[0] = x;
	pathY[0] = y;
	for(int i = 1; i <= pathlength; i++)
	{
			#ifdef DEBUG
			printf("\n(%d, %d)", pathY[i], pathX[i]);
			#endif
			field[pathY[i]][pathX[i]] = '.';
	}
	#ifdef DEBUG
	printf("\n PRINTING \n");
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				printf("%2d ",numfield(i, j));
			}
		printf("\n");
	}
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				printf("%c", field[i][j]);
			}
		printf("\n");
	}
	#else
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				fprintf(fout, "%c", field[i][j]);
			}
		fprintf(fout,"\n");
	}
	#endif
free(numfield);
fclose(fin);
fclose(fout);
return 0;
}
