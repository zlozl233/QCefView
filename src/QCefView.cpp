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
  if (!focusNextPrevChild(next)) {
    qWarning() << "Failed to focusNextPrevChild(" << next << ")";
  }
}

void
QCefView::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);

  Q_D(QCefView);

  if (d->qCefFrameBuffer_.isNull())
    return;

  QPainter painter(this);
  painter.drawImage(frameGeometry(), d->qCefFrameBuffer_);
}

void
QCefView::keyPressEvent(QKeyEvent* event)
{
  CefKeyEvent e;
  e.type = KEYEVENT_KEYDOWN;
  e.windows_key_code = event->key();
  e.native_key_code = event->nativeScanCode();
  e.is_system_key = false;
  e.character = event->nativeVirtualKey();
  // e.unmodified_character = 0;
  e.focus_on_editable_field = false;

  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendKeyEvent(e);
}

void
QCefView::keyReleaseEvent(QKeyEvent* event)
{
  CefKeyEvent e;
  e.type = KEYEVENT_KEYUP;
  e.windows_key_code = event->key();
  e.native_key_code = event->nativeScanCode();
  e.is_system_key = false;
  e.character = event->nativeVirtualKey();
  // e.unmodified_character = 0;
  e.focus_on_editable_field = false;

  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendKeyEvent(e);
}

void
QCefView::mouseMoveEvent(QMouseEvent* event)
{
  CefMouseEvent e;
  e.x = event->pos().x();
  e.y = event->pos().y();

  Q_D(QCefView);

  d->pCefBrowser_->GetHost()->SendMouseMoveEvent(e, false);
}

void
QCefView::mousePressEvent(QMouseEvent* event)
{
  CefMouseEvent e;
  e.x = event->pos().x();
  e.y = event->pos().y();

  CefBrowserHost::MouseButtonType t;
  switch (event->button()) {
    case Qt::LeftButton: {
      t = MBT_LEFT;
    } break;
    case Qt::RightButton: {
      t = MBT_RIGHT;
    } break;
    case Qt::MiddleButton: {
      t = MBT_MIDDLE;
    } break;
    default:
      break;
  }

  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendMouseClickEvent(e, t, false, 1);
}

void
QCefView::mouseReleaseEvent(QMouseEvent* event)
{
  CefMouseEvent e;
  e.x = event->pos().x();
  e.y = event->pos().y();

  CefBrowserHost::MouseButtonType t;
  switch (event->button()) {
    case Qt::LeftButton: {
      t = MBT_LEFT;
    } break;
    case Qt::RightButton: {
      t = MBT_RIGHT;
    } break;
    case Qt::MiddleButton: {
      t = MBT_MIDDLE;
    } break;
    default:
      break;
  }

  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendMouseClickEvent(e, t, true, 1);
}

void
QCefView::wheelEvent(QWheelEvent* event)
{
  CefMouseEvent e;
  e.x = event->position().x();
  e.y = event->position().y();

  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendMouseWheelEvent(e, event->pixelDelta().x(), event->pixelDelta().y());
}

void
QCefView::resizeEvent(QResizeEvent* event)
{
  QWidget::resizeEvent(event);

  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->WasResized();
}

void
QCefView::focusInEvent(QFocusEvent* event)
{
  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendFocusEvent(true);
}

void
QCefView::focusOutEvent(QFocusEvent* event)
{
  Q_D(QCefView);
  d->pCefBrowser_->GetHost()->SendFocusEvent(false);
}
