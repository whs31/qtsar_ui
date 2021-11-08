#include "checkablemodel.h"

CheckableModel::CheckableModel(QObject *parent) : QFileSystemModel(parent)
{
    connect(this, SIGNAL(itemChecked(const QModelIndex&)), SLOT(onItemChecked(const QModelIndex&)));
}

bool CheckableModel::setData( const QModelIndex& index, const QVariant& value, int role ) {

    if( role == Qt::CheckStateRole && index.column() == 0 ) {

        checkedItems[ index.internalId() ] = static_cast<Qt::CheckState>( value.toInt() );
        emit itemChecked(index);
        emit dataChanged(index, index.sibling(0,0));
        return true;

    }

    return QFileSystemModel::setData(index, value, role);

}

Qt::ItemFlags CheckableModel::flags( const QModelIndex & index ) const {

    return QFileSystemModel::flags( index ) | Qt::ItemIsUserCheckable;

}

QVariant CheckableModel::data( const QModelIndex& index, int role ) const {

    if( role == Qt::CheckStateRole && index.column()==0 ) {
        return QVariant( checkedItems[ index.internalId() ] );
    }

    return QFileSystemModel::data( index, role );
}

void CheckableModel::onItemChecked(const QModelIndex &index)
{
    Qt::CheckState state = checkedItems [index.internalId()];
    fetchMore(index);
    if ( state == Qt::Checked || state == Qt::Unchecked ) {
        for ( int i = 0; i < rowCount(index); i++ ) {
            QModelIndex child = index.child(i, 0);
            if (checkedItems [child.internalId()] != state )
                setData(child, state, Qt::CheckStateRole);
        }
    }

    QModelIndex parent = index.parent();
    if (parent.isValid()) {
        state = checkedItems [parent.child(0, 0).internalId()];
        if (state == Qt::PartiallyChecked)
            checkedItems[parent.internalId()] = state;
        else {
            int i = 1;
            while (i < rowCount(parent) && checkedItems [parent.child(i, 0).internalId()] == state)
                i++;
            if (i != rowCount(index))
                state = Qt::PartiallyChecked;
            //setData(parent, state, Qt::CheckStateRole);
            checkedItems [parent.internalId()] = state;
        }
    }

}
