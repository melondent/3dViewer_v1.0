#ifndef OGL_WIDGET_H
#define OGL_WIDGET_H

#include <glu.h>
#include <stdio.h>

#include <QMessageBox>
#include <QOpenGLWidget>
#include <QSettings>
#include <QWidget>
#include <QtOpenGL>

extern "C" {
#include "backend.h"
}

struct VData {
  QVector4D lineColor;
};

class OGWidget : public QOpenGLWidget {
 public:
  OGWidget(QWidget *parent);
  int lineStyle;
  QString filepath;
  QColor getColor();
  data_t obj;
  int error;
  bool checkFileLoad;
  bool checkDottedLine;
  bool checkDashedLine;
  bool checkCentralProjection;
  double lineWidth;
  double vertexSize;
  int vertexShape;
  void openFile(data_t *obj);
  QColor lineColor;
  QColor backgroundColor;
  QColor vertexColor;
  void lineStyleSet(unsigned int style, bool updateValue);
  void lineWidthSet(double widthValue);
  void vertexSizeSet(double sizeValue);
  void vertexShapeSet(int choose);
  void projectionSet(int index);
  QImage takeScreenshot();

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  QTimer tmr;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void drawObject();
 public slots:
  void slot(QString filepath);
};

#endif  // OGL_WIDGET_H
