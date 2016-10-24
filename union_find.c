/** @author scott fabini
 * Union-Find ADT, including init, find, and union_nodes.  Also adds a set-find, to perform find across an array of disjoint sets
 * Useful in conjunction with kruskal.h library from the same author
 */
#include "union_find.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node U;

// initialize a singleton element for the disjoint set
U init(int e) 
{
	U* vertex = (U*) malloc (sizeof (U));

	vertex->e = e;
	vertex->p = vertex;
	return *vertex;
}

// return the canonical element representing the input vertex of the disjoint set
int find(U* u) 
{
	return find_r(u)->e;
}

// recursive version to return the node version of the vertex and compact the disjoint set data structure
U* find_r(U* u) 
{
	if (u->p != u) 
	{
		u->p = find_r (u->p);
	}
	return u->p;
}

//void union_nodes(int u, int v, Edge* edge, U* array, U* A) 
Edge union_nodes(Edge edge, U* array, Edge* A, int index) 
{
	int u = edge->vertex_a;
	int v = edge->vertex_b;
	printf("Searching for nodes %d & %d\n", u, v);

	U* u_canonical_node = set_find(u, array);
	U* v_canonical_node = set_find(v, array);

	if (u_canonical_node->e != v_canonical_node->e)
	{
		v_canonical_node->p->p = u_canonical_node;
		printf("Connecting %d to %d\n", v_canonical_node->e, u_canonical_node->e);
		return edge;
	}
	return NULL; 
}

U* set_find(int e, U* array)
{
	if ((*array[e].p->p).e == e)
	{
		return array[e].p;
	}
	return array[find(array[e].p)].p;
}

// Program-testing commented out
/*
int main()
{
	test_init();
	test_find();
	test_union_nodes();
	return 0;
}
*/
/*
int test_init() 
{
	E e1; 
	U u1;

	e1 = (E) malloc (sizeof (struct element));
	e1 = 5;
	u1 = init(e1);

	printf("\nTest Init\n");
	printf("e1: %d \n", e1);
	printf("u1: %d, %p \n", u1->e, u1->p);

	free(e1);
	return 0;
}

int test_find() 
{
	E e1, e2, e3, e4;
	U u1, u2, u3, u4;
	E find_result;

	e1 = (E) malloc (sizeof (struct edge));
	e2 = (E) malloc (sizeof (struct edge));
	e3 = (E) malloc (sizeof (struct edge));
	e4 = (E) malloc (sizeof (struct edge));

	e1 = 1;
	e2 = 2;
	e3 = 3;
	e4 = 4;

	u1 = init(e1);
	u2 = init(e2);
	u3 = init(e3);
	u4 = init(e4);

	// make u2 point to u1; u3 and u4 point to u2
	u2.p = u1;
	u3.p = u2;
	u4.p = u2;

	printf("\nTest Find\n");
	printf("initilized u2 to point to u1; u3 and u4 point to u2\n");
	printf("u1: %p, u1->p: %p, u1->p->e %d \n", u1, u1.p, u1.p->e);
	printf("u2: %p, u2->p: %p, u2->p->e %d \n", u2, u2.p, u2.p->e);
	printf("u3: %p, u3->p: %p, u3->p->e %d \n", u3, u3.p, u3.p->e);
	printf("u4: %p, u4->p: %p, u4->p->e %d \n", u4, u4.p, u4.p->e);

	find_result = find(u1);
	printf("find_result on u1: %d \n", find_result);

	find_result = find(u2);
	printf("find_result on u2: %d \n", find_result);

	find_result = find(u3);
	printf("find_result on u3: %d \n", find_result);

	find_result = find(u4);
	printf("find_result on u4: %d \n", find_result);
	printf("confirmed pointers point correctly\n");
	return 0;

}


int test_union_nodes() 
{
	E e[SIZE];
	U u[SIZE];
	E find_result;
	int i;

	for (i = 0; i < SIZE; ++i) 
	{
		e[i] = (E) malloc (sizeof (struct edge));
		e[i] = i;
		u[i] = init(e[i]);

	}
	

	// make u2 point to u2; u3 and u4 point to u2
	u[1].p = u[0];
	u[2].p = u[1];
	u[3].p = u[1];


	printf("\nTest Union\n");
	for (i = 0; i < SIZE; ++i)
	{	
		printf("u[%d]: %d, u1->p: %d \n", i, u[i].e, u[i].p->e);
		find_result = find(u[i]);
		printf("find_result on u[%d]: %d \n", i, find_result);

	}

	// use union_nodes() to form pairs (4,5), (6,7), (8,9) 
	union_nodes(u[4], u[5]);
	union_nodes(u[6], u[7]);
	union_nodes(u[8], u[9]);

	// use union_nodes() to connect pairs 6 and 8 up to 4
	union_nodes(u[4], u[6]);
	union_nodes(u[4], u[8]);

	// try to connect 9 into 4.  no change because already connected
	union_nodes(u[4], u[9]);

	printf("\nuse union_nodes() to form pairs (4,5), (6,7), (8,9)\n");
	printf("use union_nodes() to connect pairs 6 and 8 up to 4\n");
	printf("try to connect 9 into 4.  no change because already connected\n");

	for (i = 0; i < SIZE; ++i)
	{	
		printf("u[%d]: %d, u1->p: %d \n", i, u[i].e, u[i].p->e);
		find_result = find(u[i]);
		printf("find_result on u[%d]: %d \n", i, find_result);

	}

	

	return 0;
}

*/
