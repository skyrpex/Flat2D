#include "Arrow.hpp"
#include "Bone.hpp"
#include <math.h>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

const qreal Pi = 3.14;

Arrow::Arrow(QGraphicsItem *startItem, QGraphicsItem *endItem, bool centerP2,
             QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
    , m_arrowSize(5),
      m_centerP2(centerP2)
{
    myStartItem = startItem;
    myEndItem = endItem;
    myColor = Qt::black;
    setPen(QPen(myColor, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(-1000);
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::updatePosition()
{
    QLineF line(p1(), p2());
    setLine(line);
}

void Arrow::setArrowSize(qreal arrowSize)
{
    m_arrowSize = arrowSize;
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *)
{
    if(myStartItem && myEndItem && !myStartItem->collidesWithItem(myEndItem)) {
        QLineF centerLine(p1(), p2());
        QPolygonF endpolygon = myEndItem->mapToScene(myEndItem->shape()).toFillPolygon();
        QPointF startPoint = intersectionPoint(centerLine, endpolygon);
        setLine(QLineF(startPoint, p1()));
    }

    QPen myPen = pen();
    myPen.setColor(myColor);
    painter->setPen(myPen);
    painter->setBrush(myColor);
    painter->drawLine(line());
    paintArrow(painter, line(), m_arrowSize);
}

QPointF Arrow::p1() const
{
    if(!myStartItem) {
        return QPointF();
    }

    Bone *bone = dynamic_cast<Bone *>(myStartItem);
    return bone? bone->scenePeakPos() : myStartItem->scenePos();
}

QPointF Arrow::p2() const
{
    if(!myEndItem) {
        return QPointF();
    }

    if(m_centerP2) {
        return myEndItem->sceneBoundingRect().center();
    }

    return myEndItem->scenePos();
}

QPointF Arrow::intersectionPoint(const QLineF &centerLine, const QPolygonF &polygon) const
{
    QPointF p1 = polygon.first();
    for (int i = 1; i < polygon.count(); ++i) {
        QPointF p2 = polygon.at(i);

        QPointF intersectPoint;
        QLineF::IntersectType intersectType = QLineF(p1, p2).intersect(centerLine, &intersectPoint);
        if(intersectType == QLineF::BoundedIntersection) {
            return intersectPoint;
        }
        p1 = p2;
    }

    return centerLine.p2();
}

void Arrow::paintArrow(QPainter *painter, const QLineF &line, qreal arrowSize)
{
    if(line.length() == 0) {
        return;
    }

    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0) {
        angle = (Pi * 2) - angle;
    }

    QPointF arrowP1 = line.p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    painter->drawPolygon(arrowHead);
}
