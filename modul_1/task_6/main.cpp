/*
​Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>

int getMedian(const int *array, int start, int end) // медиана трех
{
  int mid = (start + end) / 2; 
  if (array[start] < array[end]) 
    std::swap(start, end);

  if (array[start] < array[mid]) 
    std::swap(start, end);

  if (array[mid] > array[end]) 
    std::swap(mid, end);

  return end; // позиция медианного элемента
}


int partition(int* array, int start, int end) 
{
    int pivotPos = getMedian(array, start, end);

    if(pivotPos != end) // меняем местами опорный элемент с последним                                                
        std::swap(array[end], array[pivotPos]);
    

    int i = start; 
    int j = start;
    int pivot = array[end];
    while(j < end) 
    {
        if(array[j] <= pivot) 
        {
            // текущий элемент не больше опорного
            // меняем его с первым из больших
            std::swap(array[i++], array[j]);
        }
        j++;
    }
    if(i != end)  // ставим опорный элемент на место
        std::swap(array[i], array[end]);
    return i;
}

int kStatistic(int *array, int n, int k) 
{
    int pivot;
    int start = 0;
    int end = n - 1;
    while(true) 
    {
      pivot = partition(array, start, end);
      if(pivot == k)  
          return array[pivot];
      else if (pivot > k) // опорный элемент оказался правее искомого
          end = pivot - 1;
      else  // опорный элемент не дошел до искомого
          start = pivot + 1;
      
    }
    return array[pivot];
}

int main() 
{
  int n;
  int k;
  int result;

  std::cin >> n >> k;
  int* array = new int[n];
  for (int i = 0; i < n; i++)
    std::cin >> array[i];

  result = kStatistic(array, n, k);
  std::cout << result;
  delete[] array;
  return 0;
}
