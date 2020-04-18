#ifndef QGLVIEWER_H
#define QGLVIEWER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <QMatrix4x4>

#include "camera.h"
#include "gldata.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)


class QGLViewer : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  QGLViewer(QWidget *parent = nullptr);
  ~QGLViewer() override;

  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;

  Camera& camera() { return m_camera; }

  void setData(const GLData &data);


public slots:
  void cleanup();

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void keyPressEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

private:
  void initializeGridAndAxes();
  void setupGL();
  void setupVertexAttribs();

  QPoint m_lastPos;

  GLData m_data;

  // draw as triangles
  QOpenGLVertexArrayObject m_trisVao;
  QOpenGLBuffer m_trisVbo;

  // draw as lines: grid and axes
  QOpenGLVertexArrayObject m_linesVao;
  QOpenGLBuffer m_linesVbo;

  bool m_drawGrid;
  int m_gridVertexIdx;
  bool m_drawAxes;
  int m_axesVertexIdx;

  QOpenGLShaderProgram *m_program;

  Camera m_camera;

  int m_mvpMatrixLoc;
};

#endif
