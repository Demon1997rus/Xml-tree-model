#ifndef XMLNODE_H
#define XMLNODE_H

#include <QString>
#include <QVector>

class XmlNode {
    // constructors
public:
    XmlNode() = default;
    XmlNode(const QString &tagname, const QString &text, XmlNode *parent = Q_NULLPTR);
    ~XmlNode();

    // public functions
public:
    void appendChild(XmlNode *child);
    XmlNode *child(int row) const;
    XmlNode *parent() const Q_DECL_NOTHROW;
    int rowCount() const Q_DECL_NOTHROW;
    int columnCount() const Q_DECL_NOTHROW;
    int row() const;
    const QString &tagname() const;
    const QString &text() const;
    const QVector<QString> &attributes() const;
    void appendAttribute(const QString &attribute);
    void setText(const QString &text);

    // parent and children
private:
    XmlNode *m_parent = Q_NULLPTR;
    QVector<XmlNode *> m_children;

    // Node data
private:
    QString m_tagname;
    QString m_text;
    QVector<QString> m_attributes;
};

#endif // XMLNODE_H
