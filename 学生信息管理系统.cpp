#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<math.h>
#include<time.h>
int add(void);
int del(void);
int modify(void);
int search(void);
void outputsea(int);
void outputtablehead(void);
void outputcour(void);
int input(int,int);
int import(void);
int importsave(void);
int export(void);
int exportsave(void);
int sortstu(void);
int modcour(void);
int advanced(void);
#define CHSIZE sizeof(char)
int st_num=0;//全局变量：当前储存的学生总数
const char ChineseCharacterSample[]="例";
#define CCByte (sizeof(ChineseCharacterSample)-1)//获取一个汉字在用户操作系统编码模式下所占的字节数

struct infcourse{
	char name[15];
	double credit;
};//储存课程信息
struct infcourse course[10+1]={ {"公共课1",2.0},{"专业课1",3.0},{"专业课2",4.0} };//设置默认课程信息
int num_course=3;
double credit_sum=9.0;
struct infgrade{
	double gpa;
    double score[10];
};

struct information{
	char number[21];
	char name[21];
	char schclass[21];
	struct infgrade grade;
}st[10005];
//学生信息，其中学生成绩是嵌套的结构体变量
struct information* psearch (char* s);

int sortstu_optcour;
int cmp1(const void* a,const void* b);
int cmp2(const void* a,const void* b);
int cmp3(const void* a,const void* b);
int cmp4(const void* a,const void* b);
int cmp5(const void* a,const void* b);
int cmp6(const void* a,const void* b);
int cmp7(const void* a,const void* b);


int main()
{
	printf("┌──────────────────────────────────────┐\n");
	printf("│      欢迎使用学生信息管理系统v1.0    │\n");
	printf("└──────────────────────────────────────┘\n");
	short option;
	int isyes;
	printf("请输入选项序号，以回车键结束：\n");
	printf("[1]增加学生信息\n");
	printf("[2]删除学生信息\n");
	printf("[3]修改学生信息\n");
	printf("[4]查找学生信息\n");
	printf("[5]导入学生信息\n");
	printf("[6]导出学生信息\n");
	printf("[7]排序学生信息\n");
	printf("[8]编辑课程信息\n");
	printf("[9]其他功能\n");
	printf("[0]结束程序\n");
	printf("初次使用系统，请先输入8设置课程信息\n");
	//打开程序显示的主菜单
	while(1)
	{
		scanf("%hd",&option);
		fflush(stdin);
		switch (option){
		case 1:add();break;
		case 2:del();break;
		case 3:modify();break;
		case 4:search();break;
		case 5:import();break;
		case 6:export();break;
		case 7:sortstu();break;
		case 8:modcour();break;
		case 9:advanced();break;
		case 0:break;
		default:printf("无效的指令。请重新输入：\n");fflush(stdin);break;
		}
		
		if(option==0)
		{
			printf("您确实要退出程序吗？您的所有未导出的数据都不会被保存。\n");
			printf("如果是，请输入100；如果不是，输入任意其他数字\n");
			scanf("%d",&isyes);
			fflush(stdin);
			if(isyes==100)
				break;
		}
		option=-1;
		printf("您已回到主菜单。请继续输入序号：\n");
		printf("[1]增加学生信息\n");
		printf("[2]删除学生信息\n");
		printf("[3]修改学生信息\n");
		printf("[4]查找学生信息\n");
		printf("[5]导入学生信息\n");
		printf("[6]导出学生信息\n");
		printf("[7]排序学生信息\n");
		printf("[8]编辑课程信息\n");
		printf("[9]其他功能\n");
		printf("[0]结束程序\n");
	}
	printf("程序已退出！\n感谢您的使用！欢迎下次再来！\n");
	
	system("PAUSE");
	return 0;}

int add(void)
{
	if(st_num>=10000) {printf("储存空间已满!\n");return 1;}
	printf("请依次输入每位学生的学号、姓名、班级和分科目成绩：\n");
	printf("每一行只能输入一位学生的一项信息，以回车结束。\n");
	printf("***输入#返回主菜单***\n");
	while(1)
	{
		if(input(st_num,1)==1)  break;//调用input函数输入学生信息
		st_num++;
	}
	return 0;
}

