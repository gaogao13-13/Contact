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
	//��contact.data�е���ϵ�˵���
	CopyContact(ps);
}

void checkcapacity(struct Contact* ps)
{
	if (ps->capacity == ps->size)
	{
		//����
		struct PeoInfo* p = (struct PeoInfo*)realloc(ps->data,(ps->capacity+2)*sizeof(struct PeoInfo));
		if (p != NULL)
		{
			ps->data = p;
			printf("���ݳɹ���\n");
			ps->capacity += 2;
		}
		else
		{
			printf("����ʧ�ܣ�\n");
		}
	}
}
void AddContact(struct Contact* ps)
{
	//�ж������Ƿ�����
	checkcapacity(ps);
	printf("����������:>");
	scanf("%s", ps->data[ps->size].name);
	printf("����������:>");
	scanf("%d", &(ps->data[ps->size].age));
	printf("�������Ա�:>");
	scanf("%s", ps->data[ps->size].sex);
	printf("������绰:>");
	scanf("%s", ps->data[ps->size].tele);
	printf("�������ַ:>");
	scanf("%s", ps->data[ps->size].addr);
	ps->size++;
	printf("��ӳɹ�\n");
	
}

void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\t\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("������Ҫɾ������ϵ������:>");
	scanf("%s", name);
	//1.����Ҫɾ����������λ��
	//�ҵ��˷���Ԫ�ص��±�
	//�Ҳ�������-1��Ԫ���±겻����-1��
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("û�� %s �����ϵ��\n", name);
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("ɾ���ɹ�\n");
	}
	
}

void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];
	printf("������Ҫ��������ϵ������:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("û�� %s �����ϵ��\n", name);
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\t\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("������Ҫ�޸ĵ���ϵ������:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("û�� %s �����ϵ��\n", name);
	}
	else
	{
		printf("����������:>");
		scanf("%s", ps->data[pos].name);
		printf("����������:>");
		scanf("%d", &(ps->data[pos].age));
		printf("�������Ա�:>");
		scanf("%s", ps->data[pos].sex);
		printf("������绰:>");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ:>");
		scanf("%s", ps->data[pos].addr);
		printf("�޸ĳɹ�\n");
	}
}

//�ȽϺ��� ��һ�����ڵڶ�������>0  С�ڷ���<0  ���ڷ���0
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