#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectiondb.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QRadioButton>
#include <QDebug>
//#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("test");
    setWindowIcon(QIcon(":/burger3.png"));
    ui->pushButton_15->setVisible(false);
        ui->menuBar->hide();

    ui->comboBox->setMaxVisibleItems(10);

    connect(ui->return2,SIGNAL(triggered()),this,SLOT(go_menu()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
****************************
Ecran de LOGIN
:connection à la base ou messagebox en cas d'echec de connection
TODO : messageBox error login
****************************
*/

void MainWindow::on_pushButton_7_clicked()
{
    connectiondb * connect = new connectiondb();

    //connectiondb(string namedb,string addressdb, string user, string password);
    if(connect->connect(ui->servername->text().toStdString(),
                        ui->addressdb->text().toStdString(),
                        ui->user->text().toStdString(),
                        ui->password->text().toStdString())){

        statusBar()->showMessage("connect to " + ui->servername->text());
        ui->stackedWidget->setCurrentIndex(0);

        ui->menuBar->show();
    }
}


/*
****************************
Ecran de MENU
:navigation entre les differente partie
****************************
*/

/*
****************************
Bouton RETOUR_MENU
:retour vers le menu principale
****************************
*/

void MainWindow::go_menu()
{
    connectiondb * db = new connectiondb;
    db->disconnect();
    statusBar()->showMessage("disconnected");
    ui->stackedWidget->setCurrentIndex(5);
    ui->pushButton_15->setVisible(false);

    ui->menuBar->hide();

}

/*
****************************
Accee partie THEME
:naviagtion vers partie theme + recupération liste theme dans bdd
****************************
*/

void MainWindow::on_pushButton_clicked()
{

    QVector<Theme*>themes = Theme::getThemes();
    int i;

    if(!themes.isEmpty()){
        ui->listtheme->clear();

        //ui->list->insertItem(list->size(),newitem);
        for(i=0;i<themes.size();i++){

            QListWidgetItem * newitem = new QListWidgetItem();
            newitem->setText(QString::fromStdString(themes[i]->getName()));
            QVariant data;

            data.setValue(Theme(themes[i]->getName(),themes[i]->getId()));
            newitem->setData(1,data);
            //Question(   idq idt c1 c2)

            //ui->comboBox->addItem(QString::fromStdString(res->getString("nom_theme")),data);
            ui->listtheme->addItem(newitem);
            //***********************************
        }



        ui->listtheme->setCurrentRow(0);

        ui->stackedWidget->setCurrentIndex(1);
        ui->pushButton_15->setVisible(true);//}

    }else{
        ui->stackedWidget->setCurrentIndex(5);
        ui->pushButton_15->setVisible(false);
    }

}

/*
****************************
Accee partie QUESTION
:naviagtion vers partie question + recupération liste theme dans bdd
****************************
*/

void MainWindow::on_pushButton_2_clicked()
{
    QVector<Theme*>themes = Theme::getThemes();
    int i;

    if(!themes.isEmpty()){
        ui->comboBox->clear();

        //ui->list->insertItem(list->size(),newitem);
        for(i=0;i<themes.size();i++){

            //QListWidgetItem * newitem = new QListWidgetItem();
            //newitem->setText(QString::fromStdString(themes[i]->getName()));
            QVariant data;

            data.setValue(Theme(themes[i]->getName(),themes[i]->getId()));
            //newitem->setData(1,data);
            //Question(   idq idt c1 c2)

            //ui->comboBox->addItem(QString::fromStdString(res->getString("nom_theme")),data);
                        ui->comboBox->addItem(QString::fromStdString(themes[i]->getName()),data);
            //***********************************
        }

        ui->comboBox->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(3);
        ui->pushButton_15->setVisible(true);

    }else{
        ui->stackedWidget->setCurrentIndex(5);
        ui->pushButton_15->setVisible(false);
    }
  /*  connectiondb *db = new connectiondb;
    db->getData("select * from Theme");
    ui->comboBox->clear();
    while (db->res->next()) {
        QString * newitem = new QString(QString::fromStdString(db->res->getString("id_theme")) +" :  "+QString::fromStdString(db->res->getString("nom_theme")));

        ui->comboBox->addItem(*newitem);
           }*/



}

/*
****************************
Accee partie SCOREBOARD
:naviagtion vers partie question + recupération liste partie dans bdd
****************************
*/


void MainWindow::on_pushButton_3_clicked()
{
    /*connectiondb *db = new connectiondb;
    db->getData("select * from Partie");
    ui->listWidget_3->clear();
    while (db->res->next()) {
        QListWidgetItem * newitem = new QListWidgetItem();
        newitem->setText(QString::fromStdString(db->res->getString("nom_partie")));
        newitem->setData(1,QString::fromStdString(db->res->getString("id_partie")));
        ui->listWidget_3->addItem(newitem);
           }*/
    QVector<Partie*>parties = Partie::getParties();
    int i;

    for(i=0;i<parties.size();i++){
        QListWidgetItem * newitem = new QListWidgetItem();
        newitem->setText(QString::fromStdString(parties[i]->getName()));
        QVariant data;

        data.setValue(Partie(parties[i]->getName(),parties[i]->getId()));
        newitem->setData(1,data);
        ui->listWidget_3->addItem(newitem);
    }

    ui->listWidget_3->setCurrentRow(0);



    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_15->setVisible(true);


}

/*
****************************
Accee partie QUESTION
:naviagtion vers partie question + recupération liste theme dans bdd
****************************
*/

void MainWindow::on_pushButton_4_clicked()
{
   /* connectiondb *db = new connectiondb;
    db->getData("select * from Utilisateur");
    ui->comboBox_2->clear();
    while (db->res->next()) {
        QString * newitem = new QString(QString::fromStdString(db->res->getString("mail")));
        ui->comboBox_2->addItem(*newitem);
           }*/
    //ui->listWidget_3->setCurrentRow(0);   ---> important

    ui->comboBox_2->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(4);
    ui->pushButton_15->setVisible(true);

}






















void MainWindow::on_pushButton_8_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Confirm?"));
    msgBox.setText(tr("Confirm?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yeah!"), QMessageBox::YesRole);
    msgBox.addButton(tr("Nope"), QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton()==pButtonYes) {
        //Execute command
    }
}



void MainWindow::on_pushButton_14_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(tr("info quizz:\t\t\t\t\n autre info quizz :\t\t\t\n autre info quizz :\t\t\t"));

    msgBox.exec();
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->pushButton_15->setVisible(false);

}

