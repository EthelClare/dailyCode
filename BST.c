#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct BiTNode
{
	int data;

	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

//������������ ���Ҳ���
//T�Ƕ����������ĸ��ڵ�
//�˴�BiTree����������Ϊ��󷵻���Ҫ�Ľڵ�
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

//�������
int InsertBST(BiTree* T, int key)
{
	BiTree p, s;
	if (!SearchBST(*T, key, NULL, &p))
	{
		//���Ҳ��ɹ���ʱ��,SearchBST�᷵������ڵ�Ӧ�����ڵ�λ�õĸ��ڵ�
		s = (BiTree*)malloc(sizeof(BiTNode));
		if (!s)
		{
			printf("Memory allocation is falied;\n");
			exit(EXIT_FAILURE);
		}
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			*T = s; //��ʾԭ����û�и��ڵ�
		else if (key < p->data)
			p->lchild = s;
		else if (key > p->data)
			p->rchild = s;
		return true;
	}
	else
		return false;

}


//�Ӷ�������ɾ���ڵ�p,����������������������

int Delete(BiTree* p)
{
	BiTree q, s;
	if ((*p)->rchild == NULL) // ������Ϊ�յ���żֻ��Ҫ������������������
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
	else //������������Ϊ��
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
// �������������
void InOrderTraversal(BiTree T)
{
	if (T == NULL)
		return;

	// ����������
	InOrderTraversal(T->lchild);
	// ���ʵ�ǰ�ڵ�
	printf("%d ", T->data);
	// ����������
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
	printf("����������ϵ���ٲ鿴�����������ṹ");
	return 0;

	return 0;
}