int del(void)
{
	printf("[1]删除一条记录\n");
	printf("[2]删除所有记录\n");
	printf("[0]返回主菜单\n");
	int option,isyes;
	char cache[1005];
	struct information* p;
	int idx;
	while(1)
	{
		scanf("%d",&option);
		fflush(stdin);
		if(option==0) return 0;
		if(option!=1&&option!=2)
		{printf("无效的输入！请重试\n");continue;}
		break;
	}
	if(option==2)
	{
		printf("您要删除所有学生信息吗？\n");
		printf("如果是，请键入999；如果不是，键入任意其他数字返回主菜单\n");
		scanf("%d",&isyes);
		fflush(stdin);
		if(isyes!=999)  return 0;
		printf("再次确认，您确实要删除 全部 学生信息吗？\n");
		printf("如果是，请键入1；如果不是，键入任意其他数字返回主菜单\n");
		printf("现在程序暂停5秒钟...\n");
		fflush(stdin);
		Sleep(5000);
		fflush(stdin);
		printf("请您最后一次确认，是否要删除所有学生信息？\n");
		scanf("%d",&isyes);
		fflush(stdin);
		if(isyes!=1)  return 0;
		printf("已清空所有学生信息！\n");
		printf("如果您想撤销删除，请输入1，否则，请输入任意其他数字，程序将返回主菜单\n");
		scanf("%d",&isyes);
		fflush(stdin);
		if(isyes==1)  {printf("您已成功撤销删除！\n");return 0;}
		st_num=0;
		return 0;
	}
	
	if(option==1)
	{
		while(1)
		{
			printf("请输入要删除的学生的学号，以回车结束\n");
			scanf("%s",cache);
			fflush(stdin);
			if(cache[0]=='#') return 0;
			if(strlen(cache)>=20)  {printf("超出限定长度！请重新输入\n");continue;}
			break;
		}
		p=psearch(cache);//获取学生信息的地址
		if(p==NULL){printf("未找到相应的信息！\n");return 1;}
		printf("您确实要删除学生【%s】的信息吗？\n",p->name);
		printf("如果是，请键入1，否则请键入任意其他数字回到主菜单\n",p->name);
		scanf("%d",&isyes);
		fflush(stdin);
		if(isyes!=1)  return 0;
		for(idx=p-st;idx<=st_num-2;idx++)//删除学生信息后，数组循环前移
			st[idx]=st[idx+1];
		st_num--;
		printf("您已成功删除。\n");
		
	}
	return 0;
}

int input(int index,int typ)
{
	//第二个形参typ表示调用函数的类型，Type为1时是添加学生信息，为2时是修改学生信息
	char cache[1000];
	char number_cache[21];
	char name_cache[21];
	char schclass_cache[21];
	double dou_cache[11];
	double scoresum;
	int i;
	int rep=0;
	while(1)
	{
		while(1)//number
		{
			if(typ==2) break;
			printf("学号：");
			scanf("%100s",cache);
			fflush(stdin);
			if(cache[0]=='#') return 1;
			if(strlen(cache)>=20)  {printf("超出限定长度！请重新输入\n");continue;}
			for(i=0;i<=st_num-1;i++)
				if(!strcmp(cache,st[i].number))
				{printf("学号存在重复！请重新输入\n");rep=1;break;}
				if(rep==1){rep=0;continue;}
				strcpy(number_cache,cache);
				break;
		}
		while(1)//name
		{
			printf("姓名：");
			gets(cache);
			fflush(stdin);
			if(cache[0]=='#') return 1;
			if(strlen(cache)>=20)  {printf("超出限定长度！请重新输入\n");continue;}
			strcpy(name_cache,cache);
			break;
		}
		while(1)//schclass
		{
			printf("班级：");
			scanf("%100s",cache);
			fflush(stdin);
			if(cache[0]=='#') return 1;
			if(strlen(cache)>=20)  {printf("超出限定长度！请重新输入\n");continue;}
			strcpy(schclass_cache,cache);
			break;
		}
		while(1)//grade
		{
			for(i=0;i<=num_course-1;i++)
			{
				printf("%s分数：",course[i].name);
				scanf("%lf",&dou_cache[i]);
				fflush(stdin);
				if(dou_cache[i]==-1) return 1;
				if(dou_cache[i]>=1001||dou_cache[i]<=-1001)
				{
					printf("您输入的成绩无效！成绩将被置为零！\n");
					dou_cache[i]=0;
				}
				
			}
			break;
		}
		
		if(typ!=2)
		    strcpy(st[index].number,  number_cache);
		strcpy(st[index].name,  name_cache);
		strcpy(st[index].schclass,  schclass_cache);
		scoresum=0;
		for(i=0;i<=num_course-1;i++)
		{
			st[index].grade.score[i]=dou_cache[i];
			scoresum=scoresum+st[index].grade.score[i]*course[i].credit;
		}
		st[index].grade.gpa=scoresum/credit_sum;
		printf("该生信息录入完毕！\n");
		return 0;
	}
}

