#pragma once
#include"vector.h"

#define InHeap(n, i) ( ( -1 < i ) && ( i < n ) ) //判断PQ[i]是否合法
#define Parent(i) ( (i-1) >> 1) //PQ[i]的父节点
#define LastInternal(n) Parent(n-1) //最后一个内部结点
#define LChild(i) ( 1 + (i << 1) ) //PQ[i]的左孩子
#define RChild(i) ( (1 + i) << 1 ) //PQ[i]的右孩子
#define ParentValid(i) ( i > 0 ) //判断PQ[i]是否有父亲
#define LChildValid(n, i) InHeap(n, LChild(i)) //判断PQ[i]是否有一个(左)孩子
#define RChildValid(n, i) InHeap(n, RChild(i)) //判断PQ[i]是否有两个孩子
#define Bigger(PQ, i, j) ( lt(PQ[i],PQ[j]) ? j : i ) //取大者
#define ProperParent(PQ, n, i) /*父子三者中的大者*/ \
			( RChildValid(n,i) ? Bigger(PQ,Bigger(PQ,i,LChild(i)), RChild(i)) : \
			( LChildValid(n,i) ? Bigger(PQ, i, LChild(i)) : i \
			) \
			) //相等时父节点优先

template <typename T> struct PQ { //优先级队列PQ模板类
	virtual void insert(T) = 0; //按照比较器确定的优先级次序插入词条
	virtual T getMax() = 0; //取出优先级最高的词条
	virtual T delMax() = 0; //删除优先级最高的词条
};

template <typename T> class ComplHeap : public PQ<T>, public Vector<T> {
protected:
	Rank percolateDown(Rank n, Rank i); //下滤
	Rank percolateUp(Rank i); //上滤
	void heapify(Rank n); //Floyd建堆算法
public:
	ComplHeap() {} //默认构造
	ComplHeap(T* A, Rank n) { copyFrom(A, 0, n); heapify(n); } //批量构造
	void insert(T); //按照比较器确定的优先级次序，插入词条
	T getMax() { return _elem[0]; }; //读取优先级最高的词条
	T delMax(); //删除优先级最高的词条
};

template <typename T> void ComplHeap<T>::insert(T e) {
	insert(e);
	percolateUp(_size - 1);
}

template <typename T> Rank ComplHeap<T>::percolateUp(Rank i) { //上滤
	while (ParentValid(i)) { //当节点还有父亲时，上滤至根节点终止
		Rank j = Parent(i);
		if (lt(_elem[i], _elem[j])) break; //如果满足堆序性，则终止
		swap(_elem[i], _elem[j]); i = j; //否则，交换数据，继续向上比较
	}
	return i;
}

template <typename T> T ComplHeap<T>::delMax() {
	T maxElem = _elem[0]; _elem[0] = _elem[--_size]; //将末节点移至堆顶
	percolateDown(_size, 0); //下滤
	return maxElem;
}

template <typename T> Rank ComplHeap<T>::percolateDown(Rank n, Rank i) { //下滤
	Rank j;
	while (i != (j = ProperParent(_elem, n, i))) { //当三者不满足堆序性时，否则循环终止
		swap(_elem[i], _elem[j]); i = j; //交换元素，继续向下比较
		compute += 3; compare += 2;
	}
	return i;
}

template <typename T> void ComplHeap<T>::heapify(Rank n) {
	for (int i = LastInternal(n); InHeap(n, i); i--) //从某节点开始，由后至前
		percolateDown(n, i); //下滤
}

template <typename T> void Vector<T>::heapSort(Rank lo, Rank hi) { //堆排序
	ComplHeap<T> H(_elem + lo, hi - lo); //建立堆
	while (!H.empty()) {
		_elem[--hi] = H.delMax(); //删除最大元素，然后插入向量中
		compute++;
	}
	compare = H.compare; compute += H.compute;
}