void MainWindow::on_pushButton_6_clicked()
{
    QDialog dialog(this);
        // Use a layout allowing to have a label next to each field
        QFormLayout form(&dialog);

        // Add some text above the fields
        QLabel* label=new QLabel("Option");
           label->setAlignment(Qt::AlignCenter);
        form.addRow(label);

        // Add the lineEdits with their respective labels
       // QList<QLineEdit *> fields;
            QLineEdit *lineEdit = new QLineEdit(&dialog);
            form.addRow("Nouveau nom", lineEdit);

         //   fields << lineEdit;

        QRadioButton *radio = new QRadioButton(&dialog);
        form.addRow("activation",radio);
        // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
        QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

        // Show the dialog as modal
        if (dialog.exec() == QDialog::Accepted) {
            // If the user didn't dismiss the dialog, do something with the fields
            //foreach(QLineEdit * lineEdit, fields) {
                //qDebug() << lineEdit->text();
            //}
        }
}
/*QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("The question ?"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    for(int i = 0; i < 4; ++i) {
        QLineEdit *lineEdit = new QLineEdit(&dialog);
        QString label = QString("Value %1").arg(i + 1);
        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // If the user didn't dismiss the dialog, do something with the fields
        foreach(QLineEdit * lineEdit, fields) {
            //qDebug() << lineEdit->text();
        }
    }*/






/*
 * bool ok;
        // Ask for birth date as a string.
        QString text = QInputDialog::getText(0, "Burger Quiz",
                                             "Nouveau nom du thème:", QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty()) {
            QMessageBox msgBox;
             msgBox.setText("le nom du thème a étais modifié");
             msgBox.exec();


        }
*/

