#include "CreateCommand.hpp"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

static const char Text[] = "Create Bone";

CreateCommand::CreateCommand(QGraphicsItem *item, QGraphicsItem *parent) :
    QUndoCommand(Text),
    m_item(item),
    m_parent(parent)
{
    Q_ASSERT(m_item);
    Q_ASSERT(m_parent);
}

void CreateCommand::redo()
{
    QGraphicsScene *scene = m_parent->scene();
    Q_ASSERT(scene);
    scene->clearSelection();

    m_item->setSelected(true);

    m_item->setParentItem(m_parent);
}

void CreateCommand::undo()
{
    QGraphicsScene *scene = m_item->scene();
    Q_ASSERT(scene);
    scene->clearSelection();

    m_parent->setSelected(true);

    scene->removeItem(m_item);
}

