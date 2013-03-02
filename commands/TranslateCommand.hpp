#ifndef TRANSLATECOMMAND_HPP
#define TRANSLATECOMMAND_HPP

#include <QUndoCommand>
#include <QPointF>

class QGraphicsItem;

class TranslateCommand : public QUndoCommand
{
public:
    TranslateCommand(QGraphicsItem *item, QPointF oldPos, QPointF newPos);

    void redo();
    void undo();

private:
    QGraphicsItem *m_item;
    QPointF m_oldPos;
    QPointF m_newPos;
};

#endif // TRANSLATECOMMAND_HPP
