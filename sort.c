#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void swap(int *rootP, int* largestP)
{
	int temp = *rootP;
	*rootP = *largestP;
	*largestP = temp;
}

void heapify(int arr[], int N, int i)
{
	//Find the largest among root, left child, and right child
	//Initialize largest as root
	int largest = i;

	int left = 2 * i + 1; //index of the left child in the array
	int right = 2 * i + 2; //index of the right child in the array

	//if the left child is larger than the root
	if(left < N && arr[left] > arr[largest])
	{
		largest = left;
	}

	//if the right child is larger than the largest so far
	if(right < N && arr[right] > arr[largest])
	{
		largest = right;
	}

	//Swap and continue heapifying if root is not the largest

	//if the largest is not root
	if(largest != i)
	{
		swap(&arr[i], &arr[largest]);
		
		//recursively heapify the affected sub-tree
		heapify(arr, N, largest);
	}
}
void heapSort(int arr[], int n)
{
	//Building the binary max heap
	for(int i = n/2 - 1; i >= 0; i--)
	{
		heapify(arr, n, i);
	}

	//sort the max heap
	for(int i = n - 1; i >= 0; i--)
	{
		//swap the root node and the last leaf node
		int temp = arr[i];
		swap(&arr[i], &arr[0]);
		
		//again heapify the max heap from the root
		heapify(arr, i, 0);
	
	}


}

void merge(int arr[], int l, int m, int r)
{
	int i;
	int j;
	int k;
	int leftSize = m - l + 1;
	int rightSize = r - m;

	//Temporary Arrays
	int *leftSideArray = (int*)malloc(leftSize * sizeof(int));
	extraMemoryAllocated += leftSize * sizeof(int);

	int *rightSideArray = (int*)malloc(rightSize * sizeof(int));
	extraMemoryAllocated += rightSize * sizeof(int);

	//Copying data to the temporary arrays

	for(i = 0; i < leftSize; i++)
	{
		leftSideArray[i] = arr[l + i];
	}
	
	for(j = 0; j < rightSize; j++)
	{
		rightSideArray[j] = arr[m + 1 + j];
	}

	//Merge the temp arrays back into arr[]

	i = 0;
	j = 0;
	k = l;

	while(i < leftSize && j < rightSize)
	{
		if(leftSideArray[i] <= rightSideArray[j])
		{
			arr[k] = leftSideArray[i];
			i++;
		}
		else
		{
			arr[k] = rightSideArray[j];
			j++;
		}
		
		k++;

	}

	//Copy the remaining elements of the leftSideArray
	while(i < leftSize)
	{
		arr[k] = leftSideArray[i];
		i++;
		k++;
	}

	//Copy the remaining elements of the rightSideArray
	while(j < rightSize)
	{
		arr[k] = rightSideArray[j];
		j++;
		k++;
	}

	free(leftSideArray);
	free(rightSideArray);

}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int m = (l + r)/2; //Get the midpoint
		//Sort the first and second halves
		mergeSort(pData, l, m);
		mergeSort(pData, m+1, r);
		merge(pData, l, m, r);

	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for(int i = 0; i < dataSz; i++)
		{
			fscanf(inFile, "%d", *ppData + i);
		}
		
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	

	printf("\tData:\n\t");
	if(dataSz > 100)
	{
		for (i=0;i<100;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\t");
	
	
	
		for (i=sz;i<dataSz;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n\n");
	}
	else
	{
		for (i=0;i < dataSz ;++i)
		{
			printf("%d ",pData[i]);
		}
		printf("\n");
	}
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}