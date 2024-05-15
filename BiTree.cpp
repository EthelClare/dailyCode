

//此代码写的是二叉排序树

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct BSTNode
{
	int key;
	struct BSTNode* lchild, *rchild;
}BSTNode, *BSTree;

//非递归实现
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
//recursion ______递归
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
		return InsertBST(T->lchild, key); // 修正这里为直接插入到左子树
	}
	else if (key > T->key) // 添加对key大于T->key的情况处理，以保持BST性质
	{
		return InsertBST(T->rchild, key); // 修正这里为直接插入到右子树
	}
	else
	{
		printf("Duplicate key is not allowed\n");
		return false; // 键已存在，不允许重复插入
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

	// 遍历左子树
	InOrderTraversal(T->lchild);

	// 访问当前节点
	printf("%d ", T->key);

	// 遍历右子树
	InOrderTraversal(T->rchild);
}

//... 之前定义的函数保持不变 ...

void test01()
{
	BSTree T;
	int arr[] = { 1, 2, 5, 6, 7, 8, 9,29,59,66};
	int length = sizeof(arr) / sizeof(arr[0]);
	Creat_BST(T, arr, length);

	// 添加这一行来调用中序遍历并打印结果
	printf("In-order traversal of the BST: ");
	InOrderTraversal(T);
	printf("\n");
}

int main()
{
	test01();

	return 0;
}