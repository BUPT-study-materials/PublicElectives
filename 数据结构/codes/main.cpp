#include"ComplHeap.h"
#include<stack>
#include<utility>
#include<iomanip>

typedef struct {
	int id; //ѧ��
	string name; //����
	int* score; //���Ʒ���
	int total; //�ܷ�
} student;

string subject[9] = {"����","��ѧ","Ӣ��", "����", "��ѧ", "����", "��ʷ", "����", "����" };

void quickSort_iter(student[], int);
int partition(student[], int, int);

int main() {
	//cout << "��ѡ���������С: ";
	//cin >> n;
	int k = 0;
	int sort;
	int result[10] = { 0 };
	cout << endl << "��ѡ�������㷨��" << endl << "0/ϣ������" << endl << "1/ð������" << endl
		<< "2/�鲢����" << endl << "3/ѡ������" << endl << "4/��������" << endl << "5/��������"
		<< endl << "6/�۰��������" << endl << "7/��·��������" << endl << "8/������" << endl
		<< "9/��ϣ����" << endl; cin >> sort;
	for (int j = 1; j < 6; j++) {
		int n = j * 100;
		Vector<int> data(n); data.sortType = sort;
		cout << endl << "���ɵ���������У�" << endl;
		for (int i = 0; i < n; i++)
			data.insert(rand() % n);
		show(data); cout << endl;
		cout << "���������У�" << endl;
		data.sort();
		if (data.sortType != 9)
			show(data);
		cout << endl << "�Ƚϴ�����" << data.compare << " �������" << data.compute << endl;
		result[k++] = data.compare; result[k++] = data.compute;
	}
	for (int i = 0; i < 10; i++)
		cout << result[i] << " ";

	int n; int m;
	cout << endl << endl << "������ѧ��������"; cin >> n;
	cout << "������ѧ������"; cin >> m;
	student* students = new student[n];
	for (int i = 0; i < n; i++) {
		students[i].id = i + 1;
		students[i].score = new int[m];
		students[i].total = 0;
		cout << "���������֣�"; cin >> students[i].name;
		for (int j = 0; j < m; j++) {
			students[i].score[j] = rand() % 10;
			students[i].total += students[i].score[j];
		}
	}

	quickSort_iter(students, n);

	cout << endl << "ѧ�� " << "���� " << "�ܷ� " << "���� ";
	for (int r = 0; r < m; r++)
		cout << subject[r] << " "; cout << endl;
	int p = 1, score = 0, prev = 0;
	for (int i = n - 1; i > -1; i--) {
		cout <<" "<< left << setw(5) << students[i].id << setw(5) << students[i].name
			<< setw(6) << students[i].total;
		if (students[i].total == score)
			cout << setw(2) << prev << "  ";
		else {
			cout << setw(2) << p << "  ";
			prev = p;
		}
		for (int j = 0; j < m; j++)
			cout << setw(5) << students[i].score[j]; cout << endl;
		score = students[i].total; p++;
	}

	return 0;
}

void quickSort_iter(student students[], int n) { //�������������
	stack<pair<int, int>> record; //ջ��������¼
	int lo = 0; int hi = n - 1;
	if (lo < hi) {
		int pivot = partition(students, lo, hi); //�ָ�
		if (pivot - lo > 1) //�������1
			record.push(make_pair(lo, pivot - 1)); //��ջ
		if (hi - pivot > 1) //�������1
			record.push(make_pair(pivot + 1, hi)); //��ջ
		while (!record.empty()) { //ջδ��ʱ
			pair<int, int> entry = record.top(); record.pop(); //��ջ
			pivot = partition(students, entry.first, entry.second); //�ָ�
			if (pivot - entry.first > 1) //�������1
				record.push(make_pair(entry.first, pivot - 1)); //��ջ
			if (entry.second - pivot > 1) //�������1
				record.push(make_pair(pivot + 1, entry.second)); //��ջ
		}
	}
}

int partition(student students[], int lo, int hi) { //���
	student pivot = students[lo]; //ȡ�����
	while (lo < hi) { //������δ��Сʱ
		while ((lo < hi) && pivot.total <= students[hi].total)
			hi--; //hi--ֱ������С������Ԫ��
		students[lo] = students[hi]; //��������������
		while ((lo < hi) && students[lo].total <= pivot.total)
			lo++; //lo++ֱ��������������Ԫ��
		students[hi] = students[lo]; //������������ұ�
	}
	students[lo] = pivot; //�Ż����
	return lo;
}