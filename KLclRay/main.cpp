#include "KLcPy.h"
#include "KBaseMacro.h"
#include "KLclRay.h"
#include "KLqtMenu.h"
#include <QtWidgets/QApplication>





int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    KLclRay::getInstance()->show();

 

    return a.exec();
}
