#pragma once
#include<string.h>
#include<stdio.h>

#define min(a,b) (a<b?a:b)

using namespace std;

class Bitmap { //λͼ
private:
	char* M; int N; //M�ǵ�ַ�ռ� NΪ�ռ䳤��
	//����
	void expand(int k) { //������ȳ����ռ��С��������
		if (k < 8 * N)return; //��������������
		int oldN = N; char* oldM = M;
		init(2 * k); //��ʼ��
		memcpy_s(M, N, oldM, oldN); //����
		delete[]oldM; //�����ڴ�
	}
protected:
	//��ʼ��
	void init(int n) {
		M = new char[N = (n + 7) / 8]; //����ռ�
		memset(M, 0, N);
	}
public:
	//���캯��
	Bitmap(int n = 8) { init(n); }
	Bitmap(char* file, int n = 8) {
		init(n);
		FILE* fp = fopen(file, "r"); //���ļ�
		fread(M, sizeof(char), N, fp); //��ȡ����
		fclose(fp); //�ر��ļ�
	}
	~Bitmap() { //��������
		delete[]M; M = nullptr;
	}

	void set(int k) { expand(k);        M[k >> 3] |= (0x80 >> (k & 0x07)); } //���ñ���λ
	void clear(int k) { expand(k);        M[k >> 3] &= ~(0x80 >> (k & 0x07)); } //�������λ
	bool test(int k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); } //���Ա���λ
	//�洢����
	void dump(char* file) {
		FILE* fp = fopen(file, "w"); //���ļ�
		fwrite(M, sizeof(char), N, fp); //д������
		fclose(fp); //�ر��ļ�
	}
	//ת��Ϊ�ַ���
	char* bits2string(int n) {
		expand(n - 1);
		char* s = new char[n + 1]; s[n] = '\0';
		for (int i = 0; i < n; i++)
			s[i] = test(i) ? '1' : '0';
		return s;
	}
};