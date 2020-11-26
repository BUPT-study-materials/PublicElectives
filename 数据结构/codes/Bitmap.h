#pragma once
#include<string.h>
#include<stdio.h>

#define min(a,b) (a<b?a:b)

using namespace std;

class Bitmap { //位图
private:
	char* M; int N; //M是地址空间 N为空间长度
	//扩充
	void expand(int k) { //如果长度超过空间大小，则扩张
		if (k < 8 * N)return; //不满足扩张条件
		int oldN = N; char* oldM = M;
		init(2 * k); //初始化
		memcpy_s(M, N, oldM, oldN); //复制
		delete[]oldM; //回收内存
	}
protected:
	//初始化
	void init(int n) {
		M = new char[N = (n + 7) / 8]; //分配空间
		memset(M, 0, N);
	}
public:
	//构造函数
	Bitmap(int n = 8) { init(n); }
	Bitmap(char* file, int n = 8) {
		init(n);
		FILE* fp = fopen(file, "r"); //打开文件
		fread(M, sizeof(char), N, fp); //读取数据
		fclose(fp); //关闭文件
	}
	~Bitmap() { //析构函数
		delete[]M; M = nullptr;
	}

	void set(int k) { expand(k);        M[k >> 3] |= (0x80 >> (k & 0x07)); } //设置比特位
	void clear(int k) { expand(k);        M[k >> 3] &= ~(0x80 >> (k & 0x07)); } //清除比特位
	bool test(int k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); } //测试比特位
	//存储数据
	void dump(char* file) {
		FILE* fp = fopen(file, "w"); //打开文件
		fwrite(M, sizeof(char), N, fp); //写入数据
		fclose(fp); //关闭文件
	}
	//转化为字符串
	char* bits2string(int n) {
		expand(n - 1);
		char* s = new char[n + 1]; s[n] = '\0';
		for (int i = 0; i < n; i++)
			s[i] = test(i) ? '1' : '0';
		return s;
	}
};