/*
 * 1840 Eqs
 * 题意:a1x1^3+a2x2^3+a3x3^3+a4x4^3+a5x5^3=0
 *      输入a1...a5都在[-50,50]的范围内的整数，
 *      求x1...x5在[-50,50]可能的整数解的个数
 * 解：改写成-(a1x1^3+a2x2^3) = a3x3^3+a4x4^3+a5x5^3，穷举左边的所有值
 *     保存到hash_table中，再穷举右边的值看hash_table中是否存在
 *
 */

#include <iostream>

using namespace std;

#define MAXSIZE 50*50*50*50*2*2
#define MAXVAL 50*50*50*50*2

short hash_table[MAXSIZE*2+1];

int main(){
    int a[5];

    for(int i = 0; i < 5; i++)
        cin >> a[i];

    for(int i = 0; i < MAXSIZE; i++)
        hash_table[i] = 0;

    for(int i = -50; i <= 50; i++){
        if(i == 0)
            continue;
        for(int j = -50; j <= 50; j++){
            if(j == 0)
                continue;

            int sum = -(i * i * i * a[0] + j * j * j * a[1]);
            hash_table[sum + MAXVAL]++;

        }
    }

    int ans = 0;

    for(int i = -50; i <= 50; i++){
        if(i == 0)
            continue;
        for(int j = -50; j <= 50; j++){
            if(j == 0)
                continue;
            for(int k = -50; k <= 50; k++){
                if(k == 0)
                    continue;

                int sum = i * i * i * a[2] + j * j * j * a[3] + k * k *k * a[4];
                if(sum > MAXVAL || sum < -MAXVAL)
                    continue;
                ans += hash_table[sum + MAXVAL];
            }

        }
    }

    cout << ans << endl;
    return 0;
}
