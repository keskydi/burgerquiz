#include "score.h"
#include "connectiondb.h"
#include <QDebug>
#include<QMessageBox>


Score::Score()
{

}

QVector<Score*> Score::getAllScoreByIdGame(int partie){

    try {

        sql::ResultSet *res;
        sql::PreparedStatement *stmt;
        QVector<Score*>scores;

        sql::Connection *con = connectiondb::GetConnection();
        //qDebug() << con->
        //if(con->isValid() && con != NULL){
         //qDebug() << "test4";
            stmt = con->prepareStatement("SELECT * from Possede,Utilisateur where Possede.id_partie = ? and Possede.id_utilisateur= Utilisateur.id_utilisateur order by score DESC limit 10");
            //qDebug() << "test5";
            stmt->setInt(1, partie);

            res = stmt->executeQuery();
            //return stmt->getResultSet();//}else{return NULL;}
            while (res->next()) {
                scores.push_back(new Score(res->getInt("id_partie"),
                                           res->getInt("id_utilisateur"),
                                           res->getInt("score"),
                                           res->getInt("temps"),
                                           User(res->getString("nom"),res->getString("prenom"))));
                   }
            return scores;


        } catch (sql::SQLException &e) {
         qDebug() << "# ERR: SQLException in " << __FILE__;
         qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
         qDebug() << "# ERR: " << e.what();
         qDebug() << " (MySQL error code: " << e.getErrorCode();
         qDebug() << ", SQLState: " << QString::fromStdString(e.getSQLState()) << " )" << endl;
         QVector<Score *> empty;
         return empty;
        }catch(string e){
                    //qDebug() << QString::fromStdString(e) << endl;
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromStdString(e));
        error->exec();
        QVector<Score *> empty;
        return empty;
               }

}


QVector<Score*> Score::getAllScoreByIdUser(int partie){

    try {

        sql::ResultSet *res;
        sql::PreparedStatement *stmt;
        QVector<Score*>scores;

        sql::Connection *con = connectiondb::GetConnection();
        //qDebug() << con->
        //if(con->isValid() && con != NULL){
         //qDebug() << "test4";
            stmt = con->prepareStatement("SELECT * from Possede,Partie where Possede.id_utilisateur = ? and Possede.id_partie= Partie.id_partie");
            //qDebug() << "test5";
            stmt->setInt(1, partie);

            res = stmt->executeQuery();
            //return stmt->getResultSet();//}else{return NULL;}
            while (res->next()) {
                scores.push_back(new Score(res->getInt("id_partie"),
                                           res->getInt("id_utilisateur"),
                                           res->getInt("score"),
                                           res->getInt("temps"),
                                           Partie(res->getString("nom_partie"),res->getInt("id_partie"))));
                   }
            return scores;


        } catch (sql::SQLException &e) {
         qDebug() << "# ERR: SQLException in " << __FILE__;
         qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
         qDebug() << "# ERR: " << e.what();
         qDebug() << " (MySQL error code: " << e.getErrorCode();
         qDebug() << ", SQLState: " << QString::fromStdString(e.getSQLState()) << " )" << endl;
         QVector<Score *> empty;
         return empty;
        }catch(string e){
                    //qDebug() << QString::fromStdString(e) << endl;
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromStdString(e));
        error->exec();
        QVector<Score *> empty;
        return empty;
               }

}