struct information* psearch (char* s)
{//传入的参数为储存学号信息的字符串地址
	int i,idx=-1;
	for(i=0;i<=st_num-1;i++)
		if(!strcmp(s,st[i].number))
		{
			idx=i;
			return &st[idx];//查找到学生信息，返回对应指针
			break;
		}
		if(idx==-1)
		{
			return NULL;
		}
		return NULL;//找不到学生信息，返回空指针
}

int modify(void)
{
	char cache[1005];
	struct information* p;
	int idx;
	
	while(1)
	{
		printf("请输入要修改的学生的学号，以回车结束，输入#可返回主菜单\n");
		scanf("%s",cache);
		fflush(stdin);
		if(cache[0]=='#') return 0;
		if(strlen(cache)>=20)  {printf("超出限定长度！请重新输入\n");continue;}
		break;
	}
	p=psearch(cache);
	if(p==NULL)  {printf("未找到该生信息！\n");return 1;}
	idx=p-st;
	printf("查询到该生原有信息如下：\n");
	outputtablehead();
	outputsea(idx);
	printf("请键入修改后的该生信息，注意，学号不能修改，如果您输入错了学号，请删除后重新添加\n");
				
				if( input(idx,2)==0 )//调用input函数输入修改后的学生信息
				printf("信息已修改！\n");
				return 0;
}

void outputsea(int index)
{
	int icour;
	printf("%9s\t%7s\t%20s\t%9.2f",st[index].number,st[index].name,st[index].schclass,st[index].grade.gpa);
	for(icour=0;icour<=num_course-1;icour++)
		{  printf("\t%12.1f",st[index].grade.score[icour]);  }
	printf("\n");

}

void outputtablehead(void)
{
	int i;
	printf("%9s\t%7s\t%20s\t%9s","学号","姓名","班级","加权平均成绩");
	for(i=0;i<=num_course-1;i++)
			printf("\t%12s",course[i].name);
	printf("\n");

}

int search(void)
{
	printf("[1]输出所有学生成绩\n");
	printf("[2]按学号精确查找\n");
	printf("[3]按中文姓名模糊查找\n");
	int option;
	int i,j,k,sealen;
	int dif,size;
	int outcome;
	long idx=-1;
	char cache[1005];
	char name_search[17];
	char name_cmp[17];
	scanf("%d",&option);
	fflush(stdin);
	if(option!=1&&option!=2&&option!=3&&option!=0)
	{
		printf("无效的输入！\n");
	}
	if(option==0) return 0;
	if(option==3)
	{
		printf("请输入学生姓名，不超过4个汉字：\n");
		while(1)//name
		{
			gets(cache);
			fflush(stdin);
			if(cache[0]=='#') return 1;
			if(strlen(cache)>=17)  {printf("超出限定长度！请重新输入\n");continue;}
			strcpy(name_search,cache);
			break;
		}
		outcome=0;
		size=CCByte;
		sealen=strlen(name_search);
		outputtablehead();
		for(i=0;i<=st_num-1;i++)
		{
			dif=strlen(st[i].name)-sealen;
			for(j=0;j<=dif;j=j+size)//每次位移size个字节，size为一个汉字所占的字节数
			{
				for(k=0;k<=sealen-1;k++)//逐个字符比对
					name_cmp[k]=st[i].name[j+k];
				if( strncmp(name_search,name_cmp,sealen)==0 )//如果找到输出响应结果
				{
					outputsea(i);
					outcome++;
					break;
				}
			}
		}
		printf("已完成所有查找，共找到%d条结果。\n\n",outcome);

	}
	if(option==1)
	{
		outputtablehead();
		for(i=0;i<=st_num-1;i++)
			outputsea(i);
		return 0;
	}
	if(option==2)
	{
		while(1)
		{
			printf("请输入学号，以回车结束：\n");
			scanf("%100s",cache);
			fflush(stdin);
			idx=-1;
			if(cache[0]=='#') return 1;
			if(strlen(cache)>=20)  {printf("超出限定长度！请重新输入\n");continue;}
			for(i=0;i<=st_num-1;i++)
				if(!strcmp(cache,st[i].number))
				{
					idx=i;
					break;
				}
				if(idx==-1)
				{
					printf("没有找到！\n");
					return 2;
				}
				printf("找到以下1条结果：\n\n");
				outputtablehead();
				outputsea(idx);
				printf("\n");
				return 0;
				
		}
	}
	return 0;
}


