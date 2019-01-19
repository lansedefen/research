#include <stdint.h>
#include <string>
#include <vector>
#include <string.h>
#include <set>
#include <map>

#include<iostream>

using namespace std;

struct Char_Node
{
    int char_type;
    string charactor;
    Char_Node():char_type(0),charactor("") {};
};


std::string RemoveTopicInfo(const std::string& content) {
  std::string result = content;
  while (1) {
	  std::string::size_type head = result.find('#');
    if (head == std::string::npos || head == result.length()-1) {
      break;
    }
    size_t tail = result.find('#', head+1);
    if (tail == std::string::npos || tail <= head) {
      break;
    }
    std::string before = (head == 0) ? "" : result.substr(0, head);
    std::string after = tail + 1 < result.length() ? result.substr(tail+1,result.length()-tail-1) : "";
    result = before + after;
  }
  return result;
}

std::string RemoveAtInfo(const std::string& content) {
  std::string result = content;
  while (1) {
	  std::string::size_type head = result.find('@');
    if (head == std::string::npos || head == result.length()-1) {
      break;
    }
    size_t tail = result.find(' ', head+1);
    if (tail == std::string::npos) {
      if (result.length()-head < 20) {
	    std::string before = (head == 0)?"":result.substr(0, head);
        result = before;
        continue;
      } else {
        break;
      }
    }
    std::string before = (head == 0)?"":result.substr(0, head);
    std::string after = tail+1<result.length()? result.substr(tail+1,result.length()-tail-1):"";
    result = before + after;
  }
  return result;
}

std::string RemoveExpressionInfo(const std::string& content) {
  std::string result = content;
  while (1) {
	  std::string::size_type head = result.find('[');
    if (head == std::string::npos || head == result.length()-1) {
      break;
    }
    size_t tail = result.find(']', head+1);
    if (tail == std::string::npos || tail <= head) {
      break;
    }
    std::string before = (head == 0)?"":result.substr(0, head);
    std::string after = tail+1<result.length()? result.substr(tail+1,result.length()-tail-1):"";
    result = before + after;
  }
  return result;
}

std::string erase_sina_tag(const std::string &content)
{
	std::string str = content;
	if (str.empty()) {
		return str;
	}	
	size_t sina_beg = str.find("<sina:link");
	while (sina_beg != std::string::npos && sina_beg < str.length()) {
		size_t sina_end = str.find("/>", sina_beg + 1);
		if (sina_end == std::string::npos) {
			break;
		}		
		std::string extra = str.substr(sina_end + 2, str.length() - sina_end - 2);
		str.replace(sina_beg, str.length() - sina_beg, extra);

		sina_beg = str.find("<sina:link", sina_beg);
	}
	return str;
}

bool get_charactor_info(string &content,vector<Char_Node> &char_node_vec,char charset);

std::string erase_special_char(const std::string &content){
  std::string result = content;
  std::string info;
  vector<Char_Node> char_node_vec;
  get_charactor_info(result, char_node_vec, '1');
  for(std::vector<Char_Node>::iterator it = char_node_vec.begin();it != char_node_vec.end();it++)
  {
    if(it-> char_type == 17)
    {
       cout << it -> charactor << endl;
       it -> charactor =  "";
       //continue;
    }
    info += it -> charactor;
  } 
  return info;
}

bool HasOnlyTopic(std::string m_content) {
  if (m_content.find("//@") != std::string::npos) {
    return false;
  }
  //std::string info = RemoveExpressionInfo(RemoveAtInfo(RemoveTopicInfo(m_content)));
  //std::string info = RemoveExpressionInfo(RemoveAtInfo(m_content));
  //std::string info = erase_sina_tag(RemoveTopicInfo(m_content));
  //std::string info = RemoveTopicInfo(erase_sina_tag(RemoveExpressionInfo(m_content)));
  std::string info = erase_special_char(RemoveTopicInfo(erase_sina_tag(RemoveExpressionInfo(m_content))));
  //Trim(info);
  cout << m_content << endl;
  return info.length() == 0 ? true : false;
}

int32_t getCharactor(const char *src,char &len, int32_t remainlen, char charset); 
bool get_charactor_info(string &content,vector<Char_Node> &char_node_vec,char charset)
{
	char_node_vec.clear();
	if(content.length() <= 0)
		return true;
	string cur_char = "";
	std::string::size_type char_pos = 0;
	do{
		Char_Node node;
		char cur_char_len = 0;
		//int32 ret = getCharactor(content.c_str()+char_pos, cur_char_len,content.length()-char_pos,charset);
		getCharactor(content.c_str()+char_pos, cur_char_len,content.length()-char_pos,charset);
		cur_char = string(content.c_str()+char_pos,cur_char_len);
		int type = 17;
        //= charactor_type(cur_char);
		node.char_type = type;
		node.charactor = cur_char;
		char_node_vec.push_back(node);
		char_pos += cur_char.length();
	}while(char_pos < content.length());
	return true;
}

int32_t getCharactor(const char *src,char &len, int32_t remainlen, char charset) {
    if((unsigned char)(*src) < 128) {
        len = 1;
        return 1;
    }
    if(0 == charset) {
        if(remainlen>1) {
            len =2;
            return 2;
        }
    }

    uint8_t p =(uint8_t)(src[0]);
    if (p > 0x00 && p <= 0x7f)
        len = 1;
    else if((p & (0xff << 5))== 0xc0)
        len = 2;
    else if ((p & (0xff << 4))== 0xe0)
        len = 3;
    else if ((p & (0xff << 3))== 0xf0)
        len = 4;
    else if ((p & (0xff << 2))== 0xf8)
        len = 5;
    else if ((p & (0xff << 1))== 0xfc)
        len = 6;
    else
        len = 1;
    len = len > remainlen ? remainlen : len;
    return 2;
}

int main() {
    int xx = 0;
    string m_content = "哈哈[oo] fadfa  大人";
    bool tmp = HasOnlyTopic(m_content); 
    cout << tmp << endl;
    return -1;

}
