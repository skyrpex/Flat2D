#include "TranslateCommand.hpp"
#include <QGraphicsItem>

TranslateCommand::TranslateCommand(QGraphicsItem *item, QPointF oldPos, QPointF newPos) :
    m_item(item),
    m_oldPos(oldPos),
    m_newPos(newPos)
{
}

void TranslateCommand::redo()
{
    m_item->setPos(m_newPos);
}

void TranslateCommand::undo()
{
    m_item->setPos(m_oldPos);
}

