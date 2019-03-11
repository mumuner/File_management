#include "stdio.h" 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h>
#include <malloc.h>

#define blen 10//���С 
#define max 100//�ռ��С����������� 
#define filemax 100//�ļ���󳤶�
 
struct command//���� 
{
 char com[10];
}cmd[22];

struct blo//����� 
{
       int n;//��� 
       char c[blen];//������С 
       struct blo *next;//��һ������� 
}tblock[max];

typedef struct blo *block;


struct file//�ļ�
{
  char filename[20];
  int  length;
 // char quan;//Ȩ�޿��� a�� �ɶ���д��b��ɶ�����д 
  struct blo *first;//�ļ��ĵ�һ�������   
  struct file *next;//ͬĿ¼�µ���һ���ļ� 
};

struct dir//�ļ���
{
  char dirname[20];
  struct dir *same;//ͬһ��Ŀ¼ 
  struct dir *next;//��һ��Ŀ¼
  struct file *firstfile;//��Ŀ¼�µĵ�һ���ļ� 
};    

struct user
{
	int quan;
    char username[20];
	struct user *next;
 };
 
struct list//�ļ�·������
{
	struct dir *cur;
	struct list *next;
};

struct blo idle;//���б� ��ͷ 
struct dir root;//��Ŀ¼ 
struct dir *cur_dir; //��ǰĿ¼ 
struct list head;
struct user first;
int symbol=0;

void format()   //��ʽ��
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

     printf("��ʼ�����\n");
     printf("�����ļ�ģ��ϵͳ......\n\n");
     
     
 }
 
 
void read_system(FILE *fp)   //����ϵͳ�ļ�����Ϣ
{
     
     } 
     
     
char* read_file(char filename[],int q)//�����ļ�����
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
			printf("%s�ļ�����Ϊ��",filename);
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
	printf("û�и��ļ���������������롣\n");
	}
	return NULL;
 }
     
     
void write_system(FILE *fp) //����ϵͳ�ļ�����Ϣ
 {
      
  }
  
void callback(int length)    //���մ��̿ռ�
 {
     
     }
     
void allot(int length)     //����ռ�
{
     
     } 
     
     
void create_file(char filename[],char con[],int q) //�����ļ�
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
			 printf("���ļ��Ѵ��ڣ�������������롣\n");
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
		 printf("�洢�ռ䲻�㣬�����ļ�ʧ�ܡ�\n");
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
	 printf("�ļ������ɹ���\n");
	 }
        
}
     
     
     
void create_dir(char filename[])    //����Ŀ¼
{
	struct dir *newd=(dir *)malloc(sizeof(dir));
	struct dir *tem=cur_dir->next;
//	printf("%s",cur_dir->dirname);
	while(tem!=NULL)
	{
		if(strcmp(tem->dirname,filename)==0)
		{
			printf("�Ѵ��ڸ�Ŀ¼��������������롣\n");
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
	printf("����Ŀ¼�ɹ���\n");

}
	
void del_file(char filename[],int q)     //ɾ���ļ�
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

			 printf("�ļ�ɾ���ɹ���\n");
			 }
			 return;
		 }
		 tem1=tem;
		 tem=tem->next;
	 }
	 if(q==1)
	 {
	 printf("û�и��ļ���������������롣\n");
	 }

	 }
     
void del_dir(char filename[])     //ɾ��Ŀ¼   ��Ҫ�ж�Ŀ¼��ʱ��Ϊ��,��Ϊ�վͲ�ɾ��
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


            printf("Ŀ¼ɾ���ɹ���\n");
        }
        else
        {
            printf("Ŀ¼��Ϊ�գ�����ɾ����\n");

        }
        return;
     } 
	 tem1=tem;
     tem=tem->same;
	 i++;
   }
     printf("û�и�Ŀ¼��������������롣\n");
}  
     
void display_curdir()         //��ʾ��ǰĿ¼�µ��ļ��б�
{
    int n=0,m=0;
    struct dir *tem=cur_dir->next;
    struct file *tem1=cur_dir->firstfile;
	//printf("-----%s\n",cur_dir->next->dirname);
    while(tem!=NULL)
    {
       printf("Ŀ¼��%s\n",tem->dirname);
       tem=tem->same;
       n++;
     }
     while(tem1!=NULL)
     {
        printf("�ļ���%s\t���ȣ�%d\n",tem1->filename,tem1->length);
        tem1=tem1->next;
        m++;
       }
       printf("%d��Ŀ¼,%d���ļ�\n",n,m);
     

}    
        
     
void display_dir(char filename[])     //����ָ����Ŀ¼
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
	printf("û�и�Ŀ¼��������������롣\n");


}



void open_file(char filename[])        //���ļ�
{
     
     }



void back_dir()         //������һ��Ŀ¼
{
	struct list *tem=&head;
	if(tem->next==NULL)
	{
		printf("��Ϊ��Ŀ¼��\n");
		return;
	}


     while(tem->next->next!=NULL)
	 {
		 tem=tem->next;
	 }
	 tem->next=NULL;
	 cur_dir=tem->cur;
}




void display_sys()        //��ʾϵͳ��Ϣ������ʹ�������
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
        printf("�ռ�ʹ�������%d�����ã�%dδ�á�\n",max-i,i);
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
		printf("û�и��ļ���������������롣\n");
		return;
	}
	 while(tem2->next!=NULL)
	 {
		 tem2=tem2->next;
		 n++;
	 }
	 if(len>n)
	 {
		 printf("�洢�ռ䲻�㣬�����ļ�ʧ�ܡ�");
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
			printf("�ļ����������ļ�����Ϊ%s��\n",dname);
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
	printf("�ļ����Ƴɹ�����ǰĿ¼��ת����Ŀ¼��\n");


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
		printf("û�и��ļ���������������롣\n");
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
			printf("�ļ����������ļ�����Ϊ%s��\n",dname);
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
	printf("�ļ��ƶ��ɹ�����ǰĿ¼��ת����Ŀ¼��\n");

}

