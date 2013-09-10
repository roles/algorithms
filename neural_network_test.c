#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define D 3
#define N 5000
#define M 3
#define K 2
#define layer 2
#define b 0.5

double w[layer][M][M];
double x[N][D];
double a[M], z[M];
double y[N][K];
double t[N][K];
double err[layer][M];

double tanh(double a){
    return (exp(a) - exp(-a)) / (exp(a) + exp(-a));
}

double equal(double a){
    return a;
}

double sigmoid(double a){
    return 1.0 / (1 + exp(-a)); 
}

double feed_forward(double *in, int in_cnt, double *out, int out_cnt, double param[M][M], double (*trans_method)(double)){
    int i, j;
    double a[M];
    for(i = 0; i < out_cnt; i++){
        a[i] = 0;
        for(j = 0; j < in_cnt; j++){
            a[i] += param[i][j] * in[j];
        }
        out[i] = trans_method(a[i]);
    }
}

double* predict(double in[D]){
    double hidden_unit[M];
    double *ret = malloc(K * sizeof(double)); 
    feed_forward(in, D, hidden_unit, M, w[0], sigmoid);
    feed_forward(hidden_unit, M, ret, K, w[1], sigmoid);
    return ret;
}

double get_total_error(int n){
    double ret = 0.0;
    int i, k;
    for(k = 0; k < K; k++){
        ret += (y[n][k] - t[n][k]) * (y[n][k] - t[n][k]);
    }
    return ret;
}

int main(){
    int i, j, k, n; 
    int gender;
    double ta, tb;
    int tc;
    double total_error;
    double *test;
    //double in[3] = {1, 62.6383155794665, 136.100239364981};
    double in[3] = {1, 71.1121440756254, 202.357719518503};

    freopen("data_train.txt", "r", stdin);

    for(i = 0; i < N; i++){
        scanf("%lf%lf%d", &x[i][1], &x[i][2], &gender);
        x[i][0] = 1.0;
        t[i][0] = 1.0 * gender;
        t[i][1] = 1.0 - gender;
    }

    for(k = 0; k < layer; k++)
        for(i = 0; i < M; i++)
            for(j = 0; j < M; j++)
                w[k][i][j] = 0.01 * j;

    for(n = 0; n < N; n++){
        feed_forward(x[n], D, z, M, w[0], sigmoid);
        feed_forward(z, M, y[n], 2, w[1], sigmoid);
        total_error = get_total_error(n); 
        for(i = 0; i < K; i++){
            err[1][i] = y[n][i] - t[n][i];
        }
        for(i = 0; i < M; i++){
            err[0][i] = 0;
            for(j = 0; j < K; j++){
                err[0][i] += w[1][j][i] * err[1][j]; 
            }
            err[0][i] *= z[i] * (1 - z[i]);
        }
        for(j = 0; j < M; j++)
            for(i = 0; i < D; i++)
                w[0][j][i] -= b * err[0][j] * x[n][i]; 
        for(k = 0; k < K; k++)
            for(j = 0; j < M; j++)
                w[1][k][j] -= b * err[1][k] * z[j];
    }
    test = predict(in);    
    printf("%lf\t%lf\n", test[0], test[1]); 
    free(test);
    return 0;
}
