#include "repost_resource.h" 
#include<iostream>
#include<string>
#include<boost/algorithm/string.hpp>

using namespace boost::algorithm;
using namespace std;

strSet* hot_dict_url_init(char *filepath)
{
	strSet *hotTopicurl = new strSet;
        char line[100];
        FILE*fid=fopen(filepath,"r");
        // slog_write(LL_WARNING,"hot hit %s", filepath);
        if(NULL==fid) return NULL;
        while(NULL!=fgets(line,sizeof(line),fid)){
         	std::string lines(line);
         	//Trim(lines);
		if (lines.size() > 0)
         		hotTopicurl->insert(lines);	
        }
        fclose(fid);
	return hotTopicurl;
}

bool hit_hot_topic_url(std::string topic_url, strSet& hotTopicurl)
{
 	return (hotTopicurl.find(topic_url) != hotTopicurl.end());
}

strSet* hot_dict_init(char *filepath)
{
	    strSet *hotTopic = new strSet;
        char line[100];
        FILE*fid=fopen(filepath,"r");
        cout << "filepath2" <<filepath <<endl;
        // slog_write(LL_WARNING,"hot hit %s", filepath);
        if(NULL==fid) 
            return NULL;
        while(NULL!=fgets(line,sizeof(line),fid)){
         	std::string lines(line);
         	//Trim(lines);
            trim(lines);

            cout <<lines <<endl;
		if (lines.size() > 0)
         		hotTopic->insert(lines);	
        }
        fclose(fid);
	return hotTopic;
}

bool hit_hot_topic(std::string topic, strSet& hotTopic)
{
 	return (hotTopic.find(topic) != hotTopic.end());
}

strSet* media_user_init(char *filepath)
{
	strSet *media_user = new strSet;
        char line[100];
        FILE*fid=fopen(filepath,"r");

        // slog_write(LL_WARNING,"meida user %s", filepath);
        if(NULL==fid) return NULL;
        while(NULL!=fgets(line,sizeof(line),fid)){
         	std::string lines(line);
         	//Trim(lines);
		if (lines.size() > 0)
         		media_user->insert(lines);	
        }
        fclose(fid);
	return media_user;
}

bool hit_media_user(std::string uid, strSet& media_user)
{
	//Trim(uid);
 	return (media_user.find(uid) != media_user.end());
}


BaseResource* HOTTOPIC_DICT::Clone()
{
    return new (std::nothrow) HOTTOPIC_DICT();
}

bool HOTTOPIC_DICT::Load(const char *workpath, const char *key, const char *identity)
{
        char filepath[200];
        snprintf(filepath, sizeof(filepath), "%s%s", workpath, key);
        cout << "filepath:" << filepath << ", "<< identity << "....." << endl;
        ////slog_write(LL_WARNING,"HOTTOPIC_DICT load datapath %s",filepath);

	char data_name[256];

	if (atoi(identity) == 1) {
		//GetProfileString(filepath, "HOTTOPIC_DICT", "data", "", data_name, 256);				
        	//slog_write(LL_WARNING,"HOTTOPIC_DICT load datapath %s",data_name);
         
        string tmp(filepath);
        cout << "filepath3:" <<filepath << endl << identity <<endl;;
		topic = hot_dict_init(const_cast<char*>(tmp.c_str()));
		if (!topic) {
        		//slog_write(LL_WARNING,"HOTTOPIC_DICT load failed");
			return false;
		}
        	//slog_write(LL_WARNING,"HOTTOPIC_DICT load ok");
	}
	else if (atoi(identity) == 2) {
		//GetProfileString(filepath, "MEDIA_USER_DICT", "data", "", data_name, 256);				
        	//slog_write(LL_WARNING, "MEDIA_USER_DICT load datapath %s",data_name);
		media = media_user_init(data_name);
		if (!media) {
        		//slog_write(LL_WARNING,"MEDIA_USER_DICT load failed");
			return false;
		}
        	//slog_write(LL_WARNING,"MEDIA_USER_DICT load ok");
	}
	else if (atoi(identity) == 3) {
		//GetProfileString(filepath, "HOTTOPIC_DICT", "url_data", "", data_name, 256);				
        	//slog_write(LL_WARNING, "HOTTOPIC_DICT url_data datapath %s",data_name);
		topic_url = hot_dict_url_init(data_name);
		if (!topic_url) {
        		//slog_write(LL_WARNING,"HOTTOPIC_DICT url_data failed");
			return false;
		}
        	//slog_write(LL_WARNING,"HOTTOPIC_DICT load ourl_data ok");
	}

        return true;
}

bool HOTTOPIC_DICT::Load(const char *workpath, const char *key)
{
        //slog_write(LL_WARNING,"HOTTOPIC_DICT load1 datapath");
	return true;
}

HOTTOPIC_DICT::~HOTTOPIC_DICT()
{
	if (media) {
		delete (strSet *)media;
		media=NULL;
	}
	if (topic) {
		delete (strSet *)topic;
		topic=NULL;
	}
	if (topic_url) {
		delete (strSet *)topic_url;
		topic_url=NULL;
	}

}

