#include "xmltreemodel.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>

#include "xmlnode.h"

XmlTreeModel::XmlTreeModel(const QString &configPath, QObject *parent) :
    QAbstractItemModel(parent), m_root(new XmlNode("Имя тега", "Текст между тегов"))
{
    QFile file(configPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("%s Config opening failed %s", Q_FUNC_INFO, file.errorString().toUtf8().data());
    }

    QDomDocument document;
    QString errorMsg;
    int errorLine, errorColumn;
    if (!document.setContent(file.readAll(), &errorMsg, &errorLine, &errorColumn)) {
        qFatal("%s Xml file opening failed: %s, %d, %d", Q_FUNC_INFO, errorMsg.toUtf8().data(),
               errorLine, errorColumn);
    }
    int maxAttributesCount = 0;
    traverseNode(m_root, document, maxAttributesCount);
    for (int col = 0; col < maxAttributesCount; ++col) {
        m_root->appendAttribute(QString("Атрибут №%1").arg(col + 1));
    }
}

XmlTreeModel::~XmlTreeModel()
{
    delete m_root;
}

QModelIndex XmlTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    return createIndex(row, column, findNode(parent)->child(row));
}

QModelIndex XmlTreeModel::parent(const QModelIndex &child) const
{
    XmlNode *parent = findNode(child)->parent();
    if (parent == m_root) {
        return QModelIndex();
    }
    return createIndex(parent->row(), 0, parent);
}

int XmlTreeModel::rowCount(const QModelIndex &parent) const
{
    return findNode(parent)->rowCount();
}
int XmlTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_root->columnCount();
}

QVariant XmlTreeModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.isValid()) {
        switch (index.column()) {
            case 0: return findNode(index)->tagname();
            case 1: return findNode(index)->text();
            default: return findNode(index)->attributes().value(index.column() - 2, "-");
        }
    }
    return QVariant();
}

QVariant XmlTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return m_root->tagname();
            case 1: return m_root->text();
            default: return m_root->attributes().at(section - 2);
        }
    }
    return QVariant();
}

void XmlTreeModel::traverseNode(XmlNode *parent, const QDomNode &node, int &maxAttributesCount)
{
    if (!parent) {
        return;
    }

    QDomNode domNode = node.firstChild();
    while (!domNode.isNull()) {
        XmlNode *newParent = Q_NULLPTR;
        if (domNode.isElement()) {
            QDomElement element = domNode.toElement();
            if (!element.isNull()) {
                const QString tagname = element.tagName();
                newParent = new XmlNode(tagname, "-", parent);
                const auto &attributes = element.attributes();
                maxAttributesCount = qMax(maxAttributesCount, attributes.size());
                for (int i = 0; i < attributes.size(); ++i) {
                    const auto &attribute = attributes.item(i).toAttr();
                    newParent->appendAttribute("\"" + attribute.name() + "\"" + "=" + "\"" +
                                               attribute.value() + "\"");
                }
            }
        } else if (domNode.isText()) {
            const QString text = domNode.toText().data();
            if (!text.isEmpty()) {
                parent->setText(domNode.toText().data());
            }
        }
        traverseNode(newParent, domNode, maxAttributesCount);
        domNode = domNode.nextSibling();
    }
}

XmlNode *XmlTreeModel::findNode(const QModelIndex &index) const
{
    if (index.isValid()) {
        XmlNode *node = static_cast<XmlNode *>(index.internalPointer());
        if (node) {
            return node;
        }
    }
    return m_root;
}