void MainWindow::on_listWidget_3_currentRowChanged(int currentRow)
{
   //qDebug() << "test 0";
    if(currentRow >= 0){

        QVector<Score*> listscores = Score::getAllscores(1);
        int i;

        for(i=0;i<listscores.size();i++){

            QListWidgetItem * newitem = new QListWidgetItem();
            newitem->setText(QString::fromStdString(listscores[i]->getAllscores()));
            QVariant data;

            data.setValue(Score(listscores[i]->getPartie(),listscores[i]->getTheme(),listscores[i]->getScore(),listscores[i]->getTemps()));
            newitem->setData(1,data);
            //Question(   idq idt c1 c2)

            //ui->comboBox->addItem(QString::fromStdString(res->getString("nom_theme")),data);
            ui->listWidget_2->addItem(newitem);
            //***********************************
        }

    //qDebug() <<  ui->listWidget_3->item(currentRow)->data(1).toInt();

    /*connectiondb *db = new connectiondb;


    int i=1;
    db->getData("select * from Possede,Utilisateur where "
                "id_partie='"+ ui->listWidget_3->item(currentRow)->data(1).toString().toStdString()+"' and "
                "Possede.id_utilisateur = Utilisateur.id_utilisateur "
                "order by score desc limit 10");
    //db->res->first();
    //ui->lineEdit_2->setText(QString::fromStdString(db->res->getString("id_partie")));
    //qDebug() << QString::fromStdString(db->res->getString("id_partie"));
    ui->listWidget_2->clear();
    while (db->res->next()) {
        ui->lineEdit_2->setText(QString::fromStdString(db->res->getString("id_partie")));
        QListWidgetItem * newitem = new QListWidgetItem();
        newitem->setText(QString::number( i) +". " +QString::fromStdString(db->res->getString("prenom")) + ":" + QString::fromStdString(db->res->getString("score")));
        //newitem->setData(1,QString::fromStdString(db->res->getString("id_partie")));
        ui->listWidget_2->addItem(newitem);
        i++;
           }
    //
    ui->lineEdit_3->setText(QString::number(i-1));*/
    }

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    //qDebug() << ui->comboBox->currentData(1).value<Theme>().getId();
    //ui->comboBox->currentData(1)->
    QVector<Question*>questions = Question::getQuestions(ui->comboBox->currentData(Qt::UserRole).value<Theme>().getId());
    int i;

    //sql::ResultSet *res = Question::getQuestions(ui->comboBox->currentData(Qt::UserRole).value<Theme>().getId());
    if(!questions.isEmpty()){
        ui->listWidget_4->clear();

        for(i=0;i<questions.size();i++){

            QListWidgetItem * newitem = new QListWidgetItem();
            newitem->setText(QString::fromStdString(questions[i]->getC1()) + ", " + QString::fromStdString(questions[i]->getC2()) + " ou les deux");
            QVariant data;

            data.setValue(Question(questions[i]->getIdQuestion(),
                                   questions[i]->getIdTheme(),
                                   questions[i]->getC1(),
                                   questions[i]->getC2()));
            newitem->setData(1,data);
            //Question(   idq idt c1 c2)

            //ui->comboBox->addItem(QString::fromStdString(res->getString("nom_theme")),data);
            ui->listWidget_4->addItem(newitem);

        }


      /*  while (res->next()) {
            //qDebug() << "test";
            QListWidgetItem * newitem = new QListWidgetItem();
            newitem->setText(QString::fromStdString(res->getString("choix_un")) + ", " + QString::fromStdString(res->getString("choix_deux")) + " ou les deux");
            QVariant data;

            data.setValue(Question(res->getInt("id_question"),
                                   res->getInt("id_theme"),
                                   res->getString("choix_un"),
                                   res->getString("choix_deux")));
            newitem->setData(1,data);
            //Question(   idq idt c1 c2)

            //ui->comboBox->addItem(QString::fromStdString(res->getString("nom_theme")),data);
            ui->listWidget_4->addItem(newitem);
               }*/

        //ui->comboBox->setCurrentIndex(0);
        ui->listWidget_4->setCurrentRow(1);
        //ui->stackedWidget->setCurrentIndex(3);
        //ui->pushButton_15->setVisible(true);

    }else{
        ui->stackedWidget->setCurrentIndex(5);
        ui->pushButton_15->setVisible(false);
    }











    //int id = ui->comboBox->currentText().split(":")[0].toInt();
    //qDebug() << id ;
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    /*connectiondb *db = new connectiondb;

    db->getData("SELECT * FROM Possede,Utilisateur,"
                "(select ROUND(SUM(Possede.score)/COUNT(Possede.score)) as moyenne "
                "from Possede where Possede.id_utilisateur = 1) as test ,"
                "(select COUNT(Possede.score) as nbgame "
                "from Possede where Possede.id_utilisateur = 1) as test2 "
                "WHERE Utilisateur.id_utilisateur = '1' and "
                "Possede.id_utilisateur = Utilisateur.id_utilisateur "
                "order by Possede.score DESC");
db->res->first();
    ui->lineEdit_17->setText(QString::fromStdString(db->res->getString("mail")));
    ui->lineEdit_16->setText(QString::fromStdString(db->res->getString("nom")));
    ui->lineEdit_15->setText(QString::fromStdString(db->res->getString("prenom")));
    ui->label_14->setText(QString::fromStdString(db->res->getString("nbgame")));
    ui->label_15->setText(QString::fromStdString(db->res->getString("moyenne")+"/3000"));

    //qDebug() << "test" ;
    ui->listWidget_5->clear();

            while (db->res->next()) {
                //QString * newitem = new QString(QString::fromStdString(db->res->getString("score")));
                QListWidgetItem * newitem = new QListWidgetItem();
                newitem->setText(QString::fromStdString(db->res->getString("score")));
                //newitem->setData(1,QString::fromStdString(db->res->getString("id_partie")));
                ui->listWidget_5->addItem(newitem);
                   }*/

}

void MainWindow::on_listWidget_4_currentRowChanged(int currentRow)
{
    /*qDebug() << "tets";
    Question data = ui->listWidget_4->currentItem()->data(1).value<Question>();
            //comboBox->currentData(Qt::UserRole).value<Theme>();



    ui->lineEdit_5->setText(QString::number(data.getIdQuestion()));
    ui->lineEdit_6->setText(QString::fromStdString(data.getC1()));
    ui->lineEdit_7->setText(QString::fromStdString(data.getC2()));*/

    //5
    //67

}
