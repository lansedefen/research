#include "dyn_resource.h"

//#include <slog.h>

int DynResource::DynReload(const char *path, const char * key, const char* class_name)
{
    int ret = -1;

	//slog_write(LL_FATAL, "zese7, path:%s, key:%s, class_name:%s", path, key, class_name);
    if (m_dyn_desc != NULL)
    {
        int bak_offset = (m_dyn_desc->cur_offset+1) % DynResourceDesc::REDUNDANT;

        cout << "bak_offset:" << bak_offset<< endl;
	    //slog_write(LL_FATAL, "zese8,  bak_offset:%d",  bak_offset);
        BaseResource * & bak_rsc = m_dyn_desc->resource[bak_offset];
	    //slog_write(LL_FATAL, "zese9, bak_rsc->ReferCount():%d", bak_rsc->ReferCount());
        if (bak_rsc == NULL || bak_rsc->ReferCount() == 0)
        {
            cout << "bak_offset2:" <<bak_offset<< endl;
            delete bak_rsc;
            BaseResource *tmp=m_dyn_desc->resource[m_dyn_desc->cur_offset];
            BaseResource *tmp2=tmp->Clone();
            bak_rsc = tmp2;
            if (bak_rsc == NULL)
            {
                cout << "bak_offset3:" <<bak_offset<< endl;
                //seErrLogEx(g_logHandle, "Resource %s Clone null", key);
            }
            else if (bak_rsc->Load(path, key, class_name))
            {
                cout << "bak_offset4:" <<bak_offset<< endl;
	            //slog_write(LL_FATAL, "zese10, path:%s, key:%s, class_name:%s", path, key, class_name);
                pthread_spin_lock(&m_dyn_desc->spinlock);
                m_dyn_desc->cur_offset = bak_offset;
                pthread_spin_unlock(&m_dyn_desc->spinlock);
                cout << "bak_offset41:" <<bak_offset<< endl;
                ret = 0;
                //try to clear the resouce backup
                bak_offset = (m_dyn_desc->cur_offset+1) % DynResourceDesc::REDUNDANT;
                int retry_times = 60;
                cout << "bak_offset42:" <<bak_offset<< endl;
                while (m_dyn_desc->resource[bak_offset] && --retry_times)
                {
                    cout << "bak_offset43:" <<bak_offset<< endl;
                    usleep(100000);
                    if (m_dyn_desc->resource[bak_offset]->ReferCount() == 0)
                    {
                        delete m_dyn_desc->resource[bak_offset];
                        m_dyn_desc->resource[bak_offset] = NULL;
                    }
                }
            }
            else
            {
                cout << "bak_offset5:" <<bak_offset<< endl;
                //seErrLogEx(g_logHandle, "Resource %s Load error", key);
                delete bak_rsc;
                bak_rsc = NULL;
            }
        }
        else
        {
            cout << "bak_offset6:" <<bak_offset<< endl;
            //seErrLogEx(g_logHandle, "Resource BAK %s has referencer", key);
        }
    }
    else
    {
        cout << "bak_offset7:" << endl;
        //seErrLogEx(g_logHandle, "Resource key[%s] not exist", key);
    }

    return ret;
}

