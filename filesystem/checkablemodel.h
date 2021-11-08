#ifndef CHECKABLEMODEL_H
#define CHECKABLEMODEL_H

#include <QObject>
#include <QFileSystemModel>
#include <QStandardItem>

class CheckableModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit CheckableModel(QObject *parent = nullptr);
    virtual bool setData( const QModelIndex& index, const QVariant& value, int role );
    virtual Qt::ItemFlags flags( const QModelIndex & index ) const;
    virtual QVariant data( const QModelIndex &index, int role )const;
signals:
    void itemChecked(const QModelIndex&);
protected slots:
    void onItemChecked(const QModelIndex& index);
private:
    mutable QMap <qint64, Qt::CheckState> checkedItems;
};

#endif // CHECKABLEMODEL_H
