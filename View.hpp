#ifndef VIEW_HPP
#define VIEW_HPP

#include <QGraphicsView>
#include <QMap>

class Bone;
class Attachment;
class ResizeNode;
class Arrow;
class QMimeData;
class QFileInfo;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    enum TargetMode {
        BoneTargetMode,
        AttachmentTargetMode
    };

    enum EditMode {
        CreateEditMode,
        TransformEditMode,
        ParentEditMode
    };

    enum TransformMode {
        SelectTransformMode,
        RotateTransformMode,
        ScaleTransformMode
    };

    explicit View(QWidget *parent = 0);

public slots:
    void setBoneTargetMode();
    void setAttachmentTargetMode();

    void setTransformEditMode();
    void setCreateEditMode();
    void setParentEditMode();

    void setSelectTransformMode();
    void setRotateTransformMode();
    void setScaleTransformMode();

    void setParentalLinesVisible(bool visible);

signals:
    void switchedToBoneTargetMode();
    void switchedToAttachmentTargetMode();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);

    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Bone *topLevelBone(const QList<QGraphicsItem *> &items) const;
    QGraphicsItem *nearestItem(const QPointF &scenePos, const QList<QGraphicsItem *> &items) const;
    QGraphicsItem *targetItem(const QList<QGraphicsItem *> &items) const;
    QPointF cursorScenePos() const;

    QList<Bone *> bones() const;
    QList<Attachment *> attachments() const;

    void commitRotation();
    void commitScale();
    void commitTranslation();
    void commitBoneCreation();

    void cancelRotation();
    void cancelScale();
    void cancelBoneCreation();
    void cancelParentEdit();

//    bool isDescendant(Bone *root, Bone *bone) const;
    Bone *childToBone(Bone *root, Bone *bone) const;

    bool hasFiles(const QMimeData *mimeData) const;

    void loadAttachment(const QString &texturePath, const QPointF scenePos);

    QFileInfo findFreeFileInfo(const QFileInfo &fileInfo) const;
    QString importFile(const QString &filePath);

    Bone *m_root;

    TargetMode m_targetMode;
    EditMode m_editMode;
    TransformMode m_transformMode;

    QGraphicsEllipseItem *m_circleItem;

    QPointF m_hotSpot;

    qreal m_oldRotation;
    qreal m_oldLength;
    QGraphicsItem *m_targetItem;

    QGraphicsEllipseItem *m_ellipseItem;
    QGraphicsEllipseItem *m_thickEllipseItem;
    QGraphicsLineItem *m_lineItem;
    QGraphicsLineItem *m_solidLineItem;

    Bone *m_targetBone;

    QMap<QGraphicsItem *, qreal> m_rotationBackup;
    QMap<QGraphicsItem *, qreal> m_scaleBackup;
    QMap<QGraphicsItem *, QPointF> m_translationBackup;
    bool m_hasTranslated;

    bool m_parentalLinesVisible;

    Arrow *m_arrow;
    QGraphicsPathItem *m_parentalStartItem;
    QGraphicsPathItem *m_parentalEndItem;
};

#endif // VIEW_HPP
