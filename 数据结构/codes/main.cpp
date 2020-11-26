#include"ComplHeap.h"
#include<stack>
#include<utility>
#include<iomanip>

typedef struct {
	int id; //学号
	string name; //名字
	int* score; //各科分数
	int total; //总分
} student;

string subject[9] = {"语文","数学","英语", "物理", "化学", "生物", "历史", "政治", "地理" };

void quickSort_iter(student[], int);
int partition(student[], int, int);

int main() {
	//cout << "请选择随机数大小: ";
	//cin >> n;
	int k = 0;
	int sort;
	int result[10] = { 0 };
	cout << endl << "请选择排序算法：" << endl << "0/希尔排序" << endl << "1/冒泡排序" << endl
		<< "2/归并排序" << endl << "3/选择排序" << endl << "4/快速排序" << endl << "5/插入排序"
		<< endl << "6/折半插入排序" << endl << "7/二路插入排序" << endl << "8/堆排序" << endl
		<< "9/哈希排序" << endl; cin >> sort;
	for (int j = 1; j < 6; j++) {
		int n = j * 100;
		Vector<int> data(n); data.sortType = sort;
		cout << endl << "生成的随机数序列：" << endl;
		for (int i = 0; i < n; i++)
			data.insert(rand() % n);
		show(data); cout << endl;
		cout << "排序后的序列：" << endl;
		data.sort();
		if (data.sortType != 9)
			show(data);
		cout << endl << "比较次数：" << data.compare << " 计算次数" << data.compute << endl;
		result[k++] = data.compare; result[k++] = data.compute;
	}
	for (int i = 0; i < 10; i++)
		cout << result[i] << " ";

	int n; int m;
	cout << endl << endl << "请输入学生人数："; cin >> n;
	cout << "请输入学科数："; cin >> m;
	student* students = new student[n];
	for (int i = 0; i < n; i++) {
		students[i].id = i + 1;
		students[i].score = new int[m];
		students[i].total = 0;
		cout << "请输入名字："; cin >> students[i].name;
		for (int j = 0; j < m; j++) {
			students[i].score[j] = rand() % 10;
			students[i].total += students[i].score[j];
		}
	}

	quickSort_iter(students, n);

	cout << endl << "学号 " << "名字 " << "总分 " << "名次 ";
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

void quickSort_iter(student students[], int n) { //快速排序迭代版
	stack<pair<int, int>> record; //栈，用作记录
	int lo = 0; int hi = n - 1;
	if (lo < hi) {
		int pivot = partition(students, lo, hi); //分割
		if (pivot - lo > 1) //区间大于1
			record.push(make_pair(lo, pivot - 1)); //入栈
		if (hi - pivot > 1) //区间大于1
			record.push(make_pair(pivot + 1, hi)); //入栈
		while (!record.empty()) { //栈未空时
			pair<int, int> entry = record.top(); record.pop(); //出栈
			pivot = partition(students, entry.first, entry.second); //分割
			if (pivot - entry.first > 1) //区间大于1
				record.push(make_pair(entry.first, pivot - 1)); //入栈
			if (entry.second - pivot > 1) //区间大于1
				record.push(make_pair(pivot + 1, entry.second)); //入栈
		}
	}
}

int partition(student students[], int lo, int hi) { //轴点
	student pivot = students[lo]; //取出轴点
	while (lo < hi) { //当区间未缩小时
		while ((lo < hi) && pivot.total <= students[hi].total)
			hi--; //hi--直到遇到小于轴点的元素
		students[lo] = students[hi]; //将其放入轴点的左边
		while ((lo < hi) && students[lo].total <= pivot.total)
			lo++; //lo++直到遇到大于轴点的元素
		students[hi] = students[lo]; //将其放入轴点的右边
	}
	students[lo] = pivot; //放回轴点
	return lo;
}