#define _CRT_SECURE_NO_WARNINGS 1
#include"contact.h"
void menu()
{
	printf("***********************************\n");
	printf("****** 1.add       2.del     ******\n");
	printf("****** 3.search    4.modify  ******\n");
	printf("****** 5.show      6.sort    ******\n");
	printf("****** 7.save      0.exit    ******\n");
	printf("***********************************\n");
}
int main()
{
	int input = 0;
	//����һ��ͨѶ¼
	struct Contact con;//con��ͨѶ¼����߰�����dataָ���size��capacity
	//��ʼ��ͨѶ¼
	IntiContact(&con);
	do
	{
		menu();
		printf("������ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case EXIT:
			//����ͨѶ¼-�ͷŶ�̬���ٵ��ڴ�
			destoryContact(&con);
			printf("�˳�ͨѶ¼\n");
			break;
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case SAVE:
			SaveContact(&con);
			break;
		default:
			printf("�������\n");
			break;
		}
	} while (input);

	return 0;
}