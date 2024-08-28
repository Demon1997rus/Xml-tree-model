#include "xmlnode.h"

XmlNode::XmlNode(const QString &tagname, const QString &text, XmlNode *parent) :
    m_parent(parent), m_tagname(tagname), m_text(text)
{
    if (m_parent) {
        m_parent->appendChild(this);
    }
}

XmlNode::~XmlNode()
{
    qDeleteAll(m_children);
}

void XmlNode::appendChild(XmlNode *child)
{
    m_children.append(child);
}

XmlNode *XmlNode::child(int row) const
{
    return m_children.at(row);
}

XmlNode *XmlNode::parent() const Q_DECL_NOTHROW
{
    return m_parent;
}

int XmlNode::rowCount() const Q_DECL_NOTHROW
{
    return m_children.size();
}

int XmlNode::columnCount() const Q_DECL_NOTHROW
{
    return 2 + m_attributes.size();
}

int XmlNode::row() const
{
    if (m_parent) {
        return m_parent->m_children.indexOf(const_cast<XmlNode *>(this));
    }
    return 0;
}

const QString &XmlNode::tagname() const
{
    return m_tagname;
}

const QString &XmlNode::text() const
{
    return m_text;
}

const QVector<QString> &XmlNode::attributes() const
{
    return m_attributes;
}

void XmlNode::appendAttribute(const QString &attribute)
{
    m_attributes.append(attribute);
}

void XmlNode::setText(const QString &text)
{
    m_text = text;
}
