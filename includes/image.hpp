#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <QLabel>
#include <QUrl>
#include <QPainter>
#include <QPainterPath>

#include "api.hpp"
#include "image_loader.hpp"

class Image : public QLabel {
 Q_OBJECT
 public:
    enum : int {
        DisableAll = 0,
        RoundedCorners = 1 << 0,
        HighQuality = 1 << 1,
    };

    Image(const QString &image_path, int width, int height, int properties, QWidget *parent = nullptr);
    Image(const QUrl &url, int width, int height, int properties, QWidget *parent = nullptr);

 signals:
    void Clicked();
    void Updated();

 protected:
    void mousePressEvent(QMouseEvent *event) override;

 private slots:
    void ReceiveImage(const QByteArray &byte_array);

 private:
    QPixmap BuildPixmapFromImage(const QImage &image) const;
    QPixmap BuildPixmapWithRoundCorners(const QPixmap &source_pixmap) const;
    void BuildPixmapWithUrl(const QUrl &url) const;

    void SetImage(const QImage &image);

    int m_width;
    int m_height;
    int m_properties;
    QPixmap m_pixmap;

    ImageLoader *const m_image_loader{nullptr};
};

#endif