#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES	100	
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES];		/* 방문한 정점 표시 */
int path[MAX_VERTICES];

void print_path(int start, int end)
{  	if( path[end] != start) print_path(start, path[end]);		// end 직전 경유노드가 start가 아닌 경우, 재귀호출로 출력 의뢰 
	printf("%d->%d, ", path[end], end);		// end에서 end직전 경유 노드까지 화살표 출력 
}
								
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i<n; i++)
		if (distance[i]< min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void print_status(GraphType* g)
{
	int i;
	static int step=1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("        found:    ");
	for (i = 0; i<g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}
//
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i<g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		path[i] = start;		// 패스의 초기값은 시작 정점으로 지정 
		found[i] = FALSE;
	}
	found[start] = TRUE;    /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i<g->n-1; i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w<g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w]<distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					path[w]=u;		// 경유노드 저장 
				}
					
	}
}
int main(void)
{
	GraphType g = { 7,
	{{ 0,  7,  INF, INF,   3,  10, INF },
	{ 7,  0,    4,  10,   2,   6, INF },
	{ INF,  4,    0,   2, INF, INF, INF },
	{ INF, 10,    2,   0,  11,   9,   4 },
	{ 3,  2,  INF,  11,   0, INF,   5 },
	{ 10,  6,  INF,   9, INF,   0, INF },
	{ INF, INF, INF,   4,   5, INF,   0 } }
	};
	shortest_path(&g, 0);
	print_path(0,3);			// 정점 0에서 정점3으로 가는 최단경로 출력 
	return 0;
}
