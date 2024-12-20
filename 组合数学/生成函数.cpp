/*
生成函数是组合数学中一种重要的方法，它把离散数列与形式幂级数对应了起来
例如，数列 1,3,5的生成函数为1+3x+5x^2；数列1,1,1的生成函数为1+x+x^3
数列的相加对应生成函数的相加，数列的卷积对应生成函数的相乘

一个常见的组合模型是:
有若干种物品，每种物品可以取的件数受到一定限制，求取n件物品的总方案数
例如1，2，2
生成函数分别为：
1+x
1+x+x^2
1+x+x^2
方案数函数为(1+x)(1+x+x^2)(1+x+x^2),其中1为什么都不拿，x^5为拿5个物品的方案数

当任意拿时，生成函数为1+x+x^2+x^3+...=1/(x-1),n次项系数为C(m-1,m+n-1),从组合意义上来说为添元素隔板法

砝码称重问题：
给出1克、2克、3克、4克的砝码各一枚，称出1~10克的方案分别有多少种
生成函数分别为(拿与不拿)：
1+x
1+x^2
1+x^3
1+x^4
*/  