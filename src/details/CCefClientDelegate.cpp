﻿#include "CCefClientDelegate.h"

#include "ValueConvertor.h"

#include "QCefViewPrivate.h"

CCefClientDelegate::CCefClientDelegate() {}

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

bool
CCefClientDelegate::doClose(CefRefPtr<CefBrowser> browser)
{
  return false;
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
CCefClientDelegate::addressChanged(CefRefPtr<CefBrowser>& browser, int64_t frameId, const std::string& url)
{
  auto p = take(browser);
  if (p) {
    auto u = QString::fromStdString(url);
    p->q_ptr->addressChanged(frameId, u);
  }
}

void
CCefClientDelegate::titleChanged(CefRefPtr<CefBrowser>& browser, const std::string& title)
{
  auto p = take(browser);
  if (p) {
    auto t = QString::fromStdString(title);
    p->q_ptr->titleChanged(t);
  }
}

void
CCefClientDelegate::fullscreenModeChanged(CefRefPtr<CefBrowser>& browser, bool fullscreen)
{
  auto p = take(browser);
  if (p) {
    p->q_ptr->fullscreenModeChanged(fullscreen);
  }
}

bool
CCefClientDelegate::tooltipMessage(CefRefPtr<CefBrowser>& browser, const std::string& text)
{
  // allow the tooltip action
  return false;
}

void
CCefClientDelegate::statusMessage(CefRefPtr<CefBrowser>& browser, const std::string& value)
{
  auto p = take(browser);
  if (p) {
    auto msg = QString::fromStdString(value);
    p->q_ptr->statusMessage(msg);
  }
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
CCefClientDelegate::loadingProgressChanged(CefRefPtr<CefBrowser>& browser, double progress)
{
  auto p = take(browser);
  if (p) {
    p->q_ptr->loadingProgressChanged(progress);
  }
}

bool
CCefClientDelegate::cursorChanged(CefRefPtr<CefBrowser> browser,
                                  CefCursorHandle cursor,
                                  cef_cursor_type_t type,
                                  const CefCursorInfo& custom_cursor_info)
{
  // allow the cursor changing action
  return false;
}

void
CCefClientDelegate::takeFocus(CefRefPtr<CefBrowser>& browser, bool next)
{
  auto p = take(browser);
  if (p)
    p->onCefWindowLostTabFocus(next);
}

bool
CCefClientDelegate::setFocus(CefRefPtr<CefBrowser>& browser)
{
  // allow the focus setting action
  return false;
}

void
CCefClientDelegate::gotFocus(CefRefPtr<CefBrowser>& browser)
{
  auto p = take(browser);
  if (p)
    p->onCefWindowGotFocus();
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
                                        int64_t frameId,
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
                                       int64_t frameId,
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
    ValueConvertor::CefValueToQVariant(&qV, cV.get());
    args.push_back(qV);
  }

  auto browserId = browser->GetIdentifier();
  p->q_ptr->invokeMethod(browserId, frameId, m, args);
}

void
CCefClientDelegate::reportJSResult(CefRefPtr<CefBrowser>& browser,
                                   int64_t frameId,
                                   int64_t contextId,
                                   const CefRefPtr<CefValue>& result)
{
  auto p = take(browser);
  if (!p)
    return;

  auto browserId = browser->GetIdentifier();
  QVariant qV;
  ValueConvertor::CefValueToQVariant(&qV, result.get());
  p->q_ptr->reportJavascriptResult(browserId, frameId, contextId, qV);
}

bool
CCefClientDelegate::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
  return false;
}

void
CCefClientDelegate::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{}

bool
CCefClientDelegate::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY, int& screenX, int& screenY)
{
  return false;
}

bool
CCefClientDelegate::GetScreenInfo(CefRefPtr<CefBrowser> browser, CefScreenInfo& screen_info)
{
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
{}
