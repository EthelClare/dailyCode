#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct BiTNode
{
	int data;

	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

//二叉排序树的 查找操作
//T是二叉排序树的根节点
//此处BiTree的作用是作为最后返回需要的节点
int SearchBST(BiTree T, int key, BiTree f, BiTree* p)
{
	if (!T)
	{
		*p = f;
		return false;
	}
	else if (key == T->data)
	{
		*p = T;
		return true;
	}
	else if (key < T->data)
	{
		return SearchBST(T->lchild, key, T, p);
	}
	else if (key > T->data)
	{
		return SearchBST(T->rchild, key, T, p);
	}
}

//插入操作
int InsertBST(BiTree* T, int key)
{
	BiTree p, s;
	if (!SearchBST(*T, key, NULL, &p))
	{
		//查找不成功的时候,SearchBST会返回这个节点应该所在的位置的父节点
		s = (BiTree*)malloc(sizeof(BiTNode));
		if (!s)
		{
			printf("Memory allocation is falied;\n");
			exit(EXIT_FAILURE);
		}
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			*T = s; //表示原来的没有根节点
		else if (key < p->data)
			p->lchild = s;
		else if (key > p->data)
			p->rchild = s;
		return true;
	}
	else
		return false;

}


//从二叉树中删除节点p,并重新连接他的左右子树

int Delete(BiTree* p)
{
	BiTree q, s;
	if ((*p)->rchild == NULL) // 右子树为空的是偶只需要重新连接他的左子树
	{
		q = *p;
		(*p) = (*p)->lchild;
		free(q);
	}
	else if ((*p)->lchild == NULL)
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else //左右子树均不为空
	{
		q = *p;
		s = (*p)->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;
		if (q != *p)
		{
			q->rchild = s->lchild;
		}
		else
		{
			q->lchild = s->lchild;
		}
		free(s);
	}
	return true;

}

int DeleteBST(BiTree* T, int key)
{
	if (!T)
		return false;
	else
	{
		if (key == (*T)->data)
			return (Delete(T));
		else if (key < (*T)->data)
			return DeleteBST(&(*T)->lchild, key);
		else
			return DeleteBST(&(*T)->rchild, key);
	}

}
// 中序遍历二叉树
void InOrderTraversal(BiTree T)
{
	if (T == NULL)
		return;

	// 遍历左子树
	InOrderTraversal(T->lchild);
	// 访问当前节点
	printf("%d ", T->data);
	// 遍历右子树
	InOrderTraversal(T->rchild);
}


int main()
{
	int i;
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	BiTree T = NULL;

	for (i = 0; i < 10; i++)
	{
		InsertBST(&T, a[i]);
	}
	InOrderTraversal(T);
	printf("\n");
	DeleteBST(&T, 93);
	InOrderTraversal(T);
	printf("\n");
	DeleteBST(&T, 47);
	InOrderTraversal(T);
	printf("\n");
	printf("本样例建议断点跟踪查看二叉排序树结构");
	return 0;

	return 0;
}