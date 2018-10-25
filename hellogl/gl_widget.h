#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core
{
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

private:
  GLuint *vao;
  GLuint *vbo;
  GLuint *ibo;
  int xRot;
  int yRot;
  int zRot;
//  VertexArrayObject vao;
};