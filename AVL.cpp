#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


//二叉树的二叉链表节点结构定义
typedef struct BiTNode
{
	int data;	//	节点数据
	int bf;		//节点平衡因子
	struct BiTNode* lchild, * rchild;
}BiNode, *BiTree;
//注意这个的*BiTree这里是指将BiTree变为了一个指针类型,纸箱上面的结构体
//也就是说这个BiTree相对于这个结构体来说,相当于二级指针



//右旋操作
void R_Rotate(BiTree* p)
    {
	 BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
}

//左旋操作
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


//左平衡旋转
void LeftBalance(BiTree* T)
{
	BiTree L, Lr;
	L = (*T)->lchild;
	switch (L->bf)
	{
		//左孩子的左子树上
		case LH:
			(*T)->bf = L->bf = EH;
			R_Rotate(T);
			break;
		//这是插在了根节点左孩子的右子树上面
		case RH:
			Lr = L->rchild;
			switch (Lr->bf)
			{
				//修改T的平衡因子和左孩子的平衡因子
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

//右旋平衡
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

//现在写的事这个函数主要部分,往一个平衡二叉树插入新的节点
/*  若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
/*  数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
/*  失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。 */
bool InsertAVL(BiTree* T, int e, bool *taller)
{
	//这里表示T中没有任何节点
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
			//继续寻找,小于则去左子树找
			if(!InsertAVL(&(*T)->lchild,e,taller))
				return false;
			//已插入的T的左子树中且左子树长高
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
			//在T的右子树进行寻找
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
	printf("本样例建议断点跟踪查看平衡二叉树结构");
	return 0;


}