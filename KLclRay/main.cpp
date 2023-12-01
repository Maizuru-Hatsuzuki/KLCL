#include "C:\Users\Administrator\AppData\Local\Programs\Python\Python37\include\Python.h"
#include "KLclRay.h"
#include <QtWidgets/QApplication>



int TestPy()
{
    int nRet                    = KL_FALSE;
    PyObject* pMoudle           = NULL;
    PyObject* pMouduleDict      = NULL;
    PyObject* pPyClass          = NULL;
    PyObject* pPyClassConstruct = NULL;
    PyObject* pPyClassIns       = NULL;
    PyObject* pPyClassRet       = NULL;

    //Py_SetPythonHome(L"C:\\Users\\Administrator\\AppData\\Local\\Programs\\Python\\Python37");

    Py_Initialize();
    nRet = Py_IsInitialized();
    KL_PROCESS_ERROR(nRet);

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('H:\\HD - Trunk\\mui\\Lua\\Interface\\XAutoTest\\KL25')");
	PyRun_SimpleString("print(sys.path)");
    pMoudle = PyImport_ImportModule("WizardUltra");
    KL_PROCESS_ERROR(pMoudle);

    pMouduleDict = PyModule_GetDict(pMoudle);
    KL_PROCESS_ERROR(pMoudle);

    pPyClass = PyDict_GetItemString(pMouduleDict, "CwuKL25COM");
    KL_PROCESS_ERROR(pPyClass);

    pPyClassConstruct = PyInstanceMethod_New(pPyClass);
    KL_PROCESS_ERROR(pPyClassConstruct);

    pPyClassIns = PyObject_CallObject(pPyClassConstruct, NULL);
    KL_PROCESS_ERROR(pPyClassIns);

    pPyClassRet = PyObject_CallMethod(pPyClassIns, "getValue", NULL);
    KL_PROCESS_ERROR(pPyClassRet);

    PyArg_Parse(pPyClassRet, "i", &nRet);
    KL_PROCESS_ERROR(nRet);

    printf("nRet: %d\n", nRet);

Exit0:
    Py_DecRef(pMoudle);
    Py_DecRef(pMouduleDict);
    Py_DecRef(pPyClass);
    Py_DecRef(pPyClassConstruct);
    Py_DecRef(pPyClassIns);
    Py_DecRef(pPyClassRet);
    Py_Finalize();
    return nRet;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KLclRay w;
    
    TestPy();
    
    w.klqShow();
    w.show();

    printf("1");

    return a.exec();
}
