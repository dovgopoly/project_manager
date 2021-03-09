#include <QPainter>

#include "../includes/image.hpp"
#include "../includes/config.hpp"

Image::Image(const QString &image_path, const int width, const int height, const int properties, QWidget *parent)
    : QLabel{parent}
    , m_width{width}
    , m_height{height}
    , m_properties{properties} {

    SetImage(QImage{image_path});
}

Image::Image(const QUrl &url, const int width, const int height, const int properties, QWidget *parent)
    : QLabel{parent}
    , m_width{width}
    , m_height{height}
    , m_properties{properties}
    , m_image_loader{new ImageLoader} {

    using namespace config;

    SetImage(QImage{UNKNOWN_IMAGE_PATH});
    BuildPixmapWithUrl(url);
}

QPixmap Image::BuildPixmapWithRoundCorners(const QPixmap &source_pixmap) const {
    const auto width = source_pixmap.size().width();
    const auto height = source_pixmap.size().height();

    QPixmap pixmap_with_round_corners{source_pixmap.size()};
    pixmap_with_round_corners.fill(Qt::transparent);

    QPainterPath painter_path;
    painter_path.addRoundedRect(0, 0, width, height, width, height);

    auto painter = QPainter(&pixmap_with_round_corners);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setClipPath(painter_path);
    painter.drawPixmap(0, 0, source_pixmap);

    return pixmap_with_round_corners;
}

QPixmap Image::BuildPixmapFromImage(const QImage &image) const {
    return QPixmap::fromImage(image).scaled(
        m_width,
        m_height,
        m_properties & Image::HighQuality ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio,
        m_properties & Image::HighQuality ? Qt::SmoothTransformation : Qt::FastTransformation);
}

void Image::BuildPixmapWithUrl(const QUrl &image_url) const {
    connect(m_image_loader, &ImageLoader::ResponseReady, this, &Image::ReceiveImage);
    m_image_loader->LoadImage(image_url);
}

void Image::SetImage(const QImage &image) {
    setScaledContents(true);
    setFixedSize(m_width, m_height);
    const auto image_pixmap = BuildPixmapFromImage(image);
    if (m_properties & Image::RoundedCorners) {
        setPixmap(BuildPixmapWithRoundCorners(image_pixmap));
    } else {
        setPixmap(image_pixmap);
    }
}

void Image::ReceiveImage(const QByteArray &byte_array) {
    QImage image;
    image.loadFromData(byte_array);
    SetImage(image);
}

void Image::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}
