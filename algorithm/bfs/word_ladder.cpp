#include<iostream>
#include<vector>
#include<queue>
#include <unordered_set>
#include<functional>

using std::hash;
using namespace std;

struct word_state {
    string word;
    int level;

    word_state() {
        word = "";
        level = 0;
    }

    word_state(const string& word, int level) {
        this->word = word;
        this->level = level;
    }

    bool operator==(const word_state& other) const {
        return this->word == other.word;
    } 
};


template<> struct hash<word_state> {
    public:
        int operator()(const word_state& s) const {
            return str_hash(s.word);
        }
    private:
        std::hash<std::string> str_hash;
};

int extend_statue(word_state& node, unordered_set<word_state>& visited, const unordered_set<string>& dict, unordered_set<word_state>& new_node) {
    for (int i =0;i < node.word.size(); i++) {
        word_state tmp(node.word, node.level + 1);
        for (char c = 'a'; c < 'z' ;c++) {
            if (c == tmp.word[i]) 
                continue;
            swap(c, tmp.word[i]);
            if (dict.find(tmp.word) != dict.end() && visited.find(tmp) == visited.end() ) {
                cout << node.word << ":\t" << tmp.word << endl;
                new_node.insert(tmp);
            }
            swap(c, tmp.word[i]);
        }
    }
}

int LadderLen(const string& start, const string& end, const unordered_set<string>& dict) {
    queue<word_state> q;
    unordered_set<word_state> visited;

    word_state start_node(start, 0);
    q.push(start_node);
    visited.insert(start_node);
    while(!q.empty()) {
        word_state node = q.front();
        q.pop();

        if (node.word == end) {
            return node.level + 1;
        }
        
        unordered_set<word_state> new_node;
        extend_statue(node, visited, dict, new_node);
        for(unordered_set<word_state>::iterator it = new_node.begin() ; it != new_node.end(); it++) {
            q.push(*it);
            visited.insert(*it);
        }
    }
    return 0;
}

int main() {
    string start = "hit";
    string end = "cog";
    unordered_set<string> dict;
    dict.insert("hot");
    dict.insert("dot");
    dict.insert("dog");
    dict.insert("lot");
    dict.insert("log");
    dict.insert("cog");
    int res = LadderLen(start, end, dict);
    cout << "res:" << res << endl;
    return -1;
}
