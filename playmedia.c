#include "doublelist.h"
 
int main()
{
	//同一个标准输入 控制输入
	int choose=0;
	pid_t pid;
	int flag=0; //0 停止 1 播放 2 暂停
	char pathname[]="../music/";
	char buf[50]={0};
	autofile();
	pstu head,pstr,p;
	head=LoadInfo();
	head->prev;
	pstr=head->next;
	pstr->prev=head;
	
	while(1)
    {
		system("clear");
		print_Node(head);
		printf("\t\t\t\t\t\t  ***************************************\n");
	        printf("\t\t\t\t\t\t\t          音乐播放器                \n");
	        printf("\t\t\t\t\t\t  ***************************************\n");
		printf("\t\t\t\t\t\t\t          主界面\n\n");
		printf("\t\t\t\t\t\t\t   1 播放     2 暂停/继续\n\n");
		printf("\t\t\t\t\t\t\t   3 下一首   4 上一首\n\n");
		printf("\t\t\t\t\t\t\t   5 退出\n");
		printf("\t\t\t\t\t\t  ***************************************\n");
		scanf("%d",&choose);
		switch(choose)
		{
			 case 1:
			   {
			     //播放
				 
				 flag=1;
				 pid =fork();
				 if(pid==0)
				 {
					 close(0); 	
                                         sprintf(buf,"../music/%s",pstr->name);	
					 execlp("madplay","madplay",buf,"-r",NULL);
					 perror("execlp");
                                         exit(0);
				 }
				 
			     break;
			   }
				
			 case 2:
			     if(flag==1)
				 {
					 system("killall-19 madplay");
				 }
				 else if(flag==2)
				 {
					 system("killall-18 madplay");
				 }
			     break;
			 case 3:
			    {
				 kill(pid,9);
			     p=Find_DownNode(pstr);
				 if(p==NULL)
				 {
					p=head->next;
				 }
				 pstr=p;
				 flag=1;
				 pid =fork();
				 if(pid==0)
				 {
					 close(0);       //关闭标准输入
					 sprintf(buf,"../music/%s",p->name);
					 execlp("madplay","madplay",buf,NULL);
					 perror("execlp");
					 exit(0);
				 }
			     break;
			    }
			 case 4:
			    {
				 kill(pid,9);
			     p=Find_UpNode(pstr);
				 if(p==head)
				 {
					p=head->next;
				 }
				 pstr=p;
				 flag=1;
				 pid =fork();
				 if(pid==0)
				 {
					 close(0);       //关闭标准输入
					 sprintf(buf,"../music/%s",p->name);
					 execlp("madplay","madplay",buf,NULL);
					 perror("execlp");
					 exit(0);
				 }
			     break;
			    }
			 case 5:
			 
			     kill(pid,9);
			     exit(0);
			 default:
			 
			     printf("输入错误\n");
		}
		sleep(1);
	}
	
	return 0;
}
