//��ע��˴���д���ǵ����������ڱ��ڵ�

#include<stdio.h>
#include<stdlib.h>

//�����Ƕ��ڱ��ڵ��keyֵ����һ��ָ��
#define Infinitude -33333

typedef struct Node
{
	int key;
	struct Node* next;
}Node;



//��ʼ��һ������
Node* InitList()
{
	Node* phead = (Node*)malloc(sizeof(Node));
	if (!phead)
	{
		printf("Memory allocation is failed\n");
		exit(EXIT_FAILURE);
	}
	phead->next = NULL;
	phead->key = Infinitude;
	return phead;
}

void InsertList(Node* phead, int key)
{
	//Ĭ��ֱ��ͷ��
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode)
	{
		printf("Memory allocation is failed\n");
		exit(EXIT_FAILURE);
	}
	newNode->key = key;
	newNode->next = phead->next;
	phead->next = newNode;
}

void DeleteList(Node* phead, int key)
{
	Node* current = phead->next;
	Node* before = phead;
	if (current->next == NULL)
	{
		printf("NULL\n");
		return;
	}

	while (current != NULL)
	{
		if (current->key == key)
		{
			
			if (current->next == NULL)
			{
				free(current);
			current = NULL;
			printf("Delete successful\n");
			}
			else
			{
				Node* next = current->next;
				before->next = next;
				free(current);
				current = NULL;
				printf("Delete successful\n");
			}
			
			return;
		}
		current = current->next;
		before = before->next;
	}
	printf("Delete failed\n");
	return;
}

void PrintList(Node* phead)
{
	Node* head = phead->next;
	while (head != NULL)
	{
		printf(" %d ", head->key);
		head = head->next;
	}

}

void test01()
{
	Node* phead = InitList();
	InsertList(phead, 7);
	InsertList(phead, 3);
	InsertList(phead, 4);
	InsertList(phead, 5);
	InsertList(phead, 6);
	InsertList(phead, 8);
	InsertList(phead, 43);
	InsertList(phead, 76);
	InsertList(phead, 78);
	PrintList(phead);
	DeleteList(phead, 78);
	PrintList(phead);

}



int main()
{
	test01();
	return 0;
}
