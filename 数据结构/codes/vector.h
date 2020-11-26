#pragma once
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include"Hashtable.h"

#define DEFAULT_CAPACITY 3

using namespace std;

typedef int Rank;

template <typename T> class Vector { //����ģ����
protected:
	void copyFrom(T const* A, Rank lo, Rank hi); //����
	void expand(); //����
	void shrink(); //����

	bool bubble(Rank, Rank);
	void bubbleSort(Rank, Rank); //ð������
	Rank max(Rank, Rank);
	void selectionSort(Rank, Rank); //ѡ������
	void merge(Rank, Rank, Rank);
	void mergeSort(Rank, Rank); //�鲢����
	Rank partition(Rank, Rank);
	void quickSort(Rank, Rank); //��������
	void shellSort(Rank, Rank); //ϣ������
	void insertionSort(Rank, Rank); //��������
	void binInsertionSort(Rank, Rank); //�۰��������
	void halfInsertionSort(Rank, Rank); //��·��������
	void heapSort(Rank, Rank); //������
	void hashSort(Rank, Rank); //��ϣ����
public:
	int sortType = 0; //��������
	int compare = 0, compute = 0; //�Ƚϴ���/�������
	Rank _size; int _capacity; T* _elem; //��С/����/���ݿռ�
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
	//��������
	~Vector(){
		delete[] _elem;
	}

	bool empty() { return !_size; } //�Ƿ�Ϊ��
	int size() { return _size; } //��С
	T& operator[](Rank) const; //���������

	//���������ӿ�
	//����
	Rank search(T const& e, Rank lo, Rank hi) {
		return binSearch(e, lo, hi);
	}
	Rank binSearch(T const& e, Rank lo, Rank hi);
	//���������ӿ�
	//����
	Rank find(T const& e) const { return find(e, 0, _size); }
	Rank find(T const&, Rank, Rank);
	//����
	Rank insert(T const& e) { return insert(_size, e); }
	Rank insert(Rank, T const&);
	//ɾ��
	T remove(Rank r) {
		T e = _elem[r]; remove(r, r + 1); return e;
	}
	int remove(Rank, Rank);
	//����
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
	while (!bubble(lo, hi--)); //���������������䲻����С
}
template <typename T> bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true; //�����־
	while (++lo < hi) { //��������
		if (_elem[lo - 1] > _elem[lo]) { //����������
			sorted = false; //�����־
			swap(_elem[lo - 1], _elem[lo]); //����Ԫ��
			compute += 3;
		}
		compare++;
	}
	return sorted;
}

template <typename T> void Vector<T>::mergeSort(Rank lo, Rank hi) { //�鲢����
	if (hi - lo < 2) return; //�˻������ֱ�ӷ���
	int mi = (lo + hi) / 2; //ȡ�е�
	mergeSort(lo, mi); mergeSort(mi, hi); //�ֱ�鲢����ǰ��κͺ���
	merge(lo, mi, hi); //�鲢��������
}
template <typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi) { //�鲢
	T* A = _elem + lo;
	int lb = mi - lo; T* B = new T[lb]; //ǰ�������
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lc = hi - mi; T* C = _elem + mi; //��������
	for (Rank i = 0, j = 0, k = 0; j < lb;) { //�鲢Ϊһ������
		if ( (lc <= k) || (B[j] <= C[k])) A[i++] = B[j++]; //B��Ԫ��С��C��Ԫ�ػ���C�����ѿ�
		if ( (k  < lc) && (C[k] <  B[j])) A[i++] = C[k++]; //C��Ԫ��С��B��Ԫ����C����ǿ�
		compare += 2; compute++;
	}
}

template <typename T> void Vector<T>::selectionSort(Rank lo, Rank hi) { //ѡ������
	int n = hi - lo;
	while (n > 1) {
		Rank index = max(lo, lo + n); //�ҵ����Ԫ��
		swap(_elem[index], _elem[n - 1]); n--; //�����������������
		//T maxElem = _elem[index]; remove(index);
		//insert(lo + n - 1, maxElem); n--;
		compute += 3;
	}
}
template <typename T> Rank Vector<T>::max(Rank lo, Rank hi) { //ѡȡ���Ԫ��
	int index = lo; T max = _elem[lo];
	for (int i = lo + 1; i < hi - lo; i++) {
		if (_elem[i] > max) {
			max = _elem[i]; index = i;
		}
		compare++;
	}
	return index;
}

