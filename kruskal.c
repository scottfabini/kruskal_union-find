/* @author: scott fabini
 * An implementation of Kruskal's algorithm.  
 * Utilizes c qsort to sort a list of edges read from a file "city-pairs.txt"
 * These edges are broken into singletons in a set of disjoint sets.  
 * A Union(Find(e1,e2)) (union-find) algorithm to find the (forest of) minimum spanning trees
 * for the given graph of edges. 
 */

#include "kruskal.h"
#include "union_find.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node U;

// Kruskal's Algorithm
Edge* kruskal(Edge *edge_list) {
	Edge* A = NULL;
	int i = 0;
	int j = 0;
	U* eq_classes;
	A = (Edge*) calloc (CLASS_LEN, sizeof(Edge*));

	display_edge_list(edge_list);  // to demonstrate to grader the creation of the edge list
	qsort(edge_list, ARRAY_LEN, sizeof(Edge*), compare);
	printf("Qsort comlete\n");
	display_edge_list(edge_list);  // to demonstrate the sorted edge list
	printf("Edge List sorted\n");
	eq_classes = create_equivalence_classes(); // to demonstrate the creation of a disjoint set of singletons
	printf("EQ classes created\n");

	//Main loop of Kruskal takes each edge, and adds it if union(find(u,v)) comes back with a new edge element to add
	for(i = 0; i < ARRAY_LEN; ++i)
	{
		if (edge_list[i] != NULL)
		{
			A[j] = union_nodes(edge_list[i], eq_classes, A, j);
			if (A[j] != NULL) { j++; }
		}
	}
	printf("Displaying final list of edges\n");
	display_class_list(A);
		
	return A;
}

// Main function to kick-off execution
int main() 
{
	Edge* edge_list;
	Edge* MST_edge_list;

	edge_list = file_to_edge_list();
	MST_edge_list = kruskal(edge_list);
	display_class_list(MST_edge_list);
	return 0;
}
// Display a disjoint set of vertices
void display_eq_classes(U* eq_classes)
{
	int i;
	char * city;
	printf("Displaying EQ Classes: \n");
	for (i = 0; i < CLASS_LEN; ++i)
	{
		if (eq_classes[i].p != NULL)
		{
			city = decode_city(eq_classes[i].e);
			printf("EQ[%d]: city: %s, e: %d, &eq_class[i]: %p, eq_class[i].p: %p, eq_classes[i].p->p: %p \n", i, city, eq_classes[i].e, &eq_classes[i], eq_classes[i].p, eq_classes[i].p->p);
			//free(city);
		}
	}
	printf("\nEQ Class Display Complete\n");
}


// Display a generic list edge of length ARRAY_LEN
void display_edge_list(Edge* edge_list) {
	int i;

	for (i = 0; i < ARRAY_LEN; ++i)
	{
		if (edge_list[i] != NULL)  
		{
			printf("Edge[%d]: V1: %d, V2: %d, Weight: %d p: %p \n", i, edge_list[i]->vertex_a, edge_list[i]->vertex_b, edge_list[i]->weight, &edge_list[i]);
		}
	}
	return;
}

// Display the class list representing disjoint sets of length CLASS_LEN
void display_class_list(Edge* edge_list) {
	int i;

	for (i = 0; i < CLASS_LEN; ++i)
	{
		if (edge_list[i] != NULL)  
		{
			printf("Edge[%d]: V1: %d, V2: %d, Weight: %d p: %p \n", i, edge_list[i]->vertex_a, edge_list[i]->vertex_b, edge_list[i]->weight, &edge_list[i]);
		}
	}
	return;
}

// Create the initial singletons (equivalence classes) representing all the vertices
U* create_equivalence_classes() 
{
	U* u = (U *) calloc (CLASS_LEN, sizeof (U));
	int i = 0;

	for (i = 0; i < CLASS_LEN; ++i)
	{
		u[i] = init(i);
	}
	return u;
}

// Compare to be used in qsort
int compare (const void * a, const void * b)
{
	const Edge* e1 =  a;
	const Edge* e2 =  b;
	if (e1[0] == NULL || e1[0]->weight == 0)
	{
		return -1024*1024;
	}
	else if (e2[0] == NULL || e2[0]->weight == 0)
	{
		return -1024*1024;
	}	

//	printf("e1 weight: %d, e2 weight: %d, diff: %d\n", e1[0]->weight, e2[0]->weight, e1[0]->weight - e2[0]->weight);
	return e1[0]->weight - e2[0]->weight;
}

// Convert the file "city-pairs.txt" to an array of edge* (pointers-to-struct-edge).

Edge* file_to_edge_list() 
{
	Edge *edge_list;
	Edge next_edge;
	int i = 0;
	char * city_a;
	char * city_b;
	int weight;


	FILE *fp;

	fp = fopen("city-pairs.txt", "r");
	edge_list = (Edge*) calloc (ARRAY_LEN, sizeof(Edge));

	city_a = (char *) malloc (MAX_CITY_LENGTH * sizeof (char));
	city_b = (char *) malloc (MAX_CITY_LENGTH * sizeof (char));
	for (i = 0; i < ARRAY_LEN && fscanf(fp, "%s %s %d", city_a, city_b, &weight) > 0; ++i)
	{
		next_edge = (Edge) malloc (sizeof (struct edge));
		next_edge->vertex_a = encode_city(city_a, MAX_CITY_LENGTH);
		next_edge->vertex_b = encode_city(city_b, MAX_CITY_LENGTH);
		next_edge->weight = weight;
		edge_list[i] = next_edge;

	}
	
	fclose(fp);

	return edge_list;
}

// Encode (i.e. reversable hash) the city string into a number.
int encode_city(char * c, int length) 
{
	FILE *fp;
	int e; 
	char * city = (char *) malloc (MAX_CITY_LENGTH * sizeof (char));;
	int hash;
	int hash_read;

	fp = fopen("city-hash.txt", "r");
	while (fscanf(fp, "%s %d", city, &hash_read) > 0) 
	{
		if (strncmp(city, c, length) == 0) 
		{
			hash = hash_read;

		}
	}
	e = hash;
	free(city);
	fclose(fp);
	return e;
}

// Decode the city number, used to represent the vertex city, back to the full city string
char * decode_city(int e) 
{
	FILE *fp;
	char * city = (char *) malloc (MAX_CITY_LENGTH * sizeof (char));;
	int hash_read;

	fp = fopen("city-hash.txt", "r");

	while (fscanf(fp, "%s %d", city, &hash_read) > 0) 
	{
		if (e == hash_read) 
		{
			return city;
		}
	}
	fclose(fp);
	return city;
}



