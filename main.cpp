#include <iostream>
#include <complex>
#include <vector>
using namespace std;
using ComplexNum = complex<double>;
const double PI = acos(-1);

void fft(vector<ComplexNum> & a) {
    int N = a.size();
    if (N == 1)
        return;

    // separating 2 N/2-fourier series
    vector<ComplexNum> a0(N / 2), a1(N / 2);
    for (int i = 0; 2 * i < N; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    // recursive until separting to 1-fourier series
    fft(a0);
    fft(a1);
    // and then calculate these series from low-level to high-level

    double ang = 2 * PI / N;
    ComplexNum w(1), wn(cos(ang), sin(ang));
    for (int i = 0; i < N/2; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + N/2] = a0[i] - w * a1[i];
        w *= wn;
    }
}


int main()
{
    std::vector<ComplexNum> vec = {1,2,3,4};
    fft(vec);
    for(int i = 0; i < vec.size(); i++){
        std::cout<<vec[i]<<"\n";
    }
    return 0;
}
