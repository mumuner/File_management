#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>
#include <malloc.h>

#define blen 10//块大小 
#define max 100//空间大小（物理块数） 
#define filemax 100//文件最大长度
 
struct command//命令 
{
 char com[10];
}cmd[22];

struct blo//物理块 
{
       int n;//块号 
       char c[blen];//物理块大小 
       struct blo *next;//下一个物理块 
}tblock[max];

typedef struct blo *block;


struct file//文件
{
  char filename[20];
  int  length;
 // char quan;//权限控制 a组 可读可写，b组可读不可写 
  struct blo *first;//文件的第一个物理块   
  struct file *next;//同目录下的下一个文件 
};

struct dir//文件夹
{
  char dirname[20];
  struct dir *same;//同一级目录 
  struct dir *next;//下一级目录
  struct file *firstfile;//该目录下的第一个文件 
};    

struct user
{
	int quan;
    char username[20];
	struct user *next;
 };
 
struct list//文件路径储存
{
	struct dir *cur;
	struct list *next;
};

struct blo idle;//空闲表 表头 
struct dir root;//根目录 
struct dir *cur_dir; //当前目录 
struct list head;
struct user first;
int symbol=0;

void format()   //格式化
{
     int i;
     for(i=0;i<max-1;i++)
     {
         tblock[1].n=i;
        
        tblock[i].next=&tblock[i+1];              
      }
     tblock[max-1].next=NULL;
     idle.next=&tblock[0];
     strcpy(root.dirname,"root");
     root.same=NULL;
     root.next=NULL;
     root.firstfile=NULL;
     cur_dir=&root;
	 head.cur=&root;
	 head.next=NULL;
	 first.quan=2;
	 first.next=NULL;
	 strcpy(first.username,"admin");
	 symbol=0;

     printf("初始化完毕\n");
     printf("进入文件模拟系统......\n\n");
     
     
 }
 
 
void read_system(FILE *fp)   //读出系统文件的信息
{
     
     } 
     
     
char* read_file(char filename[],int q)//读出文件内容
 {
	struct file *tem=cur_dir->firstfile;
	block tem1;
	char tem2[filemax];
	tem2[0]='\0';
	int i=0;


	while(tem!=NULL)
	{
		if(strcmp(tem->filename,filename)==0)
		{
			tem1=tem->first;
			if(q==1)
			{
			printf("%s文件内容为：",filename);
			}
	     	while(tem1!=NULL)
			{
				strcat(tem2,tem1->c);
				if(q==1)
				{
				printf("%s",tem1->c);
				}
				tem1=tem1->next;
				i=i+10;
				tem2[i]='\0';
			}
			if(q==1)
			{
			printf("\n");
			}
			return tem2;
		}
		tem=tem->next;
	}
	if(q==1)
	{
	printf("没有该文件，请检查后重新输入。\n");
	}
	return NULL;
 }
     
     
void write_system(FILE *fp) //读出系统文件的信息
 {
      
  }
  
void callback(int length)    //回收磁盘空间
 {
     
     }
     
void allot(int length)     //分配空间
{
     
     } 
     
     
void create_file(char filename[],char con[],int q) //创建文件
{
     
     int len=strlen(con)/blen+1;
	 int n=0;
	 block tem1=&idle;
	 struct file *newf=(file *)malloc(sizeof(file));
	 struct file *tem=cur_dir->firstfile;
	 while(tem!=NULL)
	 {
		 if(strcmp(tem->filename,filename)==0)
		 {
			 printf("该文件已存在，请检查后重新输入。\n");
			 return;
		 }
		 tem=tem->next;
	 }
	 tem=cur_dir->firstfile;


	 while(tem1->next!=NULL)
	 {
		 tem1=tem1->next;
		 n++;
	 }
	 if(n<len)
	 {
		 printf("存储空间不足，创建文件失败。\n");
		 return;
	 }
	 tem1=idle.next;
	  strcpy(newf->filename,filename);
	 newf->length=len;
	newf->next=NULL;
	newf->first=tem1;
	for(n=0;n<len-1;n++)
	{
		strncpy(tem1->c,con,blen);
		tem1=tem1->next;
		con=con+10;
	}
	strcpy(tem1->c,con);
	idle.next=tem1->next;
	tem1->next=NULL;


	 if(tem==NULL)
	 {
		 cur_dir->firstfile=newf;
	 }
	 else
	 {
		while(tem->next!=NULL)
		{
			tem=tem->next;
		}
		tem->next=newf;
	 }
	 if(q==1)
	 {
	 printf("文件创建成功。\n");
	 }
        
}
     
     
     
