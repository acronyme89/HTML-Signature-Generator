#ifndef SIGNATUREHTML_H
#define SIGNATUREHTML_H

#include <QMainWindow>

namespace Ui {
class signatureHTML;
}

class signatureHTML : public QMainWindow
{
    Q_OBJECT

public:
    explicit signatureHTML(QWidget *parent = nullptr);
    ~signatureHTML();

private:
    Ui::signatureHTML *ui;

private slots:
    void genererCode();

public:
    // Methode
    void chemin();

private:
    // Attribut
    QString m_nom;
    QString m_prenom;
    QString m_fonction;
    QString m_service;
    QString m_fonctionEN;
    QString m_serviceEN;
    QString m_telephone;

    QString m_chemin;
};

#endif // SIGNATUREHTML_H
