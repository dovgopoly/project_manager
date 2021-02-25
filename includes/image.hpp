#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <QLabel>
#include <QUrl>

class Image : public QLabel {
 Q_OBJECT
 public:
    explicit Image(const QString &image_path, int width, int height, QWidget *parent = nullptr);
    ~Image() override = default;

 private:
    // TODO: ImageDownloader
};

#endif