void create_dir(char filename[])    //创建目录
{
	struct dir *newd=(dir *)malloc(sizeof(dir));
	struct dir *tem=cur_dir->next;
//	printf("%s",cur_dir->dirname);
	while(tem!=NULL)
	{
		if(strcmp(tem->dirname,filename)==0)
		{
			printf("已存在该目录，请检查后重新输入。\n");
			return;
		}
		tem=tem->same;
	}
	tem=cur_dir->next;


		strcpy(newd->dirname,filename);
	//	
		newd->firstfile=NULL;
		newd->next=NULL;
		newd->same=NULL;
	if(tem==NULL)
	{
		cur_dir->next=newd;
//	printf("----%s",cur_dir->next->dirname);
	}
	else
	{
		while(tem->same!=NULL)
		{
			tem=tem->same;
		}
	
		tem->same=newd;

	}
	printf("创建目录成功。\n");

}
	
void del_file(char filename[],int q)     //删除文件
{
     struct file *tem=cur_dir->firstfile;
	 struct file *tem1=tem;
	 int i=0;
	 while(tem!=NULL)
	 {
		 if(strcmp(tem->filename,filename)==0)
		 {
			 if(tem->next==NULL)
			 {
				 if(i==0)
				 {
					 cur_dir->firstfile=NULL;
				 }
				 else
				 {
					 tem1->next=NULL;
				 }
			 }
			 else
			 {
				 if(i==0)
				 {
					 cur_dir->firstfile=tem->next;
				 }
				 else
				 {
					 tem1->next=tem->next;
				 }
			 }
			 	block tem2=&idle;
	           while(tem2->next!=NULL)	
			   {
	            	tem2=tem2->next;
			   }
			 tem2->next=tem->first;
			 free(tem);
			 if(q==1)
			 {

			 printf("文件删除成功。\n");
			 }
			 return;
		 }
		 tem1=tem;
		 tem=tem->next;
	 }
	 if(q==1)
	 {
	 printf("没有该文件，请检查后重新输入。\n");
	 }

	 }
     
void del_dir(char filename[])     //删除目录   需要判断目录下时候为空,不为空就不删除
{
     struct dir *tem=cur_dir->next;
	 struct dir *tem1=cur_dir;
	 int i=0;
    while(tem!=NULL)
   {
     if(strcmp(tem->dirname,filename)==0)
     {
        if(tem->next==NULL&&tem->firstfile==NULL)
        {
           if(tem->same==NULL)
           {
			   if(i==0)
			   {
                   cur_dir->next=NULL;
			   }
			   else
			   {
				   tem1->same=NULL;
			   }
           }
            else
            {
				if(i==0)
				{
                    cur_dir->next=tem->same;
				}
				else
				{
					tem1->same=tem->same;
				}
            }
			free(tem);


            printf("目录删除成功。\n");
        }
        else
        {
            printf("目录不为空，不能删除。\n");

        }
        return;
     } 
	 tem1=tem;
     tem=tem->same;
	 i++;
   }
     printf("没有该目录，请检查后重新输入。\n");
}  
     
