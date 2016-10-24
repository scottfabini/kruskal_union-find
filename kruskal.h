#ifndef _H_KRUSKAL_
#define _H_KRUSKAL_

#include "union_find.h"
typedef struct node U;
typedef struct edge *Edge;
U* file_to_graph(void);
U* sort_graph(Edge *edge_list);
Edge* kruskal(Edge *edge_list);
void display_edge_list(Edge *edge_list);
void display_class_list(Edge *edge_list);
void display_forest(U* forest);
int compare (const void *a, const void * b);
Edge* file_to_edge_list();
int encode_city(char *c, int length);
char * decode_city(int e);
U* edge_list_to_equivalence_classes(Edge* edge_list);
void display_eq_classes(U* forest);
U* create_equivalence_classes();

//E get_line(FILE file);
#define MAX_CITY_LENGTH 20
#define ARRAY_LEN 1000 
#define CLASS_LEN 29 

#endif
