#ifndef ARROW_HPP
#define ARROW_HPP

#include <QGraphicsLineItem>

 class QGraphicsPolygonItem;
 class QGraphicsScene;
 class QRectF;
 class QGraphicsSceneMouseEvent;
 class QPainterPath;

 class Arrow : public QGraphicsLineItem
 {
 public:
     enum { Type = UserType + 4 };

     Arrow(QGraphicsItem *startItem, QGraphicsItem *endItem,
       QGraphicsItem *parent = 0);

     int type() const
         { return Type; }
     QRectF boundingRect() const;
     QPainterPath shape() const;
     void setColor(const QColor &color)
         { myColor = color; }
     QGraphicsItem *startItem() const
         { return myStartItem; }
     QGraphicsItem *endItem() const
         { return myEndItem; }

     void setStartItem(QGraphicsItem *item) {
         myStartItem = item;
     }
     void setEndItem(QGraphicsItem *item) {
         myEndItem = item;
     }

     void updatePosition();

 protected:
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget = 0);

 private:
     QPointF p1() const;
     QPointF p2() const;

     QGraphicsItem *myStartItem;
     QGraphicsItem *myEndItem;
     QColor myColor;
     QPolygonF arrowHead;
 };

#endif // ARROW_HPP
