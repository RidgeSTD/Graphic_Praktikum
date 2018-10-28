#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QGLWidget>

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();
  static const unsigned int num_verts = 4;
  static const unsigned int num_tris = 2;

protected:
  void initializeGL();
  void initShaders();
  void paintGL();
  void resizeGL(int width, int height);
//  void mousePressEvent(QMouseEvent *event);
//  void mouseMoveEvent(QMouseEvent *event);
//  void wheelEvent(QWheelEvent *event);

private:
  QOpenGLVertexArrayObject vao;
  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo;
  int xRot;
  int yRot;
  int zRot;
  QOpenGLShaderProgram *program;
  int mvpUniformLoc;
  int colorUniformLoc;

  QMatrix4x4 projectionM;
  QMatrix4x4 viewM;
  QMatrix4x4 modelM;
  QPoint m_lastPos;
};

#endif