void display_curdir()         //显示当前目录下的文件列表
{
    int n=0,m=0;
    struct dir *tem=cur_dir->next;
    struct file *tem1=cur_dir->firstfile;
	//printf("-----%s\n",cur_dir->next->dirname);
    while(tem!=NULL)
    {
       printf("目录：%s\n",tem->dirname);
       tem=tem->same;
       n++;
     }
     while(tem1!=NULL)
     {
        printf("文件：%s\t长度：%d\n",tem1->filename,tem1->length);
        tem1=tem1->next;
        m++;
       }
       printf("%d个目录,%d个文件\n",n,m);
     

}    
        
     
void display_dir(char filename[])     //进入指定的目录
{
	struct dir *tem=cur_dir->next;


//	printf("---%s,filename  %s\n",tem->dirname,filename);
	struct list *tem1=&head;
	struct list *newl=(list *)malloc(sizeof(list));
	while(tem1->next!=NULL)
	{
		tem1=tem1->next;
	}



	while(tem!=NULL)
	{
		if(strcmp(tem->dirname,filename)==0)
		{
			cur_dir=tem;
		
			newl->cur=cur_dir;
		
			newl->next=NULL;
			tem1->next=newl;
			return;
		}
		tem=tem->same;
	}
	printf("没有该目录，请检查后重新输入。\n");


}



void open_file(char filename[])        //打开文件
{
     
     }



void back_dir()         //返回上一级目录
{
	struct list *tem=&head;
	if(tem->next==NULL)
	{
		printf("此为根目录。\n");
		return;
	}


     while(tem->next->next!=NULL)
	 {
		 tem=tem->next;
	 }
	 tem->next=NULL;
	 cur_dir=tem->cur;
}




void display_sys()        //显示系统信息（磁盘使用情况）
{
     int i;
     struct blo *tem=&idle;
     
     for(i=0;i<max;i++)
     {
          if(tem->next==NULL)
          {
                 break;            
            }  
             tem=tem->next;            
        }
        printf("空间使用情况：%d块已用，%d未用。\n",max-i,i);
}     


void copy_file(char path[],char filename[])
{
	struct file *tem1=cur_dir->firstfile;
	struct blo *tem2=&idle;
	struct file *tem3=(file *)malloc(sizeof(file));
	block tem4;
	block tem5=idle.next;

	struct file *tem;
	char *h=path;
	char *c=path;
	char dname[20];
	int len,n=0;
//	printf("+++++%s\n",path);
	while(tem1!=NULL)
	{
		if(strcmp(tem1->filename,filename)==0)
		{
			len=tem1->length;
			break;
		}
		tem1=tem1->next;
	}
	if(tem1==NULL)
	{
		printf("没有该文件，请检查后重新输入。\n");
		return;
	}
	 while(tem2->next!=NULL)
	 {
		 tem2=tem2->next;
		 n++;
	 }
	 if(len>n)
	 {
		 printf("存储空间不足，复制文件失败。");
		 return;
	 }


	 cur_dir=&root;
	 head.cur=&root;
	 head.next=NULL;


	while(h!=NULL)
	{
		h=strchr(c,'\\');
		if(h!=NULL)
		{
			strncpy(dname,c,h-c);			
			dname[h-c]='\0';
			if(c!=path)
			{
				display_dir(dname);
			//	printf("+++++%s\n",dname);
			}
			c=h+1;	
		}

	}

	   display_dir(c);

	//printf("$$$++%s\n",dname);
	tem=cur_dir->firstfile;
	strcpy(dname,filename);

	while(tem!=NULL)
	{
		if(strcmp(tem->filename,filename)==0)
		{
			
			strcat(dname,"@");
			printf("文件重名，新文件命名为%s。\n",dname);
			break;
		}
	}
	tem4=tem1->first;
	strcpy(tem3->filename,dname);
	tem3->first=tem5;
	tem3->length=len;
	tem3->next=NULL;
	for(n=0;n<len-1;n++)
	{
		strcpy(tem5->c,tem4->c);
		tem5=tem5->next;
		tem4=tem4->next;
	}
	strcpy(tem5->c,tem4->c);
	idle.next=tem5->next;
	tem5->next=NULL;

	if(tem==NULL)
	{
		cur_dir->firstfile=tem3;
	}
	else
	{
		while(tem->next!=NULL)
		{
			tem=tem->next;
		}
		tem->next=tem3;
	}
	printf("文件复制成功，当前目录已转至新目录。\n");


}




