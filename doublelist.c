#include "doublelist.h"
 
//自动生成音乐目录集
void autofile()
{
	system("ls ../music > ../songname");   	
}
//加载数据
pstu LoadInfo()
{
	char name[20];
	char filename[]="../songname";
	FILE *fp;
	pstu head,ptr,tmp;
	
	//创建头文件
	head=calloc(1,SIZE);
	ptr=head;
	ptr->next=NULL;
	if((fp=fopen(filename,"r"))==NULL)
	{
		perror("fopen");
		exit(0);
	}
	tmp=(pstu)calloc(1,SIZE);
	
	while(fscanf(fp,"%s\n",name)!=EOF)
	{	
		strcpy(tmp->name, name);	
		ptr->next=tmp;
		tmp->prev=ptr;
		ptr = tmp;
		tmp = (pstu)calloc(1,SIZE);	
	}
        free(tmp);
	fclose(fp);  //关闭文件,已得到保存data信息的链表head
	return head;
}
pstu Find_DownNode(pstu head)
{
	pstu p;
	p=head->next;
	return p;
}
pstu Find_UpNode(pstu head)
{
	pstu p;
	p=head->prev;
	
	return p;
}
void print_Node(pstu head)
{
	pstu ptr=head;
	pstu p=ptr->next;
	printf("\t\t\t\t\t\t\t\t 歌   单\n\n");
	printf("\t\t\t\t\t\t\t\t============== \n");
	while(p!=NULL)
	{
		printf("\t\t\t\t\t\t\t\t %s\n",p->name);		
		p=p->next;
	}	
	printf("\t\t\t\t\t\t\t\t============== \n\n");
}
