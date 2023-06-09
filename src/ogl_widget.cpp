#define GL_SILENCE_DEPRECATION
#include "ogl_widget.h"

OGWidget::OGWidget(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("3D_Viewer");
  lineColor = QColor(255, 255, 255);
  backgroundColor = QColor(0, 0, 0);
  vertexColor = QColor(255, 0, 0);
  vertexSize = 10.0f;
}

void OGWidget::openFile(data_t *obj) {
  QByteArray ba = filepath.toLocal8Bit();
  char *path_file = ba.data();
  FILE *one = fopen(path_file, "r");
  if (one == NULL) {
    QMessageBox::critical(this, "Error", "Can't open the file!");
  } else {
    count_of_vertexes(one, obj);
    rewind(one);
    fill(obj, one);
  }
}

void OGWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);

  if (!checkDashedLine && !checkDottedLine) {
    glLineStipple(1, 0xFFFF);
  } else {
    if (checkDashedLine) glLineStipple(1, 0x00FF);
    if (checkDottedLine) glLineStipple(1, 0x0101);
  }
}

void OGWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  projectionSet(checkCentralProjection);
}

void OGWidget::paintGL() {
  projectionSet(checkCentralProjection);
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (checkDashedLine || checkDottedLine) {
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(lineWidth);
  glTranslatef(0, 0, -2.5);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  glRotatef(zRot, 0, 0, 1);
  drawObject();
}

void OGWidget::drawObject() {
  glVertexPointer(3, GL_DOUBLE, 0, obj.V);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (vertexShape) {
    glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glPointSize(vertexSize);
    if (vertexShape == 1) glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, obj.count_of_vertexes);
    if (vertexShape == 1) glDisable(GL_POINT_SMOOTH);
  }
  glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  glDrawElements(GL_LINES, obj.facets, GL_UNSIGNED_INT, obj.polygon);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void OGWidget::projectionSet(int index) {
  if (index) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, qreal(640) / qreal(480), 0.1, 100.0);

    checkCentralProjection = true;
    update();
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glOrtho(-1, 1, -1, 1, -1, 100);
    glOrtho(-7, 7, -6, 6, -100, 100);
    checkCentralProjection = false;
    update();
  }
}

void OGWidget::lineStyleSet(unsigned int style, bool updateValue) {
  makeCurrent();
  glLineStipple(1, style);
  if (updateValue) {
    if (style == 0x0101) {
      checkDottedLine = true;
      checkDashedLine = false;
    } else if (style == 0x00FF) {
      checkDottedLine = false;
      checkDashedLine = true;
    } else if (style == 0xFFFF) {
      checkDottedLine = false;
      checkDashedLine = false;
    }
  }
  update();
}

void OGWidget::vertexShapeSet(int choose) {
  vertexShape = choose;
  update();
}

void OGWidget::lineWidthSet(double widthValue) {
  makeCurrent();
  lineWidth += widthValue;
  if (lineWidth < 1.0f) {
    lineWidth = 1.0f;
  }
  glLineWidth(lineWidth);
  update();
}

void OGWidget::vertexSizeSet(double sizeValue) {
  vertexSize += sizeValue;
  if (vertexSize < 1.0f) {
    vertexSize = 1.0f;
  }
  update();
}

QImage OGWidget::takeScreenshot() { return grabFramebuffer(); }

void OGWidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void OGWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
