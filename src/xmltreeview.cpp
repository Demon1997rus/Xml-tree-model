#include "xmltreeview.h"

#include "xmltreemodel.h"

XmlTreeView::XmlTreeView(const QString &configPath, QWidget *parent) : QWidget(parent)
{
    init(configPath);
    settings();
    setupLayout();
}

void XmlTreeView::init(const QString &configPath)
{
    mainLayout = new QGridLayout(this);
    treeView = new QTreeView(this);
    model = new XmlTreeModel(configPath, this);
}

void XmlTreeView::settings()
{
    // Установка модели
    treeView->setModel(model);

    // Настройки главной формы
    this->setWindowTitle("Tree xml");
}

void XmlTreeView::setupLayout()
{
    mainLayout->addWidget(treeView);

    this->setLayout(mainLayout);
}
