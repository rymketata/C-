#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked(int index);
    void onCancelButtonClicked(int index);
    void onResetAllClicked();

private:
    Ui::MainWindow *ui;
    QVector<QLabel*> imageLabels; // Labels pour afficher les images
    QVector<QPushButton*> cancelButtons;
    QPushButton* resetAllButton;
};

#endif // MAINWINDOW_H
