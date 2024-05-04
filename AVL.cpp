#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//�������Ķ�������ڵ�ṹ����
typedef struct BiTNode
{
	int data;	//	�ڵ�����
	int bf;		//�ڵ�ƽ������
	struct BiTNode* lchild, * rchild;
}BiNode, *BiTree;
//ע�������*BiTree������ָ��BiTree��Ϊ��һ��ָ������,ֽ������Ľṹ��
//Ҳ����˵���BiTree���������ṹ����˵,�൱�ڶ���ָ��



//��������
void R_Rotate(BiTree* p)
    {
	 BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

//��������
void L_Rotate(BiTree* p)
{
	BiTree R;
	R = (*p)->rchild;
	(*p)->rchild = R->lchild;
	R->lchild = (*p);
	*p = R;
}


#define LH 1
#define EH 0
#define RH -1    


//��ƽ����ת
void LeftBalance(BiTree* T)
{
	BiTree L, Lr;
	L = (*T)->lchild;
	switch (L->bf)
	{
		//���ӵ���������
		case LH:
			(*T)->bf = L->bf = EH;
			R_Rotate(T);
			break;
		//���ǲ����˸��ڵ����ӵ�����������
		case RH:
			Lr = L->rchild;
			switch (Lr->bf)
			{
				//�޸�T��ƽ�����Ӻ����ӵ�ƽ������
				case LH:
					(*T)->bf = RH;
					L->bf = EH;
					break;
				case EH:
					(*T)->bf = L->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					break;
			}
			Lr->bf = EH;
			L_Rotate(&(*T)->lchild);
			R_Rotate(T);
	}


}

//����ƽ��
void RightBalance(BiTree* T)
{
	BiTree R, Rl;
	R = (*T)->rchild;
	switch (R->bf)
	{
	case RH:
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	case LH:
		Rl = R->lchild;
		switch (R->bf)
		{
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		case EH:
			(*T)->bf = EH;
			break;
		case LH:
			(*T)->bf = RH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);
		L_Rotate(T);
	}

}

//����д�������������Ҫ����,��һ��ƽ������������µĽڵ�
/*  ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ�� */
/*  ����Ԫ��Ϊe���½�㣬������1�����򷵻�0����������ʹ���������� */
/*  ʧȥƽ�⣬����ƽ����ת������������taller��ӳT������� */
bool InsertAVL(BiTree* T, int e, bool *taller)
{
	//�����ʾT��û���κνڵ�
	if (!*T)
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller =  true;
	}
	else
	{
		if (e == (*T)->data)
		{
			*taller = true;
			return false;
		}
		if (e < (*T)->data)
		{
			//����Ѱ��,С����ȥ��������
			if(!InsertAVL(&(*T)->lchild,e,taller))
				return false;
			//�Ѳ����T����������������������
			if (*taller)
			{
				switch ((*T)->bf)
				{
				case LH:
					LeftBalance(T);
					*taller = true;
					break;
				case EH:
					(*T)->bf = LH;
					*taller = true;
					break;
				case RH:
					(*T)->bf = EH;
					*taller = false;
					break;
				}
			}

		}
		else
		{
			//��T������������Ѱ��
			if (!InsertAVL(&(*T)->rchild, e, taller))
			return false;
			if (*taller)
			{
				switch ((*T)->bf)
				{
				case LH:
					(*T)->bf = EH;
					*taller = false;
					break;
				case EH:
					(*T)->bf = RH;
					*taller = true;
					break;
				case RH:
					RightBalance(T);
					*taller = false;
					break;
				}
			}
		}



	}
	return true;

}



int main()
{

	int i;
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	BiTree T = NULL;
	bool taller;
	for (i = 0; i < 10; i++)
	{
		InsertAVL(&T, a[i], &taller);
	}
	printf("����������ϵ���ٲ鿴ƽ��������ṹ");
	return 0;


}