#include "Bone.hpp"
#include "Attachment.hpp"
#include "Arrow.hpp"
#include "Application.hpp"
#include <QGraphicsScene>
#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <math.h>

static const qreal DefaultBoneLength = 80.0;
static const qreal DefaultBoneHeight = 5.0;

static const qreal DefaultJointWidth = 15.0;
static const QRectF JointRect(-DefaultJointWidth/2, -DefaultJointWidth/2, DefaultJointWidth, DefaultJointWidth);

Bone::Bone(const QString &name, Bone *parent)
    : QGraphicsPathItem(parent)
    , m_arrow(new Arrow(parent, this))
    , m_isJoint(true)
    , m_name(name)
    , m_sceneRotation(0)
    , m_sceneScale(1)
    , m_boneLength(0)
{
    setFlags(ItemIsSelectable | ItemIsMovable | ItemIsPanel | ItemDoesntPropagateOpacityToChildren);
    setAcceptHoverEvents(true);
    setBrush(Qt::lightGray);
    setPen(QPen(Qt::black, 0));

    if(parent && parent->scene()) {
        parent->scene()->addItem(m_arrow);
    }

    setJoint(true);
}

Bone::~Bone()
{
    qDeleteAll(attachments());
    delete m_arrow;
}

Bone *Bone::parentBone() const
{
    return dynamic_cast<Bone *>(parentItem());
}

QList<Bone *> Bone::childBones() const
{
    QList<Bone *> childBones;
    foreach(QGraphicsItem *child, childItems()) {
        Bone *bone = dynamic_cast<Bone *>(child);
        if(bone) {
            childBones << bone;
        }
    }
    return childBones;
}

QString Bone::name() const
{
    return m_name;
}

QList<Attachment *> Bone::attachments() const
{
    return m_attachments;
}

void Bone::addAttachment(Attachment *attachment)
{
    Q_ASSERT( attachment && !m_attachments.contains(attachment) );

    if(attachment->bone()) {
        attachment->bone()->removeAttachment(attachment);
    }

    attachment->setBone(this);
    m_attachments << attachment;
}

void Bone::removeAttachment(Attachment *attachment)
{
    Q_ASSERT( attachment && m_attachments.contains(attachment) );

    attachment->setBone(NULL);
    m_attachments.removeOne(attachment);
}

void Bone::mapAttachmentsToScene()
{
    m_sceneRotation = rotation();
    m_sceneScale = scale();
    if(parentBone()) {
        m_sceneRotation += parentBone()->m_sceneRotation;
        m_sceneScale *= parentBone()->m_sceneScale;
    }

    foreach(Attachment *attachment, m_attachments) {
        attachment->setPos(mapToScene(attachment->localPos()));
        attachment->setRotation(attachment->localRotation() + m_sceneRotation);
        attachment->setScale(attachment->localScale() * m_sceneScale);
    }

    foreach(Bone *child, childBones()) {
        child->mapAttachmentsToScene();
    }
}

void Bone::mapAttachmentsFromScene() const
{
    foreach(Attachment *attachment, m_attachments) {
        attachment->setLocalPos(mapFromScene(attachment->pos()));
        attachment->setLocalRotation(attachment->rotation() - m_sceneRotation);
        attachment->setLocalScale(attachment->scale() / m_sceneScale);
    }

    foreach(Bone *child, childBones()) {
        child->mapAttachmentsFromScene();
    }
}

void Bone::setScenePos(const QPointF &scenePos)
{
    setPos(mapFromScene(scenePos));
}

void Bone::setSceneRotation(qreal sceneRotation)
{
    Bone *parent = parentBone();
    if(parent) {
        sceneRotation -= parent->m_sceneRotation;
    }
    setRotation(sceneRotation);
}

void Bone::setSceneScale(qreal sceneScale)
{
    Bone *parent = parentBone();
    if(parent) {
        sceneScale /= parent->m_sceneScale;
    }
    setScale(sceneScale);
}

void Bone::setScaleFromLength(qreal length)
{
    if(length < 10) {
        setJoint(true);
        setScale(1);
    }
    else {
        setJoint(false);
        setScale(length / DefaultBoneLength);
    }
}

void Bone::setScaleFromSceneLength(qreal sceneLength)
{
    Bone *parent = parentBone();
    if(parent) {
        sceneLength /= parent->m_sceneScale;
    }
    setScaleFromLength(sceneLength);
}

qreal Bone::sceneRotation() const
{
    return m_sceneRotation;
}

QPointF Bone::scenePeakPos() const
{
    return mapToScene(QPointF(m_boneLength, 0));
}

void Bone::setBoneLength(qreal length)
{
    bool isJoint = (length < DefaultJointWidth);
    setJoint(isJoint);

    m_boneLength = length;
}

void Bone::setBoneSceneLength(qreal sceneLength)
{
    Bone *parent = parentBone();
    if(parent) {
        sceneLength /= parent->m_sceneScale;
    }
    setBoneLength(sceneLength / scale());
}

QVariant Bone::itemChange(GraphicsItemChange change, const QVariant &value)
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
    else if(change == ItemParentHasChanged) {
        m_arrow->setStartItem(parentItem());
    }

    return QGraphicsPathItem::itemChange(change, value);
}

void Bone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor penColor;

    bool isSelected = (option->state & QStyle::State_Selected);
    bool isMouseOver = (option->state & QStyle::State_MouseOver);
    if(isMouseOver) {
        penColor = qApp->color(Application::MouseOverGraphicsItem);
    }
    else if(isSelected) {
        penColor = qApp->color(Application::SelectedGraphicsItem);
    }

    painter->setBrush(brush());
    painter->setPen(QPen(penColor, 0));
    painter->drawPath(shape());
}

QPolygonF Bone::jointPolygon() const
{
    return JointRect;
}

void Bone::setJoint(bool isJoint)
{
    m_isJoint = isJoint;

    QPainterPath path;
    path.addPolygon(isJoint? jointPolygon() : bonePolygon());
    setPath(path);
}

Arrow *Bone::arrow() const
{
    return m_arrow;
}

QPolygonF Bone::bonePolygon() const
{
    qreal height = 0.9*DefaultBoneHeight*log(0.7 * (m_boneLength*DefaultBoneHeight) / DefaultBoneLength);
    height = qMax(height, DefaultBoneHeight);

    qreal offset = m_boneLength / 8.0;
    offset = qMin(offset, 10.0);
    return QPolygonF() << QPointF(0, 0)
                       << QPointF(offset, height)
                       << QPointF(m_boneLength, 0)
                       << QPointF(offset, -height)
                       << QPointF(0, 0);
}

//QPainterPath Bone::bonePath() const
//{
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addPolygon(bonePolygon());
//    path.closeSubpath();
//    path.addEllipse(QPointF(), DefaultJointWidth/2, DefaultJointWidth/2);
//    return path.simplified();
//}

//QPainterPath Bone::shape() const
//{
//}
