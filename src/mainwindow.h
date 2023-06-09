#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QProcess>
#include <QSettings>
#include <QTimer>
#include <QtOpenGL>

#include "QtGifImage-master/src/gifimage/qgifimage_p.h"

extern "C" {
#include "backend.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void saveSettings();
  void loadSettings();

 private slots:

  void on_pushButtonOpenFile_clicked();
  void on_pushButtonMove_clicked();
  void on_pushButtonSettings_clicked();

  void on_moveButtonZoomOut_clicked();
  void on_moveButtonZoomIn_clicked();
  void on_setZoom_clicked();

  void on_pushButton_MoveX_minus_clicked();
  void on_pushButton_MoveX_plus_clicked();

  void on_pushButton_MoveY_minus_clicked();
  void on_pushButton_MoveY_plus_clicked();

  void on_pushButton_MoveZ_minus_clicked();
  void on_pushButton_MoveZ_plus_clicked();

  void on_pushButton_RotationX_minus_clicked();
  void on_pushButton_RotationX_plus_clicked();

  void on_pushButton_RotationY_minus_clicked();
  void on_pushButton_RotationY_plus_clicked();

  void on_pushButton_RotationZ_minus_clicked();
  void on_pushButton_RotationZ_plus_clicked();

  void on_setMove_clicked();
  void on_setRotation_clicked();

  void on_dottedLineChoice_clicked();
  void on_solidLineChoice_clicked();
  void on_dashedLineChoice_clicked();

  void on_lineWidthMinus_clicked();
  void on_lineWidthPlus_clicked();

  void on_circleVertexChoice_clicked();
  void on_enableVertexChoice_clicked();
  void on_squareVertexChoice_clicked();

  void on_vertexSizeMinus_clicked();
  void on_vertexSizePlus_clicked();

  void on_projectionCentralChoice_clicked();
  void on_projectionParallelChoice_clicked();

  void on_lineColor_currentTextChanged(const QString &arg1);
  void on_backgroundColor_currentTextChanged(const QString &arg2);
  void on_vertexColor_currentTextChanged(const QString &arg3);

  void on_takeScreenshot_clicked();

  void on_takeGIF_clicked();
  void saveGIFFrame();

 private:
  Ui::MainWindow *ui;
  QString fileSettings;
  QGifImage gif;
  QTimer *timer;
  int time;

  QImage mp[100];

 signals:
  // void signal(QString);
};
#endif  // MAINWINDOW_H
