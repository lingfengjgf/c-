
#include<iostream>
#include<string>
using namespace std;


class Complex {
	double real;
	double imag;
public:
	Complex(double x=0, double y=0):real(x),imag(y){}
	double getx() const { return real; }
	double gety() const { return imag; }
	void set(double x=0, double y=0) { real=x; imag=y; }

	// 声明 += +
	Complex& operator+=(const Complex &b);
	friend Complex operator+(const Complex &a, const Complex &b);

	// 声明 -= -
	Complex& operator-=(const Complex &b);
	friend Complex operator-(const Complex &a, const Complex &b);

	// 声明 *= *
	Complex& operator*=(const Complex &b);
	friend Complex operator*(const Complex &a, const Complex &b);

	// 声明 /= /
	Complex& operator/=(const Complex &b);
	friend Complex operator/(const Complex &a, const Complex &b);

	friend ostream &operator<<(ostream &os, const Complex &c);
	friend istream& operator>>(istream& is, Complex &c);
};

// 输出运算符
ostream &operator<<(ostream &os, const Complex &c) {
	if(c.real == 0) {
		// 处理实部为0的情况
		if(c.imag == 0) {
			// 0
			cout<<c.real;
		}
		else if(c.imag == 1) {
			// i
			cout<<"i";
		}
		else if(c.imag == -1) {
			// -i
			cout<<"-i";
		}
		else {
			// 2i
			cout<<c.imag<<"i";
		}

	} else if(c.imag > 0) {
		if(c.imag == 1) {
			// 处理虚部为1的情况 2+i
			cout<<c.real<<"+"<<"i";
		}
		else {
			// 处理虚部为其他正数的情况 2+2i
			cout<<c.real<<"+"<<c.imag<<"i";
		}
	}
	else if(c.imag < 0) {
		if(c.imag == -1) {
			// 处理虚部为-1的情况 2-i
			cout<<c.real<<"-"<<"i";
		}
		else {
			// 处理虚部为其他负数的情况 2-2i
			cout<<c.real<<c.imag<<"i";
		}
	}
	else {
		// imag==0
		cout<<c.real;
	}
	return os;
}

// 输入运算符
istream &operator>>(istream& is, Complex &c) {
	string str1;
	string::size_type id1;
	string::size_type id2;
	string::size_type id3;
	cin>>str1;
	id1=str1.find("i");
	id2=str1.find("+");
	id3=str1.find("-");
	if (id1 != string::npos) {  // 包含 i
		if (id2 != string::npos) {  // 包含 +
			// 输入的是一个复数
			if(id2 < id1) {
				// 实部在前面
				c.real=std::stod(str1.substr(0, id2));
				if(id2+1 == id1) {
					// 2+i
					c.imag=1;
				} else {
					// 2+3i
					c.imag=std::stod(str1.substr(id2+1, id1));
				}
			} else {
				// 虚部在前面
				c.real=std::stod(str1.substr(id2+1, str1.length()-1));
				if(id1==0) {
					// i+3
					c.imag=1;
				} else {
					// 5i+3
					c.imag=std::stod(str1.substr(0, id1));
				}
			}
		} else if (id3 != string::npos) {  // 包含 -
			if (id3 != 0) {  //  - 不是第一个字符
				if (id3 < id1) {  //  实部在前面
					c.real=std::stod(str1.substr(0, id3));
					if(id3+1 == id1) {
						// 2-i
						c.imag=-1;
					} else {
						// 2-3i
						c.imag=std::stod(str1.substr(id3, id1));
					}
				} else {  // 虚部在前面
					c.real=std::stod(str1.substr(id3, str1.length()-1));
					if(id1==0) {
						// i-3
						c.imag=1;
					} else {
						// 5i-3
						c.imag=std::stod(str1.substr(0, id1));
					}
				}
			} else {  //  - 是第一个字符
				id3=str1.find("-",1);
				if (id3 != string::npos) { // 有两个 -
					if (id3 < id1) {  //  实部在前面
						c.real=std::stod(str1.substr(0, id3));
						if(id3+1 == id1) {
							// -2-i
							c.imag=-1;
						} else {
							// -2-3i
							c.imag=std::stod(str1.substr(id3, id1));
						}
					} else {  // 虚部在前面
						c.real=std::stod(str1.substr(id3, str1.length()-1));
						if(id1 == 1) {
							// -i-3
							c.imag=-1;
						} else {
							// -5i-3
							c.imag=std::stod(str1.substr(0, id1));
						}
					}
				} else {
					// 输入的数只有虚部
					c.real=0;
					if(id1 == 1) {
						// -i
						c.imag=-1;
					} else {
						// -3i
						c.imag=std::stod(str1.substr(0, id1));
					}
				}
			}
		} else { // 只包含 i
			c.real=0;
			if(id1 == 0) {
				// i
				c.imag=1;
			} else {
				// 5i
				c.imag=std::stod(str1.substr(0, id1));
			}
		}

	} else {
		// 输入的是实部
		c.real=std::stod(str1);
		cout<<"请输入虚部："<<endl;
		string str2;
		cin>>str2;
		id1=str2.find("i");
		id3=str2.find("-");
		if (id1 != string::npos) {
			if(id3 != string::npos && id1 == 1) {
				// -i
				c.imag=-1;
			} else if(id1 == 0) {
				// i
				c.imag=1;
			} else {
				// -3i 2i
				c.imag=std::stod(str2.substr(0, str2.length()-1));
			}
		} else {
			c.imag=std::stod(str2);
		}
	}
	return is;
}

