#include <stdio.h>

struct node
{
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main()
{
    int dmat[20][20];
    int n, i, j, k, count;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix(999 if no link):\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dmat[i][j]);
            dmat[i][i] = 0;
            rt[i].dist[j] = dmat[i][j];
            rt[i].from[j] = j;
        }
    }
    do
    {
        count = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                for (k = 0; k < n; k++)
                {
                    if (rt[i].dist[j] > rt[i].dist[k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = rt[i].from[k];
                        count++;
                    }
                }
            }
        }
    } while (count != 0);
    for (i = 0; i < n; i++)
    {
        printf("\nFor Rounter %d:\n", i);
        for (j = 0; j < n; j++)
        {   
            printf("node %d via %d distance: %d\n", j, rt[i].from[j],rt[i].dist[j]);
        }
    }

    return 0;
}