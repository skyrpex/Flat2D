#include "TextureIconProvider.hpp"
#include <QDebug>

TextureIconProvider::TextureIconProvider()
{
}

QIcon TextureIconProvider::icon(const QFileInfo &info) const
{
    if(info.isDir() || !info.isReadable() || info.suffix() != "png") {
        return QFileIconProvider::icon(info);
    }

    return QIcon(info.filePath());
}
