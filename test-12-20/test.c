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
	//创建一个通讯录
	struct Contact con;//con是通讯录，里边包括：data指针和size，capacity
	//初始化通讯录
	IntiContact(&con);
	do
	{
		menu();
		printf("请输入选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case EXIT:
			//销毁通讯录-释放动态开辟的内存
			destoryContact(&con);
			printf("退出通讯录\n");
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
			printf("输入错误\n");
			break;
		}
	} while (input);

	return 0;
}