#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX 1000
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDR 30
#define DEFAULT_SZ 3
struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
};

struct Contact
{
	struct PeoInfo* data;
	int size;//��¼ͨѶ¼�е�Ԫ�ظ���
	int capacity;//��ǰͨѶ¼���������
};

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT,
	SAVE
};


//��������
//��ʼ��ͨѶ¼�ĺ���
void IntiContact(struct Contact* ps);
//���һ����Ϣ��ͨѶ¼
void AddContact(struct Contact* ps);
//��ӡͨѶ¼�е���Ϣ
void ShowContact(const struct Contact* ps);
//ɾ��ָ����ϵ��
void DelContact(struct Contact* ps);
//����ָ����ϵ��
void SearchContact(const struct Contact* ps);
//�޸�ָ����ϵ��
void ModifyContact(struct Contact* ps);
//��������������ϵ��
void SortContact(const struct Contact* ps);
//����ͨѶ¼-�ͷŶ�̬�����ڴ�
void destoryContact(struct Contact* ps);
//����ͨѶ¼��Ϣ���ļ�
void SaveContact(struct Contact* ps);