#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool isMatch(string s, string p) {
          string target = s;
          string pattern = p;
		  //cout << "run s, p:" << s << ", " << p << endl;
          if (target == "" && (pattern == "" || pattern == "*") ) {
              //cout << "1 target&& pattern is empty." << endl;;
              return true;
          } 

          if (pattern[0] == '*') {
             //cout << "2 target: " << target << ", pattern: " << pattern << endl;
             bool flag = false;
			 while(pattern[1] == '*') {
                 pattern = pattern.substr(1);
			 }
             pattern = pattern.substr(1);

             while ( !flag ) {
                flag = isMatch(target, pattern );
                //cout << "3 flag:" << flag << "tar, pattt"<< target << "," << pattern <<endl;
                if (!target.empty())
                   target = target.substr(1);
				else {
				   return flag;
				}
             }
			 //cout << "3.1 flag:" << flag << endl; 
             return flag;
          }          
		  
         if( (target[0] == pattern[0]) || (pattern[0] == '?' && !target.empty()) ) {
             //cout << "4 target[0] == pattern[0]:" << target[0] << endl;
             return isMatch(target.substr(1), pattern.substr(1));
         } else {
              //cout << "5 target[0] != pattern[0], target:" << target[0] << ", pattern:" << pattern[0] << endl;
              return false;
         }
}

bool isMatch2(string s, string p) {
        if (p.empty()) return s.empty();
        if (p.size() == 1) {
            return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
        }
        if (p[1] != '*') {
            if (s.empty()) return false;
            return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
        }
        while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
            if (isMatch(s, p.substr(2))) return true;
            s = s.substr(1);
        }
        return isMatch(s, p.substr(2));
    }

bool isMatch3(char *s, char *p) {
    char *scur = s, *pcur = p, *sstar = NULL, *pstar = NULL;
    while (*scur) {
        if (*scur == *pcur || *pcur == '?') {
            ++scur;
            ++pcur;
        } else if (*pcur == '*') {
            pstar = pcur++;
            sstar = scur;
        } else if (pstar) {
            pcur = pstar + 1;
            scur = ++sstar;
        } else return false;
    } 
    while (*pcur == '*') ++pcur;
    return !*pcur;
}

bool isMatch4(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool> > dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*') dp[0][i] = dp[0][i - 1];
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
					cout << "dp[i,j]:" << dp[i][j] <<  endl;
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
}

int main() {
   string s= "";
   string p = "***";
   s = "zacabz";
   p = "*a?b*";
   s = "babaaababaabababbbbbbaabaabbabababbaababbaaabbbaaab";
   p = "***bba**a*bbba**aab**b";
   s = "baaabbaabaabbababbaab";
   p = "**b*ba*a";

   s = "babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb";
   //p = "*a*a*a*c";
   p = "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***b";
   //p = "b*bb*a*bba*b*a*bbb*aba*babbb*aa*aabb*bbb*a";
   //p = "b*bb*a*bba*b*a*bbb*aba*babbb*aa*aabb*bbb*a";
   //cout << isMatch3((char*)s.data(), (char*)p.data()) << endl;
   p = "a*f";
   s = "afa";
   cout << isMatch4(s, p) << endl;
   return -1;
}
