#include "MainWindow.h"

#include <QLabel>
#include <QTabBar>
#include <QToolButton>

#include "BrowserWidget.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  // Create button what must be placed in tabs row
  QToolButton* tb = new QToolButton();
  tb->setText("+");
  ui.tabWidget->setCornerWidget(tb, Qt::TopLeftCorner);

  connect(tb, SIGNAL(clicked()), this, SLOT(onCreateTabRequest()));
}

MainWindow::~MainWindow() {}

void
MainWindow::onCreateTabRequest()
{
  ui.tabWidget->addTab(new BrowserWidget(), "New Tab");
}

void
MainWindow::onCloseTabRequest(int id)
{
  auto w = ui.tabWidget->widget(id);
  ui.tabWidget->removeTab(id);
  delete w;
}

#if defined(OS_WINDOWS)
#include <windows.h>
#include <windowsx.h>
#endif

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
bool
MainWindow::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
#else
bool
MainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
#endif
  return QMainWindow::nativeEvent(eventType, message, result);
}
