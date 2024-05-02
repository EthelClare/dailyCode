//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct TreeNode
//{
//	int data;
//	struct TreeNode* L_child;
//	struct TreeNode* R_child;
//
//}TreeNode;
//
////创造一个节点
//TreeNode* creatNode(int value)
//{
//	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
//	if (!newNode)
//	{
//		printf("Memory allocation is failed!\n");
//		exit(EXIT_FAILURE);
//	}
//	newNode->data = value;
//	newNode->L_child = NULL;
//	newNode->R_child = NULL;
//	return newNode;
//
//}
//
////插入
//TreeNode* insertNode(TreeNode* root, int value)
//{
//	if (root == NULL)
//		return creatNode(value);
//
//	if (value < root->data)
//	{
//		root->L_child = insertNode(root->L_child, value);
//	}
//	else if (value > root->data)
//	{
//		root->R_child = insertNode(root->R_child, value);
//	}
//	else
//	{
//		printf("Value %d already in the tree!\n");
//		return root;
//	}
//	return root;
//}
//
//
//// 辅助函数：找到右子树中的最小节点
//TreeNode* findSmallest(TreeNode* root) 
//{
//	while (root->L_child != NULL) 
//	{
//		root = root->R_child;
//	}
//	return root;
//}
//
//TreeNode* deleteNode(TreeNode* root, int value)
//{
//	if (root == NULL)
//		return root;
//	
//	if (value < root->data)
//	{
//		root->L_child = deleteNode(root->L_child, value);
//	}
//	else if (value > root->data)
//	{
//		root->R_child = deleteNode(root->R_child, value);
//	}
//	else
//	{
//		if (root->L_child ==NULL && root->R_child == NULL)
//		{
//			free(root);
//			root = NULL;
//		}
//		else if (root->R_child == NULL)
//		{
//			TreeNode* temp = root->R_child;
//			free(root);
//			root = temp;
//		}
//		else if (root->L_child == NULL)
//		{
//			TreeNode* temp = root->L_child;
//			free(root);
//			root = temp;
//		}
//		else
//		{
//			TreeNode* smallestInRight = findSmallest(root->R_child);
//			root->data = smallestInRight->data;
//			root->R_child = deleteNode(root->R_child, smallestInRight->data);
//		}
//
//	}
//
//}
//
//// 层序遍历（广度优先遍历）
//void levelOrderTraversal(TreeNode* root) {
//	if (root == NULL) return;
//
//	TreeNode* current;
//	TreeNode* queue[100];
//	int front = 0, rear = 0;
//
//	queue[rear++] = root;
//
//	while (front < rear) {
//		current = queue[front++];
//		printf("%d ", current->data);
//
//		if (current->L_child) queue[rear++] = current->L_child;
//		if (current->R_child) queue[rear++] = current->R_child;
//	}
//}
//
//
//TreeNode* searchNode(TreeNode* root, int value)
//{
//	if (root == NULL || root->data == value)
//		return root;
//	TreeNode* found = searchNode(root->L_child, value);
//
//
//	return found ? found : searchNode(root->R_child, value);
//}
//#include <assert.h> // 引入assert宏，用于断言验证
//
//
//int main()
//{
//	
//	TreeNode* root = creatNode(50);
//
//	// 插入节点
//	insertNode(root, 30);
//	insertNode(root, 70);
//	insertNode(root, 20);
//	insertNode(root, 40);
//	insertNode(root, 60);
//	insertNode(root, 80);
//
//	
//	levelOrderTraversal(root);
//
//
//	
//
//
//
//	return 0;
//}





#include<stdio.h>
#include<stdlib.h>
 
typedef struct TreeNode
{
	int data;
	struct TreeNode* L_child;
	struct TreeNode* R_child;

}TreeNode;




TreeNode* creatNode(int data)
{
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (!newNode)
	{
		printf("Memoty allocation is failed !\n");
		exit(EXIT_FAILURE);
	}
	newNode->data = data;
	newNode->L_child = NULL;
	newNode->R_child = NULL;
	return newNode;

}

TreeNode* insertNode(TreeNode* root, int value)
{
	if (root == NULL)
	{
		return	 creatNode(value);	
	}
	
	 if (value < root->data)
	{
		root->L_child = insertNode(root->L_child, value);
	}
	else if (value > root->data)
	{
		root->R_child = insertNode(root->R_child, value);
	}
	else
	{
		printf("Goal is already exit!\n");
		return NULL;
	}
	return root;

}


// 辅助函数：找到右子树中的最小节点
TreeNode* findSmallest(TreeNode* root) 
{
	while (root->L_child != NULL) 
	{
		root = root->R_child;
	}
	return root;
}

TreeNode* deleteNode(TreeNode* root, int value)
{
	if (root == NULL)
		return root;
	if (value < root->data)
	{
		root->L_child = deleteNode(root->L_child, value);
	}
	else if (value > root->data)
	{
		root->R_child = deleteNode(root->R_child, value);
	}
	else
	{
		if (root->L_child == NULL && root->R_child == NULL)
		{
			free(root);
			root = NULL;
		}
		else if (root->R_child == NULL)
		{
			TreeNode* temp = root->L_child;
			free(root);
			root = temp;
		}
		else if (root->L_child == NULL)
		{
			TreeNode* temp = root->R_child;
			free(root);
			root = temp;
		}
		else
		{
			TreeNode* smallestInRight = findSmallest(root->R_child);
			root->data = smallestInRight->data;
			root->R_child = deleteNode(root->R_child, smallestInRight->data);
					
		}
	}
}


void levelOrderTraversal(TreeNode* root)
{
	if (root == NULL) return;
	TreeNode* current;
	TreeNode* queue[100];
	int front = 0;
	int rear = 0;
	queue[rear++] = root;
	while (front < rear)
	{
		current = queue[front++];
		printf("%d ", current->data);
		if (current->L_child)  queue[rear++] = current->L_child;
		if (current->R_child)  queue[rear++] = current->R_child;
	}


}

TreeNode* searchNode(TreeNode* root, int value)
{
	if (root == NULL || root->data == value)
		return root;
	TreeNode* found = searchNode(root->L_child, value);


	return found ? found : searchNode(root->R_child, value);
}
#include <assert.h> // 引入assert宏，用于断言验证


int main()
{
	
	TreeNode* root = creatNode(50);

	// 插入节点
	insertNode(root, 30);
	insertNode(root, 70);
	insertNode(root, 20);
	insertNode(root, 40);
	insertNode(root, 60);
	insertNode(root, 80);

	
	levelOrderTraversal(root);


	



	return 0;
}