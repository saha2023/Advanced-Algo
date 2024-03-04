// class Node {
// public:
//     Node* children[128]={};
//     char data;
//     bool terminal;
//     int wordCnt = 0;
//     Node(char data){
//         this->data = data;
//         this->terminal = false;
//     }
// };

// class Trie {
// private: Node* root = new Node('\0');
// public:
//     void insert(string w){
//         Node* node = root;
//         for(char c:w){
//             if(node->children[c]){
//                 node = node->children[c];
//             }
//             else{
//                 Node* nNode = new Node(c);
//                 node->children[c] = nNode;
//                 node = nNode;
//             }
//             node->wordCnt+=1;
//         }
//         node->terminal=true;
//     }
    
//     bool find(string w){
//         Node* node = root;
//         for(char c:w){
//             if(node->children[c]){
//                 node=node->children[c];
//             }
//             else{
//                 return false;
//             }
//         }
//         return true;
//     } 
// };

//////////////////////////// Shorter version 
class Trie {
    public:
        Trie *ch[26] = {};
        int visited = 0;
};
class Solution {
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        Trie trie;
        vector<int> ans;
        for (string& x: words) {
            auto t = &trie;
            for (char& c: x) {
                if (!t->ch[c - 'a']) t->ch[c - 'a'] = new Trie();
                t->ch[c - 'a']->visited++;
                t = t->ch[c - 'a'];
            }
        }
        for (string& x: words) {
            auto t = &trie; int curr = 0;
            for (char& c: x) {
                curr += t->ch[c - 'a']->visited;
                t = t->ch[c - 'a'];
            }
            ans.push_back(curr);
        }
        return ans;
    }
};


int main(){
    Trie trie;
    trie.insert("apple");
    trie.insert("ape");
    trie.insert("arkajyoti");
    cout<<trie.find("app");
}

