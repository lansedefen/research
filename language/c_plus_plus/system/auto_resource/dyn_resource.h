#ifndef __DYN_RESOURCE_H
#define __DYN_RESOURCE_H

#include <string>
#include <assert.h>
//#include <selog.h>
#include <typeinfo>

#include "base_resource.h"
//extern LOG_HANDLE g_logHandle;
#include<iostream>

using namespace std;

class DynResource
{

private:

	/**
	 * @brief 动态词典描述符
	 **/
	struct DynResourceDesc
	{
		enum {REDUNDANT = 2};

		BaseResource * resource[REDUNDANT];
		int cur_offset;
		pthread_spinlock_t spinlock;

		DynResourceDesc()
		{
			for (int i = 0; i < REDUNDANT; ++i)
			{
				resource[i] = NULL;
			}

			cur_offset = 0;

            pthread_spin_init(&spinlock, 0);
		}

		~DynResourceDesc()
		{
			pthread_spin_lock(&spinlock);
			for (int i = 0; i < REDUNDANT; ++i)
			{
				if (resource[i] != NULL && resource[i]->ReferCount() == 0)
				{
					delete resource[i];
					resource[i] = NULL;
				}
			}
			pthread_spin_unlock(&spinlock);

			pthread_spin_destroy(&spinlock);
		}
	};

public:
    DynResource():m_dyn_desc(NULL)
    {
        pthread_mutex_init(&m_lock, NULL);
        m_initialized = false;
    }
    ~DynResource()
    {
        pthread_mutex_destroy(&m_lock);
        if (m_dyn_desc)
        {
            delete m_dyn_desc;
            m_dyn_desc = NULL;
        }
    }

	/**
	 * @brief 动态词典引用接口，词典引用计数加1
	 * @warnning 动态词典使用后需要调用 UnReference 解引用
	 * @seeto BaseResource::UnReference()
	 **/
	template <typename T>
	T * Reference(const char *path, const char * key, const char *class_name)
	{
		if (key == NULL)
		{
			return NULL;
		}

		BaseResource * base_temp = NULL;

		if (m_initialized == false)
		{
			pthread_mutex_lock(&m_lock);

			if (m_initialized == false)
			{
				base_temp = new (std::nothrow) T();
				m_dyn_desc = new (std::nothrow) DynResourceDesc();
				assert(base_temp != NULL && m_dyn_desc != NULL);

                cout << "dy" << path << "," <<key << "," << class_name << endl;
				if (!base_temp->Load(path, key, class_name))
				{
                    cout << "dy2" << path << "," <<key << "," << class_name << endl;
					delete base_temp;
					delete m_dyn_desc;
					pthread_mutex_unlock(&m_lock);
					return NULL;
				}
				else
				{
                    cout << "dy3:" << path << "," <<key << "," << class_name << endl;
					m_dyn_desc->resource[m_dyn_desc->cur_offset] = base_temp;
                    cout << "dy4:" << m_dyn_desc->cur_offset << ", " << base_temp<< endl;
                    asm volatile("mfence": : :"memory");  //ensure not changed the order
                    m_initialized = true;
				}
			}
		    pthread_mutex_unlock(&m_lock);
		}
        
        assert(m_dyn_desc != NULL);
		
		pthread_spin_lock(&(m_dyn_desc->spinlock));

		int offset = m_dyn_desc->cur_offset;
		base_temp = m_dyn_desc->resource[offset];

		pthread_spin_unlock(&(m_dyn_desc->spinlock));

        T *temp = static_cast<T *>(base_temp);

		if (temp != NULL)
		{
            cout << "dy5:" << temp << endl;
			temp->Reference();
		}
		else
		{
			try
			{
				//seErrLogEx(g_logHandle, "static_cast<%s> (%s) is null", typeid(T *).name(),
						//typeid(m_dyn_desc->resource[offset]).name());
			}
			catch(...)
			{
				//seErrLogEx(g_logHandle, "static_cast<T> (%s) is null", key);
			}
		}
		
		return temp;
	}

	/**
	 * @brief 动态词典reload操作
	 * @warning todo 多线程安全?
	 **/
    int DynReload(const char *path, const char * key, const char* class_name);
	
private:
    DynResourceDesc *m_dyn_desc;
	//pthread_rwlock_t m_dynrwlock;
    pthread_mutex_t m_lock;
    volatile bool m_initialized;

};

#endif
