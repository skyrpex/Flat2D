#ifndef CREATECOMMAND_HPP
#define CREATECOMMAND_HPP

#include <QUndoCommand>

class QGraphicsItem;

class CreateCommand : public QUndoCommand
{
public:
    CreateCommand(QGraphicsItem *item, QGraphicsItem *parent);

    void redo();
    void undo();

private:
    QGraphicsItem *m_item;
    QGraphicsItem *m_parent;
};

#endif // CREATECOMMAND_HPP
