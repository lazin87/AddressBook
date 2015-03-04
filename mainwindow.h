#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/*
namespace Ui {
class MainWindow;
}
*/
class QItemSelection;
class AddressWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateActions(const QItemSelection &selection);
    void openFile();
    void saveFile();

private:
  //  Ui::MainWindow *ui;
    void createMenus();

    AddressWidget *addressWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
};

#endif // MAINWINDOW_H
