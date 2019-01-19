#include<iostream>
#include<string>

using namespace std;

bool isMatch(string s, string p) {
          string target = s;
          string pattern = p;

		  cout << "run s, p:" << s << ", " << p << endl;
          if (target == "" && (pattern == "" || pattern == "*") ) {
              cout << "1 target&& pattern is empty." << endl;;
              return true;
          } 

          if (pattern[0] == '*') {
             cout << "2 target: " << target << ", pattern: " << pattern << endl;
             bool flag = false;
			 while(pattern[1] == '*') {
                 pattern = pattern.substr(1);
			 }
             pattern = pattern.substr(1);

             while ( !flag ) {
                flag = isMatch(target, pattern );
                cout << "3 flag:" << flag << "tar, pattt"<< target << "," << pattern <<endl;
                if (!target.empty())
                   target = target.substr(1);
				else {
				   return flag;
				}
             }
			 cout << "3.1 flag:" << flag << endl; 
             return flag;
          }          
		  
         if( (target[0] == pattern[0]) || (pattern[0] == '?' && !target.empty()) ) {
             cout << "4 target[0] == pattern[0]:" << target[0] << endl;
             return isMatch(target.substr(1), pattern.substr(1));
         } else {
              cout << "5 target[0] != pattern[0], target:" << target[0] << ", pattern:" << pattern[0] << endl;
              return false;
         }
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
   p = "*a*a*a*c";
   //p = "b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a";
   cout << isMatch(s, p) << endl;
   return -1;
}
