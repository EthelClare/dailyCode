//
//#define _CRT_SECURE_NO_WARNINGS
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<stdbool.h>
//
//
//#define HASHSIZE 12
//#define NULLKEY -33768
//  
//
//typedef int Status;
//
//typedef struct
//{
//	int* elem;	//用于储存元素储存的地址
//	int count;	//用来记录当前的元素个数
//}HashTable;
//
//int m = 0;
//
////初始化散列表
//bool InitHashTable(HashTable *H)
//{
//	m = HASHSIZE;
//	H->count = m;
//	H->elem = (int*)malloc(sizeof(int) * HASHSIZE);
//	if(!H->elem)
//	{
//		printf("Memrry allocation is failed\n");
//		exit(EXIT_FAILURE);
//	}
//	for (int i = 0; i < m; i++)
//	{
//		H->elem[i] = NULLKEY;
//	}
//	return true;
//}
//
////散列函数
//int Hash(int key)
//{
//	return key % m;	//除数留余法
//}
//
////开放地址法的线性探测法 插入关键字
//void InsertHash(HashTable* H, int key)
//{
//	int addr = Hash(key);	//先求散列地址
//	while (H->elem[addr] != NULLKEY)
//	{
//		addr = (addr + 1) % m;
//	}
//	H->elem[addr] = key; 
//}
//
//bool SearchHash(HashTable H, int key, int* addr)
//{
//	*addr = Hash(key);
//	while (H.elem[*addr] != key)
//	{
//		*addr = (*addr + 1) % m;
//		if (H.elem[*addr] == NULLKEY)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}
//
//
//int main()
//{
//	HashTable H;
//	int searchKey = 5; // 用于测试查找的键值
//	int searchAddr;
//
//	// 初始化哈希表
//	if (!InitHashTable(&H))
//	{
//		printf("初始化哈希表失败。\n");
//		return -1;
//	}
//
//	printf("哈希表初始化成功。\n");
//
//	// 插入12个元素
//	int keysToInsert[] = { 15, 33, 47, 21, 9, 39, 55, 27, 11, 43, 3, 25 };
//	printf("正在插入键值：\n");
//	for (int i = 0; i < 12; i++)
//	{
//		InsertHash(&H, keysToInsert[i]);
//		printf("%d ", keysToInsert[i]);
//	}
//	printf("\n插入完成。\n");
//
//	printf("请输入你想查找的值\n");
//	int find = 0;
//	scanf("%d", &find);
//	searchKey = find;
//	 //查找一个存在的键值
//	if (SearchHash(H, searchKey, &searchAddr))
//	{
//		printf("找到键值%d，位于地址%d。\n", searchKey, searchAddr);
//	}
//	else
//	{
//		printf("未找到键值%d。\n", searchKey);
//	}
//
//	// 注意：这里没有实现释放内存的操作，实际应用中应在程序结束前释放H.elem指向的内存
//	 free(H.elem);
//
//	return 0;
//}




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#define NULLKEY -32786

typedef int Status;

//这里写拉链法
#define HASHSIZE 12
typedef struct Node
{
	int key;
	struct Node* next;
}Node;

typedef struct
{
	Node* table[HASHSIZE];
}HashTable;

void InitHash(HashTable* H)
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		H->table[i] = NULL;
	}
}

unsigned int Hash(int key)
{
	return key % HASHSIZE;
}


//创造新节点
Node* CreatHash(int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Memory allocation is failed \n");
		exit(EXIT_FAILURE);
	}
	newNode->key = key;
	newNode->next = NULL;
	return newNode;
}

//插入函数
void InsertHash(HashTable* H, int key)
{
	unsigned int index = Hash(key);
	Node* newNode = CreatHash(key);
	
	if (H->table[index] == NULL)
	{
		H->table[index] = newNode;
	}
	else
	{
		Node* current = H->table[index];
		while (current->next != NULL)
		{
			current = current->next;
		}
		current = newNode;
	}

}


void DeleteHash(HashTable* H, int key)
{
	unsigned int index = Hash(key);
	Node* current = H->table[index];
	Node* prev = NULL;

	while (current != NULL)
	{
		if (current->key == key)
		{
			if (prev == NULL) // 如果是链表头节点
			{
				H->table[index] = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current);
			return; // 删除后直接返回，避免继续遍历
		}
		prev = current;
		current = current->next;
	}

	printf("Element not found\n");

}

Node* SearchHash(HashTable* H, int key)
{
	unsigned int index = Hash(key);
	Node* current = H->table[index];
	while (current != NULL)
	{
		if (current->key == key)
		{
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void PrintHashTable(HashTable* H) {
	for (int i = 0; i < HASHSIZE; i++) {
		printf("Bucket %d: ", i);
		Node* current = H->table[i];
		while (current != NULL) {
			printf("%d -> ", current->key);
			current = current->next;
		}
		printf("NULL\n");
	}
}

int main() {
	HashTable H;
	InitHash(&H);

	// 插入一些元素
	InsertHash(&H, 56);
	InsertHash(&H, 27);
	InsertHash(&H, 18);
	InsertHash(&H, 34);

	// 打印哈希表
	PrintHashTable(&H);

	// 查找并打印找到的节点
	Node* node = SearchHash(&H, 27);
	if (node != NULL) {
		printf("Found: %d\n", node->key);
	}
	else {
		printf("Not Found\n");
	}

	// 删除一个元素
	DeleteHash(&H, 27);

	// 再次打印哈希表
	printf("\nAfter deletion:\n");
	PrintHashTable(&H);

	return 0;
}
