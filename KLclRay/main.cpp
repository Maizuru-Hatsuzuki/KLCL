#include "KLcPy.h"
#include "KBaseMacro.h"
#include "KLclRay.h"
#include <QtWidgets/QApplication>



int TestPy()
{
    KLcBool klBool = KL_FALSE;
	klBool = KLpInitPy3();
    KL_PROCESS_ERROR(klBool);

    klBool = KLpePfEyeLaunch();
    KL_PROCESS_ERROR(klBool);

    klBool = KLpUninitPy3();
    KL_PROCESS_ERROR(klBool);

Exit0:
    return klBool;
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //KLclRay w;
    
    TestPy();
    
    //w.klqShow();
    //w.show();

 

    //return a.exec();
    return 1;
}
