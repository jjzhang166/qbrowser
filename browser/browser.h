#pragma once


#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BROWSER_LIB)
#  define BROWSER_EXPORT Q_DECL_EXPORT
# else
#  define BROWSER_EXPORT Q_DECL_IMPORT
# endif
#else
# define BROWSER_EXPORT
#endif

typedef void* BROWSER_HANDLE;

extern "C" 
{
    BROWSER_EXPORT bool initBrowserSevice();

    // ����һ���µĴ���
    BROWSER_EXPORT BROWSER_HANDLE createBrowser();

    // cur_tab �Ƿ��õ�ǰ�ı�ǩҳ
    BROWSER_EXPORT bool openUrl(BROWSER_HANDLE h, const QString& url, bool new_tab);
    
}