int import(void)
{
	printf("[1]从上次存档点导入\n");
	printf("[2]从外部txt文件导入\n");
	printf("[0]返回主菜单\n");
	int option;
	int old_num;
	while(1)
	{
		scanf("%d",&option);
		fflush(stdin);
		if(option==0) return 0;
		if(option!=1&&option!=2)
		{printf("无效的输入！请重试\n");continue;}
		break;
	}
	if(option==1)
		return importsave();
	
	printf("注意事项：\n");
	printf("*********************************\n");
	printf("请将欲导入的文件，命名为\"import.txt\"，以文本的形式，与本程序储存在同一目录下\n");
	printf("文件的每一行储存一个学生的信息\n");
	printf("每一行内，一个学生的不同信息以制表键Tab分割\n");
	printf("文件不要包含表头，每一行内，储存的信息依次是\n");
	printf("学生的学号、姓名、班级、各门课程的成绩\n");
	printf("各科成绩的顺序依次是：\n");
	int k;
	for(k=0;k<=num_course-1;k++)
		printf("[%6s]\t",course[k].name);
	printf("\n");
	printf("您不必也不能储存学生的总成绩，程序会根据您设置的学分，自动计算学生的加权平均成绩\n");
	printf("您可以将Excel中的信息复制到txt文件后导入\n");
	printf("除学生姓名外，其他信息不能包含空格\n");
	printf("文件导入前，请检查数据是否超出范围\n");
	printf("学生的学号、姓名、班级均不应超过20个字符（10个汉字）\n");
	printf("学生的学号不得有重复\n");
	printf("如果学号重复，程序只会读入第一条数据\n");
	printf("程序最多储存10000名学生信息，超出的部分不会被导入\n");
	printf("导入后会覆盖原有的学生信息\n");
	printf("请您自行仔细检查您的文件是否都符合上述要求\n");
	printf("【特别注意】当前系统中共有%d门课程，请确保与您文件中的课程数量一致！\n",num_course);
	printf("*********************************\n");
	printf("输入1将开始导入文件，否则将返回主菜单\n");
	scanf("%d",&k);
	fflush(stdin);
	if(k!=1) return 0;
	printf("即将开始导入");
	for(k=0;k<=2;k++)
	{
		Sleep(200);
		printf(". ");//每0.2s打印出一个点
		fflush(stdout);
	}
	old_num=st_num;
	printf("\n");
	FILE *fp;
	char number_cache[21];
	char name_cache[21];
	char schclass_cache[21];
	double grade_cache;
	int i,rep,skip;
	int icour;
	double scoresum;
	
	if  (( fp=fopen("import.txt","r") )==NULL)
	{
		printf("文件不存在或打开失败！\n");
		return 1;
	}
	skip=0;
	while( (!feof(fp)) &&(st_num<=10000) )
	{
		fscanf(fp,"%20s\t",number_cache);

		for(i=0;i<=st_num-1;i++)
		    if(!strcmp(number_cache,st[i].number))
			{skip++;rep=1;break;}
		if(rep==1)//如果学号重复，假装继续读取这一行的其他数据，但不写入学生信息
		{
			fscanf(fp,"%20[^\t]",name_cache);
		    fscanf(fp,"%20s\t",schclass_cache);
			for(icour=0;icour<=num_course-1;icour++)
			{ 
			fscanf(fp,"%lf",&grade_cache); 
			}
			fscanf(fp,"\n");
			rep=0;continue;
		}
		strcpy(st[st_num].number,number_cache);
		fscanf(fp,"%20[^\t]",st[st_num].name);
		fscanf(fp,"%20s\t",st[st_num].schclass);
		scoresum=0;
		for(icour=0;icour<=num_course-1;icour++)
		{ 
			fscanf(fp,"%lf",&st[st_num].grade.score[icour]); 
			scoresum=scoresum+st[st_num].grade.score[icour]*course[icour].credit ;
		}
		fscanf(fp,"\n");
		st[st_num].grade.gpa=scoresum/credit_sum;
		st_num++;
		
	}
	if(fclose(fp))
	{
		printf("文件关闭失败！\n");
		return 1;
	}
	printf("成功导入%d条数据！%d条数据因学号重复未被导入。\n",st_num-old_num,skip);
	return 0;
}


