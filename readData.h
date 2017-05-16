#ifndef readData_H
#define readData_H

void readURL(FILE *a_file,Item curr ,Queue toVist,Graph map);
void visitURL(Graph map,Queue toVist,int max_iteration);
void readFirstSection(FILE *a_file,Item curr,Queue toVist,Graph map);
Queue GetCollection(Queue toVist);

#endif