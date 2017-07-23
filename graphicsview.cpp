#include <QMouseEvent>

#include "graphicsview.hpp"

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView (parent)
{
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void GraphicsView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event);

    if (event->button() == Qt::LeftButton) {
        auto x = event->x();
        auto y = event->y();
        emit mouse_click(x, y);
    }
}
