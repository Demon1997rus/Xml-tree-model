#ifndef XMLTREEMODEL_H
#define XMLTREEMODEL_H

#include <QAbstractItemModel>

class XmlNode;
class QDomNode;
class XmlTreeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    XmlTreeModel(const QString &configPath, QObject *parent = Q_NULLPTR);
    virtual ~XmlTreeModel();

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role) const override;

private:
    void traverseNode(XmlNode *parent, const QDomNode &node, int &maxAttributesCount);
    XmlNode *findNode(const QModelIndex &index) const;

private:
    XmlNode *m_root = Q_NULLPTR;
};

#endif // XMLTREEMODEL_H
