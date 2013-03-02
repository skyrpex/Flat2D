#include "RotateCommand.hpp"
#include <QGraphicsItem>

static const char Text[] = "Rotate";

RotateCommand::RotateCommand(QGraphicsItem *item, qreal oldRotation, qreal newRotation, QUndoCommand *parent) :
    QUndoCommand(Text, parent),
    m_item(item),
    m_oldRotation(oldRotation),
    m_newRotation(newRotation)
{
    Q_ASSERT(item);
}

void RotateCommand::redo()
{
    m_item->setRotation(m_newRotation);
}

void RotateCommand::undo()
{
    m_item->setRotation(m_oldRotation);
}
