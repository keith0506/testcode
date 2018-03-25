void adjustHeap(int *arr, int i, int len)
{
	int temp = arr[i];
	for (int k = i*2+1; k < len; k = k*2+1)
	{
		if(k+1 < len && arr[k+1] > arr[k])
			k++;
		if(arr[k] > temp)
		{
			arr[i] = arr[k]; //big heap
			i = k;
		}
		else
			break;
	}
	arr[i] = temp;
}
void swap(int *arr, int i, int j)
{
	arr[j] = arr[i]^arr[j];
	arr[i] = arr[i]^arr[j];
	arr[j] = arr[i]^arr[j];
}
void heapSort(int *arr, int num)
{
	for(int i = num/2-1; i >= 0; i --)
		adjustHeap(arr, i, num);
	for(int j = num - 1; j > 0; j--)
	{
		swap(arr, 0, j);
		adjustHeap(arr, 0, j);
	}
}