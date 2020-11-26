#pragma once
#include<vector>
#include"Bitmap.h"

template <typename K, typename V>
struct Entry { //��������ϣ���д洢�����ݵ�λ
	K key; V value; //��ֵ��
	//���캯��
	Entry(K k = K(), V v = V()) :key(k), value(v) {};
	Entry(Entry<K, V> const& e) :key(e.key), value(e.value) {};
	//���ز��������
	bool operator< (Entry<K, V> const& e) { return key < e.key; }
	bool operator> (Entry<K, V> const& e) { return key > e.key; }
	bool operator==(Entry<K, V> const& e) { return key == e.key; }
	bool operator!=(Entry<K, V> const& e) { return key != e.key; }
};

template <typename K, typename V>
class Hashtable { //��ϣ�����ݽṹ
private:
	vector<Entry<K, V>*>* ht; //����ַ��
	int M; //Ͱ��������
	int N; //��������

	//ɢ����ת��
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
	Hashtable(int c = 5); //���캯��
	//~Hashtable();
	int size() const { return N; } //��ǰ������Ŀ
	bool put(K, V); //����
	V* get(K k); //��ȡ
	void sort(); //����
};

template <typename K, typename V>
Hashtable<K, V>::Hashtable(int c) {
	M = primeNLT(c, 1048576, "primeNumber.txt"); //�ҵ�����M����С����
	N = 0; ht = new vector<Entry<K,V>*> [M]; //��ʼ��Ͱ����
	memset(ht, 0, sizeof(vector<Entry<K, V>*>) * M);
}

int primeNLT(int c, int n, char* file) { //�ҵ�����cС��n����С����
	Bitmap B(file, n);
	while (c < n)
		if (B.test(c)) c++;
		else return c;
	return c;
}

template <typename K, typename V>
V* Hashtable<K, V>::get(K k) { //���ʺ���
	int r = hashCode(k) % M; //�ҵ�Ҫ���ʵĵ�
	for (auto it = ht[r].cbegin(); it != ht[r].cend(); it++) {
		if ((*it)->key = k)
			return &(*it->value);
	}
	return nullptr;
}

template <typename K, typename V>
bool Hashtable<K, V>::put(K k, V v) { //�����ֵ��
	int r = hashCode(k) % M; //�ҵ��յ�λ��
	if (!ht[r].empty()) //�����λ������Ԫ��
		ht[r].push_back(new Entry<K, V>(k, v)); //�����Ԫ��
	else { //���򴴽��µ�����
		vector<Entry<K, V>*> vec;
		vec.push_back(new Entry<K, V>(k, v));
		ht[r] = vec;
		++N; //�����µļ�ֵ��
	}
	return true;
}

template <typename K, typename V>
void Hashtable<K, V>::sort() {
	for (int i = 0; i < M; i++) //������ַ�ռ�
		if (ht[i].size() > 0) //���ÿ����ַ������
			for (int j = 0; j < ht[i].size(); j++)
				cout << ht[i][j]->value << " ";
}