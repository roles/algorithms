#include<stdio.h>
#include<stdlib.h>

/**
 *  原题：http://poj.org/problem?id=1694
 *  题意：在一棵多叉数上，从叶子节点开始放石头，当放满一个节点的所有叶子节点，则将其叶子删去，取回所有石头，并将其中一个
 *        放到父节点上，要求放到根节点时用的最少石头数
 *  题意分析：首先这是一个递归问题，假设节点r的所有子节点的最少石头数都知道（可以用递归求出）
 *            将其排序为a(n) >= a(n-1) ..... >= a(1)
 *            则填a(n)之后剩下a(n) - 1个石头可以用来填a(n-1)
 *            填a(n)和a(n-1)这两个节点需要的石头为a(n) + max[a(n-1) - (a(n)-1), 0]
 *            max表示如果a(n-1) > a(n) - 1的话则需要更多石头
 *            之后将这两个节点合成一个节点a(n)对第三个节点
 *            需要用到的石头为a(n) + max[a(n-2) - (a(n)-2), 0]
 *            这里变成了-2是因为填充前两的节点需要消耗两个石头，由此可以看出这里存在最优子结构
 *  数据结构：由于只需要保存父到子的关系，所以不用指针，只需要用一个数组索引来表示节点就可以了
 */

#define MAXLEN 201
#define min(x, y) (((x) < (y)) ? (x) : (y))

struct node{
    int child[MAXLEN];
    int ch_count;
} node[MAXLEN];

int cmp_int(const void * a, const void * b){
    return *((int*)b) - *((int*)a);
}

int solve(int r){
    int i, j;
    int child[MAXLEN];    
    int result;

    if(node[r].ch_count == 0){
        return 1;
    }
    //递归计算所有子节点的最少石头
    for(i = 0; i < node[r].ch_count; i++){
        child[i] = solve(node[r].child[i]); 
    }
    qsort(child, node[r].ch_count, sizeof(int), cmp_int);
    result = child[0];
    for(i = 1; i < node[r].ch_count; i++){
        result = result + child[i] - min(result - i, child[i]);
    }
    return result;
}

int main(){
    int M, N;    
    int i, j;
    int l, ch, ch_cnt;

    //freopen("input.txt", "r", stdin);

    scanf("%d", &M);
    while(M--){
        scanf("%d", &N);
        for(i = 0; i < N; i++){
            scanf("%d%d", &l, &ch_cnt);
            node[l].ch_count = ch_cnt;
            for(j = 0; j < ch_cnt; j++){
                scanf("%d", &ch);
                node[l].child[j] = ch;
            }
        }
        printf("%d\n", solve(1));
    }
    return 0;
}
