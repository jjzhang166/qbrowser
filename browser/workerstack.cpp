#include "stdafx.h"
#include "workerstack.h"
#include "tabwidget.h"
#include "webview.h"
#include "fquerypanel.h"

WorkerStack::WorkerStack(QWidget *parent, TabWidget* tab)
    : QTabWidget(parent), tab_(tab)
{
    Q_ASSERT(tab);

    ui.setupUi(this);
    // setFixedWidth(320);
    setMinimumWidth(200);
    setStyleSheet("KStyledWidget{border-left:1px solid #828790;border-bottom:1px solid #828790; }");

    // ���ܲ�ѯ���
    query_panel_ = new FQueryPanel(this);
    addTab(query_panel_, QSL("���ܲ�ѯ"));
    connect(query_panel_, &FQueryPanel::openUrl, this, &WorkerStack::onOpenUrl);

    if (tab_){
        // ���tab�仯
        connect(tab_, &TabWidget::tabCreated, this, &WorkerStack::onNewTab);
        connect(tab_, &TabWidget::tabClosed, this, &WorkerStack::onCloseTab);
        connect(tab_, &TabWidget::currentChanged, this, &WorkerStack::onTabsChanged);
    }
}

WorkerStack::~WorkerStack()
{
}

void WorkerStack::onNewTab(WebView* w)
{
    query_panel_->setWebView(w);
}

void WorkerStack::onCloseTab(WebView* w)
{

}

void WorkerStack::onTabsChanged(int)
{
    if (WebView* w = tab_->currentWebView()){
        query_panel_->setWebView(w);
    }
}

void WorkerStack::onOpenUrl(QString file, bool newtab)
{
    if (newtab){
        if (WebView* w = tab_->newTab(true)){
            w->setUrl(file);
        }
    }
    else{
        if (WebView* w = tab_->currentWebView()){
            w->setUrl(file);
        }
    }
}
