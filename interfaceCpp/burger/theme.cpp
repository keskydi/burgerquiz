#include "theme.h"
#include "connectiondb.h"
#include <QDebug>
#include<QMessageBox>

Theme::Theme(){

}

sql::ResultSet* Theme::getThemes(){

    try {

        sql::ResultSet *res;
        sql::PreparedStatement *stmt;

        sql::Connection *con = connectiondb::GetConnection();
        //qDebug() << con->
        //if(con->isValid() && con != NULL){
         //qDebug() << "test4";
            stmt = con->prepareStatement("SELECT * from Theme");
            //qDebug() << "test5";
            return stmt->executeQuery();
            //return stmt->getResultSet();//}else{return NULL;}


        } catch (sql::SQLException &e) {
         qDebug() << "# ERR: SQLException in " << __FILE__;
         qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
         qDebug() << "# ERR: " << e.what();
         qDebug() << " (MySQL error code: " << e.getErrorCode();
         qDebug() << ", SQLState: " << QString::fromStdString(e.getSQLState()) << " )" << endl;
         return NULL;
        }catch(string e){
                    //qDebug() << QString::fromStdString(e) << endl;
        QMessageBox *error = new QMessageBox;
        error->setText(QString::fromStdString(e));
        error->exec();
                    return NULL;
               }

}

//sql::ResultSet *res;
//sql::PreparedStatement *pstmt;
//sql::Statement *stmt;
//sql::Connection *con = connectiondb::GetConnection();

//pstmt = con->prepareStatement("SELECT id FROM test ORDER BY id ASC"); // ?
  //pstmt->setInt(1, i);
  //return pstmt->executeQuery();
  //pstmt->executeUpdate();

/* Select in ascending order */
//pstmt = con->prepareStatement("SELECT id FROM test ORDER BY id ASC");
//res = pstmt->executeQuery();