int importsave(void)
{
	int isyes,icour;
	int InputNumCour;
	FILE* fp;
	printf("导入学生将会覆盖现有学生信息\n");
	printf("如果学生数量超过最大限制，那么超出的部分将不会被导入\n");
	printf("是否继续？若是，请输入1\n");
	scanf("%d",&isyes);
	fflush(stdin);
	if(isyes!=1)
	{printf("您已取消导入！\n");return 2;}
	if  (( fp=fopen("SAVE.txt","r") )==NULL)
	{
		printf("文件不存在或打开失败！\n");
		return 1;
	}
	fscanf(fp,"%d\n",&InputNumCour);
	if(InputNumCour!=num_course)
	{
		printf("课程数量与上一次保存时不一致！请先回主菜单输入8设置课程信息！\n");
		return 4;
	}
	st_num=0;
	while( (!feof(fp)) &&(st_num<=10000) )
	{
		fscanf(fp,"%20s\t",st[st_num].number);
		fscanf(fp,"%20[^\t]",st[st_num].name);
		fscanf(fp,"%20s\t",st[st_num].schclass);
		for(icour=0;icour<=num_course-1;icour++)
		{ 
			fscanf(fp,"%lf",&st[st_num].grade.score[icour]); 
		}
		fscanf(fp,"%lf",&st[st_num].grade.gpa); 
		fscanf(fp,"\n");
		st_num++;
	}
	if(fclose(fp))
		printf("文件关闭失败！\n");
	if(st_num>=10001)
		printf("数量可能超过最大限制，部分数据可能未被导入！\n");
	printf("共导入了%d条数据。\n",st_num);
	printf("导入完成！\n");
	return 0;
}


int export(void)
{
	printf("[1]存档当前信息\n");
	printf("[2]导出为txt文件\n");
	printf("[0]返回主菜单\n");
	int option;
	while(1)
	{
		scanf("%d",&option);
		fflush(stdin);
		if(option==0) return 0;
		if(option!=1&&option!=2)
		{printf("无效的输入！请重试\n");continue;}
		break;
	}
	if(option==1)
		return exportsave();
	
	FILE *fp;
	int i;
	int icour;
	if  (( fp=fopen("export.txt","w") )==NULL)
	{
		printf("文件建立失败！\n");
		return 1;
	}
	fprintf(fp,"%20s\t%10s\t%30s","学号","姓名","班级");
	for(i=0;i<=num_course-1;i++)
		fprintf(fp,"\t%20s",course[i].name );
	fprintf(fp,"\t总分");
	for(i=0;i<=st_num-1;i++)
	{
		fprintf(fp,"\n%20s\t",st[i].number);
		fprintf(fp,"%10s\t",st[i].name);
		fprintf(fp,"%30s",st[i].schclass);
		for(icour=0;icour<=num_course-1;icour++)
		{  fprintf(fp,"\t%20.1f",st[i].grade.score[icour]);  }
		fprintf(fp,"\t");
		fprintf(fp,"%.2lf",st[i].grade.gpa);
	}
	if(fclose(fp))
	{
		printf("文件关闭失败！\n");
		return 1;
	}
	printf("导出成功！\n");
	printf("文件以明文txt文件的形式，存储在本程序目录下的\"export.txt\"文件中\n");
	Sleep(1000);
	return 0;
}

int exportsave(void)
{
	int isyes;
	int i,icour;
	FILE* fp;
	printf("导出学生信息会覆盖原有的学生信息和课程信息，是否继续？若是，请输入1\n");
	scanf("%d",&isyes);
	fflush(stdin);
	if(isyes!=1)
	{printf("您已取消导出！\n");return 2;}
	if(st_num==0)
	{printf("当前还没有添加任何学生！\n");return 3;}
	if( (fp=fopen("SAVE.txt","w"))==NULL )
		{printf("文件建立失败！\n");return 1;}
	fprintf(fp,"%d\n",num_course);
	for(i=0;i<=st_num-1;i++)
	{
		fprintf(fp,"%s\t",st[i].number);
		fprintf(fp,"%s\t",st[i].name);
		fprintf(fp,"%s",st[i].schclass);
		for(icour=0;icour<=num_course-1;icour++)
		{  fprintf(fp,"\t%f",st[i].grade.score[icour]);  }
		fprintf(fp,"\t");
		fprintf(fp,"%lf\n",st[i].grade.gpa);
	}
	if(fclose(fp))
		printf("文件关闭失败！\n");
	printf("导出完成！\n");
	return 0;
}

void outputcour(void)
{
	int i;
	printf("课程");
	for(i=1;i<=num_course;i++)
		printf("\t%8s",course[i-1].name);
	printf("\n");
	printf("学分");
	for(i=1;i<=num_course;i++)
		printf("\t%8.1f",course[i-1].credit);
	printf("\n");
}


