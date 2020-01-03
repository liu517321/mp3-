#include<linux/input.h>
#include<sys/mman.h>
#include<stdio.h>
#include<string.h> 
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

void get_xy(int *x,int *y){      //运行代码
	char* str[3]={"/mp3_files1/3.mp3","/mp3_files1/4.mp3","/mp3_files1/5.mp3"};
//拼接字符串
	char cmd[300];
	int i=0;
	int flag=0;
	memset(cmd,0,300);    //把cmd起始的连续的100个字节地址空间 赋值为0（清空）
	int fd_touch = open("/dev/input/event0",O_RDONLY);  
	if(fd_touch == -1){
		printf("open touch screen err\n");
		return;
		}
	struct input_event ts;
	while(1){
		read(fd_touch,&ts,sizeof(ts));
		if(ts.type == 3){
			if(ts.code == 0){
					*x=ts.value*800/1024;
			}else if(ts.code == 1){
					*y=ts.value*480/600;
			}
		}
		if((ts.code == 330) && (ts.value == 0)){
			continue;
		}
		printf("x=%dy=%d\n",*x,*y);
		if((*x>1&&*x<247)&&(*y>15&&*y<124))
		{
			sprintf(cmd,"madplay --amplify=-10 %s -r &",str[i]);
//把格式化的字符串放入cmd中，开始播放音乐
			system(cmd);
		}
	
		if((*x>517&&*x<780)&&(*y>15&&*y<133))
		{
			flag=!flag;
			if(flag==1)
			{
				system("killall -STOP madplay &");//发送信号，暂停播放
			}
			else
			{
				system("killall -CONT madplay &");//发送信号，继续播放
			}
		}
		if((*x>1&&*x<260)&&(*y>360&&*y<472))       //播放下一首
		{
			system("killall madplay");   //结束当前的歌曲

			i++;
			sprintf(cmd,"madplay --amplify=-10 %s -r &",str[i%3]);
			system(cmd);
		}
		if((*x>517&&*x<780)&&(*y>360&&*y<472))
		{
			system("killall madplay");

			i--;
			sprintf(cmd,"madplay --amplify=-10 %s -r &",str[i%3]);
			system(cmd);
		}
		if((*x>252&&*x<488)&&(*y>184&&*y<314))
		{
			system("killall madplay");     //结束
		}
	}
	close(fd_touch);   //关闭文件
}

void bmp_show(char *bmp_name){          //触控
		int fd_lcd=open("/dev/fb0",O_RDWR); //LCD会自动从fb0中读取信息
		if(fd_lcd == -1){
			printf("open lcd err\n");
			return;
		}
//映射起始地址，映射区长度，页内容可被读写，与其他对象共享映射空间，文件描述符，被映射对象的内容起点
		Unsigned char* fp=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,fd_lcd,0);
//将文件fd_lcd映射到内存/地址空间中，即文件地址与虚拟空间地址有一一对应关系，进程可采用指针的方式读写这段内存空间
//完成了对文件的操作而不用调用read.write等系统调用函数
		if(fp == (void*)-1){
			printf("mmap err\n");
			return;
		}

		int fd_bmp = open(bmp_name,O_RDONLY);//以只读的方式打开2.bmp图片

		if(fd_bmp == -1){
			printf("open bmp err\n");
			close(fd_lcd);
			munmap(fp,800*480*4);
//mmap函数用于申请一段内存空间，将文件直接映射到其中，
//munmap函数则释放由mmap创建的内存空间
//fp参数是被映射文件对应的文件描述符
			return;
		}

		char bmp_buf[800*480*3];   //800*480*3个灯，每三个一组。RGB一组
		read(fd_bmp,bmp_buf,54);
		read(fd_bmp,bmp_buf,800*480*3);
//800*480*4即每个像素点4个字节
		int i,j;

		for(j=0;j<480;j++){   //宽
			for(i=0;i<800;i++){  //长
				memcpy(fp+i*4+800*4*j,bmp_buf+i*3+800*3*(479-j),3);
//复制到哪里去，从哪里复制，要复制的字节数
//内存拷贝函数
//将灯转化为像素点
				fp[i*4+3+800*4*j]=0; 
				}
			}
		close(fd_lcd);  //LCD触控文件描述符
		close(fd_bmp);  //关闭图片
		munmap(fp,800*480*4);//释放映射内存
	}
int main()
{
	int x,y;
	char bmp_name[]="/tupian/2.bmp";
	bmp_show(bmp_name);
	get_xy(&x,&y);
	return 0;
}
