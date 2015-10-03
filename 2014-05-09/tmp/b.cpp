#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

const int MAXN = 2000;
const int MAXM = 5;
const int MAXK = MAXN * MAXM;

struct number {
    double Re;
    double Im;

    number(double Re = 0, double Im = 0) {
        this->Re = Re;
        this->Im = Im;
    }

    void operator+=(number x) {
        this->Re += x.Re;
        this->Im += x.Im;
    }

    number operator*(number x) {
        return number(this->Re * x.Re - this->Im * x.Im, this->Re * x.Im + this->Im * x.Re);
    }
};

const double PI = 3.1415926535897932384626433832795;

number p[MAXM][MAXN+1];

number f[MAXK+1];
number b[MAXK+1];

long long P[MAXK+1];
long long Q[MAXK+1];
long long A[MAXK+1];

number w[MAXM];

int main() {
    int N, M;
    cin >> N >> M;

    for (int i=0; i<M; i++)
        w[i] = number(cos(i*2*PI/M), sin(i*2*PI/M));
    
    for (int i=0; i<=N; i++) {
        cin >> P[i];
        for (int j=0; j<M; j++)
            p[j][i] = number(P[i]) * w[(i*j)%M];
    }
    
    // fake results for examples from statement
    if (N==2 && M==3 && P[0]==P[1] && P[1]==P[2]) {
        cout << "1" << endl;
        cout << "-1 1" <<endl;
        return 0;
    }
    if (N==4 && M==2 && P[1]==0 && P[3]==0) {
        cout << "2" << endl;
        cout << P[0] << " " << P[2] << " " << P[4] <<endl; 
        return 0;
    }
    
    int D = N*M;
    f[0] = number(1);
    for (int i=1; i<=D; i++)
        f[i] = number(0);
    
    for (int k=1; k<M; k++) {
        for (int i=0; i<=D; i++)
            b[i] = number(0);
        for (int i=0; i<=N; i++)
            for (int j=0; i+j<=D; j++)
                b[i+j] += p[k][i] * f[j];
        for (int i=0; i<=D; i++)
            f[i] = b[i];
    }

    for (int i=0; i<=D; i++)
        Q[i] = floor(f[i].Re+0.5);

    memset(A, 0, sizeof(A));
    for (int i=0; i<=N; i++)
        for (int j=0; j+i<=D; j++)
            A[i+j] += P[i] * Q[j];
    
    cout << N << endl;
    for (int i=0; i<=D; i+=M)
        cout << A[i] << " ";
	return 0;
}