int sortstu(void)
{
	printf("[1]按学号排序\n");
	printf("[2]按姓名排序\n");
	printf("[3]按班级排序\n");
	printf("[4]按总分排序\n");
	printf("[5]按班级-总分排序\n");
	printf("[6]按单科成绩排序\n");
	printf("[7]按班级-单科成绩排序\n");
	printf("[0]返回主菜单\n");
	int option;
	int i;
	while(1)
	{
		scanf("%d",&option);
		fflush(stdin);
		if(option==0) return 0;
		if(option<=0||option>=8)
		{printf("无效的输入！请重试\n");continue;}
		break;
	}

	if(option==6||option==7)
	{
		printf("您要根据第几门课程的成绩排序？请输入序号：\n");
		outputcour();
		while(1)
		{
		scanf("%d",&sortstu_optcour);
		fflush(stdin);
		if(sortstu_optcour==0) return 0;
		if(sortstu_optcour<=0||sortstu_optcour>=num_course+1)
		{printf("无效的输入！请重试\n");continue;}
		sortstu_optcour--;//-1,yuxiabiaopipei
		break;
		}
	}

	switch (option)//选择不同的排序模式
	{
        case 1: qsort( st, st_num, sizeof(st[0]), cmp1 ); break;
        case 2: qsort( st, st_num, sizeof(st[0]), cmp2 ); break;
		case 3: qsort( st, st_num, sizeof(st[0]), cmp3 ); break;
		case 4: qsort( st, st_num, sizeof(st[0]), cmp4 ); break;
		case 5: qsort( st, st_num, sizeof(st[0]), cmp5 ); break;
		case 6: qsort( st, st_num, sizeof(st[0]), cmp6 ); break;
		case 7: qsort( st, st_num, sizeof(st[0]), cmp7 ); break;
	}
	printf("排序完成！\n");
	if(st_num<=80)
	{
		outputtablehead();
		for(i=0;i<=st_num-1;i++)
			outputsea(i);
	}
	if(st_num>=81)
		printf("由于学生过多，在这里不显示排序结果，如有需要，请返回主菜单自行查看。\n");
	return 0;
}

int cmp1(const void* a,const void* b)
{return strcmp( ((struct information*)a)->number, ((struct information*)b)->number );}
int cmp2(const void* a,const void* b)
{return strcmp( ((struct information*)a)->name, ((struct information*)b)->name );}
int cmp3(const void* a,const void* b)
{return strcmp( ((struct information*)a)->schclass, ((struct information*)b)->schclass );}
int cmp4(const void* a,const void* b)
{return  ((struct information*)a)->grade.gpa>((struct information*)b)->grade.gpa?-1:1 ;}
int cmp5(const void* a,const void* b)
{   int res;
	res=strcmp( ((struct information*)a)->schclass, ((struct information*)b)->schclass );
	if(  res!=0 )
	return  res ;
	else return ((struct information*)a)->grade.gpa>((struct information*)b)->grade.gpa?-1:1;}
int cmp6(const void* a,const void* b)
{return  ((struct information*)a)->grade.score[sortstu_optcour]>((struct information*)b)->grade.score[sortstu_optcour]?-1:1 ;}
int cmp7(const void* a,const void* b)
{   int res;
	res=strcmp( ((struct information*)a)->schclass, ((struct information*)b)->schclass );
	if(  res!=0 )
	return  res ;
	else return ((struct information*)a)->grade.score[sortstu_optcour]>((struct information*)b)->grade.score[sortstu_optcour]?-1:1 ;}

