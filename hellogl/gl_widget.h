#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLShaderProgram>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core
{
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

protected:
  void initializeGL();
  void initShaders();
  void paintGL();
  void resizeGL(int width, int height);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

private:
  const static unsigned int NUM_VERTS = 4;
  const static unsigned int NUM_TRIS = 2;
  GLuint vao;
  GLuint vbo;
  GLuint ibo;
  int xRot;
  int yRot;
  int zRot;
  QOpenGLShaderProgram *program;
  const GLfloat vertex_position[3 * NUM_VERTS] =
      {
          1.0, 1.0, 0.0,
          -1.0, 1.0, 0.0,
          -1.0, -1.0, 0.0,
          1.0, -1.0, 0.0};

  const GLuint vertex_index[3 * NUM_TRIS] =
      {
          0, 1, 2,
          0, 2, 3};
};

#endif
