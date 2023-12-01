#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include "KBaseMacro.h"
#include "KLclRayEx.h"
#include "ui_KLclRay.h"


typedef QTextEdit* PQTEXTEDIT;

class KLclRay : public QMainWindow
{
    Q_OBJECT

public:
    KLclRay(QWidget *parent = nullptr);
    ~KLclRay();
    
    void klqUpdateText(PQTEXTEDIT pTextEdit, const char* cszpText);
    void klqCreateTextEdit(PQTEXTEDIT* ppQTextEdit);
    void klqShow();

private:
    float m_fWindowHeight = 0;
    float m_fWindowWidth = 0;

    QHBoxLayout* m_pQHLayoutBase = NULL;
    QHBoxLayout* m_pQHLayoutBottom = NULL;

private:
    Ui::KLclRayClass ui;
};
