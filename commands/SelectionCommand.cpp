#include "SelectionCommand.hpp"
#include <QGraphicsScene>
#include <QGraphicsItem>

SelectionCommand::SelectionCommand(QGraphicsScene *scene, const QList<QGraphicsItem *> &items) :
    m_scene(scene),
    m_items(items)
{
    Q_ASSERT(m_scene);
}

void SelectionCommand::redo()
{
    m_scene->clearSelection();
    foreach(QGraphicsItem *item, m_items) {
        item->setSelected(true);
    }
}

void SelectionCommand::undo()
{
    redo();
}
