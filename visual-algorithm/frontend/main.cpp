#include "mainwindow.h"
#include <QApplication>

static void msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  QByteArray localMsg = msg.toLocal8Bit();
  const char *file = context.file ? context.file : "";
  const char *function = context.function ? context.function : "";
  switch (type)
  {
  case QtDebugMsg:
    fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
    break;
  case QtInfoMsg:
    fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
    break;
  case QtWarningMsg:
    fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
    break;
  case QtCriticalMsg:
    fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
    break;
  case QtFatalMsg:
    fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
#if 1
    __asm__ __volatile__("int $3\n\tnop\n\t"); // Breakpoint on x86
#else
    abort();
#endif
    break;
  }
}

int main(int argc, char *argv[])
{
    //qInstallMessageHandler(msgHandler);
    QApplication a(argc, argv);
    MainWindow &w = MainWindow::instance();
    w.show();

    return a.exec();
}
