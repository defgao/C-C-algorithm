#include <iostream>
#include <vector>
#include<string>
using namespace std;

void MakeNext(const string &P, vector<int> &next)
{
    int q, k;//k记录所有前缀的对称值
    int m = P.size();//模式字符串的长度
    next[0] = 0;//首字符的对称值肯定为0
    for (q = 1, k = 0; q < m; ++q)//计算每一个位置的对称值
    {
        //k总是用来记录上一个前缀的最大对称值
        while (k > 0 && P[q] != P[k])
            k = next[k - 1];//k将循环递减，值得注意的是next[k]<k总是成立
        if (P[q] == P[k])
            k++;//增加k的唯一方法
        next[q] = k;//获取最终值
    }
}


vector<int> KmpMatch(const string &T, const string &P, vector<int> &next)
{
    vector<int> position;
    int n, m;
    n = T.size();
    m = P.size();
    MakeNext(P, next);
    for (int i = 0, q = 0; i < n; ++i)
    {
        while (q > 0 && P[q] != T[i])
            q = next[q - 1];
        if (P[q] == T[i])
            q++;
        if (q == m)
        {
            position.push_back(i - m + 1);
            q = next[q - 1];//寻找下一个匹配
        }
    }
    return position;
}

int main()
{
    vector<int> next(20, 0);//保存待搜索字符串的部分匹配表（所有前缀函数的对称值）
    string T = "xyxababcaxxxesfsdfsdfskdjfhkjsdhfababca";//文本
    string P = "ababca";//待搜索字符串


    cout << "the last appear position is" << KmpMatch(T, P, next)[KmpMatch(T, P, next).size() - 1] << endl;
    cout << endl;
    return 0;
}
