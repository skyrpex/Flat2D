#ifndef SELECTIONCOMMAND_HPP
#define SELECTIONCOMMAND_HPP

#include <QUndoCommand>
#include <QList>

class QGraphicsScene;
class QGraphicsItem;

class SelectionCommand : public QUndoCommand
{
public:
    SelectionCommand(QGraphicsScene *scene, const QList<QGraphicsItem *> &items);

    void redo();
    void undo();

private:
    QGraphicsScene *m_scene;
    QList<QGraphicsItem *> m_items;
};

#endif // SELECTIONCOMMAND_HPP
