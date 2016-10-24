#ifndef _union_nodes_H_
#define _union_nodes_H_
typedef struct node U;
typedef struct edge *Edge;

struct edge {
	int vertex_a;
	int vertex_b;
	int weight;	
};


struct node { 
	int e;
	U *p;
};


extern U init(int e);
extern int find(U* u);
extern U* find_r(U* u);
extern Edge union_nodes(Edge edge, U* array, Edge* A, int length);
U* set_find(int e, U* array);
int test_init(void);
int test_find(void);
int test_union_nodes(void);

#define SIZE 20 
#endif
