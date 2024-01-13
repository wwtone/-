#include <QApplication>
//#include "BubbleSimple.h"
#include "MainUI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //BubbleSimple window; //验证逻辑，最简示例
    //window.show();
    MainUI window;
    analyze_window a_window;
    window.show();
   // a_window.show();
    return app.exec();
}
