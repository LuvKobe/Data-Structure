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
		printf("��ѡ����Ĳ���:> ");
		scanf("%d", &option);
		switch (option)
		{
		case PUSHBACK:
			printf("��������Ҫβ�������:> ");
			int val = 0;
			scanf("%d", &val);
			SeqListPushBack(&s, val);
			break;
		case POPBACK:
			SeqListPopBack(&s);
			printf("β��ɾ�����ݳɹ�\n");
			break;
		case PUSHFRONT:
			printf("��������Ҫͷ�������:> ");
			val = 0;
			scanf("%d", &val);
			SeqListPushFront(&s, val);
			break;
		case POPFRONT:
			SeqListPopFront(&s);
			printf("ͷ��ɾ�����ݳɹ�\n");
			break;
		case SLINSERT:
			printf("������Ҫ��˳�����Ǹ�λ�ò�������:> ");
			int pos = 0;
			scanf("%d", &pos);
			printf("������Ҫ�����������ʲô:> ");
			val = 0;
			scanf("%d", &val);
			SeqListInsert(&s, pos, val);
			break;
		case SLERASE:
			printf("������Ҫ��˳�����Ǹ�λ��ɾ������:> ");
			pos = 0;
			scanf("%d", &pos);
			SeqListErase(&s, pos);
			printf("ɾ�����ݳɹ�\n");
			break;
		case FINDSL:
			printf("��������Ҫ���ҵ�����:> ");
			val = 0;
			scanf("%d", &val);
			SeqListFind(&s, val);
			break;
		//case MODIFYSL:
		//	printf("������Ҫ��˳�����Ǹ�λ���޸�����:> ");
		//	pos = 0;
		//	scanf("%d", &pos);
		//	printf("������Ҫ�޸ĵ�������ʲô:> ");
		//	val = 0;
		//	scanf("%d", &val);
		//	SeqListModify(&s, pos, val);
		//	break;
		case SLPRINT:
			SeqListPrint(&s);
			break;
		case 0:
			//SeqListDestroy(&s);
			printf("�˳�˳���\n");
			break;
		}
	} while (option);
	return 0;
}