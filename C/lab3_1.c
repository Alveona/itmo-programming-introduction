#include<stdio.h>
#define LIMINF 99999999
#define numfield(i,j) numfield[(i)*W+j]
#define N H*W
#define false 0
#define true 1
#define printsf(s) printf("%s", s);
typedef struct Node_t Node;
struct Node_t{
	int coords;
	Node* node;
};

int main(int argc, char** argv)
{
	FILE* fin = fopen(argv[1], "r");
	int W, H;
	int x, y;
	int coords;
	int exitcoords;
	fscanf(fin, "%d %d%*c", &W, &H);
	printf("W = %d H = %d\n", W, H);
	//char field[H][W];
	if (fin == NULL){
		perror("exception occured");
		return 255;
	}
	char field[H][W+2];
	//int numfield[H][W];
	int *numfield = malloc(H * W * sizeof(int));
	int distances[H][W];
	int graph[N][N];
	int flags[H][W];
	for (int i = 0; i < H; i++)
	{
		if (fgets(field[i], W+2, fin) != NULL)
		{
		printf("%s", field[i]);
		}
	}
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				if(field[i][j] == '+')
					numfield(i, j) = 2;
					distances[i][j] = 9;
				if(field[i][j] == '-' || field[i][j] == '|')
					numfield(i, j) = 1;
					distances[i][j] = 9;
				if(field[i][j] == ' ')
					numfield(i, j) = 0;
					distances[i][j] = 9;
				if(field[i][j] == '*')
				{
					numfield(i, j) = 3;
					y = i;
					x = j;
					coords = y*W+j;
					printf("\nCoords: %d\n", coords);
					distances[i][j] = 0;
				}
				flags[i][j] = 0;
				//graph[i][j] = 1;
			}
		//graph[i][i] = 0;
	}
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if(numfield(i, j) == 0 && j == (W-1) || numfield(i, j) == 0 && j == 0 
						|| numfield(i, j) == 0 && i == (H-1) || numfield(i, j) == 0 && i == 0)
			 exitcoords = i*W+j;
		}
	}
	printf("Exit coords: %d", exitcoords); 
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			graph[i][j] = 9;
			//if(graph[i][j] != 1)
			//graph[i][j] = 2;
			if (j % W == 0 && i - W >= 0)
			{
			if (numfield[i - W] != 2 && numfield[i - W] != 1)
			graph[i][i - W] = 1;
			if (numfield[i - W] != 2 && numfield[i - W] != 1)
			graph[i - W][i] = 1;
			if (numfield[i + W] != 2 && numfield[i + W] != 1)
			graph[i][i + W] = 1;
			if (numfield[i - W] != 2 && numfield[i - W] != 1)
			graph[i + W][i] = 1;
			}
		}
		
		graph[i][i] = 0;
		//if(i - W > 0)
		//graph[i - W][i] = 1;
		if ((i+1) % W != 0){
		if (numfield[i + 1] != 2 && numfield[i + 1] != 1)
		graph[i][i+1] = 1;}
		if (i % W != 0)		
		{
		if (numfield[i - 1] != 2 && numfield[i - 1] != 1)
		graph[i][i-1] = 1;}
		
	}
	//dijkstra
	char visited[N];
	int D[N];
	Node start;
	start.coords = coords;

	for(int i = 0; i < N; i++)
	{
		D[i] = graph[coords][i];
		visited[i] = false;
	}
	D[coords] = 0;
	for(int i = 0; i < N; i++)
		printf("\nD%d: %d", i, D[i]);
	int index = 0, u = 0;
	for(int i = 0; i < N; i++)
	{
		int min = LIMINF;
		for(int j = 0; j < N; j++)
		{
			if(!visited[j] && D[j] < min)
			{
				min = D[j];
				index = j;
			}
		}
		u = index;
		visited[u] = true;
		for(int j = 0; j < N; j++)
		{
			if (!visited[j] && graph[u][j] != LIMINF && D[u] != LIMINF && (D[u] + graph[u][j] < D[j]))
				D[j] = D[u] + graph[u][j];
		}
	}
	printf("\n FINISH \n");
	for(int i = 0; i < N; i++)
	{
		if(D[i]!=LIMINF)
			printf("D%d: %d\n",i,  D[i]);
	}
	printf("Distance to exit: %d", D[exitcoords]);
	//
	printf("\n PRINTING \n");
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
			{
				printf("%d ",numfield(i, j));
			}
		printf("\n");
	}
/*	printf("\n");
	for(int i = 0; i < N; i++)
		printf("%d ", graph[26][i]);
*/
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			{
				printf("%d ", graph[i][j]);
			}
		printf("\n");
	}
	return 0;
}
