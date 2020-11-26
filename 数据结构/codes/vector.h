#pragma once
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include"Hashtable.h"

#define DEFAULT_CAPACITY 3

using namespace std;

typedef int Rank;

template <typename T> class Vector { //向量模板类
protected:
	void copyFrom(T const* A, Rank lo, Rank hi); //拷贝
	void expand(); //扩容
	void shrink(); //缩容

	bool bubble(Rank, Rank);
	void bubbleSort(Rank, Rank); //冒泡排序
	Rank max(Rank, Rank);
	void selectionSort(Rank, Rank); //选择排序
	void merge(Rank, Rank, Rank);
	void mergeSort(Rank, Rank); //归并排序
	Rank partition(Rank, Rank);
	void quickSort(Rank, Rank); //快速排序
	void shellSort(Rank, Rank); //希尔排序
	void insertionSort(Rank, Rank); //插入排序
	void binInsertionSort(Rank, Rank); //折半插入排序
	void halfInsertionSort(Rank, Rank); //二路插入排序
	void heapSort(Rank, Rank); //堆排序
	void hashSort(Rank, Rank); //哈希排序
public:
	int sortType = 0; //排序种类
	int compare = 0, compute = 0; //比较次数/计算次数
	Rank _size; int _capacity; T* _elem; //大小/容量/数据空间
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
	//析构函数
	~Vector(){
		delete[] _elem;
	}

	bool empty() { return !_size; } //是否为空
	int size() { return _size; } //大小
	T& operator[](Rank) const; //访问运算符

	//有序向量接口
	//查找
	Rank search(T const& e, Rank lo, Rank hi) {
		return binSearch(e, lo, hi);
	}
	Rank binSearch(T const& e, Rank lo, Rank hi);
	//无序向量接口
	//查找
	Rank find(T const& e) const { return find(e, 0, _size); }
	Rank find(T const&, Rank, Rank);
	//插入
	Rank insert(T const& e) { return insert(_size, e); }
	Rank insert(Rank, T const&);
	//删除
	T remove(Rank r) {
		T e = _elem[r]; remove(r, r + 1); return e;
	}
	int remove(Rank, Rank);
	//排序
	void sort(Rank, Rank);
	void sort() { sort(0, _size); }
};

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template <typename T> static bool lt(T& a, T& b) { return a <= b; }
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }
template <typename T> static bool eq(T& a, T& b) { return a == b; }

template <typename T> void show(Vector<T>& data) {
	for (int i = 0; i < data.size(); i++)
		cout << data[i] << " ";
}

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 1 > _capacity) return;
	T* oldElem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template <typename T>
Rank Vector<T>::binSearch(T const& e, Rank lo, Rank hi) {
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		(e < _elem[mi]) ? hi = mi : lo = mi + 1;
	}
	return --lo;
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) {
	while ((lo < hi--) && (_elem[hi] != e));
	return hi;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e; _size++;
	return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const {
	return _elem[r];
}

template <typename T> void Vector<T>::sort(Rank lo, Rank hi) {
	switch (sortType)
	{
	case 0:shellSort(0, _size); break;
	case 1:bubbleSort(0, _size); break;
	case 2:mergeSort(0, _size); break;
	case 3:selectionSort(0, _size); break;
	case 4:quickSort(0, _size); break;
	case 5:insertionSort(0, _size); break;
	case 6:binInsertionSort(0, _size); break;
	case 7:halfInsertionSort(0, _size); break;
	case 8:heapSort(0, _size); break;
	case 9:hashSort(0, _size); break;
	default:
		break;
	}
}

template <typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	while (!bubble(lo, hi--)); //若无序，则排序，区间不断缩小
}
template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true; //有序标志
	while (++lo < hi) { //遍历区间
		if (_elem[lo - 1] > _elem[lo]) { //若存在逆序
			sorted = false; //无序标志
			swap(_elem[lo - 1], _elem[lo]); //交换元素
			compute += 3;
		}
		compare++;
	}
	return sorted;
}

template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi) { //归并排序
	if (hi - lo < 2) return; //退化情况，直接返回
	int mi = (lo + hi) / 2; //取中点
	mergeSort(lo, mi); mergeSort(mi, hi); //分别归并排序前半段和后半段
	merge(lo, mi, hi); //归并两段区间
}
template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { //归并
	T* A = _elem + lo;
	int lb = mi - lo; T* B = new T[lb]; //前半段区间
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi; T* C = _elem + mi; //后半段区间
	for (Rank i = 0, j = 0, k = 0; j < lb;) { //归并为一个区间
		if ( (lc <= k) || (B[j] <= C[k])) A[i++] = B[j++]; //B中元素小于C中元素或者C区间已空
		if ( (k  < lc) && (C[k] <  B[j])) A[i++] = C[k++]; //C中元素小于B中元素且C区间非空
		compare += 2; compute++;
	}
}

