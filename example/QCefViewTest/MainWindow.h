#ifndef QCEFVIEWTEST_H
#define QCEFVIEWTEST_H

#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = 0);
  ~MainWindow();

protected slots:
  void onCreateTabRequest();

  void onCloseTabRequest(int);

private:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
  virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif

private:
  Ui::MainWindow ui;
};

#endif // QCEFVIEWTEST_H
