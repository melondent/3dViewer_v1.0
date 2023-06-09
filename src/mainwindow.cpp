#include "mainwindow.h"

#include <ogl_widget.h>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);
  fileSettings = QApplication::applicationDirPath() + "settings.conf";
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_pushButtonOpenFile_clicked() {
  ui->widget->filepath =
      QFileDialog::getOpenFileName(this, "Open file", "/Users/", "*.obj");
  if (ui->widget->filepath != "") {
    ui->widget->openFile(&ui->widget->obj);
    ui->widget->update();
    ui->show_name->setText(
        ui->widget->filepath.right(ui->widget->filepath.size() -
                                   ui->widget->filepath.lastIndexOf("/") - 1));
    ui->count_vertexes->setText(
        QString::number(ui->widget->obj.count_of_vertexes, 10));
    ui->count_poligons->setText(
        QString::number(ui->widget->obj.count_of_facets, 10));
    ui->widget->checkFileLoad = true;
  } else {
    QMessageBox::critical(this, "Error",
                          "Can't open the file.\nPlease try again.");
    ui->widget->checkFileLoad = false;
  }
}

void MainWindow::on_pushButtonMove_clicked() {
  if (ui->widget->checkFileLoad) {
    ui->stackedWidget->setCurrentIndex(1);
  }
}

void MainWindow::on_pushButtonSettings_clicked() {
  if (ui->widget->checkFileLoad) {
    ui->stackedWidget->setCurrentIndex(2);
  }
}

