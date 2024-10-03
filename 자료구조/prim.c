#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i <n; i++)
		if (!selected[i]) {		// 방문 안한 노드들 중에서 
			v = i;				// 최소거리를 찾기위해 임의의 비교대상 v를 초기 선정 
			break;
		}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) v = i;		// 선정된 v보다 거리 가중치가 작은 i를 찾아 다시 v로 선정 
	return (v);			// 결국 거리가 최소값이 되는 노드v가 최종 선택됨 
}
//
void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;		// 모든 노드의 거리를 INF로 초기화 
	distance[s] = 0;			// 0으로 초기화하여 큐에서 s가 제일먼저 선택됨 
	for (i = 0; i<g->n; i++) {
		u = get_min_vertex(g->n);		// 우선순위 큐에서 u를 선택 
		selected[u] = TRUE;				// u는 방문한 노드이므로 표시 
		if (distance[u] == INF) return;		// u까지 거리가 INF라면 인접노드가 없는 경우 
		printf("정점 %d 추가\n", u);
		for (v = 0; v<g->n; v++)
			if (g->weight[u][v] != INF)		// u입장에서 v가 인접노드라면 
				if (!selected[v] && g->weight[u][v]< distance[v])	// 방문 안한 인접노드가 유효 가중치를 가지면
					distance[v] = g->weight[u][v];	// 인접노드 거리 책정 
	}
}

int main(void)
{
	GraphType g = { 7, 
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};
	prim(&g, 0);
	return 0;
}
