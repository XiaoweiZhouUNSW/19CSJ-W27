#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include "queue.h"
#include "set.h"
#include "readData.h"
#define MAX_VALUE 500


 
 int main(int argc,char * argv[]){

    Queue toVist = newQueue();
    Graph map = newGraph(MAX_VALUE);
    toVist = GetCollection(toVist);
    showQueue(toVist);
    int max_iteration = 10;
    if (argc > 1) {
        max_iteration = atoi(argv[1]);
    }
    visitURL(map,toVist,max_iteration);
    showGraph(map,1);
    showGraph(map,2);
    disposeQueue(toVist);
    disposeGraph(map);
    return 0;
}






