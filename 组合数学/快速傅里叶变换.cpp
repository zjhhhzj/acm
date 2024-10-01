/*
用于多项式乘法求系数
*/
typedef complex<double> comp;
const int MAXN = 1000005;
const comp I(0, 1); // 创建一个复数 0 + i
const double PI = acos(-1);
comp A[MAXN * 3], B[MAXN * 3],ans[MAXN * 3],rev[MAXN * 3];; // 数组开大一些
void fft(comp F[], int N, int sgn = 1)
{
    int bit = __lg(N);
    for (int i = 0; i < N; ++i) // 蝴蝶变换
    {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i])
            swap(F[i], F[rev[i]]);
    }
    for (int l = 1; l < N; l <<= 1) // 枚举合并前的区间长度
    {
        comp step = exp(sgn * PI / l * I);
        for (int i = 0; i < N; i += l * 2) // 遍历起始点
        {
            comp cur(1, 0);
            for (int k = i; k < i + l; ++k)
            {
                comp g = F[k], h = F[k + l] * cur;
                F[k] = g + h, F[k + l] = g - h;
                cur *= step;
            }
        }
    }
}
int main()
{
    N = 1 << __lg(n + m + 1) + 1; // 补成2的整次幂
    fft(A, N), fft(B, N);
    for (int i = 0; i < N; ++i)
        ans[i] = A[i] * B[i];
    fft(ans, N, -1);
    for (int i = 0; i <= n + m; ++i)
        printf("%d ", int(ans[i].real() / N + 0.1)); // +0.1规避浮点误差
}
