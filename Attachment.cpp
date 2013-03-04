#include "Attachment.hpp"
#include "Arrow.hpp"
#include "Bone.hpp"
#include "Application.hpp"
#include <QDebug>
#include <QGraphicsScene>
#include <QxMeshDef>
#include <QxMesh>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

Attachment::Attachment(const QPixmap &pixmap)
    : QGraphicsPixmapItem(pixmap)
    , m_bone(NULL)
    , m_arrow(new Arrow(NULL, this))
    , m_localRotation(0)
    , m_localScale(1)
{
    setFlags(ItemIsSelectable | ItemIsMovable);
    setZValue(-1);
    setTransformationMode(Qt::SmoothTransformation);
    setAcceptHoverEvents(true);

    QPointF offset = -QPointF(static_cast<qreal>(pixmap.width()), static_cast<qreal>(pixmap.height()))/2;
    setOffset(offset);

    foreach(QxMeshDef meshDef, QxMeshDef::fromImage(pixmap.toImage())) {
        meshDef.simplifyByTolerance(1);
        m_shape.addPolygon(meshDef.boundary);
        m_shape.closeSubpath();
    }
    m_shape.translate(offset);
}

Attachment::~Attachment()
{
    delete m_arrow;
}

Bone *Attachment::bone() const
{
    return m_bone;
}

void Attachment::setBone(Bone *bone)
{
    m_bone = bone;
    m_arrow->setStartItem(bone);
}

Arrow *Attachment::arrow() const
{
    return m_arrow;
}

QPointF Attachment::localPos() const
{
    return m_localPos;
}

qreal Attachment::localRotation() const
{
    return m_localRotation;
}

qreal Attachment::localScale() const
{
    return m_localScale;
}

void Attachment::setLocalPos(const QPointF &pos)
{
    m_localPos = pos;
}

void Attachment::setLocalRotation(qreal rotation)
{
    m_localRotation = rotation;
}

void Attachment::setLocalScale(qreal scale)
{
    m_localScale = scale;
}

QPainterPath Attachment::shape() const
{
    return m_shape;
}

QVariant Attachment::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemSceneChange) {
        if(scene()) {
            scene()->removeItem(m_arrow);
        }

        QGraphicsScene *scene = value.value<QGraphicsScene *>();
        if(scene) {
            scene->addItem(m_arrow);
        }
    }

    return QGraphicsPixmapItem::itemChange(change, value);
}

void Attachment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Default paint (unselected)
    QStyleOptionGraphicsItem myOption(*option);
    myOption.state &= ~QStyle::State_Selected;
    QGraphicsPixmapItem::paint(painter, &myOption, widget);

    // If selected, draw shape
    bool isSelected = (option->state & QStyle::State_Selected);
    bool isMouseOver = (option->state & QStyle::State_MouseOver);
    if(isSelected || isMouseOver) {
        Application::Color appColor = (isMouseOver? Application::MouseOverGraphicsItem
                                                  : Application::SelectedGraphicsItem);
        painter->setPen(QPen(qApp->color(appColor)));
        painter->drawPath(shape());
    }
}
