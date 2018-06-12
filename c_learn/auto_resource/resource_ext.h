/***************************************************************************
 * 
 * Copyright (c) 2011 Sina.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
/**
 * @file resource.h
 * @author wuhua1(minisearch@staff.sina.com.cn)
 * @date 2011/06/23 17:19:17
 * @version $Revision$ 
 * @brief 
 * 资源管理器，负责全局级只读词典共享
 **/


#ifndef  __RESOURCE_EXT_H_
#define  __RESOURCE_EXT_H_

#include <string>
#include <ext/hash_map>
#include <string.h>
#include <assert.h>
//#include <selog.h>
#include <stdio.h>

#include "base_resource.h"
#include "dyn_resource.h"
//extern LOG_HANDLE g_logHandle;
#include<iostream>

using namespace std;

class ResourceExt
{
public:

	static bool Init(const char * workPath, const char * confName);

	static void Destory();

	/**
	 * @brief 静态词典获取接口
	 **/
	template <typename T>
	static T * getResource(const char * key)
	{
		BaseResource * value = find(key);
		if (value == NULL)
		{
			pthread_mutex_lock(&m_lock);

			value = find(key);
			if (value == NULL)
			{
				value = new (std::nothrow) T();
				assert(value != NULL);
				if (!value->Load(m_path.c_str(), key))
				{
					//seErrLogEx(g_logHandle, "Resource %s Load error", key);
					delete value;
					value = NULL;
				}
				else
				{
					m_flyweight.insert(std::make_pair<std::string, BaseResource*> (key, value));
				}
			}
            pthread_mutex_unlock(&m_lock);
		}
		return static_cast<T *> (value);
	}
	
	/**
	 * @brief 动态词典引用接口，词典引用计数加1
	 * @warnning 动态词典使用后需要调用 UnReference 解引用
	 * @seeto BaseResource::UnReference()
	 **/
	template <typename T>
	static T * Reference(const char * key, int id)
    {
        char id_str[256];
        sprintf(id_str, "%d", id);
        return Reference<T>(key, &id_str[0]);
    }

	template <typename T>
	static T * Reference(const char * key, const char* class_name = NULL)
	{
		if (key == NULL)
		{
			return NULL;
		}

        std::string query_key = key;
        if (class_name != NULL)
            catenateString(query_key, class_name);

        DynResource *dyn_resource = find_dyn(query_key.c_str());

        cout << "1" << m_path <<", " <<key <<", " << class_name <<endl;
        if (dyn_resource == NULL) //need initialize the resoruce
        {

            cout << "2" << m_path <<", " <<key <<", " << class_name <<endl;
            pthread_spin_lock(&m_spinlock);

            cout << "3" << m_path <<", " <<key <<", " << class_name <<endl;
            dyn_resource = find_dyn(query_key.c_str());

            if (dyn_resource == NULL)
            {
                dyn_resource = new (std::nothrow) DynResource();
                assert(dyn_resource != NULL);

                m_dynflyweight.insert(std::make_pair(query_key, dyn_resource));
            }

            pthread_spin_unlock(&m_spinlock);
        }

        assert(dyn_resource != NULL);

        T* temp = dyn_resource->Reference<T>(m_path.c_str(), key, class_name);
        cout << "4:" << m_path <<", " <<key <<", " << class_name <<endl;

        if (temp == NULL)
        {

            cout << "load err" <<endl; 
            if (class_name == NULL) {
                //seErrLogEx(g_logHandle, "Resource %s Load error", key);
            }
            else {
                //seErrLogEx(g_logHandle, "Resource %s with config file %s load error", class_name, key);
            }
        }

        return temp;
	}

	/**
	 * @brief 动态词典reload操作
	 * @warning todo 多线程安全?
	 **/
	static int DynReload(const char * key, const char *class_name = NULL);
	
private:
    inline static void catenateString(std::string &base, const char* suffix)
    {
        base += "_";
        base += suffix;
    }

	static BaseResource * find(const char * key)
	{
		hash_map::iterator iter = m_flyweight.find(key);
		if (iter != m_flyweight.end())
		{
			return iter->second;
		}

		return NULL;
	}

	static DynResource * find_dyn(const char * key)
	{
		dynhash_map::iterator iter = m_dynflyweight.find(key);
		if (iter != m_dynflyweight.end())
		{
			return iter->second;
		}

		return NULL;
	}

	struct flyweight_hash 
	{
		unsigned int operator () (const std::string & str) const
		{
			register unsigned int h;       
			register unsigned char *p;
			for (h = 0, p = (unsigned char *) str.c_str(); *p ; ++p) 
			{
				h = 31 * h + *p;  
			}
			return h; 
		} 
	};

	struct flyweight_compare
	{
		bool operator () (const std::string & a, const std::string &b) const
		{
			return (!strcmp(a.c_str(), b.c_str()));        
		}
	};
	
	typedef __gnu_cxx::hash_map <std::string, BaseResource *,
			flyweight_hash, flyweight_compare> hash_map;
			
	typedef __gnu_cxx::hash_map <std::string, DynResource *,
			flyweight_hash, flyweight_compare> dynhash_map;

	static hash_map m_flyweight;

	static pthread_mutex_t m_lock;
    static pthread_spinlock_t m_spinlock;

	static std::string m_path;
	static dynhash_map m_dynflyweight;
};

#endif  //__RESOURCE_EXT_H_