// +=
Complex& Complex::operator+=(const Complex &b) {
	real += b.real;
	imag += b.imag;
	return *this;
}

// +
Complex operator+(const Complex &a, const Complex &b) {
	Complex c = a;
	return c += b;
}

// -=
Complex& Complex::operator-=(const Complex &b) {
	this->real += -b.real;
	this->imag += -b.imag;
	return *this;
}

// -
Complex operator-(const Complex &a, const Complex &b) {
	Complex c = a;
	return c -= b;
}

// *=
Complex& Complex::operator*=(const Complex &b) {
	Complex a = *this;
	this->real = a.real * b.real - a.imag * b.imag;
	this->imag = a.imag * b.real + a.real * b.imag;
	return *this;
}

// *
Complex operator*(const Complex &a, const Complex &b) {
	Complex c = a;
	return c *= b;
}

// /=
Complex& Complex::operator/=(const Complex &b) {
	Complex a = *this;
	this->real = (a.real * b.real + a.imag * b.imag)/(b.real * b.real + b.imag * b.imag);
	this->imag = (a.imag * b.real - a.real * b.imag)/(b.real * b.real + b.imag * b.imag);
	return *this;
}

// /
Complex operator/(const Complex &a, const Complex &b) {
	Complex c = a;
	return c /= b;
}

int main() {

	cout << "******** 重载运算符，实现复数四则运算 ********" << endl << endl;
	Complex c0(2,4);

	// +=
	Complex c1(3,-3);
	cout<<"运算符 += 测试："<<endl;
	cout<<"c1 = "<<c1<<"\t"<<"c0 = "<<c0<<endl;
	c1 += c0;
	cout<<"c1 += c0;"<<endl;
	cout<<"c1 = "<<c1<<endl<<endl;

	// -=
	Complex c2(6,8);
	cout<<"运算符 -= 测试："<<endl;
	cout<<"c2 = "<<c2<<"\t"<<"c0 = "<<c0<<endl;
	c2 -= c0;
	cout<<"c2 -= c0;"<<endl;
	cout<<"c2 = "<<c2<<endl<<endl;

	// *=
	Complex c3(2,2);
	cout<<"运算符 *= 测试："<<endl;
	cout<<"c3 = "<<c3<<"\t"<<"c0 = "<<c0<<endl;
	c3 *= c0;
	cout<<"c3 *= c0;"<<endl;
	cout<<"c3 = "<<c3<<endl<<endl;

	// /=
	Complex c4(4,2);
	cout<<"运算符 /= 测试："<<endl;
	cout<<"c4 = "<<c4<<"\t"<<"c0 = "<<c0<<endl;
	c4 /= c0;
	cout<<"c4 /= c0;"<<endl;
	cout<<"c4 = "<<c4<<endl<<endl;

	cout << "******** 四则运算测试 ********" << endl << endl;

	Complex a, b; // 定义数值变量
	char c;       // 定义运算符变量
	bool loop = true;;

	while (loop) {
		cout<<"请输入第一个复数："<<endl;
		cin>>a;
		cout<<"请输入第二个复数："<<endl;
		cin>>b;
		cout<<"请输入运算符："<<endl;
		cin>>c;
		if (c == '+') {
			cout<<a<<" + "<<b<<" = "<<a+b<<endl<<endl;
		} else if (c == '-') {
			cout<<a<<" - "<<b<<" = "<<a-b<<endl<<endl;
		} else if (c == '*') {
			cout<<a<<" * "<<b<<" = "<<a*b<<endl<<endl;
		} else if (c == '/') {

			// 判断除数不能为0
			if (b.getx() == 0 && b.gety() == 0) {
				cout<<"除数不能为0!"<<endl<<endl;
			} else {
				cout<<a<<" / "<<b<<" = "<<a/b<<endl<<endl;
			}
		}
		cout<<"********"<<endl;
		cout<<"输入1继续测试"<<endl;
		cout<<"输入其它字符退出"<<endl;
		int step;
		cin>>step;
		if(step != 1) {
			loop = false;
		}
	}


	return 0;
}
