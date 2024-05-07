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
//	int* elem;	//���ڴ���Ԫ�ش���ĵ�ַ
//	int count;	//������¼��ǰ��Ԫ�ظ���
//}HashTable;
//
//int m = 0;
//
////��ʼ��ɢ�б�
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
////ɢ�к���
//int Hash(int key)
//{
//	return key % m;	//�������෨
//}
//
////���ŵ�ַ��������̽�ⷨ ����ؼ���
//void InsertHash(HashTable* H, int key)
//{
//	int addr = Hash(key);	//����ɢ�е�ַ
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
//	int searchKey = 5; // ���ڲ��Բ��ҵļ�ֵ
//	int searchAddr;
//
//	// ��ʼ����ϣ��
//	if (!InitHashTable(&H))
//	{
//		printf("��ʼ����ϣ��ʧ�ܡ�\n");
//		return -1;
//	}
//
//	printf("��ϣ���ʼ���ɹ���\n");
//
//	// ����12��Ԫ��
//	int keysToInsert[] = { 15, 33, 47, 21, 9, 39, 55, 27, 11, 43, 3, 25 };
//	printf("���ڲ����ֵ��\n");
//	for (int i = 0; i < 12; i++)
//	{
//		InsertHash(&H, keysToInsert[i]);
//		printf("%d ", keysToInsert[i]);
//	}
//	printf("\n������ɡ�\n");
//
//	printf("������������ҵ�ֵ\n");
//	int find = 0;
//	scanf("%d", &find);
//	searchKey = find;
//	 //����һ�����ڵļ�ֵ
//	if (SearchHash(H, searchKey, &searchAddr))
//	{
//		printf("�ҵ���ֵ%d��λ�ڵ�ַ%d��\n", searchKey, searchAddr);
//	}
//	else
//	{
//		printf("δ�ҵ���ֵ%d��\n", searchKey);
//	}
//
//	// ע�⣺����û��ʵ���ͷ��ڴ�Ĳ�����ʵ��Ӧ����Ӧ�ڳ������ǰ�ͷ�H.elemָ����ڴ�
//	 free(H.elem);
//
//	return 0;
//}




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#define NULLKEY -32786

typedef int Status;

//����д������
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


//�����½ڵ�
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

//���뺯��
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
			if (prev == NULL) // ���������ͷ�ڵ�
			{
				H->table[index] = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current);
			return; // ɾ����ֱ�ӷ��أ������������
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

	// ����һЩԪ��
	InsertHash(&H, 56);
	InsertHash(&H, 27);
	InsertHash(&H, 18);
	InsertHash(&H, 34);

	// ��ӡ��ϣ��
	PrintHashTable(&H);

	// ���Ҳ���ӡ�ҵ��Ľڵ�
	Node* node = SearchHash(&H, 27);
	if (node != NULL) {
		printf("Found: %d\n", node->key);
	}
	else {
		printf("Not Found\n");
	}

	// ɾ��һ��Ԫ��
	DeleteHash(&H, 27);

	// �ٴδ�ӡ��ϣ��
	printf("\nAfter deletion:\n");
	PrintHashTable(&H);

	return 0;
}
