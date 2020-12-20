#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
void checkcapacity(struct Contact* ps);
void CopyContact(struct Contact* ps)
{
	struct PeoInfo temp = { 0 };
	FILE* fpRead = fopen("contact.txt", "rb");
	if (!fpRead)
	{
		perror("CopyContact:");
		return;
	}
	while (fread(&temp, sizeof(struct PeoInfo), 1, fpRead))
	{
		checkcapacity(ps);
		ps->data[ps->size] = temp;
		ps->size++;
	}
	fclose(fpRead);
	fpRead = NULL;
}
void IntiContact(struct Contact* ps)
{
	ps->data = (struct PeoInfo*)malloc(DEFAULT_SZ*(sizeof(struct PeoInfo)));
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	//把contact.data中的联系人导入
	CopyContact(ps);
}

void checkcapacity(struct Contact* ps)
{
	if (ps->capacity == ps->size)
	{
		//增容
		struct PeoInfo* p = (struct PeoInfo*)realloc(ps->data,(ps->capacity+2)*sizeof(struct PeoInfo));
		if (p != NULL)
		{
			ps->data = p;
			printf("增容成功！\n");
			ps->capacity += 2;
		}
		else
		{
			printf("增容失败！\n");
		}
	}
}
void AddContact(struct Contact* ps)
{
	//判断容量是否满了
	checkcapacity(ps);
	printf("请输入姓名:>");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("请输入性别:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址:>");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("添加成功\n");
	
}

void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\t\n", "姓名", "年龄", "性别", "电话", "地址");
		for (i = 0; i < ps->size; i++)
		{
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\t\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr);
		}
	}
}
static int FindByName(const struct Contact* ps, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (!(strcmp(name, ps->data[i].name)))
		{
			return i;
		}
	}
	return -1;
}

void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要删除的联系人姓名:>");
	scanf("%s", name);
	//1.查找要删除的人所在位置
	//找到了返回元素的下标
	//找不到返回-1（元素下标不会是-1）
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("没有 %s 这个联系人\n", name);
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("删除成功\n");
	}
	
}

void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要搜索的联系人姓名:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("没有 %s 这个联系人\n", name);
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\t\n", "姓名", "年龄", "性别", "电话", "地址");
		printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\t\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr);
	}
}

void ModifyContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要修改的联系人姓名:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("没有 %s 这个联系人\n", name);
	}
	else
	{
		printf("请输入姓名:>");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄:>");
		scanf("%d", &(ps->data[pos].age));
		printf("请输入性别:>");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话:>");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址:>");
		scanf("%s", ps->data[pos].addr);
		printf("修改成功\n");
	}
}

//比较函数 第一个大于第二个返回>0  小于返回<0  等于返回0
int compar(const struct Contact* str1, const struct Contact* str2)
{
	if ((strcmp(str1->data->name, str2->data->name)) > 0)
		return 1;
	else if ((strcmp(str1->data->name, str2->data->name)) < 0)
		return -1;
	else
		return 0;
}
void SortContact(const struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(struct PeoInfo), compar);
}

void destoryContact(struct Contact* ps)
{
	SaveContact(ps);
	free(ps->data);
	ps->data = NULL;
}

void SaveContact(struct Contact* ps)
{
	struct PeoInfo temp = { 0 };
	FILE* fpWrite = fopen("contact.txt", "wb");
	if (!fpWrite)
	{
		perror("SaveContact:");
		return;
	}
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		temp = ps->data[i];
		fwrite(&temp, sizeof(struct PeoInfo), 1, fpWrite);
	}
	fclose(fpWrite);
	fpWrite = NULL;
}