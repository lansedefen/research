/***************************************************************************
 * 
 * Copyright (c) 2011 Sina.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
/**
 * @file auto_mutex.h
 * @author wuhua1(minisearch@staff.sina.com.cn)
 * @date 2011/07/13 10:08:04
 * @version $Revision$ 
 * @brief 
 * 自动互斥量, 构造函数加锁，析构函数解锁避免使用者忘记释放锁
 *  
 **/

#ifndef  __AUTO_MUTEX_H_
#define  __AUTO_MUTEX_H_

class auto_mutex
{

public:

	explicit auto_mutex(pthread_mutex_t & mutex): m_mutex(mutex)
	{
		pthread_mutex_lock(&m_mutex);
	}

	~auto_mutex()
	{
		pthread_mutex_unlock(&m_mutex);
	}

private:

	auto_mutex(const auto_mutex &);

	auto_mutex operator = (const auto_mutex &);

	pthread_mutex_t & m_mutex;
};

#endif  //__AUTO_MUTEX_H_

