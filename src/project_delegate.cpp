#include "../includes/project_delegate.hpp"
#include "../includes/project.hpp"
#include "../includes/project_widget.hpp"

ProjectDelegate::ProjectDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {
}

void ProjectDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) {
        return;
    }
    painter->save();
    auto *const project_widget = new ProjectWidget{qvariant_cast<Project>(index.model()->data(index, Qt::DisplayRole))};
    project_widget->resize(option.rect.size());
    painter->translate(option.rect.topLeft());
    if (option.state & QStyle::State_MouseOver) {
        project_widget->setStyleSheet(QString{"background-color: %1"}.arg("blue"));
    }
    project_widget->render(painter, QPoint(), QRegion(), QWidget::DrawChildren);
    painter->restore();
}

QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) {
        return QSize{};
    }
    auto *const project_widget = new ProjectWidget{qvariant_cast<Project>(index.model()->data(index, Qt::DisplayRole))};
    return project_widget->sizeHint();
}

bool ProjectDelegate::editorEvent(QEvent *event,
                                  QAbstractItemModel *model,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) {
    // TODO: implement
    return false;
}
