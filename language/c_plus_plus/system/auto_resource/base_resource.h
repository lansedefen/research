/***************************************************************************
 * 
 * Copyright (c) 2011 Sina.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
/**
 * @file base_resource.h
 * @author wuhua1(minisearch@staff.sina.com.cn)
 * @date 2011/06/27 22:38:10
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __BASE_RESOURCE_H_
#define  __BASE_RESOURCE_H_

#include <assert.h>
#include <pthread.h>

#include "auto_mutex.h"
#include<iostream>
using namespace std;

class BaseResource
{

public:

	BaseResource()
	{
		refer_count = 0;
		assert(pthread_mutex_init(&mutex, NULL) == 0);
	}

	virtual ~BaseResource()
	{
		pthread_mutex_destroy(&mutex);
	}

	virtual BaseResource * Clone()
	{
		return NULL;
	}

	virtual bool Load(const char * path, const char * dict) = 0;
	virtual bool Load(const char * path, const char * dict, const char * class_name)
    {
        if (class_name == NULL)
            return Load(path, dict);
        return false;
    }

	void Reference()
	{
		auto_mutex am(mutex);

        cout << "add mutex:" << refer_count<<endl;
		++refer_count;
	}

	void UnReference()
	{
		auto_mutex am(mutex);
		if (refer_count > 0)
		{
            cout << "before refer_count:" <<refer_count<<endl;
			--refer_count;
            cout << "after refer_count:" <<refer_count<<endl;
		}
	}

	int ReferCount()
	{
		auto_mutex am(mutex);
		return refer_count;
	}

private:

	int refer_count;	/**< 词典被引用的线程数 */
	pthread_mutex_t mutex;	/**< 引用计数互斥锁 */
};

#endif  //__BASE_RESOURCE_H_


