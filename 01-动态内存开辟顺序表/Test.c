#define _CRT_SECURE_NO_WARNINGS 1
#include "SeqList.h"


enum Options
{
	EXIT,
	PUSHBACK,
	POPBACK,
	PUSHFRONT,
	POPFRONT,
	SLINSERT,
	SLERASE,
	FINDSL,
	MODIFYSL,
	SLPRINT
};

void menu() {
	printf("+------------------------------+\n");
	printf("|            SeqList           |\n");
	printf("|  1.PushBack       2.PopBack  |\n");
	printf("|  3.PushFront      4.PopFront |\n");
	printf("|  5.SLInsert       6.SLErase  |\n");
	printf("|  7.FindSL         8.ModifySL |\n");
	printf("|  9.SLPrint        0.Exit     |\n");
	printf("+------------------------------+\n");
}

int main()
{
	SeqList s;
	SeqListInit(&s);
	int option = 0;
	do
	{
		menu();
		printf("请选择你的操作:> ");
		scanf("%d", &option);
		switch (option)
		{
		case PUSHBACK:
			printf("请输入你要尾插的数据:> ");
			int val = 0;
			scanf("%d", &val);
			SeqListPushBack(&s, val);
			break;
		case POPBACK:
			SeqListPopBack(&s);
			printf("尾部删除数据成功\n");
			break;
		case PUSHFRONT:
			printf("请输入你要头插的数据:> ");
			val = 0;
			scanf("%d", &val);
			SeqListPushFront(&s, val);
			break;
		case POPFRONT:
			SeqListPopFront(&s);
			printf("头部删除数据成功\n");
			break;
		case SLINSERT:
			printf("请问你要在顺序表的那个位置插入数据:> ");
			int pos = 0;
			scanf("%d", &pos);
			printf("请问你要插入的数据是什么:> ");
			val = 0;
			scanf("%d", &val);
			SeqListInsert(&s, pos, val);
			break;
		case SLERASE:
			printf("请问你要在顺序表的那个位置删除数据:> ");
			pos = 0;
			scanf("%d", &pos);
			SeqListErase(&s, pos);
			printf("删除数据成功\n");
			break;
		case FINDSL:
			printf("请输入你要查找的数据:> ");
			val = 0;
			scanf("%d", &val);
			SeqListFind(&s, val);
			break;
		//case MODIFYSL:
		//	printf("请问你要在顺序表的那个位置修改数据:> ");
		//	pos = 0;
		//	scanf("%d", &pos);
		//	printf("请问你要修改的数据是什么:> ");
		//	val = 0;
		//	scanf("%d", &val);
		//	SeqListModify(&s, pos, val);
		//	break;
		case SLPRINT:
			SeqListPrint(&s);
			break;
		case 0:
			//SeqListDestroy(&s);
			printf("退出顺序表\n");
			break;
		}
	} while (option);
	return 0;
}