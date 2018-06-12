#ifndef REPOST_RESOURCE_H
#define REPOST_RESOURCE_H

//#include "resource.h"
#include "resource_ext.h"
#include "base_resource.h"
#include<set>
#include<string>
//#include "tag_util.h"
//#include "slog.h"
//#include "pcre_util.h"
//#include "hot_topic_load.h"
//#include "daconfig.h"

//#include "slog.h"
//#include "docdata_t.h"
//#include "segment.h"
//#include "feature_input.h"
//#include "tag_util.h"
//#include "tag_topic.h"

typedef std::set<std::string> strSet;

class HOTTOPIC_DICT: public BaseResource
{
        public:
               	HOTTOPIC_DICT():media(NULL), topic(NULL), topic_url(NULL){};
                virtual bool Load(const char *workpath, const char *key, const char *identity);
                virtual bool Load(const char *workpath, const char *key);
               	virtual ~HOTTOPIC_DICT();
		
		virtual BaseResource* Clone();
   		strSet* GetMediadict(){return media;}   		
		strSet* GetHotdict(){return topic;}
		strSet* GetHoturldict(){return topic_url;}

        private:
		strSet* media;
		strSet* topic;
		strSet* topic_url;
};


#endif
