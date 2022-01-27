#include "CCefClientDelegate.h"

#pragma region qt_headers
#include <QPoint>
#include <QRect>
#pragma endregion qt_headers

#include "QCefViewPrivate.h"
#include "ValueConvertor.h"

#include <QCefView.h>

QCefViewPrivate*
CCefClientDelegate::take(CefRefPtr<CefBrowser>& browser)
{
  if (!browser)
    return nullptr;
  auto it = view_map_.find(browser->GetIdentifier());
  if (it == view_map_.end())
    return nullptr;

  return it->second;
}

void
CCefClientDelegate::insertBrowserViewMapping(CefRefPtr<CefBrowser>& browser, QCefViewPrivate* view)
{
  auto id = browser->GetIdentifier();
  view_map_[id] = view;
}

void
CCefClientDelegate::removeBrowserViewMapping(CefRefPtr<CefBrowser>& browser)
{
  auto id = browser->GetIdentifier();
  view_map_.erase(id);
}

void
CCefClientDelegate::loadingStateChanged(CefRefPtr<CefBrowser>& browser,
                                        bool isLoading,
                                        bool canGoBack,
                                        bool canGoForward)
{
  auto p = take(browser);
  if (p)
    p->q_ptr->loadingStateChanged(isLoading, canGoBack, canGoForward);
}

void
CCefClientDelegate::loadStart(CefRefPtr<CefBrowser>& browser)
{
  auto p = take(browser);
  if (p)
    p->q_ptr->loadStart();
}

void
CCefClientDelegate::loadEnd(CefRefPtr<CefBrowser>& browser, int httpStatusCode)
{
  auto p = take(browser);
  if (p)
    p->q_ptr->loadEnd(httpStatusCode);
}

void
CCefClientDelegate::loadError(CefRefPtr<CefBrowser>& browser,
                              int errorCode,
                              const std::string& errorMsg,
                              const std::string& failedUrl,
                              bool& handled)
{
  auto p = take(browser);
  if (p) {
    auto msg = QString::fromStdString(errorMsg);
    auto url = QString::fromStdString(failedUrl);
    p->q_ptr->loadError(errorCode, msg, url, handled);
  }
}

void
CCefClientDelegate::draggableRegionChanged(CefRefPtr<CefBrowser>& browser,
                                           const std::vector<CefDraggableRegion>& regions)
{
  auto p = take(browser);
  if (!p)
    return;

  // Determine new draggable region.
  QRegion draggableRegion;
  QRegion nonDraggableRegion;
  std::vector<CefDraggableRegion>::const_iterator it = regions.begin();
  for (; it != regions.end(); ++it) {
    if (it->draggable) {
      draggableRegion += QRegion(it->bounds.x, it->bounds.y, it->bounds.width, it->bounds.height);
    } else {
      nonDraggableRegion += QRegion(it->bounds.x, it->bounds.y, it->bounds.width, it->bounds.height);
    }
  }

  p->q_ptr->draggableRegionChanged(draggableRegion, nonDraggableRegion);
}

void
CCefClientDelegate::consoleMessage(CefRefPtr<CefBrowser>& browser, const std::string& message, int level)
{
  auto p = take(browser);
  if (p) {
    auto msg = QString::fromStdString(message);
    p->q_ptr->consoleMessage(msg, level);
  }
}

void
CCefClientDelegate::takeFocus(CefRefPtr<CefBrowser>& browser, bool next)
{
  auto p = take(browser);
  if (p) {
    p->q_ptr->takeFocus(next);
  }
}

bool
CCefClientDelegate::setFocus(CefRefPtr<CefBrowser>& browser)
{
  auto p = take(browser);
  if (p) {
    return false;
  }

  return true;
}

void
CCefClientDelegate::gotFocus(CefRefPtr<CefBrowser>& browser)
{
  auto p = take(browser);
  if (p) {
    p->q_ptr->setFocus();
  }
}

void
CCefClientDelegate::processUrlRequest(const std::string& url)
{
  // deprecated feature
  // auto view = take(browser);
  // if (view) {
  //  auto u = QString::fromStdString(url);
  //  view->onQCefUrlRequest(u);
  //}
}

void
CCefClientDelegate::processQueryRequest(CefRefPtr<CefBrowser>& browser,
                                        int frameId,
                                        const std::string& request,
                                        const int64_t query_id)
{
  auto p = take(browser);
  if (p) {
    auto browserId = browser->GetIdentifier();
    auto req = QString::fromStdString(request);
    p->q_ptr->cefQueryRequest(browserId, frameId, QCefQuery(req, query_id));
  }
}

void
CCefClientDelegate::invokeMethodNotify(CefRefPtr<CefBrowser>& browser,
                                       int frameId,
                                       const std::string& method,
                                       const CefRefPtr<CefListValue>& arguments)
{
  auto p = take(browser);
  if (!p)
    return;

  auto m = QString::fromStdString(method);
  QVariantList args;
  for (int i = 0; i < arguments->GetSize(); i++) {
    QVariant qV;
    auto cV = arguments->GetValue(i);
    ValueConvertor::CefValueToQVariant(&qV, cV);
    args.push_back(qV);
  }

  auto browserId = browser->GetIdentifier();
  p->q_ptr->invokeMethod(browserId, frameId, m, args);
}

bool
CCefClientDelegate::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
  auto p = take(browser);
  if (!p) {
    return false;
  }

  QRect rcWindow = p->q_ptr->window()->frameGeometry();
  rect.Set(rcWindow.left(), rcWindow.right(), rcWindow.width(), rcWindow.height());
  return true;
}

void
CCefClientDelegate::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
  auto p = take(browser);
  if (!p) {
    rect.Set(0, 0, 1, 1);
    return;
  }

  QRect rcView = p->q_ptr->frameGeometry();
  QPoint ptScreen = p->q_ptr->mapToGlobal(rcView.topLeft());
  rect.Set(ptScreen.x(), ptScreen.y(), rcView.width(), rcView.height());
}

bool
CCefClientDelegate::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY)
{
  auto p = take(browser);
  if (!p) {
    return false;
  }

  QPoint ptScreen = p->q_ptr->mapToGlobal(QPoint(viewX, viewY));
  screenX = ptScreen.x();
  screenY = ptScreen.y();
  return true;
}

bool
CCefClientDelegate::GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& screen_info)
{
  auto p = take(browser);
  if (!p) {
    return false;
  }

  return false;
}

void
CCefClientDelegate::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
{}

void
CCefClientDelegate::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
{}

void
CCefClientDelegate::OnPaint(CefRefPtr<CefBrowser> browser,
                            CefRenderHandler::PaintElementType type,
                            const CefRenderHandler::RectList& dirtyRects,
                            const void* buffer,
                            int width,
                            int height)
{
  auto p = take(browser);
  if (!p) {
    return;
  }

  p->paintCefFrameBuffer(static_cast<const uchar*>(buffer), width, height);
}