void move_file(char path[],char filename[])
{
	struct file *tem1=cur_dir->firstfile;
	struct blo *tem2=&idle;
	struct file *tem3=(file *)malloc(sizeof(file));
	block tem4;

	struct file *tem,*tem5=tem1;
	char *h=path;
	char *c=path;
	char dname[20];
	int len;

	while(tem1!=NULL)
	{
		if(strcmp(tem1->filename,filename)==0)
		{
			len=tem1->length;
			break;
		}
		tem5=tem1;
		tem1=tem1->next;
	}

	if(tem1==NULL)
	{
		printf("没有该文件，请检查后重新输入。\n");
		return;
	}

	 cur_dir=&root;
	 head.cur=&root;
	 head.next=NULL;


	while(h!=NULL)
	{
		h=strchr(c,'\\');
		if(h!=NULL)
		{
			strncpy(dname,c,h-c);			
			dname[h-c]='\0';
			if(c!=path)
			{
				display_dir(dname);
			//	printf("+++++%s\n",dname);
			}
			c=h+1;	
		}

	}

	   display_dir(c);

	//printf("$$$++%s\n",dname);
	tem=cur_dir->firstfile;
	strcpy(dname,filename);

	while(tem!=NULL)
	{
		if(strcmp(tem->filename,filename)==0)
		{
			
			strcat(dname,"@");
			printf("文件重名，新文件命名为%s。\n",dname);
			break;
		}
	}
	tem4=tem1->first;
	strcpy(tem3->filename,dname);
	tem3->first=tem4;
	tem3->length=len;
	tem3->next=NULL;

	if(tem5==tem1)
	{
		cur_dir->firstfile=NULL;
	}
	else
	{
		tem5->next=tem1->next;
	}
	free(tem1);

	

	if(tem==NULL)
	{
		cur_dir->firstfile=tem3;
	}
	else
	{
		while(tem->next!=NULL)
		{
			tem=tem->next;
		}
		tem->next=tem3;
	}
	printf("文件移动成功，当前目录已转至新目录。\n");

}

