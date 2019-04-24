#include "signaturehtml.h"
#include "ui_signaturehtml.h"
#include <QApplication>
#include <QMessageBox>
#include <QTextEdit>   // Nous allons tout de même afficher le contenu du fichier ^^
#include <QFile>       // Pour utiliser le fichier
#include <QTextStream> // Flux sortant du fichier
#include <QDir>

signatureHTML::signatureHTML(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signatureHTML)
{
    ui->setupUi(this);

    // Connexions des signaux et des slots
    connect(ui->quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(ui->generer,SIGNAL(clicked()),this,SLOT(genererCode()));
}

void signatureHTML::genererCode()
{
    m_nom=ui->nom->text();
    m_prenom=ui->prenom->text();
    m_telephone=ui->telephone->text();
    m_service=ui->service->text();
    m_fonction=ui->fonction->text();
    m_serviceEN=ui->serviceEN->text();
    m_fonctionEN=ui->fonctionEN->text();

    //"m_chemin="C:\\Users\\SANDRINE\\Desktop";

    if(m_nom=="" or m_prenom=="" or m_telephone ==""){
        QMessageBox::warning(this,"Attention","Merci de compléter au minimum les champs nom, prénom et téléphone");
        return;
    }

    QFile modele(QCoreApplication::applicationDirPath() + "/modele");
    if(modele.open(QIODevice::ReadOnly)) {
        QString dataText = modele.readAll();
        modele.close();

        dataText.replace("<prenom>", m_prenom);
        dataText.replace("<nom>", m_nom);
        dataText.replace("<telephone>", m_telephone);

        if(m_fonction!=""){
            dataText.replace("<fonction>", m_fonction+"<br/>");
        }
        else {
            dataText.replace("<fonction>", "");
        }
        if(m_service!=""){
            dataText.replace("<service>", m_service+"<br/>");
        }
        else {
            dataText.replace("<service>", "");
        }
        if(m_fonctionEN!=""){
            dataText.replace("<fonctionEN>", m_fonctionEN+"<br/>");
        }
        else {
            dataText.replace("<fonctionEN>", "");
        }
        if(m_serviceEN!=""){
            dataText.replace("<serviceEN>", m_serviceEN+"<br/>");
        }
        else {
            dataText.replace("<serviceEN>", "");
        }

        QFile fichier(m_chemin+"\\Geficca-"+m_nom+".htm");
        if(fichier.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&fichier);
            out << dataText;

            fichier.close();
        }


        QMessageBox::information(this,"Log",m_chemin+"\n\nTout est ok " + m_prenom + " " + m_nom + ".");
    }
    else {
        QMessageBox::critical(this,"Erreur","Le fichier \"modele.txt\" est introuvable. \n Merci de vérifier qu'il se trouve bien dans le même répertoire que l'application.");
        return;
    }
}

void signatureHTML::chemin()
{
    QString appdata = QDir::homePath();
    appdata = QDir::toNativeSeparators(appdata);

    QString extensionHTML =".htm";
    QString extensionTXT =".txt";
    QString complement ="\\AppData\\Roaming\\Microsoft\\Signatures\\";
    QString designation = "test";

    m_chemin = appdata + complement;
    //QString adresseSignatureTXT = appdata + complement + designation + extensionTXT;
    ui->chemin->setText(m_chemin);
}

signatureHTML::~signatureHTML()
{
    delete ui;
}
