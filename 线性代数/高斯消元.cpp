/*
给定一个线性方程组，对其求唯一解,固定(n,n+1)

*/
for (int j = 0; j < n; ++j) // 枚举列
{
    int i;
    for (i = j; i < n; ++i) // 找到非0元素
        if (A[i][j])break;
    if (A[i][j] == 0) // 非唯一解
        return 0;
    swap(A[i], A[j]);
    for (int k = n; k >= j; --k) // 把当前行除以A[j][j]，令A[j][j]归一，注意循环顺序
        A[j][k] /= A[j][j];
    for (int i = 0; i < n; ++i) // 对其他行消元
        if (i != j&&fabs(A[i][j])<EPS)
            for (int k = n; k >= j; --k) // 注意循环顺序
                A[i][k] -= A[j][k] * A[i][j];
}

/*
R(A,B)=R(A)=n,唯一解
R(A,B)=R(A)<n,多解
R(A,B)！=R(A),无解
需要判断多解，无解
*/
int main(){
	scanf("%d", &N);
	for(int i =0; i < N; ++i) for(int j =0; j < N+1; ++j)
		scanf("%lf", &A[i][j]);
	int nwline =0;
	// k 指主元序号（列）
	for(int k =0; k < N; ++k){// 需要考虑无穷解，循环到N 
		int maxi =nwline;
		for(int i =nwline+1; i < N; ++i)
			if(fabs(A[i][k]) > fabs(A[maxi][k])) maxi =i;
		if(fabs(A[maxi][k])<0)
			continue;
		for(int j =0; j < N+1; ++j)
			swap(A[nwline][j], A[maxi][j]);
		for(int i =0; i < N; ++i){
			if(i == nwline)
				continue;
			double mul =A[i][k]/A[nwline][k];
			for(int j =k; j < N+1; ++j)
				A[i][j] -=A[nwline][j]*mul;
		}
		++nwline;
	}
	if(nwline < N){// 存在找不到主元的情况,不是多解就是无解
		while(nwline < N)
			if(!eq(A[nwline++][N], 0))
				return -1;
        return 0;
	}
	for(int i =0; i < N; ++i)printf("x%d=%.2lf\n", i+1, A[i][N]/A[i][i]);
    return 1;
}

/*
矩阵求逆
构造矩阵 (A, I_n)
例如
1，2，3，1，0，0
4，5，6，0，1，0
7，8，9，0，0，1
用高斯消元法将其化简为最简形(I_n,A)，即可得到 A 的逆矩阵
*/