#pragma once
#include"vector.h"

#define InHeap(n, i) ( ( -1 < i ) && ( i < n ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define Parent(i) ( (i-1) >> 1) //PQ[i]�ĸ��ڵ�
#define LastInternal(n) Parent(n-1) //���һ���ڲ����
#define LChild(i) ( 1 + (i << 1) ) //PQ[i]������
#define RChild(i) ( (1 + i) << 1 ) //PQ[i]���Һ���
#define ParentValid(i) ( i > 0 ) //�ж�PQ[i]�Ƿ��и���
#define LChildValid(n, i) InHeap(n, LChild(i)) //�ж�PQ[i]�Ƿ���һ��(��)����
#define RChildValid(n, i) InHeap(n, RChild(i)) //�ж�PQ[i]�Ƿ�����������
#define Bigger(PQ, i, j) ( lt(PQ[i],PQ[j]) ? j : i ) //ȡ����
#define ProperParent(PQ, n, i) /*���������еĴ���*/ \
			( RChildValid(n,i) ? Bigger(PQ,Bigger(PQ,i,LChild(i)), RChild(i)) : \
			( LChildValid(n,i) ? Bigger(PQ, i, LChild(i)) : i \
			) \
			) //���ʱ���ڵ�����

template <typename T> struct PQ { //���ȼ�����PQģ����
	virtual void insert(T) = 0; //���ձȽ���ȷ�������ȼ�����������
	virtual T getMax() = 0; //ȡ�����ȼ���ߵĴ���
	virtual T delMax() = 0; //ɾ�����ȼ���ߵĴ���
};

template <typename T> class ComplHeap : public PQ<T>, public Vector<T> {
protected:
	Rank percolateDown(Rank n, Rank i); //����
	Rank percolateUp(Rank i); //����
	void heapify(Rank n); //Floyd�����㷨
public:
	ComplHeap() {} //Ĭ�Ϲ���
	ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(n); } //��������
	void insert(T); //���ձȽ���ȷ�������ȼ����򣬲������
	T getMax() { return _elem[0]; }; //��ȡ���ȼ���ߵĴ���
	T delMax(); //ɾ�����ȼ���ߵĴ���
};

template <typename T> void ComplHeap<T>::insert(T e) {
	insert(e);
	percolateUp(_size - 1);
}

template <typename T> Rank ComplHeap<T>::percolateUp(Rank i) { //����
	while (ParentValid(i)) { //���ڵ㻹�и���ʱ�����������ڵ���ֹ
		Rank j = Parent(i);
		if (lt(_elem[i], _elem[j])) break; //�����������ԣ�����ֹ
		swap(_elem[i], _elem[j]); i = j; //���򣬽������ݣ��������ϱȽ�
	}
	return i;
}

template <typename T> T ComplHeap<T>::delMax() {
	T maxElem = _elem[0]; _elem[0] = _elem[--_size]; //��ĩ�ڵ������Ѷ�
	percolateDown(_size, 0); //����
	return maxElem;
}

template <typename T> Rank ComplHeap<T>::percolateDown(Rank n, Rank i) { //����
	Rank j;
	while (i != (j = ProperParent(_elem, n, i))) { //�����߲����������ʱ������ѭ����ֹ
		swap(_elem[i], _elem[j]); i = j; //����Ԫ�أ��������±Ƚ�
		compute += 3; compare += 2;
	}
	return i;
}

template <typename T> void ComplHeap<T>::heapify(Rank n) {
	for (int i = LastInternal(n); InHeap(n, i); i--) //��ĳ�ڵ㿪ʼ���ɺ���ǰ
		percolateDown(n, i); //����
}

template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi) { //������
	ComplHeap<T> H(_elem + lo, hi - lo); //������
	while (!H.empty()) {
		_elem[--hi] = H.delMax(); //ɾ�����Ԫ�أ�Ȼ�����������
		compute++;
	}
	compare = H.compare; compute += H.compute;
}