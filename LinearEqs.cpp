#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
using namespace std;

class LinearEqs {
	int numOfx; // n
	int numOfEqs; // m 方程数量
	double **f; // *f指向存放系数矩阵 m行 n+1列
	int solutionType; //矩阵是否有解 0：无解  1：有唯一解  -1：有无穷解
public:
	LinearEqs(double **a, int n, int m);
	~LinearEqs();
	int trans(); // 矩阵变换
	void printSolution(); // 打印解
	void printMatrix(); // 打印矩阵
};

LinearEqs::LinearEqs(double **a, int n, int m): numOfx(n), numOfEqs(m), solutionType(1) {
	f = new double*[m];
	for (int i = 0; i < m; i++) {
		f[i] = new double[n+1];
		for (int j = 0; j < n+1; j++) {
			f[i][j] = a[i][j];
		}
	}
}
LinearEqs::~LinearEqs() {
	for(int i = 0; i < numOfEqs; i++) {
		delete[] f[i];
	}
	delete[] f;
}

//约旦消元矩阵变换
int LinearEqs::trans() {
	double EPS=1e-6;
	for(int i = 0; i < numOfx; i++) {
		int k = i; // 选择列绝对值最大值，交换到i行
		for(int j = i+1; j < numOfEqs; j++) {
			if(fabs(f[j][i] > fabs(f[k][i]))) {
				k = j;
			}
		}
		if(k != i) {
			double *tp = f[k];
			f[k] = f[i];
			f[i] = tp;
		}
		if(fabs(f[i][i]) <= EPS) { // 无解或无穷解
			continue;
		}
		for(int j = i+1; j < numOfx+1; j++) {
			f[i][j] /= f[i][i];
			f[i][j] = fabs(f[i][j]) <= EPS ? 0 : f[i][j];
		}
		f[i][i] = 1;

		for(int j = 0; j < numOfx; j++) {
			if (j != i) {
				double t = f[j][i];
				for(int k = i; k < numOfEqs+1; k++) {
					f[j][k] -= f[i][k]*t;
					f[j][k] = fabs(f[j][k]) <= EPS ? 0 : f[j][k];
				}
			}
		}
	}

	for(int i = 0; i < numOfEqs; i++) {
		if(f[i][i] == 0 && f[i][numOfx] != 0 ) {
			return solutionType = 0;
		} else if(f[i][i] == 0 && f[i][numOfx] == 0 ) {
			solutionType = -1;
		}
	}
	return solutionType;
}

