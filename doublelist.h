#include "lib.h"
 
typedef struct node
{
	 char name[20];
	 struct node *prev;
	 struct node *next;
}stu,*pstu;
 
#define SIZE sizeof(stu)
 
pstu LoadInfo();
void print_Node(pstu head);
pstu Find_DownNode(pstu head);
pstu Find_UpNode(pstu head);
void autofile();
