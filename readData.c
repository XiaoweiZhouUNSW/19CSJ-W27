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
#define MAX_LINE_SIZE 256
#define MAX_NAME_SIZE 20


Queue GetCollection(Queue toVist){
    FILE * a_file = fopen("collection.txt","r");
    if(!a_file){
        printf("collection.txt not found, it should be under the same directry\n");
        exit(1);
        
    }
    readURL(a_file,"collection",toVist,NULL);
    fclose(a_file);
    return toVist;
}


void readURL(FILE *a_file,Item curr,Queue toVist,Graph map){
    char a_line[MAX_LINE_SIZE];
    char file_num[MAX_LINE_SIZE];
    char substring[] ="url";
    char * temp_link;
    int i,name_len;
    
    while (!feof(a_file)) {
        //need to put it into a queue
        fgets(a_line,256,a_file);
        if (strstr(a_line,"#end Section-1")){
            break;
        }else {
            temp_link = strtok(a_line,substring);
            while (temp_link!=NULL) {
                for (i=0; i<strlen(temp_link); i++) {
                    if (!isalnum(temp_link[i])) {
                        temp_link[i]='\0';
                    }
                }
                if(temp_link&&isalnum(*temp_link)){
                    printf(" ---%s\n",temp_link);
                    name_len = strlen(temp_link);
                    strcpy(file_num,temp_link);
                    file_num[name_len]='\0';
                    printf(">%s\n",file_num);
                    enterQueue(toVist,file_num);
                    showQueue(toVist);
                    if (strcmp(curr,"collection")) {
                        //if we are reading the collection, then dont put them in the graph
                        if(!isConnected(map,curr, file_num)){
                            addEdge(map,curr,file_num);
                            
                        }
                    }
                    showQueue(toVist);
                }
                temp_link = strtok(NULL,substring);
            }
            
            
        }
    }
    
}

void visitURL(Graph map ,Queue toVist,int max_iteration){
    Item curr;
    Set visited = newSet();
    
    int num_iteration=0;
    char full_link[MAX_NAME_SIZE];
    
    while ((num_iteration < max_iteration) && !emptyQueue(toVist) && (nVertices(map) < maxVertices(map))) {
        curr = leaveQueue(toVist);
        if (isElem(visited,curr)) {
            continue;
        }
        //assume the url are in the same file of the excution file
        sprintf(full_link,"url%s.txt",curr);
        FILE * a_file = fopen(full_link,"r");
        assert(a_file);
        if (a_file != NULL) {
            printf("visiting %s .. \n",full_link);
            readFirstSection(a_file,curr,toVist,map);
            num_iteration++;
        }
        
        
        fclose(a_file);
    }
    
    
    disposeSet(visited);
    
}

void readFirstSection(FILE *a_file,Item curr,Queue toVist,Graph map){
    int num;
    printf("reading..\n");
    fscanf(a_file,"  #start Section-%d  ",&num);
    if (num==1) {
        
        printf("reading section 1..\n");
        readURL(a_file,curr,toVist,map);
        
    }
    
    
}


