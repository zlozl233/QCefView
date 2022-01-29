#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>

#include "ui_BrowserWidget.h"

#include <QCefView.h>

class BrowserWidget : public QWidget
{
  Q_OBJECT

public:
  explicit BrowserWidget(QWidget* parent = nullptr);
  ~BrowserWidget();

  void onBtnChangeColorClicked();

  void onDraggableRegionChanged(const QRegion& draggableRegion, const QRegion& nonDraggableRegion);

  void onInvokeMethod(int browserId, int frameId, const QString& method, const QVariantList& arguments);

  void onQCefQueryRequest(int browserId, int frameId, const QCefQuery& query);

private:
  Ui::BrowserWidget ui;

  QCefView* cefViewWidget;
  QRegion draggableRegion_;
  QRegion nonDraggableRegion_;
};

#endif // BROWSERWIDGET_H
