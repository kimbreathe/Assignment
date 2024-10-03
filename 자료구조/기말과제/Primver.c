#include <stdio.h>
#include <stdlib.h>	// qsort 함수를 사용하기 위한 라이브러리 정의

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100	// 최대 정점 정의
#define INF 1000	// weight값을 무한대로 초기화하기 위한 변수 정의

int parent[MAX_VERTICES];	// 부모 노드 초기화

// 배열에 그래프를 저장하기 위해 초기화시켜주는 함수
void set_init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		parent[i] = -1;	// 배열의 값이 -1이면 루트 노드임
	}
}

// 루트 노드를 찾아주는 함수
int set_find(int c) {
	if (parent[c] == -1) {
		return c;	// 배열의 값이 -1이므로 루트 노드를 리턴
	}
	while (parent[c] != -1) {
		c = parent[c];	// 루트 노드가 아니면 부모 노드를 타고 올라감
	}
	return c;
}

// 두 노드를 합쳐주는 함수
void set_union(int a, int b) {
	int root1 = set_find(a);	// 노드 a의 루트노드를 찾는다.
	int root2 = set_find(b);	// 노드 b의 루트노드를 찾는다.
	if (root1 != root2) {		// 두 노드의 루트노드가 다르면 합쳐준다.
		parent[root1] = root2;
	}
}

// 간선을 담을 구조체
struct Edge {
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// 간선의 개수 카운팅
	struct Edge edges[2 * MAX_VERTICES];	// 동적 메모리 할당을 위해 2배
} GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
	int i;
	g->n = 0;
	for (i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;	// weight값이 0이면 자기 자신이기 때문에 INF로 초기화
	}
}

// 그래프 자료구조에 간선을 삽입하는 연산
void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort()에 사용되는 비교함수
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// kruskal 알고리즘
void kruskal(GraphType* g) {
	int selected = 0;	// 현재까지 선택된 간선의 수를 저장할 변수 초기화
	int uset, vset;			// 정점 u, v의 루트 노드를 저장할 변수
	struct Edge e;

	set_init(g->n);			// 그래프 g 초기화

	// qsort(정렬할 배열, 요소 개수, 요소 크기, 비교함수);
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("정수기 검침원 MST 알고리즘\n");
	int i = 0;	// edge를 순차적으로 검사할 때 사용할 인덱스 변수
	int total = 0;	// 총 소요시간을 저장할 변수
	while (selected < (g->n - 1)) {
		e = g->edges[i];
		uset = set_find(e.start);	// 정점 u의 루트 노드
		vset = set_find(e.end);		// 정점 v의 루트 노드
		if (uset != vset) {
			printf("%d번 가정 다음에 %d번 가정 방문\n", e.start, e.end);
			total = total + e.weight;	// total값을 업데이트
			printf("현재 %d분 소요\n\n", total);
			selected++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 0, 1, 5);
	insert_edge(g, 0, 2, 11);
	insert_edge(g, 1, 2, 19);
	insert_edge(g, 1, 4, 33);
	insert_edge(g, 1, 5, 28);
	insert_edge(g, 2, 3, 17);
	insert_edge(g, 2, 4, 20);
	insert_edge(g, 3, 4, 10);
	insert_edge(g, 4, 5, 9);
	insert_edge(g, 4, 6, 23);
	insert_edge(g, 5, 6, 15);

	kruskal(g);
	free(g);
	return 0;
}