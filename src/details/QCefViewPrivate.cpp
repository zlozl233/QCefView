#include "QCefViewPrivate.h"

#pragma region std_headers
#include <stdexcept>
#pragma endregion std_headers

#pragma region qt_headers
#include <QPainter>
#include <QPlatformSurfaceEvent>
#include <QVBoxLayout>
#include <QWindow>
#include <QtDebug>
#pragma endregion qt_headers

#pragma region cef_headers
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_frame.h>
#include <include/cef_parser.h>
#pragma endregion cef_headers

#include <CefViewCoreProtocol.h>

#include "CCefClientDelegate.h"
#include "QCefContext.h"
#include "ValueConvertor.h"

QCefViewPrivate::QCefViewPrivate(QCefView* view, const QString& url, const QCefSettingPrivate* setting)
  : q_ptr(view)
  , pContext_(QCefContext::instance()->d_func())
  , pCefBrowser_(nullptr)
{
  createBrowser(view, url, setting);
}

QCefViewPrivate::~QCefViewPrivate()
{
  destroyBrowser();
}

void
QCefViewPrivate::createBrowser(QCefView* view, const QString url, const QCefSettingPrivate* setting)
{
  // Set window info
  CefWindowInfo window_info;
  window_info.SetAsWindowless((CefWindowHandle)(view->window()->winId()));

  // create the browser object
  CefBrowserSettings browserSettings;
  if (setting)
    setting->CopyToCefBrowserSettings(browserSettings);

  auto pCefBrowser = CefBrowserHost::CreateBrowserSync(window_info,         // window info
                                                       pContext_->pClient_, // handler
                                                       url.toStdString(),   // url
                                                       browserSettings,     // settings
                                                       nullptr,
                                                       CefRequestContext::GetGlobalContext());
  if (!pCefBrowser) {
    Q_ASSERT_X(pCefBrowser, "QCefViewPrivate::createBrowser", "Failed to create cer browser");
    return;
  }

  // register view to client delegate
  pContext_->pClientDelegate_->insertBrowserViewMapping(pCefBrowser, this);
  pCefBrowser_ = pCefBrowser;

  // close the browser when app is doubt to exit
  connect(QCoreApplication::instance(), SIGNAL(onAboutToQuit()), this, SLOT(onAboutToQuit()));
  return;
}

void
QCefViewPrivate::closeBrowser()
{
  if (!pCefBrowser_)
    return;

  // clean resource
  pCefBrowser_->StopLoad();
  pCefBrowser_->GetHost()->CloseBrowser(true);

  // remove from delegate mapping
  pContext_->pClientDelegate_->removeBrowserViewMapping(pCefBrowser_);

  pCefBrowser_ = nullptr;
}

void
QCefViewPrivate::destroyBrowser()
{
  // close again
  closeBrowser();
}

void
QCefViewPrivate::onAboutToQuit()
{
  destroyBrowser();
}

int
QCefViewPrivate::browserId()
{
  if (pCefBrowser_)
    return pCefBrowser_->GetIdentifier();

  return -1;
}

void
QCefViewPrivate::navigateToString(const QString& content)
{
  if (pCefBrowser_) {
    std::string data = content.toStdString();
    data = CefURIEncode(CefBase64Encode(data.c_str(), data.size()), false).ToString();
    data = "data:text/html;base64," + data;
    pCefBrowser_->GetMainFrame()->LoadURL(data);
  }
}

void
QCefViewPrivate::navigateToUrl(const QString& url)
{
  if (pCefBrowser_) {
    CefString strUrl;
    strUrl.FromString(url.toStdString());
    pCefBrowser_->GetMainFrame()->LoadURL(strUrl);
  }
}

bool
QCefViewPrivate::browserCanGoBack()
{
  if (pCefBrowser_)
    return pCefBrowser_->CanGoBack();

  return false;
}

bool
QCefViewPrivate::browserCanGoForward()
{
  if (pCefBrowser_)
    return pCefBrowser_->CanGoForward();

  return false;
}

void
QCefViewPrivate::browserGoBack()
{
  if (pCefBrowser_)
    pCefBrowser_->GoBack();
}

void
QCefViewPrivate::browserGoForward()
{
  if (pCefBrowser_)
    pCefBrowser_->GoForward();
}

bool
QCefViewPrivate::browserIsLoading()
{
  if (pCefBrowser_)
    return pCefBrowser_->IsLoading();

  return false;
}

void
QCefViewPrivate::browserReload()
{
  if (pCefBrowser_)
    pCefBrowser_->Reload();
}

void
QCefViewPrivate::browserStopLoad()
{
  if (pCefBrowser_)
    pCefBrowser_->StopLoad();
}

bool
QCefViewPrivate::triggerEvent(const QString& name,
                              const QVariantList& args,
                              int frameId /*= CefViewBrowserHandler::MAIN_FRAME*/)
{
  if (!name.isEmpty()) {
    return sendEventNotifyMessage(frameId, name, args);
  }

  return false;
}