void rename_file(char filename[],char newname[])
{
	struct file *tem=cur_dir->firstfile;
	while(tem!=NULL)
	{
		if(strcmp(tem->filename,filename)==0)
		{
			strcpy(tem->filename,newname);
			printf("�����ɹ���\n");
			return;
		}
		tem=tem->next;
	}
	printf("û�и��ļ���������������롣\n");

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
			printf("û�и��ļ���������������롣\n");
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
		printf("׷���ļ����ݳɹ���\n");

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
			printf("û�и��ļ���������������롣\n");
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
		printf("�༭�ļ����ݳɹ���\n");

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
				printf("��¼�ɹ���\n");
				return;
			}
			tem=tem->next;
		}
		printf("û�и��û���������������롣\n");

	}




	void add_user(char username[],int quan)
	{
		if(symbol!=3)
		{
			printf("�Բ���ֻ�й���Ա������û���\n");
			return;
		}
		
		struct user *tem=&first;
		struct user *tem1=tem;
		while(tem!=NULL)
		{
			if(strcmp(tem->username,username)==0)
			{
				printf("���û��Ѵ��ڣ�������������롣\n");
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
		printf("�����û��ɹ���\n");
	}



	void remove_user(char username[])
	{
		if(symbol!=3)
		{
			printf("�Բ���ֻ�й���Ա���Ƴ��û���\n");
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
			printf("û�и��û���������������롣\n");
			return;
		}
		tem1->next=tem->next;
		free(tem);


		printf("ɾ���û��ɹ���\n");

	}


	void chomd(char username[],int quan)
	{
		if(symbol!=3)
		{
			printf("�Բ���ֻ�й���Ա�ܹ����û���\n");
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
			printf("û�и��û���������������롣\n");
			return;
		}
		tem->quan=quan;
		printf("�û�%sȨ���޸ĳɹ���\n",username);

	}


	void see()
	{
		struct user *tem=&first;
		printf("\t\t�û���\t\t\tȨ��\n");
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










void help()  //��ʾ������Ϣ
{
 //printf("ע�⣺�������ļ����� < 100\n\n"); //˵���ļ�
 printf(" 0.��ʼ��---------------------format\n");
 printf(" 1.��ʾ�ռ�ʹ�����-----------df\n");
 printf(" 2.����Ŀ¼-------------------md-----------(md+Ŀ¼��)  \n");
 printf(" 3.ɾ��Ŀ¼-------------------rd-----------(rd+Ŀ¼��)   \n");
 printf(" 4.��ʾĿ¼-------------------dir   \n");
 printf(" 5.����Ŀ¼-------------------cd-----------(cd+Ŀ¼��)   \n");
 printf(" 6.�����ļ�-------------------create-------(create+�ļ���+�ļ�����)  \n");
 printf(" 7.ɾ���ļ�-------------------delete-------(delete+�ļ���) \n");
 printf(" 8.���ļ�---------------------read---------(read++�ļ���)\n");
 printf(" 9.�ļ�����-------------------copy---------(copy+�ļ���+·����)\n");
 printf("10.�ļ��ƶ�-------------------move---------(move+�ļ���+·����)\n");
 printf("11.�ļ�����-------------------rename-------(rename+�ļ���+���ļ���)\n");
 printf("12.׷���ļ�����---------------append-------(append+�ļ���+׷������)\n");
 printf("13.�༭�ļ�����---------------ed-----------(ed+�ļ���+�޸���ʼλ��+����)\n");
 printf("14.Ȩ�޿���-------------------chomd--------(chomd+�û���+Ȩ��)\n");
 printf("15.�����û�-------------------add----------(add+�û���+Ȩ��)\n");
 printf("16.�Ƴ��û�-------------------remove-------(remove+�û���)\n");
 printf("17.�û���¼-------------------login--------(login+�û���)  \n");
 printf("18.�鿴�û�Ȩ��---------------see  \n");
 printf("19.������һ��Ŀ¼-------------cd..  \n");
 printf("20.��ʾ��������---------------help  \n");
 printf("22.�˳��ļ�ģ��---------------quit  \n");
 printf("ע��Ȩ�����ã�1 �ɶ�����д��2 �ɶ���д��\n");
 
}
                                            
int main()        //������
{
 char tmp[20],com[20],tmp2[filemax],tmp3[100];
 

 int i, j=0,p=-1,len=0;
 int q=-1;

 help();


 strcpy(cmd[0].com,"format");    //�����������������
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
	printf("�������û���:");
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

	scanf("%s",com);//��������
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
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		break;
    case 1:display_sys();
		break;
    case 2:scanf("%s",tmp);
				if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		create_dir(tmp); 
		break;
    case 3:scanf("%s",tmp);
				if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
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
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		create_file(tmp,tmp2,1);
		break;
    case 7:scanf("%s",tmp);
		if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
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
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		copy_file(tmp3,tmp);
		break;
    case 10:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		move_file(tmp3,tmp);
		break;
    case 11:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		rename_file(tmp,tmp3);
		break;
    case 12:scanf("%s",tmp);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
			continue;
		}
		append_file(tmp,tmp3);
		break;
    case 13:scanf("%s",tmp);
		scanf("%d",&q);
		scanf("%s",tmp3);
				if(symbol==1)
		{
			printf("�Բ�����û��д��Ȩ�ޡ�\n");
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
	default:printf("û��������������������롣\n");
	}

}


}
