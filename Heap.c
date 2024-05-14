#include<stdio.h>
#include<stdlib.h>

void HeapAdjust(int arr[], int length, int k)
{
	int temp, j;
	temp = arr[k];

	for (j = 2 * k + 1; j <= length; j *= 2)
	{
		// �ҵ����Һ����нϴ���Ǹ�
		if (j < length && arr[j] < arr[j + 1])
		{
			j++;
		}
		// ������ڵ�С�ں����еĽϴ��ߣ��򽻻�
		if (temp < arr[j])
		{
			arr[k] = arr[j];
			arr[j] = temp;
			k = j;
		}
		else
		{
			break; // ���ڵ���ڵ���������ӣ��������ѭ��
		}
	}
}


void HeapSort(int arr[], int length)
{
	//�����ȶ�ÿ�����ն˽ڵ��������ɴ����,�����һ�����ն˽ڵ㿪ʼ
	for (int i = length / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(arr, length, i);
	}

	for (int i = length-1; i > 0; i--)
	{
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		HeapAdjust(arr, i-1, 0);
		
	}
}

void printArray(int arr[], int length) 
{
	for (int i = 0; i < length; i++) 
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int arr[] = { 50, 10, 90, 30, 70, 40, 80, 60, 20 };
	int length = sizeof(arr) / sizeof(arr[0]);

	printf("Before sorting: ");
	printArray(arr, length);

	HeapSort(arr, length);

	printf("After sorting: ");
	printArray(arr, length);

	return 0;
}