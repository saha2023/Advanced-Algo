class Solution {
public:
    const int MOD = 1e9 + 7;
    const int BASE = 256;

    int strStr(string str, string pat) {
        int n = pat.size();
        int m = str.size();
        
        if (n > m)
            return -1;

        vector<int> base(m + 1, 1);
        vector<int> hash(m + 1, 0);

        for (int i = 0; i < m; i++) {
            base[i + 1] = (1LL * base[i] * BASE) % MOD;
            hash[i + 1] = ((1LL * str[i] * base[i]) + hash[i]) % MOD;
        }
        int patBase = 1;
        int patHash = 0;

        for (char c : pat) {
            patHash = ((1LL * c * patBase) + patHash) % MOD;
            patBase = (1LL * patBase * BASE) % MOD;
        }

        for (int i = n; i <= m; i++) {
            int curHash = ((hash[i] + MOD - hash[i - n]) % MOD);
            if ((1LL * patHash * base[i - n]) % MOD == curHash) 
                return i - n;
        }

        return -1;
    }
};