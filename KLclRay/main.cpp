#include "KLcPy.h"
#include "KBaseMacro.h"
#include "KLclRay.h"
#include "KLqtMenu.h"
#include "KLcContainer.h"
#include <QtWidgets/QApplication>


KLcBool debugCC()
{
    KLcBool kbRet = KL_FALSE;
    KLCMAP_PTR ptMap = NULL;
    KTVALUE tKey = { 0 };
    KTVALUE_PTR ptValue = NULL;
    KTVALUE_PTR ptSearchValue = NULL;

    kbRet = KLcmCreateMap(&ptMap);
    KL_PROCESS_ERROR(kbRet);
    KLCMAP_SETSTRINGKEYVALUE(ptMap, tKey, "szAccount", ptValue, kbRet);

    ptValue->emType = KT_INT;
    ptValue->uValue.n = 1234;

    KLCMAP_GETSTRINGKEYVALUE(ptMap, "szAccount", &ptSearchValue);
    printf("Search value: %d\n", ptSearchValue->uValue.n);

    kbRet = KL_TRUE;
    
Exit0:
    return kbRet;
}

int main(int argc, char *argv[])
{
    debugCC();
    QApplication a(argc, argv);
    
    
    KLclRay::getInstance()->show();

 

    return a.exec();
}
