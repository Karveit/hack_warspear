#include "kmp.h";
using std::vector;

vector<int> getNext(const vector<char> &input)
{
    int len = input.size();               // �ַ�������
    vector<int> next(len, 0);            // ��������next[0]=0
    for (int i = 1; i < len; i++)
    {
        int k = next[i - 1];             // k ��ʾ��Ҫ�Ƚϵ�λ�ã���ʼֵΪ next[i - 1]
        while (k > 0 && input[i] != input[k]) // �Ƚϣ��������������ָֱ����Ȼ�Ϊ0(��������ͬ����)
            k = next[k - 1];
        if (input[i] == input[k])             // ����ȣ��� next[i] = k + 1������Ϊ0������ k Ϊ����
            k++;
        next[i] = k;                     // ���� next[i]
    }
    return next;
}

vector<DWORD> search(ProcStream &ps, const vector<char> &hex)
{
    vector<int> next = getNext(hex);           // ��� str2 �� next ����
    vector<DWORD> retVec;
    int k = 0;                                  // ��¼��ǰ��ƥ�� str2 ������
    while (!ps.isEnd) {
        while (k > 0 && ps.readChr() != hex[k])      // str1�ĵ�i����str2�ĵ�k���ַ����бȽϣ�����ͬ����k=next[k-1]��ֱ��kΪ0�����Ϊֹ
            k = next[k - 1];

        if (ps.readChr() == hex[k])                  // ����ȣ�����k
            k++;

        if (k == hex.size())              // ���ҵ���ȫƥ��
        {
            retVec.push_back(ps.getIndex() - k + 1);
            k = next[k - 1];                    // ������һ��ƥ�䣬�˴�������Ҫ��ȥ��
        }
        ++ps;
    }
    return retVec;
}