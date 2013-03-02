#include "Application.hpp"
#include <QUndoStack>
#include <stylehelper.h>
#include <manhattanstyle.h>

Application::Application(int argc, char **argv) :
    QApplication(argc, argv),
    m_undoStack(new QUndoStack(this))
{
    setOrganizationName("Remacu");
    setApplicationName("Flat2D");
    setApplicationVersion("Alpha");

    Manhattan::Utils::StyleHelper::setBaseColor(Qt::darkGray);
    setStyle(new ManhattanStyle("Manhattan"));
}

QUndoStack *Application::undoStack() const
{
    return m_undoStack;
}

QColor Application::color(Application::Color color) const
{
    switch(color) {
    case MouseOverGraphicsItem:
        return Qt::cyan;

    case SelectedGraphicsItem:
        return Qt::white;

    default:
        return QColor();
    }
}

QList<QString> Application::availableImageExtensions() const
{
    static const QList<QString> extensions = {"png"};
    return extensions;
}
