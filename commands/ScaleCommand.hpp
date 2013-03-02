#ifndef SCALECOMMAND_HPP
#define SCALECOMMAND_HPP

#include <QUndoCommand>

class QGraphicsItem;

class ScaleCommand : public QUndoCommand
{
public:
    ScaleCommand(QGraphicsItem *item, qreal oldScale, qreal newScale);

    void redo();
    void undo();

private:
    QGraphicsItem *m_item;
    qreal m_oldScale;
    qreal m_newScale;
};

#endif // SCALECOMMAND_HPP
