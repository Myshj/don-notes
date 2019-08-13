#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace don {
namespace notes {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNoteLineChanged(const QString&);
    void onNoteEntered();

private:
    Ui::MainWindow *ui;
};

}
}


#endif // MAINWINDOW_H
