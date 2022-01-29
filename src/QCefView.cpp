#include <QCefView.h>

#pragma region qt_headers
#include <QDebug>
#include <QPaintDevice>
#include <QPainter>
#include <QPoint>
#include <QResizeEvent>
#pragma endregion qt_headers

#include <QCefContext.h>

#include "details/QCefEventPrivate.h"
#include "details/QCefViewPrivate.h"

QCefView::QCefView(const QString url, const QCefSetting* setting, QWidget* parent /*= 0*/)
  : QWidget(parent)
  , d_ptr(new QCefViewPrivate(this, url, setting ? setting->d_func() : nullptr))
{
  setMouseTracking(true);
  setFocusPolicy(Qt::StrongFocus);
  connect(this, SIGNAL(takeFocus(bool)), this, SLOT(onCefFocusEvent(bool)));
}

QCefView::QCefView(QWidget* parent /*= 0*/)
  : QCefView("about:blank", nullptr, parent)
{}

QCefView::~QCefView() {}

int
QCefView::browserId()
{
  Q_D(QCefView);

  return d->browserId();
}

void
QCefView::navigateToString(const QString& content)
{
  Q_D(QCefView);

  d->navigateToString(content);
}

void
QCefView::navigateToUrl(const QString& url)
{
  Q_D(QCefView);

  d->navigateToUrl(url);
}

bool
QCefView::browserCanGoBack()
{
  Q_D(QCefView);

  return d->browserCanGoBack();
}

bool
QCefView::browserCanGoForward()
{
  Q_D(QCefView);

  return d->browserCanGoForward();
}

void
QCefView::browserGoBack()
{
  Q_D(QCefView);

  d->browserGoBack();
}

void
QCefView::browserGoForward()
{
  Q_D(QCefView);

  d->browserGoForward();
}

bool
QCefView::browserIsLoading()
{
  Q_D(QCefView);

  return d->browserIsLoading();
}

void
QCefView::browserReload()
{
  Q_D(QCefView);

  d->browserReload();
}

void
QCefView::browserStopLoad()
{
  Q_D(QCefView);

  d->browserStopLoad();
}

bool
QCefView::triggerEvent(const QCefEvent& event)
{
  Q_D(QCefView);

  return d->triggerEvent(event.eventName(), event.d_func()->args, CefViewBrowserClient::MAIN_FRAME);
}

bool
QCefView::triggerEvent(const QCefEvent& event, int frameId)
{
  Q_D(QCefView);

  return d->triggerEvent(event.eventName(), event.d_func()->args, frameId);
}

bool
QCefView::broadcastEvent(const QCefEvent& event)
{
  Q_D(QCefView);

  return d->triggerEvent(event.eventName(), event.d_func()->args, CefViewBrowserClient::ALL_FRAMES);
}

bool
QCefView::responseQCefQuery(const QCefQuery& query)
{
  Q_D(QCefView);

  return d->responseQCefQuery(query);
}

void
QCefView::onCefFocusEvent(bool next)
{
  if (!QWidget::focusNextPrevChild(next)) {
    qWarning() << "Failed to focusNextPrevChild(" << next << ")";
  }
}

void
QCefView::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);
  QPainter painter(this);

  Q_D(QCefView);
  d->onPaint(painter);
}

void
QCefView::resizeEvent(QResizeEvent* event)
{
  Q_D(QCefView);
  d->onResize();
}

bool
QCefView::focusNextPrevChild(bool next)
{
  return false;
}

void
QCefView::keyPressEvent(QKeyEvent* event)
{
  Q_D(QCefView);
  d->onKeyEvent(event, true);
}

void
QCefView::keyReleaseEvent(QKeyEvent* event)
{
  Q_D(QCefView);
  d->onKeyEvent(event, false);
}

void
QCefView::mouseMoveEvent(QMouseEvent* event)
{
  Q_D(QCefView);
  d->onMouseMoveEvent(event);
}

void
QCefView::mousePressEvent(QMouseEvent* event)
{
  Q_D(QCefView);
  d->onMouseClickEvent(event, false);
}

void
QCefView::mouseReleaseEvent(QMouseEvent* event)
{
  Q_D(QCefView);
  d->onMouseClickEvent(event, true);
}

void
QCefView::wheelEvent(QWheelEvent* event)
{
  Q_D(QCefView);
  d->onMouseWheelEvent(event);
}

void
QCefView::focusInEvent(QFocusEvent* event)
{
  Q_D(QCefView);
  d->onFocusEvent(event, true);
}

void
QCefView::focusOutEvent(QFocusEvent* event)
{
  Q_D(QCefView);
  d->onFocusEvent(event, false);
}