void MainWindow::on_moveButtonZoomOut_clicked() {
  if (ui->widget->checkFileLoad) {
    zoom(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_moveButtonZoomIn_clicked() {
  if (ui->widget->checkFileLoad) {
    zoom(&ui->widget->obj, 1.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_MoveX_minus_clicked() {
  if (ui->widget->checkFileLoad) {
    move_x(&ui->widget->obj, -0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_MoveX_plus_clicked() {
  if (ui->widget->checkFileLoad) {
    move_x(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_MoveY_minus_clicked() {
  if (ui->widget->checkFileLoad) {
    move_y(&ui->widget->obj, -0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_MoveY_plus_clicked() {
  if (ui->widget->checkFileLoad) {
    move_y(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_MoveZ_minus_clicked() {
  if (ui->widget->checkFileLoad) {
    move_z(&ui->widget->obj, -0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_MoveZ_plus_clicked() {
  if (ui->widget->checkFileLoad) {
    move_z(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_setMove_clicked() {
  if (ui->widget->checkFileLoad) {
    move_x(&ui->widget->obj, ui->MoveX_value->text().toDouble());
    move_y(&ui->widget->obj, ui->MoveY_value->text().toDouble());
    move_z(&ui->widget->obj, ui->MoveZ_value->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_setZoom_clicked() {
  if (ui->widget->checkFileLoad) {
    double zoomValue = ui->Zoom_value->text().toDouble();
    if (zoomValue > 0) {
      zoom(&ui->widget->obj, zoomValue);
      ui->widget->update();
    }
  }
}

void MainWindow::on_pushButton_RotationX_minus_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_x(&ui->widget->obj, -0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_RotationX_plus_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_x(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_RotationY_minus_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_y(&ui->widget->obj, -0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_RotationY_plus_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_y(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_RotationZ_minus_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_z(&ui->widget->obj, -0.5);
    ui->widget->update();
  }
}

void MainWindow::on_pushButton_RotationZ_plus_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_z(&ui->widget->obj, 0.5);
    ui->widget->update();
  }
}

void MainWindow::on_setRotation_clicked() {
  if (ui->widget->checkFileLoad) {
    rotation_x(&ui->widget->obj, ui->RotationX_value->text().toDouble());
    rotation_y(&ui->widget->obj, ui->RotationY_value->text().toDouble());
    rotation_z(&ui->widget->obj, ui->RotationZ_value->text().toDouble());
    ui->widget->update();
  }
}

void MainWindow::on_dottedLineChoice_clicked() {
  ui->widget->lineStyleSet(0x0101, 1);
}

void MainWindow::on_solidLineChoice_clicked() {
  ui->widget->lineStyleSet(0xFFFF, 1);
}

void MainWindow::on_dashedLineChoice_clicked() {
  ui->widget->lineStyleSet(0x00FF, 1);
}

void MainWindow::on_lineWidthMinus_clicked() {
  ui->widget->lineWidthSet(-0.5f);
}

void MainWindow::on_lineWidthPlus_clicked() { ui->widget->lineWidthSet(0.5f); }

void MainWindow::on_circleVertexChoice_clicked() {
  ui->widget->vertexShapeSet(1);
}

void MainWindow::on_enableVertexChoice_clicked() {
  ui->widget->vertexShapeSet(0);
}

void MainWindow::on_squareVertexChoice_clicked() {
  ui->widget->vertexShapeSet(2);
}

void MainWindow::on_vertexSizeMinus_clicked() {
  ui->widget->vertexSizeSet(-1.0f);
}

void MainWindow::on_vertexSizePlus_clicked() {
  ui->widget->vertexSizeSet(1.0f);
}

void MainWindow::on_projectionCentralChoice_clicked() {
  ui->widget->projectionSet(1);
  ui->widget->update();
}

void MainWindow::on_projectionParallelChoice_clicked() {
  ui->widget->projectionSet(0);
  ui->widget->update();
}

void MainWindow::on_lineColor_currentTextChanged(const QString &arg1) {
  QString color = arg1;
  if (QString::compare(color, "Red", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(255, 0, 0);
  } else if (QString::compare(color, "White", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(255, 255, 255);
  } else if (QString::compare(color, "Black", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(0, 0, 0);
  } else if (QString::compare(color, "Blue", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(0, 0, 255);
  } else if (QString::compare(color, "Dark blue", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(0, 0, 139);
  } else if (QString::compare(color, "Gray", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(128, 128, 128);
  } else if (QString::compare(color, "Green", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(0, 255, 0);
  } else if (QString::compare(color, "Yellow", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(255, 255, 0);
  } else if (QString::compare(color, "Orange", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(255, 165, 0);
  } else if (QString::compare(color, "Pink", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(255, 192, 203);
  } else if (QString::compare(color, "Deep pink", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(255, 20, 147);
  } else if (QString::compare(color, "Purple", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(128, 0, 128);
  } else if (QString::compare(color, "Lavender", Qt::CaseInsensitive) == 0) {
    ui->widget->lineColor = QColor(230, 230, 250);
  }
  ui->widget->update();
}

void MainWindow::on_vertexColor_currentTextChanged(const QString &arg3) {
  QString color = arg3;
  if (QString::compare(color, "Red", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(255, 0, 0);
  } else if (QString::compare(color, "White", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(255, 255, 255);
  } else if (QString::compare(color, "Black", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(0, 0, 0);
  } else if (QString::compare(color, "Blue", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(0, 0, 255);
  } else if (QString::compare(color, "Dark blue", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(0, 0, 139);
  } else if (QString::compare(color, "Gray", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(128, 128, 128);
  } else if (QString::compare(color, "Green", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(0, 255, 0);
  } else if (QString::compare(color, "Yellow", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(255, 255, 0);
  } else if (QString::compare(color, "Orange", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(255, 165, 0);
  } else if (QString::compare(color, "Pink", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(255, 192, 203);
  } else if (QString::compare(color, "Deep pink", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(255, 20, 147);
  } else if (QString::compare(color, "Purple", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(128, 0, 128);
  } else if (QString::compare(color, "Lavender", Qt::CaseInsensitive) == 0) {
    ui->widget->vertexColor = QColor(230, 230, 250);
  }
  ui->widget->update();
}

void MainWindow::on_backgroundColor_currentTextChanged(const QString &arg2) {
  QString color = arg2;
  if (QString::compare(color, "Red", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(255, 0, 0);
  } else if (QString::compare(color, "White", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(255, 255, 255);
  } else if (QString::compare(color, "Black", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(0, 0, 0);
  } else if (QString::compare(color, "Blue", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(0, 0, 255);
  } else if (QString::compare(color, "Dark blue", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(0, 0, 139);
  } else if (QString::compare(color, "Gray", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(128, 128, 128);
  } else if (QString::compare(color, "Green", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(0, 255, 0);
  } else if (QString::compare(color, "Yellow", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(255, 255, 0);
  } else if (QString::compare(color, "Orange", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(255, 165, 0);
  } else if (QString::compare(color, "Pink", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(255, 192, 203);
  } else if (QString::compare(color, "Deep pink", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(255, 20, 147);
  } else if (QString::compare(color, "Purple", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(128, 0, 128);
  } else if (QString::compare(color, "Lavender", Qt::CaseInsensitive) == 0) {
    ui->widget->backgroundColor = QColor(230, 230, 250);
  }
  ui->widget->update();
}

void MainWindow::loadSettings() {
  QFile file(fileSettings);

  if (file.exists()) {
    QSettings settings(fileSettings, QSettings::IniFormat);
    ui->widget->vertexShape = settings.value("vertexShape").toInt();
    ui->widget->checkDashedLine = settings.value("checkDashedLine").toBool();
    ui->widget->checkDottedLine = settings.value("checkDottedLine").toBool();
    ui->widget->checkCentralProjection =
        settings.value("checkCentralProjection").toBool();
    ui->widget->lineWidth = settings.value("lineWidth").toDouble();
    ui->widget->vertexSize = settings.value("vertexSize").toDouble();
    ui->widget->lineColor = settings.value("lineColor").value<QColor>();
    ui->widget->vertexColor = settings.value("vertexColor").value<QColor>();
    ui->widget->backgroundColor =
        settings.value("backgroundColor").value<QColor>();
  }
}

void MainWindow::saveSettings() {
  QSettings settings(fileSettings, QSettings::IniFormat);
  settings.setValue("vertexShape", ui->widget->vertexShape);
  settings.setValue("checkDashedLine", ui->widget->checkDashedLine);
  settings.setValue("checkDottedLine", ui->widget->checkDottedLine);
  settings.setValue("checkCentralProjection",
                    ui->widget->checkCentralProjection);
  settings.setValue("vertexSize", ui->widget->vertexSize);
  settings.setValue("lineWidth", ui->widget->lineWidth);
  settings.setValue("lineColor", ui->widget->lineColor);
  settings.setValue("vertexColor", ui->widget->vertexColor);
  settings.setValue("backgroundColor", ui->widget->backgroundColor);
}

void MainWindow::on_takeScreenshot_clicked() {
  if (ui->widget->checkFileLoad) {
    QImage screenshot = ui->widget->takeScreenshot();
    QString fileExtension = "JPEG Files (*.jpg *.jpeg);;BMP Files (*.bmp)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save screenshot"),
                                                    "", fileExtension);

    if (!fileName.isEmpty()) {
      QFileInfo fileInfo(fileName);
      QString fileSaveExtension = fileInfo.suffix().toLower();

      if (fileSaveExtension.isEmpty() ||
          !(fileSaveExtension == "jpg" || fileSaveExtension == "jpeg" ||
            fileSaveExtension == "bmp")) {
        fileName += ".jpeg";
      }

      screenshot.save(fileName);
    }
  }
}

void MainWindow::on_takeGIF_clicked() {
  timer = new QTimer();
  time = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(saveGIFFrame()));
  timer->start(100);
}

void MainWindow::saveGIFFrame() {
  if (time == 50) {
    timer->stop();
    disconnect(timer);
    time = 0;
    for (int i = 0; i < 51; gif.addFrame(mp[i++], 100)) {
    }
    QString str = QFileDialog::getSaveFileName(this, tr("Save GIF"), "",
                                               "GIF Files (*.gif)");
    gif.save(str);
    ui->takeGIF->setText("GIF");
    ui->takeGIF->setEnabled(1);
  } else {
    mp[time] = ui->widget->grab().toImage();
    time += 1;
    ui->takeGIF->setText(QString::number(time / 10));
  }
}
