#pragma once
#include<vector>
#include"Bitmap.h"

template <typename K, typename V>
struct Entry { //词条，哈希表中存储的数据单位
	K key; V value; //键值对
	//构造函数
	Entry(K k = K(), V v = V()) :key(k), value(v) {};
	Entry(Entry<K, V> const& e) :key(e.key), value(e.value) {};
	//重载操作运算符
	bool operator< (Entry<K, V> const& e) { return key < e.key; }
	bool operator> (Entry<K, V> const& e) { return key > e.key; }
	bool operator==(Entry<K, V> const& e) { return key == e.key; }
	bool operator!=(Entry<K, V> const& e) { return key != e.key; }
};

template <typename K, typename V>
class Hashtable { //哈希表数据结构
private:
	vector<Entry<K, V>*>* ht; //链地址法
	int M; //桶数组容量
	int N; //词条数量

	//散列码转换
	static size_t hashCode(char c) { return (size_t)c; }
	static size_t hashCode(int k) { return (size_t)k; }
	static size_t hashCode(long long i) { return (size_t)((i >> 32) + (int)i); }
	static size_t hashCode(char s[]) {
		int h = 0;
		for (size_t n = strlen(s), i = 0; i < n; i++) {
			h = (h << 5) | (h >> 27); h += (int)s[i];
		}
		return (size_t)h;
	}

public:
	Hashtable(int c = 5); //构造函数
	//~Hashtable();
	int size() const { return N; } //当前词条数目
	bool put(K, V); //插入
	V* get(K k); //读取
	void sort(); //排序
};

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c) {
	M = primeNLT(c, 1048576, "primeNumber.txt"); //找到大于M的最小质数
	N = 0; ht = new vector<Entry<K,V>*> [M]; //初始化桶数组
	memset(ht, 0, sizeof(vector<Entry<K, V>*>) * M);
}

int primeNLT(int c, int n, char* file) { //找到大于c小于n的最小质数
	Bitmap B(file, n);
	while (c < n)
		if (B.test(c)) c++;
		else return c;
	return c;
}

template <typename K, typename V>
V* Hashtable<K, V>::get(K k) { //访问函数
	int r = hashCode(k) % M; //找到要访问的点
	for (auto it = ht[r].cbegin(); it != ht[r].cend(); it++) {
		if ((*it)->key = k)
			return &(*it->value);
	}
	return nullptr;
}

template <typename K, typename V>
bool Hashtable<K, V>::put(K k, V v) { //插入键值对
	int r = hashCode(k) % M; //找到空的位置
	if (!ht[r].empty()) //如果该位置已有元素
		ht[r].push_back(new Entry<K, V>(k, v)); //则插入元素
	else { //否则创建新的容器
		vector<Entry<K, V>*> vec;
		vec.push_back(new Entry<K, V>(k, v));
		ht[r] = vec;
		++N; //插入新的键值对
	}
	return true;
}

template <typename K, typename V>
void Hashtable<K, V>::sort() {
	for (int i = 0; i < M; i++) //遍历地址空间
		if (ht[i].size() > 0) //输出每个地址的数据
			for (int j = 0; j < ht[i].size(); j++)
				cout << ht[i][j]->value << " ";
}