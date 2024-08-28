#ifndef XMLTREEVIEW_H
#define XMLTREEVIEW_H

#include <QGridLayout>
#include <QTreeView>
#include <QWidget>

class XmlTreeModel;
class XmlTreeView : public QWidget {
    Q_OBJECT
public:
    explicit XmlTreeView(const QString &configPath, QWidget *parent = nullptr);

private:
    void init(const QString &configPath);
    void settings();
    void setupLayout();

private:
    QGridLayout *mainLayout = Q_NULLPTR;
    QTreeView *treeView = Q_NULLPTR;
    XmlTreeModel *model = Q_NULLPTR;
};

#endif // XMLTREEVIEW_H
