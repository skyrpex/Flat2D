#include "ScaleCommand.hpp"
#include <QGraphicsItem>

ScaleCommand::ScaleCommand(QGraphicsItem *item, qreal oldScale, qreal newScale) :
    m_item(item),
    m_oldScale(oldScale),
    m_newScale(newScale)
{
}

void ScaleCommand::redo()
{
    m_item->setScale(m_newScale);
}

void ScaleCommand::undo()
{
    m_item->setScale(m_oldScale);
}
