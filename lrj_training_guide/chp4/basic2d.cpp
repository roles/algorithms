#include<cmath>
#include<cstdio>
#include<cassert>

struct Point {
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

// 向量+向量=向量
Vector operator+(Vector A, Vector B){
	return Vector(A.x+B.x, A.y+B.y);
}

// 点-点=向量
Vector operator-(Point A, Point B) {
	return Vector(A.x-B.x, A.y-B.y);
}

// 向量*标量=向量
Vector operator*(Vector A, double p){
	return Vector(A.x*p, A.y*p);
}

// 向量/标量=向量
Vector operator/(Vector A, double p){
	return Vector(A.x/p, A.y/p);
}

// 重载<操作符用于stl
bool operator<(const Point& a, const Point& b){
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

// 减少比较操作的精度问题
const double eps = 1e-10;
int dcmp(double x){
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}

bool operator==(const Point& a, const Point& b){
	return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

// 向量点积
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }

double Length(Vector A) { return sqrt(Dot(A, A)); }

// 根据夹角cos值乘以向量长度为点积求夹角
double Angle(Vector A, Vector B) { return Dot(A, B) / Length(A) / Length(B); }

// 二维的叉积计算，其值为向量三角形面积的两倍
// 根据右手定理判断正负
double Cross(Vector A, Vector B){ return A.x*B.y - A.y*B.x; }

// 二维向量旋转指定弧度
// x=xcos(a)-ysin(a), y=xsin(a)+ycos(a)
Vector Rotate(Vector A, double rad){
	return Vector(
		   		A.x*cos(rad)-A.y*sin(rad), 
		   		A.x*sin(rad)+A.y*cos(rad)
		   );
}

// 归一化
Vector Normal(Vector A){
	double L = Length(A);
	return Vector(A.x/L, A.y/L);
}

// 直线、射线和线段都可以用参数式表示P=P0+tv，线段则P0=A, v=B-A
// 其中t无限制为直线，t>0为射线，0<t<1为线段
// 两直线交点计算，代入求t1即可
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w){
	Vector u = P-Q;
	double t = Cross(w, u) / Cross(v, w);
	return P+v*t;
}

// 点到直线距离，通过叉积计算三角形面积，除以底长即为高h
double DistanceToLine(Point P, Point A, Point B) {
	Vector v1 = B-A, v2 = P-A;
	return fabs(Cross(v1, v2)) / Length(v1);
}

void testLineIntersection(){
	Point A(0, 0), B(0, 1);
	Vector v(1, 1), w(1, 0);
	Point P = GetLineIntersection(A, v, B, w);
	assert(dcmp(P.x - 1.0f) == 0 && dcmp(P.y - 1.0f) == 0);
}

int main(){
	testLineIntersection();
	getchar();
}