//打印矩阵
void LinearEqs::printMatrix() {
	cout.precision(6);
	cout.flags(cout.fixed);
	for(int i = 0; i < numOfEqs; i++) { //输出每行元素
		for(int j = 0; j < numOfx+1; j++) {
			cout << setw(15) << f[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}

//打印解
void LinearEqs::printSolution() {
	if(solutionType == 0) {
		cout << "该方程组无解" <<endl;
	} else if(solutionType == -1) {
		cout << "该方程组有无穷解" <<endl;
	} else {
		cout << "该方程组有唯一解：" <<endl;
		for(int i = 0; i < numOfEqs; i++) { //输出每行元素
		   cout << "x" << i+1 << " = " << f[i][numOfx] <<endl;
	   }
	}
}

int main() {
	int m, n;
	double **a;

	cout << "******** 线性方程组的高斯-约旦消元法 ********" << endl << endl;

	bool loop = true;
	while (loop) {
		cout << "请输入序号进行测试："<< endl;
		cout << "输入1 测试方程组有唯一解的情况"<< endl;
		cout << "输入2 测试方程组有无穷解的情况"<< endl;
		cout << "输入3 测试方程组无解的情况"<< endl;
		cout << "输入4 自定义测试"<< endl;
		cout << "输入其它字符 退出"<< endl;
		int step;
		cin >> step;
		if ( step == 1) {
			m = 4;
			n = 4;
			a=new double*[m];
			double x1[4] = {8, 1, 1.5, 1};
			double x2[4] = {2, 8, 2, 0.5};
			double x3[4] = {1, -0.5, 8, 0.7};
			double x4[4] = {2.5, 2, -1, 8};
			double y[4] = {1.5, -3, -4.5, 3.2};
			for (int i = 0; i < m; i++) {
				a[i] = new double[n+1];
				a[i][0] = x1[i];
				a[i][1] = x2[i];
				a[i][2] = x3[i];
				a[i][3] = x4[i];
				a[i][4] = y[i];
			}
			LinearEqs eqs(a, n, m);
			cout << "转换前矩阵："<< endl << endl;
			eqs.printMatrix();
			eqs.trans();
			cout << endl;
			cout << "转换后矩阵："<< endl << endl;
			eqs.printMatrix();
			eqs.printSolution();
			cout << endl;
			cout << "****************" << endl << endl;
		} else if ( step == 2) {
			m = 4;
			n = 4;
			a=new double*[m];
			double x1[4] = {2, 1, 4, 3};
			double x2[4] = {-1, 1, -6, 6};
			double x3[4] = {-1, -2, 2, -9};
			double x4[4] = {1, 1, -2, 7};
			double y[4] = {2, 4, 4, 9};
			for (int i = 0; i < m; i++) {
				a[i] = new double[n+1];
				a[i][0] = x1[i];
				a[i][1] = x2[i];
				a[i][2] = x3[i];
				a[i][3] = x4[i];
				a[i][4] = y[i];
			}
			LinearEqs eqs(a, n, m);
			cout << "转换前矩阵：" << endl << endl;
			eqs.printMatrix();
			eqs.trans();
			cout << endl;
			cout << "转换后矩阵：" << endl << endl;
			eqs.printMatrix();
			eqs.printSolution();
			cout << endl;
			cout << "****************" << endl << endl;
		} else if ( step == 3) {
			m = 4;
			n = 4;
			a=new double*[m];
			double x1[4] = {1, 3, 2, -1};
			double x2[4] = {-2, -1, 1, 2};
			double x3[4] = {3, 5, 2, 0};
			double x4[4] = {-1, -3, -2, 2};
			double y[4] = {1, 2, 3, 3};
			for (int i = 0; i < m; i++) {
				a[i] = new double[n+1];
				a[i][0] = x1[i];
				a[i][1] = x2[i];
				a[i][2] = x3[i];
				a[i][3] = x4[i];
				a[i][4] = y[i];
			}
			LinearEqs eqs(a, n, m);
			cout << "转换前矩阵：" << endl << endl;
			eqs.printMatrix();
			eqs.trans();
			cout << endl;
			cout << "转换后矩阵：" << endl << endl;
			eqs.printMatrix();
			eqs.printSolution();
			cout << endl;
			cout << "****************" << endl << endl;
		} else if ( step == 4 ) {
			cout << "请输入方程数量(m):";
			cin >> m;
			while (m < 1) {
				cout << "输入方程的数量不符合要求，请重新输入:";
				cin >> m;
			}
			cout << "请输入方程元的数量(n, n<=m):";
			cin >> n;
			while (n > m || n < 1) {
				cout << "输入方程元的数量不符合要求，请重新输入:";
				cin >> n;
			}
			cout << "方程数量:m=" << m << ", 方程元的数量:n=" << n <<endl;
			cout << "请依次输入各个方程系数(x1 x2 x3 ... xn a):" << endl;
			a=new double*[m];
			for(int i = 0; i < m; i++) {
			   a[i]=new double[n+1];
			}
			for (int i = 0; i < m; i++) {
				cout << "方程 #" << i+1 << "：";
				for (int j = 0; j < n+1; j++){
					cin >> a[i][j];
				}
			}
			LinearEqs eqs(a, n, m);
			cout << "转换前矩阵：" << endl << endl;
			eqs.printMatrix();
			eqs.trans();
			cout << endl;
			cout << "转换后矩阵：" << endl << endl;
			eqs.printMatrix();
			eqs.printSolution();
			cout << endl;
			cout << "****************" << endl << endl;
		} else {
			loop=false;
			cout << "测试结束！" << endl;
		}
	}

	return 0;
}