template <typename T> void Vector<T>::quickSort(Rank lo, Rank hi) { //��������
	if (hi - lo < 2)return; //�˻������ֱ�ӷ���
	Rank mi = partition(lo, hi - 1); //�ҵ����
	quickSort(lo, mi); //��������ǰ���
	quickSort(mi + 1, hi); //�������ĺ���
}
template <typename T> Rank Vector<T>::partition(Rank lo, Rank hi) { //��㹹���㷨
	swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
	T pivot = _elem[lo]; //���ѡ����㣬ȡ����Ԫ��
	while (lo < hi) { //
		while ((lo < hi) && (pivot <= _elem[hi])) {
			hi--; //hi--ֱ������С������Ԫ��
			compare++;
		}
		_elem[lo] = _elem[hi]; //��������������
		compute++;
		while ((lo < hi) && (_elem[lo] <= pivot)) {
			lo++; //lo++ֱ��������������Ԫ��
			compare++;
		}
		_elem[hi] = _elem[lo]; //������������ұ�
		compute++;
	}
	_elem[lo] = pivot; //�������
	return lo; //�������λ��
}

template <typename T> void Vector<T>::insertionSort(Rank lo, Rank hi) { //��������
	for (int i = lo; i < hi - lo; i++) //��lo��ʼ����Ԫ��
		for (int j = i; j > lo; j--) { //���������������
			if (_elem[j - 1] > _elem[j]) {
				swap(_elem[j - 1], _elem[j]);
				compute += 3;
			}
			else
				break;
			compare++;
		}
}

template <typename T> void Vector<T>::binInsertionSort(Rank lo, Rank hi) { //�۰��������
	for (int i = lo; i < hi - lo; i++) { //��lo��ʼ����Ԫ��
		int low = lo, high = i;
		while (low < high) { //ͨ���۰��ҵ�����λ��
			int mid = (low + high) / 2;
			_elem[mid] > _elem[i] ? high = mid : low = mid + 1;
			compare++;
		}
		for (int j = i; j > low; j--) { //����Ԫ��
			swap(_elem[j], _elem[j - 1]);
			compute += 3;
		}
	}
}

template <typename T> void Vector<T>::halfInsertionSort(Rank lo, Rank hi) { //��·��������
	int first = 0, last = 0; int* buffer = new int[_size]; //��ʼ����������
	buffer[0] = _elem[0];
	for (int i = 0; i < _size; i++) {
		if (_elem[i] < buffer[first]) { //���С����СԪ��
			first = (first + _size - 1) % _size; //����ǰ����
			buffer[first] = _elem[i];
			compare++; compute++;
		}
		else if (buffer[last] <= _elem[i]) { //����������Ԫ��
			last++; //��������
			buffer[last] = _elem[i];
			compare += 2; compute++;
		}
		else { //�������СԪ�غ����Ԫ��֮��
			int low = first, high = last; //������۰����
			while (low != high) {  //ͨ���۰��ҵ�����λ��
				int n = (high - low + _size) % _size;
				int mid = (low + n/2) % _size;
				buffer[mid] > _elem[i] ? high = mid : low = (mid + 1) % _size;
				compare++;
			}
			for (int k = last + 1; k != low; k = (k - 1 + _size) % _size) { //�ƶ�Ԫ��
				buffer[k] = buffer[(k - 1 + _size) % _size];
				compute++;
			}
			buffer[low] = _elem[i]; last++; //����Ԫ��
			compare += 2; compute++;
		}
	}
	for (int i = 0; i < _size; i++) { //������������
		_elem[i] = buffer[(first + i) % _size];
		compute++;
	}
	delete[]buffer;
}

template <typename T> void Vector<T>::shellSort(Rank lo, Rank hi) { //ϣ������
	int h = 1, n = hi - lo;
	while (h < n / 3)
		h = h * 3 + 1;//�ҵ��������������䳤�ȵ��������
	while (h >= 1) {
		for (int i = h; i < n; i++)
			for (int j = i; h <= j && _elem[j] < _elem[j - h]; j -= h) { //��ÿһ���ֲ�������
				swap(_elem[j], _elem[j - h]);
				compare++; compute += 3;
			}
		h /= 3; //������С��������
	}
}

template <typename T> void Vector<T>::hashSort(Rank lo, Rank hi) {
	Hashtable<T, T> H(hi - lo); //������ϣ��
	for (int i = lo; i < hi; i++)
		H.put(_elem[i], _elem[i]); //����Ԫ��(����)
	H.sort(); //������
}