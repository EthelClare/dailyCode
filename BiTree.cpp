

//�˴���д���Ƕ���������

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct BSTNode
{
	int key;
	struct BSTNode* lchild, *rchild;
}BSTNode, *BSTree;

//�ǵݹ�ʵ��
BSTNode* SearchBST(BSTree T,int key )
{
	
	while (T != NULL && key != T->key)
	{
		if (key < T->key)
			T = T->lchild;
		else
			T = T->rchild;
	}
	return T;
}
//recursion ______�ݹ�
BSTNode* BSTSearch_recursion(BSTree T, int key)
{
	if (T == NULL)
		return NULL;
	if (key == T->key)
		return T;
	else if (key < T->key)
		return BSTSearch_recursion(T->lchild, key);
	else
		return BSTSearch_recursion(T->rchild, key);
}


bool InsertBST(BSTree& T, int key)
{
	if (T == NULL)
	{
		T = (BSTree)malloc(sizeof(BSTNode));
		if (!T)
		{
			printf("Memory allocation is failed\n");
			exit(EXIT_FAILURE);
		}

		T->key = key;
		T->lchild = T->rchild = NULL;
		return true;
	}
	else if (key < T->key)
	{
		return InsertBST(T->lchild, key); // ��������Ϊֱ�Ӳ��뵽������
	}
	else if (key > T->key) // ��Ӷ�key����T->key����������Ա���BST����
	{
		return InsertBST(T->rchild, key); // ��������Ϊֱ�Ӳ��뵽������
	}
	else
	{
		printf("Duplicate key is not allowed\n");
		return false; // ���Ѵ��ڣ��������ظ�����
	}
}

void Creat_BST(BSTree& T, int str[], int n)
{
	T = NULL;
	int i = 0;
	while (i < n)
	{
		InsertBST(T, str[i]);
		i++;
	}

}

void InOrderTraversal(BSTree T)
{
	if (T == NULL)
		return;

	// ����������
	InOrderTraversal(T->lchild);

	// ���ʵ�ǰ�ڵ�
	printf("%d ", T->key);

	// ����������
	InOrderTraversal(T->rchild);
}

//... ֮ǰ����ĺ������ֲ��� ...

void test01()
{
	BSTree T;
	int arr[] = { 1, 2, 5, 6, 7, 8, 9,29,59,66};
	int length = sizeof(arr) / sizeof(arr[0]);
	Creat_BST(T, arr, length);

	// �����һ�������������������ӡ���
	printf("In-order traversal of the BST: ");
	InOrderTraversal(T);
	printf("\n");
}

int main()
{
	test01();

	return 0;
}