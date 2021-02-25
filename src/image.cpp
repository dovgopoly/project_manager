#include "../includes/image.hpp"

Image::Image(const QString &image_path, const int width, const int height, QWidget *parent)
    : QLabel{parent} {
    setScaledContents(true);
    setPixmap(QPixmap::fromImage(QImage{image_path}).scaled(
        width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
