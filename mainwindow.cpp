#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialiser les labels pour les images, les boutons "Annuler" et le bouton "Réinitialiser tous"
    imageLabels = findChildren<QLabel*>(QRegularExpression("imageLabel\\d+"));
    cancelButtons = findChildren<QPushButton*>(QRegularExpression("cancelButton\\d+"));
    resetAllButton = findChild<QPushButton*>("resetAllButton");

    // Connexion des boutons à la fonction onButtonClicked
    QList<QPushButton*> buttons = findChildren<QPushButton*>(QRegularExpression("pushButton\\d+"));
    for (int i = 0; i < buttons.size(); ++i) {
        connect(buttons[i], &QPushButton::clicked, this, [this, i]() {
            onButtonClicked(i);
        });

        // Connexion des boutons "Annuler" à la fonction onCancelButtonClicked
        connect(cancelButtons[i], &QPushButton::clicked, this, [this, i]() {
            onCancelButtonClicked(i);
        });
    }

    // Connexion du bouton "Réinitialiser tous" à la fonction onResetAllClicked
    connect(resetAllButton, &QPushButton::clicked, this, &MainWindow::onResetAllClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClicked(int index)
{
    if (index >= 0 && index < imageLabels.size()) {
        // Changez l'image du label associé (vous devez avoir des images différentes pour chaque état)
        QPixmap pixmap(":/Reserve.png");
        imageLabels[index]->setPixmap(pixmap.scaled(imageLabels[index]->size(), Qt::KeepAspectRatio));
        qDebug() << "Champ " << index + 1 << " réservé";
    }
}

void MainWindow::onCancelButtonClicked(int index)
{
    if (index >= 0 && index < imageLabels.size()) {
        // Réinitialisez l'image du label associé
        QPixmap pixmap(":/libre.png");
        imageLabels[index]->setPixmap(pixmap.scaled(imageLabels[index]->size(), Qt::KeepAspectRatio));
        qDebug() << "Annulation de la réservation pour le champ " << index + 1;
    }
}
void MainWindow::onResetAllClicked()
{
    // Réinitialisez toutes les images pour les rendre disponibles
    for (QLabel* label : imageLabels) {
        label->setPixmap(QPixmap(":/../../Downloads/libre.png"));
    }
    qDebug() << "Tous les champs réinitialisés.";

    // Mettez à jour l'interface ou effectuez d'autres actions nécessaires
}
