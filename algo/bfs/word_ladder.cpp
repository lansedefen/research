#include<iostream>
#include<vector>
#include<queue>
#include <unordered_set>

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
}



int LadderLen(const string& start, const string& end, const unordered_set<string>& dict) {
    queue<word_statue> q;
    unordered_set<word_state> visited;

    word_state start_node(start, 0);
    q.push(start_node);
    visited.insert(start_node);
    while(!q.empty()) {
        word_state node = q.front();
        q.pop();

        if (node.word == "end") {
            return node.level + 1;
        }
        
        vector<word_state> new_node = extend_statue(node);
        for(int i =0 ;i< new_node.size();i++) {
            q.push(new_node[i]);
            visited.insert(new_node[i]);
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
    LadderLen(start, end, dict);
    return -1;
}
