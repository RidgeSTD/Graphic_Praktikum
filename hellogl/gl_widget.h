#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QGLWidget>
#include "cube.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

public slots:
  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);
  void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
  void initializeGL();
  void initShaders();
  void paintGL();
  void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void setupVertexAttribs();
  static const unsigned int num_verts = 4;
  static const unsigned int num_tris = 2;
  Cube mCube;
  GLuint vertex_index[6] =
      {
          0, 1, 2,
          0, 2, 3};
  QOpenGLVertexArrayObject vao;
  QOpenGLBuffer vbo;
  QOpenGLBuffer ibo;
  int xRot;
  int yRot;
  int zRot;
  QOpenGLShaderProgram *program;
  int mvMatrixLoc;
  int mNomalMatrixLoc;
  int mProjMatrixLoc;
  int colorUniformLoc;

  QMatrix4x4 m_proj;
  QMatrix4x4 m_camera;
  QMatrix4x4 m_world;
  QPoint m_lastPos;
};

#endif
