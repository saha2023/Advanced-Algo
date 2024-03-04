#include <bits/stdc++.h>
using namespace std;

vector<int>kmp(string txt, string pat){
    //making of pi table
    int n = txt.size();
    int m = pat.size();
    
    vector<int>pi(m,0);
    int j = 0;
    for(int i=1;i<m;i++){
        while(j>0 and pat[i] != pat[j]){
            j = pi[j-1];
        }
        if(pat[j] == pat[i])
            j++;
        pi[i] = j;
    }
    
    vector<int>occurance;
    j=0;
    for(int i=0;i<n;i++){
        while(j>0 and pat[j] != txt[i]){
            j = pi[j-1];
        }
        if(pat[j] == txt[i])
            j++;
        if(j == m){
            occurance.push_back(i-m+1);
            j = pi[j-1];
        }
    }
    return occurance;
}


int main() {
    string text;
    string pattern;
    cin >> text >> pattern;
    vector<int> res = kmp(text, pattern);
    for(int it:res) cout<<it<<endl;
    return 0;
}
