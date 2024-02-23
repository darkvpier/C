#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define INFITY 999
#define startnode 0

void shortestpath(int cost[MAX][MAX], int n)
{
	int distance[MAX], pred[MAX], visited[MAX], count, i, j, mindistance, nextnode;
	for (i = 0; i < n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	while (count < n - 1)
	{
		mindistance = INFITY;
		for (i = 0; i < n; i++)
		{
			if (!visited[i] && (distance[i] < mindistance))
			{
				mindistance = distance[i];
				nextnode = i;
			}
		}
		visited[nextnode] = 1;

		for (i = 0; i < n; i++)
		{
			if (!visited[i] && (distance[i] > (mindistance + cost[nextnode][i])))
			{
				distance[i] = mindistance + cost[nextnode][i];
				pred[i] = nextnode;
			}
		}
		count++;
	}

	for (i = 0; i < n; i++)
	{
		if (i != startnode)
		{
			printf("\nDistance of node %d from node %d: %d\n", i, startnode, distance[i]);
			j = i;
			printf("\nPath: %d",i);
			do
			{
				j = pred[j];
				printf("<-%d", j);
			}while(j!=startnode);
		}
	}
}

int main()
{
	int cost[MAX][MAX], n, i, j;
	printf("Enter Number of nodes: ");
	scanf("%d", &n);

	printf("Enter the Cost Matrix:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &cost[i][j]);
		}
	}
	shortestpath(cost, n);
	return 0;
}