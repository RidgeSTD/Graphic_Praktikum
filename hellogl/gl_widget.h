#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

protected:
  void initializeGL();
  void paintGL();

private:
  int xRot;
  int yRot;
  int zRot;
};
