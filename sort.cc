#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include "timer.h"

using namespace std;

int UniformRand(int n) {
  int top = (RAND_MAX - n + 1) / n * n - 1 + n;
  int num;
  do {
    num = rand();
  } while (num > top);
  return num % n;
}

template <typename T>
void BubbleSort(vector<T> &v) {
  bool swapped = true;
  int n = v.size();
  while (swapped) {
    swapped = false;
    for (size_t i = 1; i < n; ++i) {
      if (v[i - 1] > v[i]) {
        swap(v[i - 1], v[i]);
        swapped = true;
      }   
    }
    --n;
  }
}

template <typename T>
void SelectionSort(vector<T> &v) {
  for (int i = 0; i < v.size(); ++i) {
    T min = v[i];
    int ix = i;
    for (int j = i; j < v.size(); ++j) {
      if (v[j] < min) {
        min = v[j];
        ix = j;
      }
    }
    swap(v[ix], v[i]);
  }
} 

template <typename T>
void InsertionSort(vector<T> &v) {
  for (int i = 1; i < v.size(); ++i) {
    for (int j = i; j > 0 && v[j - 1] > v[j]; --j) {
      swap(v[j - 1], v[j]);
    }
  }
}

int Partition(vector<int> &v, int start, int finish) {
  int i = start, j = finish + 1;
  int pivot = v[start];
  while (true) {
    while (v[--j] > pivot) ;
    while (v[++i] < pivot) if (i == finish) break;
    if (i >= j) break;
    swap(v[i], v[j]);
  }
  swap(v[j], v[start]);
  return j;
}

int PartitionRand(vector<int> &v, int start, int finish) {
  int r = start + UniformRand(finish - start + 1);
  swap(v[start], v[r]);
  return Partition(v, start, finish); 
}

void QuickSort(vector<int> &v, int start, int finish) {
  if (start >= finish) return;
  int boundary = PartitionRand(v, start, finish);
  QuickSort(v, start, boundary - 1);
  QuickSort(v, boundary + 1, finish);
}

void QuickSortSTL(vector<int> &v, vector<int>::iterator start, vector<int>::iterator end) {
  if (start >= end) return;
  vector<int>::iterator boundary = stable_partition(start, end, bind2nd(less<int>(), *start));
  QuickSortSTL(v, start, boundary);
  QuickSortSTL(v, boundary + 1, end);
}

void Merge(vector<int> &v, int lo, int hi) {
  int n = hi - lo;
  int i = 0, j = n / 2 + 1;
  vector<int> aux;
  for (int k = lo; k <= hi; ++k) {
    aux.push_back(v[k]);
  }
  for (int k = lo; k <= hi; ++k) {
    if (i > n / 2)
      v[k] = aux[j++];
    else if (j > n)
      v[k] = aux[i++];
    else if (aux[i] < aux[j])
      v[k] = aux[i++];
    else
      v[k] = aux[j++];
  } 
}

void MergeSort(vector<int> &v, int lo, int hi) {
  if (lo >= hi) return;
  int mid = lo + (hi - lo) / 2;
  MergeSort(v, lo, mid);
  MergeSort(v, mid + 1, hi);
  Merge(v, lo, hi);
}

vector<int> RandVec(int size) {
  vector<int> ret;
  for (int i = 0; i < size; ++i) {
    ret.push_back(rand());
  }
  return ret;
}

int main() {
  srand(time(NULL));
  int size;
  cin >> size;
  vector<int> v = RandVec(size);
  vector<int> check = v;
  QuickSort(check, 0, check.size() - 1);
  Timer t;
  t.Start();
  for (int i = 0; i < 8; ++i) {
    vector<int> tmp = v;
    switch (i) {
      case 0: BubbleSort(tmp); break;
      case 1: SelectionSort(tmp); break;
      case 2: InsertionSort(tmp); break;
      case 3: MergeSort(tmp, 0, tmp.size() - 1); break;
      case 4: QuickSort(tmp, 0, tmp.size() - 1); break;
      case 5: QuickSortSTL(tmp, tmp.begin(), tmp.end()); break;
      case 6: sort(tmp.begin(), tmp.end()); break;
      case 7: stable_sort(tmp.begin(), tmp.end()); break;
      default: cout << "Error!" << endl; exit(1);
    }
    cout << t.GetMs() << endl;
    if (tmp == check) cout << "correct" << endl; else cout << "error" << endl;
  }
  return 0;
}