void rename_file(char filename[],char newname[])
{
	struct file *tem=cur_dir->firstfile;
	while(tem!=NULL)
	{
		if(strcmp(tem->filename,filename)==0)
		{
			strcpy(tem->filename,newname);
			printf("更名成功。\n");
			return;
		}
		tem=tem->next;
	}
	printf("没有该文件，请检查后重新输入。\n");

}

	void append_file(char filename[],char con[])
	{
		struct file *tem1=cur_dir->firstfile;
		while(tem1!=NULL)
		{
			if(strcmp(tem1->filename,filename)==0)
			{
				break;
			}
			tem1=tem1->next;
		}
		if(tem1==NULL)
		{
			printf("没有该文件，请检查后重新输入。\n");
			return;
		}


		char tem[filemax];
		strcpy(tem,read_file(filename,0));
	//	printf("1");
		strcat(tem,con);
	//	printf("2");
		del_file(filename,0);
	//	printf("3");
		create_file(filename,tem,0);
		printf("追加文件内容成功。\n");

	}

	void edit_file(char filename[],int beg,char con[])
	{
		struct file *tem1=cur_dir->firstfile;
		while(tem1!=NULL)
		{
			if(strcmp(tem1->filename,filename)==0)
			{
				break;
			}
			tem1=tem1->next;
		}
		if(tem1==NULL)
		{
			printf("没有该文件，请检查后重新输入。\n");
			return;
		}

		char tem[filemax];
		char tem2[filemax];
		int len=strlen(con);
		strcpy(tem,read_file(filename,0));
		strcpy(tem2,tem);
		strcpy(tem+beg,con);
		strcat(tem,tem2+beg+len);
		del_file(filename,0);
		create_file(filename,tem,0);
		printf("编辑文件内容成功。\n");

	}

	void login(char username[])
	{
		struct user *tem=&first;
		while(tem!=NULL)
		{
			if(strcmp(tem->username,username)==0)
			{
				if(tem->quan==2)
				{
			    	symbol=2;
				}
				else
				{
					symbol=1;
				}
				if(strcmp(tem->username,"admin")==0)
				{
					symbol=3;
				}
				printf("登录成功。\n");
				return;
			}
			tem=tem->next;
		}
		printf("没有该用户，请检查后重新输入。\n");

	}




	void add_user(char username[],int quan)
	{
		if(symbol!=3)
		{
			printf("对不起，只有管理员能添加用户。\n");
			return;
		}
		
		struct user *tem=&first;
		struct user *tem1=tem;
		while(tem!=NULL)
		{
			if(strcmp(tem->username,username)==0)
			{
				printf("该用户已存在，请检查后重新输入。\n");
				return;
			}
			tem1=tem;
			tem=tem->next;
		}
		struct user *newu=(user *)malloc(sizeof(user));
		newu->next=NULL;
		newu->quan=quan;
		strcpy(newu->username,username);
		tem1->next=newu;
		printf("创建用户成功。\n");
	}



	void remove_user(char username[])
	{
		if(symbol!=3)
		{
			printf("对不起，只有管理员能移除用户。\n");
			return;
		}

		struct user *tem=&first;
		struct user *tem1=tem;
		while(tem!=NULL)
		{
			if(strcmp(tem->username,username)==0)
			{
				
				break;
			}
			tem1=tem;
			tem=tem->next;
		}
		if(tem==NULL)
		{
			printf("没有该用户，请检查后重新输入。\n");
			return;
		}
		tem1->next=tem->next;
		free(tem);


		printf("删除用户成功。\n");

	}


	void chomd(char username[],int quan)
	{
		if(symbol!=3)
		{
			printf("对不起，只有管理员能管理用户。\n");
			return;
		}

		struct user *tem=&first;
		struct user *tem1=tem;
		while(tem!=NULL)
		{
			if(strcmp(tem->username,username)==0)
			{
				
				break;
			}
			tem1=tem;
			tem=tem->next;
		}
		if(tem==NULL)
		{
			printf("没有该用户，请检查后重新输入。\n");
			return;
		}
		tem->quan=quan;
		printf("用户%s权限修改成功。\n",username);

	}


	void see()
	{
		struct user *tem=&first;
		printf("\t\t用户名\t\t\t权限\n");
		char *a="R";
		char *b="WR";
		while(tem!=NULL)
		{
			if(tem->quan==1)
			{
				printf("\t\t%s\t\t\t%s\n",tem->username,a);
			}
			else
			{
				printf("\t\t%s\t\t\t%s\n",tem->username,b);
			}
			tem=tem->next;
		}


	}










void help()  //显示帮助信息
{
 //printf("注意：创建的文件长度 < 100\n\n"); //说明文件
 printf(" 0.初始化---------------------format\n");
 printf(" 1.显示空间使用情况-----------df\n");
 printf(" 2.创建目录-------------------md-----------(md+目录名)  \n");
 printf(" 3.删除目录-------------------rd-----------(rd+目录名)   \n");
 printf(" 4.显示目录-------------------dir   \n");
 printf(" 5.进入目录-------------------cd-----------(cd+目录名)   \n");
 printf(" 6.创建文件-------------------create-------(create+文件名+文件内容)  \n");
 printf(" 7.删除文件-------------------delete-------(delete+文件名) \n");
 printf(" 8.读文件---------------------read---------(read++文件名)\n");
 printf(" 9.文件拷贝-------------------copy---------(copy+文件名+路径名)\n");
 printf("10.文件移动-------------------move---------(move+文件名+路径名)\n");
 printf("11.文件更名-------------------rename-------(rename+文件名+新文件名)\n");
 printf("12.追加文件内容---------------append-------(append+文件名+追加内容)\n");
 printf("13.编辑文件内容---------------ed-----------(ed+文件名+修改起始位置+内容)\n");
 printf("14.权限控制-------------------chomd--------(chomd+用户名+权限)\n");
 printf("15.增加用户-------------------add----------(add+用户名+权限)\n");
 printf("16.移除用户-------------------remove-------(remove+用户名)\n");
 printf("17.用户登录-------------------login--------(login+用户名)  \n");
 printf("18.查看用户权限---------------see  \n");
 printf("19.返回上一级目录-------------cd..  \n");
 printf("20.显示帮助命令---------------help  \n");
 printf("22.退出文件模拟---------------quit  \n");
 printf("注：权限设置：1 可读不可写；2 可读可写。\n");
 
}
                                            