template <typename T> void Vector<T>::selectionSort(Rank lo, Rank hi) { //选择排序
	int n = hi - lo;
	while (n > 1) {
		Rank index = max(lo, lo + n); //找到最大元素
		swap(_elem[index], _elem[n - 1]); n--; //交换至有序的区间中
		//T maxElem = _elem[index]; remove(index);
		//insert(lo + n - 1, maxElem); n--;
		compute += 3;
	}
}
template <typename T> Rank Vector<T>::max(Rank lo, Rank hi) { //选取最大元素
	int index = lo; T max = _elem[lo];
	for (int i = lo + 1; i < hi - lo; i++) {
		if (_elem[i] > max) {
			max = _elem[i]; index = i;
		}
		compare++;
	}
	return index;
}

template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi) { //快速排序
	if (hi - lo < 2)return; //退化情况，直接返回
	Rank mi = partition(lo, hi - 1); //找到轴点
	quickSort(lo, mi); //排序轴点的前半段
	quickSort(mi + 1, hi); //排序轴点的后半段
}
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi) { //轴点构造算法
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
	T pivot = _elem[lo]; //随机选择轴点，取出该元素
	while (lo < hi) { //
		while ((lo < hi) && (pivot <= _elem[hi])) {
			hi--; //hi--直到遇到小于轴点的元素
			compare++;
		}
		_elem[lo] = _elem[hi]; //将其放入轴点的左边
		compute++;
		while ((lo < hi) && (_elem[lo] <= pivot)) {
			lo++; //lo++直到遇到大于轴点的元素
			compare++;
		}
		_elem[hi] = _elem[lo]; //将其放入轴点的右边
		compute++;
	}
	_elem[lo] = pivot; //放入轴点
	return lo; //返回轴点位置
}

template <typename T> void Vector<T>::insertionSort(Rank lo, Rank hi) { //插入排序
	for (int i = lo; i < hi - lo; i++) //从lo开始插入元素
		for (int j = i; j > lo; j--) { //插入有序的区间中
			if (_elem[j - 1] > _elem[j]) {
				swap(_elem[j - 1], _elem[j]);
				compute += 3;
			}
			else
				break;
			compare++;
		}
}

template <typename T> void Vector<T>::binInsertionSort(Rank lo, Rank hi) { //折半插入排序
	for (int i = lo; i < hi - lo; i++) { //从lo开始插入元素
		int low = lo, high = i;
		while (low < high) { //通过折半找到插入位置
			int mid = (low + high) / 2;
			_elem[mid] > _elem[i] ? high = mid : low = mid + 1;
			compare++;
		}
		for (int j = i; j > low; j--) { //插入元素
			swap(_elem[j], _elem[j - 1]);
			compute += 3;
		}
	}
}

template <typename T> void Vector<T>::halfInsertionSort(Rank lo, Rank hi) { //二路插入排序
	int first = 0, last = 0; int* buffer = new int[_size]; //初始化辅助数组
	buffer[0] = _elem[0];
	for (int i = 0; i < _size; i++) {
		if (_elem[i] < buffer[first]) { //如果小于最小元素
			first = (first + _size - 1) % _size; //则向前插入
			buffer[first] = _elem[i];
			compare++; compute++;
		}
		else if (buffer[last] <= _elem[i]) { //如果大于最大元素
			last++; //则向后插入
			buffer[last] = _elem[i];
			compare += 2; compute++;
		}
		else { //如果在最小元素和最大元素之间
			int low = first, high = last; //则进行折半插入
			while (low != high) {  //通过折半找到插入位置
				int n = (high - low + _size) % _size;
				int mid = (low + n/2) % _size;
				buffer[mid] > _elem[i] ? high = mid : low = (mid + 1) % _size;
				compare++;
			}
			for (int k = last + 1; k != low; k = (k - 1 + _size) % _size) { //移动元素
				buffer[k] = buffer[(k - 1 + _size) % _size];
				compute++;
			}
			buffer[low] = _elem[i]; last++; //插入元素
			compare += 2; compute++;
		}
	}
	for (int i = 0; i < _size; i++) { //更新有序向量
		_elem[i] = buffer[(first + i) % _size];
		compute++;
	}
	delete[]buffer;
}

template <typename T> void Vector<T>::shellSort(Rank lo, Rank hi) { //希尔排序
	int h = 1, n = hi - lo;
	while (h < n / 3)
		h = h * 3 + 1;//找到不大于排序区间长度的最大增量
	while (h >= 1) {
		for (int i = h; i < n; i++)
			for (int j = i; h <= j && _elem[j] < _elem[j - h]; j -= h) { //对每一划分插入排序
				swap(_elem[j], _elem[j - h]);
				compare++; compute += 3;
			}
		h /= 3; //继续减小增量排序
	}
}

template <typename T> void Vector<T>::hashSort(Rank lo, Rank hi) {
	Hashtable<T, T> H(hi - lo); //构建哈希表
	for (int i = lo; i < hi; i++)
		H.put(_elem[i], _elem[i]); //插入元素(排序)
	H.sort(); //输出结果
}