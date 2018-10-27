# Grapa 的学习笔记

## Assignment 1: HelloGL

### 遇到的问题：

#### initializeOpenGLFunctions  段地址错误

原因是不应该在构造函数里自己调用，可能那时候还有参数没有分配内存导致 BAD_ACCESS。只要覆写`initializeGL`等待 QT 自己调用就好了。

#### 资源文件

资源文件是跨平台的重要帮手，资源文件要写在 qrc 文件中，在 pro 文件中添加`RESOURCE`字段让 QT 识别，这样才能使用`:/`前缀从资源文件中所引到正确的资源文件。据说这个资源文件会打包到可执行文件中跨平台调用

### 函数使用笔记

#### glViewPort(x, y, width, height)

 重设绘制窗体的范围，x, y 表示绘制窗口的左下角，一般是(0, 0)

#### glGenBuffer(GLsizei n, GLuint \* buffers)

分配一个给定大小的缓存空间并把生成的缓存空间名存到`buffers`中。第一个参数指定你想要创建对象的数量。
