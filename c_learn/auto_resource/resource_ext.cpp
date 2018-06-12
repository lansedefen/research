/***************************************************************************
 * 
 * Copyright (c) 2011 Sina.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
/**
 * @file resource.cpp
 * @author wuhua1(minisearch@staff.sina.com.cn)
 * @date 2011/06/23 17:19:23
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "resource_ext.h"
//#include <slog.h>

const int HashTableSize = 211;
std::string ResourceExt::m_path;
pthread_mutex_t ResourceExt::m_lock;
pthread_spinlock_t ResourceExt::m_spinlock;
ResourceExt::hash_map ResourceExt::m_flyweight(HashTableSize);
ResourceExt::dynhash_map ResourceExt::m_dynflyweight(HashTableSize);

bool ResourceExt::Init(const char * workPath, const char * confName)
{
	if (workPath == NULL || confName == NULL)
	{
		return false;
	}

	m_path = workPath;

	if (pthread_mutex_init(&m_lock, NULL) != 0)
	{
		return false;
	}

	if (pthread_spin_init(&m_spinlock, 0) != 0)
	{
		return false;
	}

	return true;
}

int ResourceExt::DynReload(const char * key, const char *class_name)
{
	int ret = -1;
    //no need to add lock here, cause reload can only be happened after loading
    std::string query_key = key;
    if (class_name != NULL)
        catenateString(query_key, class_name);

	DynResource *dyn_resource = find_dyn(query_key.c_str());

	//slog_write(LL_FATAL, "zese2, query_key:%s", query_key.c_str());
	if (dyn_resource != NULL)
	{

	    //slog_write(LL_FATAL, "zese3, query_key:%s, mpath:%s, key:%s, class_name:%s", query_key.c_str(), m_path.c_str(), key, class_name);
        return dyn_resource->DynReload(m_path.c_str(), key, class_name);
	}
	else
	{
	    //slog_write(LL_FATAL, "zese4, query_key:%s, class_name:%s", query_key.c_str(), class_name);
        if (class_name == NULL) {
		    //seErrLogEx(g_logHandle, "Resource key[%s] not exist", key);
		}
        else {
		    //seErrLogEx(g_logHandle, "Resource [%s] in config file [%s] not exist", class_name, key);
		}
	}
	return ret;
}

void ResourceExt::Destory()
{
	hash_map::iterator end = m_flyweight.end();
	for (hash_map::iterator iter = m_flyweight.begin(); iter != end; ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	} 

	dynhash_map::iterator dend = m_dynflyweight.end();
	for (dynhash_map::iterator iter = m_dynflyweight.begin(); iter != dend; ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}

	pthread_mutex_destroy(&m_lock);
	pthread_spin_destroy(&m_spinlock);
}
