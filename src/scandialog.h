#ifndef SCANDIALOG_H
#define SCANDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QListView>
#include <QStringList>
#include <QStandardItemModel>
#include <QAbstractItemView>

class ScanDialog : public QDialog
{
    Q_OBJECT
public:
    ScanDialog(QWidget *parent, const QString &strPath);
	QStringList filter();
signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    void scanClicked();
    void checkedAll();

private:
    QLabel *m_pLabel;
    QPushButton *m_pScanButton;
    QPushButton *m_pCloseButton;
    QStandardItemModel *m_pItemModel;
    QListView *m_pListView;
    QCheckBox *m_pCheckedAll;
};

#endif // SCANDIALOG_H
