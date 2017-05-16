

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

#define strEQ(g,t) (strcmp((g),(t)) == 0)
struct GraphRep {
    int max_vtx;
    int num_vtx;
    int ** edges;
    char ** names;
};

int key_of_names (Graph map,char* target);




Graph newGraph(int maxV){
    Graph map = malloc(sizeof(struct GraphRep));
    map->max_vtx = maxV;
    map->num_vtx= 0;
    map->names = malloc(maxV *sizeof(char*));
    map->edges = malloc(maxV*sizeof(int*));
    int row,col;
    for (row=0; row < maxV; row++) {
        map->edges[row] = malloc(maxV*sizeof(int));
    }
    for (row=0; row<maxV; row++) {
        map->names[row] = NULL;
        for (col=0; col<maxV; col++) {
            map->edges[row][col] = 0;
        }
    }
    return map;
}


// disposeGraph(Graph) from lab08
// - clean up memory associated with Graph
void disposeGraph(Graph g)
{
    if (g == NULL) return;
    int i;
    for (i = 0; i < g->num_vtx; i++) {
        free(g->names[i]);
    }
    for (i = 0; i < g->max_vtx; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
}


int isConnected(Graph map, char *src, char *dest)
{
    int src_id  = key_of_names(map,src);
    int dest_id = key_of_names(map,dest);
    if (src_id < 0 || dest_id < 0) {
        return 0;
    }else{
        return map->edges[src_id][dest_id];
    }



}



//reference from lab08
// addEdge(Graph,Src,Dest)
// - add an edge from Src to Dest
// - returns 1 if edge successfully added
// - returns 0 if unable to add edge
//   (usually because nV exceeds maxV)
int addEdge(Graph g, char *src, char *dest)
{
    assert(g != NULL);
    int v = vertexID(src,g->names,g->num_vtx);
    if (v < 0) {
        if (g->nV >= g->max_vtx) return 0;
        v = addVertex(src,g->names,g->num_vtx);
        g->num_vtx++;
    }
    int w = vertexID(dest,g->names,g->num_vtx);
    if (w < 0) {
        if (g->names >= g->max_vtx) return 0;
        w = addVertex(dest,g->names,g->num_vtx);
        g->num_vtx++;
    }
    g->edges[v][w] = 1;
    return 1;
}





int key_of_names (Graph map,char* target){
    int found=-1;
    int i;
    for (i=0; i < (map->num_vtx); i++) {
        if(!strcmp(map->names[i],target)){
            found = i;
            break;
        }
    }

    return found;
}

// - add Str at end of Names
int addVertex(char *str, char *names[], int N)
{
    names[N] = strdup(str);
    return N;
}




int maxVertices(Graph map){

    return map->max_vtx;

}
int   nVertices(Graph map){

    return map->num_vtx;
}










// showGraph(Graph)
// - display Graph
void showGraph(Graph g, int mode)
{
    assert(g != NULL);
    if (g->num_vtx == 0)
        printf("Graph is empty\n");
    else {
        printf("Graph has %d vertices:\n",g->num_vtx);
        int i, j;
        if (mode == 1) {
            for (i = 0; i < g->num_vtx; i++) {
                for (j = 0; j < g->num_vtx; j++)
                    printf("%d",g->edges[i][j]);
                putchar('\n');
            }
        }
        else if (mode == 2) {
            
            for (i = 0; i < g->num_vtx; i++) {
                printf("Vertex: %s\n", g->names[i]);
                printf("connects to\n");
                for (j = 0; j < g->num_vtx; j++) {
                    if (g->edges[i][j])
                        printf("   %s\n",g->names[j]);
                }
            }
        }else if (mode == 3) {
            // JSON type persentation
            // Originate
            int num_of_vertex_printed;
            printf("{\"map\":[\n");
            for (i = 0; i < g->num_vtx; i++) {
                if(i!=0){
                    printf("    ,\n");
                }
                
                //printf("    \"Vtx%d\":\n",i);
                printf("    {\n");
                printf("    \"Vtx%d\": \"%s\",\n", i,g->names[i]);
                
                printf("    \"connected link\": \n");
                printf("        [\n");
                for (j = 0,num_of_vertex_printed = 0; j < g->num_vtx; j++){
                    
                    if (g->edges[i][j]){
                        
                        if (num_of_vertex_printed > 0 ) {
                            printf("            ,\n");
                        }
                        
                        printf("           {");
                        printf("\"Vertex\": \"%s\"", g->names[j]);
                        
                        num_of_vertex_printed++;
                        
                        printf("}\n");
                    }
                    
                    
                }
                
                printf("        ]\n");
                
                printf("    }\n");
                
            }
            printf("]}\n");
            
        }
    }
}