int main()        //主函数
{
 char tmp[20],com[20],tmp2[filemax],tmp3[100];
 

 int i, j=0,p=-1,len=0;
 int q=-1;

 help();


 strcpy(cmd[0].com,"format");    //将各个命令存进命令表
 strcpy(cmd[1].com,"df");
 strcpy(cmd[2].com,"md");
 strcpy(cmd[3].com,"rd");
 strcpy(cmd[4].com,"dir");
 strcpy(cmd[5].com,"cd");
 strcpy(cmd[6].com,"create");
 strcpy(cmd[7].com,"delete");
 strcpy(cmd[8].com,"read");
 strcpy(cmd[9].com,"copy");
 strcpy(cmd[10].com,"move");
 strcpy(cmd[11].com,"rename");
 strcpy(cmd[12].com,"append");
 strcpy(cmd[13].com,"ed");
 strcpy(cmd[14].com,"chomd");
 strcpy(cmd[15].com,"add");
 strcpy(cmd[16].com,"remove");
 strcpy(cmd[17].com,"login");
 strcpy(cmd[18].com,"see");
 strcpy(cmd[19].com,"cd..");
 strcpy(cmd[20].com,"help");
 strcpy(cmd[21].com,"quit");

   format(); 

while(1)
{
	printf("请输入用户名:");
	scanf("%s",tmp);
	login(tmp);
	if(symbol>0)
	{
		break;
	}
}



while(1)
{

	//printf("===%s\n",cur_dir->dirname);

	struct list *tem=&head;
	while(tem!=NULL)
	{
		printf("%s\\",tem->cur->dirname);
		tem=tem->next;
	}

	scanf("%s",com);//输入命令
	for(i=0;i<22;i++)
	{
		if(strcmp(com,cmd[i].com)==0)
		{
			p=i;
			break;
		}
	}




	if(i==22)
	{
		p=23;
	}
	//	printf("----%d\n",p);

	switch(p)
	{
	case 0:format();
		if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		break;
    case 1:display_sys();
		break;
    case 2:scanf("%s",tmp);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		create_dir(tmp); 
		break;
    case 3:scanf("%s",tmp);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		del_dir(tmp);
		break;
    case 4:display_curdir();
		break;
    case 5:scanf("%s",tmp);
		display_dir(tmp);
		break;
    case 6:scanf("%s",tmp);
		scanf("%s",tmp2);
		if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		create_file(tmp,tmp2,1);
		break;
    case 7:scanf("%s",tmp);
		if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		del_file(tmp,1); 
		break;
    case 8:scanf("%s",tmp);
		 read_file(tmp,1);
		break;
    case 9:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		copy_file(tmp3,tmp);
		break;
    case 10:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		move_file(tmp3,tmp);
		break;
    case 11:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		rename_file(tmp,tmp3);
		break;
    case 12:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		append_file(tmp,tmp3);
		break;
    case 13:scanf("%s",tmp);
		scanf("%d",&q);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("对不起，你没有写的权限。\n");
			continue;
		}
		edit_file(tmp,q,tmp3);
		break;
    case 14:scanf("%s",tmp);
		scanf("%d",&q);
		chomd(tmp,q);
		break;
    case 15:scanf("%s",tmp);
		scanf("%d",&q);		
		add_user(tmp,q);		
		break;
    case 16:scanf("%s",tmp);
		remove_user(tmp);
		break;
    case 17:scanf("%s",tmp);
		login(tmp);
		break;
	case 18:see();
	//	login(tmp);
		break;
    case 19:back_dir();
		break;
    case 20:help();
	//	login(tmp);
		break;
    case 21:exit(1);
		//login(tmp);
		break;
	default:printf("没有这个命令，请检查后重新输入。\n");
	}

}


}
