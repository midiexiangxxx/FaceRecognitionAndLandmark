#include "customsqltablemodel.h"

CustomSqlTableModel::CustomSqlTableModel()
{

}


QVariant CustomSqlTableModel::data(const QModelIndex &idx, int role = Qt::DisplayRole) const
{
     if (idx.column() == 3) {
         QString imgFile = QSqlTableModel::data(idx, Qt::DisplayRole).toString(); // get path string

        if (role == Qt::DisplayRole)
            return QString(); // return the path string for display role

        QImage image(imgFile);
        /* some modification to the image, maybe */

        QPixmap pixmap(imgFile);
        if (role == Qt::DecorationRole)
            return pixmap;   // return QPixmap for decoration role

        if (role == Qt::SizeHintRole)
            return pixmap.size(); // in case need the image size

     }
     return QSqlTableModel::data( idx, role ); // use original data() outside the imageColumn
}