bool
QCefViewPrivate::responseQCefQuery(const QCefQuery& query)
{
  if (pContext_ && pContext_->pClient_) {
    CefString res;
    res.FromString(query.response().toStdString());
    return pContext_->pClient_->ResponseQuery(query.id(), query.result(), res, query.error());
  }
  return false;
}

void
QCefViewPrivate::notifyMoveOrResizeStarted()
{
  if (pCefBrowser_) {
    CefRefPtr<CefBrowserHost> host = pCefBrowser_->GetHost();
    if (host)
      host->NotifyMoveOrResizeStarted();
  }
}

bool
QCefViewPrivate::sendEventNotifyMessage(int frameId, const QString& name, const QVariantList& args)
{
  CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create(TRIGGEREVENT_NOTIFY_MESSAGE);
  CefRefPtr<CefListValue> arguments = msg->GetArgumentList();

  //** arguments(CefValueList)
  //** +------------+
  //** | event name |
  //** | event arg1 |
  //** | event arg2 |
  //** | event arg3 |
  //** | event arg4 |
  //** |    ...     |
  //** |    ...     |
  //** |    ...     |
  //** |    ...     |
  //** +------------+
  int idx = 0;
  CefString eventName = name.toStdString();
  arguments->SetString(idx++, eventName);
  for (auto& qV : args) {
    auto cVal = CefValue::Create();
    ValueConvertor::QVariantToCefValue(cVal, &qV);
    arguments->SetValue(idx++, cVal);
  }

  return pContext_->pClient_->TriggerEvent(pCefBrowser_, frameId, msg);
}

void
QCefViewPrivate::setFocus(bool focus)
{
  if (pCefBrowser_)
    pCefBrowser_->GetHost()->SetFocus(focus);
}

void
QCefViewPrivate::paintCefFrameBuffer(const uchar* buf, int width, int height)
{
  Q_Q(QCefView);
  QImage newFrame(buf, width, height, QImage::Format_ARGB32);

  qCefFrameBuffer_ = QImage(width, height, QImage::Format_ARGB32);
  QPainter painter(&qCefFrameBuffer_);
  painter.drawImage(0, 0, newFrame);

  q->update();
}

void
QCefViewPrivate::updateDragCursor(int operation)
{
  qDebug() << "cursor operation";
}

void
QCefViewPrivate::onPaint(QPainter& painter)
{
  if (!pCefBrowser_ || qCefFrameBuffer_.isNull())
    return;

  painter.drawImage(0, 0, qCefFrameBuffer_);
}

void
QCefViewPrivate::onResize()
{
  if (!pCefBrowser_)
    return;

  pCefBrowser_->GetHost()->WasResized();
  pCefBrowser_->GetHost()->NotifyMoveOrResizeStarted();
}

void
QCefViewPrivate::onKeyEvent(QKeyEvent* event, bool down)
{
  if (!pCefBrowser_)
    return;

  CefKeyEvent e;
  e.type = down ? KEYEVENT_KEYDOWN : KEYEVENT_KEYUP;
  e.windows_key_code = event->key();
  e.native_key_code = event->nativeScanCode();
  e.is_system_key = false;
  e.character = event->key();
  // e.unmodified_character = 0;
  e.focus_on_editable_field = false;
  e.modifiers = event->nativeModifiers();

  pCefBrowser_->GetHost()->SendKeyEvent(e);
}

void
QCefViewPrivate::onMouseMoveEvent(QMouseEvent* event)
{
  if (!pCefBrowser_)
    return;

  CefMouseEvent e;
  e.x = event->pos().x();
  e.y = event->pos().y();
  pCefBrowser_->GetHost()->SendMouseMoveEvent(e, false);
}

void
QCefViewPrivate::onMouseClickEvent(QMouseEvent* event, bool up)
{
  if (!pCefBrowser_)
    return;

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

  pCefBrowser_->GetHost()->SendMouseClickEvent(e, t, up, 1);
}

void
QCefViewPrivate::onMouseWheelEvent(QWheelEvent* event)
{
  if (!pCefBrowser_)
    return;

  CefMouseEvent e;
  e.x = event->position().x();
  e.y = event->position().y();

  QPoint numPixels = event->pixelDelta();
  QPoint numDegrees = event->angleDelta() / 8;
  QPoint delta;

  if (!numPixels.isNull()) {
    delta = numPixels;
  } else if (!numDegrees.isNull()) {
    delta = numDegrees / 15;
  }

  // pCefBrowser_->GetHost()->SendMouseWheelEvent(e, 1, 1);
}

void
QCefViewPrivate::onFocusEvent(QFocusEvent* event, bool focusIn)
{
  if (!pCefBrowser_)
    return;

  pCefBrowser_->GetHost()->SendFocusEvent(focusIn);
}