int modcour()
{
	int option;
	int i,j;
	int order;
	int isyes;
	FILE* fp;
	char name_cache[1000];
	double credit_cache;
	printf("[1]查询课程信息\n");
	printf("[2]增加课程信息\n");
	printf("[3]修改课程信息\n");
	printf("[4]删除课程信息\n");
	printf("[5]导出课程信息\n");
	printf("[6]导入课程信息\n");
	printf("[0]返回主菜单\n");
	while(1)
	{
		printf("请选择[1]查询[2]增加[3]修改[4]删除[5]导出[6]导入[0]返回：\n");
		scanf("%d",&option);
		fflush(stdin);
		if(!option) {printf("已回到主菜单\n");break;}
		fflush(stdin);

		if(option==5)
		{
			printf("导出课程信息会覆盖原有的文件，是否继续？若是，请输入1\n");
			scanf("%d",&isyes);
			fflush(stdin);
			if(isyes!=1)
			{printf("您已取消导出！\n");continue;}
			if( (fp=fopen("Course.txt","w"))==NULL )
			{printf("文件建立失败！\n");continue;}
			fprintf(fp,"%d",num_course);
			for(i=0;i<=num_course-1;i++)
				fprintf(fp,"\n%s",course[i].name);
			for(i=0;i<=num_course-1;i++)
				fprintf(fp,"\n%f",course[i].credit);
			if(fclose(fp))
				printf("文件关闭失败！\n");
			printf("导出成功！\n");
		}

		if(option==6)
		{
			if(st_num!=0)
			{printf("导入课程信息前必须清空学生列表，否则学生将没有新添加课程的成绩！\n");return 0;}
			printf("导入课程信息会覆盖现有的信息，是否继续？若是，请输入1\n");
			scanf("%d",&isyes);
			fflush(stdin);
			if(isyes!=1)
			{printf("您已取消导入！\n");continue;}
			if( (fp=fopen("Course.txt","r"))==NULL )
			{printf("文件打开失败！\n");continue;}
			fscanf(fp,"%d",&num_course);
			for(i=0;i<=num_course-1;i++)
				fscanf(fp,"%s",course[i].name);
			credit_sum=0;
			for(i=0;i<=num_course-1;i++)
			{
				fscanf(fp,"%lf",&course[i].credit);
				credit_sum=credit_sum+course[i].credit;
			}
			if(fclose(fp))
				printf("文件关闭失败！\n");
			printf("导入成功！\n");

		}

		if(option==2)
		{
			if(st_num!=0)  {printf("欲增加课程信息，请先将学生列表置空！否则学生将没有新添加课程的成绩！\n");continue;}
			if(num_course>=10)  {printf("添加的课程数量已达上限！\n");continue;}
		}
		
		if(option==4)
		{
			if(st_num!=0)  
			{
			printf("欲删除课程信息，请先将学生列表置空！\n\
				如果您想让某一门课程不计入总成绩，您可以将其学分置零。\n");
			continue;
			}
		}
		
		if(option>=1&&option<=4)
		{
			if(num_course==0) 
				printf("您还没有添加任何课程信息！\n");
			if(num_course!=0)
			{
				printf("当前已添加的课程信息如下：\n");
				printf("课程");
				for(i=1;i<=num_course;i++)
					printf("\t%12s",course[i-1].name);
				printf("\n");
				printf("学分");
				for(i=1;i<=num_course;i++)
					printf("\t%12.1f",course[i-1].credit);
				printf("\n");
			}
		}
		if(option==1)  printf("操作成功！请继续：\n");
		
		if(option==2)
		{
			
			while (1)
			{
				printf("您要使新添加的课程排在课程列表的第几位？请键入：\n");
				scanf("%d",&order);
				fflush(stdin);
				if(order>num_course+1||order<=0)
				{
					printf("无效的输入，请重试！\n");fflush(stdin);order=-1;continue;
				}
				fflush(stdin);
				printf("请输入要添加的课程的名称：\n");
				scanf("%s",name_cache);
				fflush(stdin);
				name_cache[14]=0;
				printf("请输入要添加的课程的学分：\n");
				scanf("%lf",&credit_cache);
				if(credit_cache>=128||credit_cache<=-1)
				{
					printf("无效的数据，学分将被赋值为零！请稍后检查\n");credit_cache=0;
				}
				fflush(stdin);
				for(i=num_course; i>=order ;i--)
					course[i]=course[i-1];
				
				course[i].credit=credit_cache;
				for(j=0;name_cache[j]!=0;j++)
					course[i].name[j]=name_cache[j];
				course[i].name[j]=0;
				num_course++;
				credit_sum=credit_sum+credit_cache;
				printf("添加成功！请继续：\n");
				break;
			}
		}
		if(option==3)
		{
			while (1)
			{
				printf("您要修改第几门课程的信息？请键入一个阿拉伯数字：\n");
				scanf("%d",&order);
				fflush(stdin);
				if(order>num_course||order<=0)
				{
					printf("无效的输入，请重试！\n");fflush(stdin);order=-1;continue;
				}
				fflush(stdin);
				printf("请重新设置该课程的名称：\n");
				scanf("%s",name_cache);
				fflush(stdin);
				name_cache[14]=0;
				printf("请重新设置该课程的学分：\n");
				scanf("%lf",&credit_cache);
				if(credit_cache>=128||credit_cache<=-1)
				{
					printf("无效的数据，学分将被赋值为零！请稍后检查\n");credit_cache=0;
				}
				fflush(stdin);
				course[order-1].credit=credit_cache;
				for(j=0;name_cache[j]!=0;j++)
					course[order-1].name[j]=name_cache[j];
				course[order-1].name[j]=0;
				for(credit_sum=0,j=0;j<=num_course-1;j++)
					credit_sum=credit_sum+course[j].credit;
				printf("修改成功！请继续：\n");
				break;
			}
		}
		
		if(option==4)
		{
			if(num_course<=1)
			{
				printf("课程数量已达最小值，不允许继续删除！\n");
				return 1;
			}
			while (1)
			{
				printf("您要删除第几门课程的信息？请键入一个阿拉伯数字：\n");
				scanf("%d",&order);
				fflush(stdin);
				if(order>num_course||order<=0)
				{
					printf("无效的输入，请重试！\n");fflush(stdin);order=-1;continue;
				}
				fflush(stdin);
				printf("您确实要删除课程【%s】吗？如果是，请键入1，如果不是，键入任意其他数字\n",course[order-1].name);
				scanf("%d",&i);
				fflush(stdin);
				if(i!=1)
				{printf("已取消删除\n");break;}
				credit_sum=credit_sum-course[order-1].credit;
				for(j=order-1;j<=num_course-2;j++)
					course[j]=course[j+1];
				num_course--;
				
				printf("删除成功！\n");
				break;				
			}
		}
	option=-10;
	}
	return 0;
}
int advanced(void)
{
	char* author="作者信息：github@Sorbose\nhttps://github.com/sorbose/C-Programming-Design\n谢谢您的使用！\n*****************\n";
	int option,optcour;
	int i,num,res=0;
	float fres;
	double sum,ave,std,devsum;
	FILE *fp;
	printf("[1]计算平均分和标准差\n");
	printf("[2]随机生成供测试用的近似服从正态分布的学生成绩\n");
	printf("[8]显示作者信息\n");
	printf("[9]清屏\n");
	printf("[0]返回主菜单\n");
	scanf("%d",&option);
	fflush(stdin);
	if(option==9)
		system("CLS");//清屏
	if(option==1)
	{
		printf("您要计算第几门课程的平均分和标准差？请输入：\n");
		printf("如果您要计算总分的平均分和标准差？请输入0\n");
		outputcour();
		while(1)
		{
		scanf("%d",&optcour);
		fflush(stdin);
		if(optcour<=-1||optcour>=num_course+1)
		{
			printf("无效的输入，请重试！\n");
			continue;
		}
		optcour--;
		break;
		}
		
		if(optcour==-1)
		{
			sum=ave=std=devsum=0;
			for(i=0;i<=st_num-1;i++)
				sum=sum+st[i].grade.gpa;
			ave=sum/st_num;
			printf("总分的平均分是%.2f\n",ave);
			for(i=0;i<=st_num-1;i++)
				devsum=devsum+(st[i].grade.gpa-ave)*(st[i].grade.gpa-ave);
			std=sqrt((devsum/st_num));
			printf("总分的标准差是%.2f\n",std);
			printf("计算完成！\n");
		}
		if(optcour>=0)
		{
			sum=ave=std=devsum=0;
			for(i=0;i<=st_num-1;i++)
				sum=sum+st[i].grade.score[optcour];
			ave=sum/st_num;
			printf("课程【%s】的平均分是%.2f\n",course[optcour].name,ave);
			for(i=0;i<=st_num-1;i++)
				devsum=devsum+(st[i].grade.gpa-ave)*(st[i].grade.gpa-ave);
			std=sqrt((devsum/st_num));
			printf("课程【%s】的标准差是%.2f\n",course[optcour].name,std);
			printf("计算完成！\n");
		}
	}

	if(option==2)
	{
		printf("请输入要生成的随机数的数量：\n");
		while(1)
		{
		scanf("%d",&num);
		fflush(stdin);
		if(num<=0||num>=20000)
		{
			printf("超出数据范围，请重试！\n");
			continue;
		}
		break;
		}
		if  (( fp=fopen("RandomNumbers.txt","w") )==NULL)
		{
		printf("文件建立失败！\n");
		return 1;
		}

		for(i=1;i<=num;i++)
		{
		srand((unsigned int)time(0)+res);
		res=rand()%300+rand()%300+rand()%300;
		res=res/3+18;
		fres=res*1.0/2;
		if(fres>100){i--;continue;}
		fprintf(fp,"%g\n",fres);
		}
        if(fclose(fp))
		{
	     	printf("文件关闭失败！\n");
	     	return 1;
		}
		printf("随机数已生成完毕！保存在本程序目录下的RandomNumbers.txt文件中。\n");
	}
	if(option==8)
		printf(author);//输出作者信息
	return 0;
}
