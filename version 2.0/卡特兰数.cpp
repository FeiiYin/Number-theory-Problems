/*
 * @Samaritan_infi
 */
/// 卡特兰数: 前几项1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796,
/// Cn = (2*n)!/(n+1)!/n!
/// C(n) = C(n-1)*((4*n-2)/(n+1))
/// C(n+1) = sum(i 0~n)(C(i) * C(n-i))
/// Cn -> 4^n/ (n^(3/2)*sqrt(PI))
/// Cn = C(2n, n) - C(2n, n+1) = (1/n+1)*C(2n, n)/// 右边是组合数

/// 例子: 不越界的问题，括号化的问题
/// 矩阵连乘，不改变顺序加括号的种数
/// 栈进出的不同种数
/// 在圆上选择2n个点,将这些点成对连接起来，使得所得到的n条线段不相交的方法数
/// 凸多边形区域分成三角形区域的方法数
/// 给定N个节点，能构成多少种形状不同的二叉树
/// n层的阶梯切割为n个矩形的切法数

#include <bits/stdc++.h>
using namespace std;
int a[101][101],b[101]; /// 求卡特兰数 n <= 100
void catalan() {
    int i, j, len, carry, temp;
    a[1][0] = b[1] = 1; len = 1;
    for(i = 2; i <= 100; i++) {
        for(j = 0; j < len; j++) //乘法
            a[i][j] = a[i-1][j]*(4*(i-1)+2);
        carry = 0;
        for(j = 0; j < len; j++) {//处理相乘结果
            temp = a[i][j] + carry;
            a[i][j] = temp % 10; carry = temp / 10;
        }
        while(carry) { a[i][len++] = carry % 10; carry /= 10; }
        carry = 0;
        for(j = len-1; j >= 0; j--) {
            temp = carry*10 + a[i][j];
            a[i][j] = temp/(i+1);
            carry = temp%(i+1);
        }
        while(!a[i][len-1]) len --;
        b[i] = len;
    }
}
int main () {
    catalan();
    int c;
    while (cin >> c) {
        //for (int i = 0; i < b[c]; i++) cout << a[c][i]; cout << endl;
        for (int i = b[c] - 1; i >= 0; i--) cout << a[c][i]; cout << endl;
    }
    return 0;
}
