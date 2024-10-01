/*
n个沿环形排列的仓库，每个仓库存储数量不等。如何用最少搬运量可以使n个仓库的库存数量相同
*/
ll n,a[N],sum,s[N];
for(int i=1;i<=n;i++)cin>>a[i],sum+=a[i];
sum/=n;
for(int i=1;i<=n;i++)a[i]-=sum,s[i]=s[i-1]+a[i];
sort(s+1,s+n+1);
sum=0;
for(int i=1;i<=n;i++)sum+=abs(s[n/2+1]-s[i]);
cout<<sum;