#ifndef TEXTUREICONPROVIDER_HPP
#define TEXTUREICONPROVIDER_HPP

#include <QFileIconProvider>

class TextureIconProvider : public QFileIconProvider 
{
public:
    TextureIconProvider();

    QIcon icon(const QFileInfo &info) const;
};

#endif // TEXTUREICONPROVIDER_HPP
