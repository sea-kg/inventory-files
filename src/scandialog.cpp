#include <QtGui>
#include <iostream>
#include "scandialog.h"
#include "detection/detection.h"

ScanDialog::ScanDialog(QWidget *parent, const QString &strPaths) : QDialog(parent){
	m_pLabel = new QLabel(tr("Scan in \n") + strPaths);
	m_pScanButton = new QPushButton(tr("&Scan"));
	m_pScanButton->setDefault(true);
	m_pCloseButton = new QPushButton(tr("&Close"));
	m_pCheckedAll = new QCheckBox("Checked All");
	m_pCheckedAll->setChecked(true);
	
	connect(m_pScanButton, SIGNAL(clicked()),this, SLOT(scanClicked()));
	connect(m_pCloseButton, SIGNAL(clicked()),this, SLOT(close()));
	connect(m_pCheckedAll, SIGNAL(clicked()),this, SLOT(checkedAll()));

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addWidget(m_pLabel);

	// File types
	{
		m_pListView = new QListView();
		m_pItemModel = new QStandardItemModel();
		Detection *pDetection = new Detection();
		QStringList ft;
		pDetection->types(ft);
		for (int i = 0; i < ft.size(); i++) {
			QString s = ft.at(i);
			// leftLayout->addWidget(new QCheckBox(s));
			QStandardItem *pItem = new QStandardItem(s);
			pItem->setCheckable(true);
			pItem->setCheckState(Qt::Checked);
			m_pItemModel->setItem(i, pItem);
		}
		m_pListView->setModel(m_pItemModel);
		leftLayout->addWidget(m_pListView);
	}

	leftLayout->addWidget(m_pCheckedAll);
	leftLayout->addWidget(m_pScanButton);
	leftLayout->addWidget(m_pCloseButton);
	// leftLayout->addStretch();
	

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	// mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);
	// setLayout(leftLayout);
	setWindowTitle(tr("Scan"));
	setFixedHeight(sizeHint().height());
}

// ---------------------------------------------------------------------

QStringList ScanDialog::filter(){
	QStringList f;
	for(int i = 0; i < m_pItemModel->rowCount(); i++){
		QStandardItem *pItem = m_pItemModel->item(i);
		if(pItem->checkState() == Qt::Checked)
			f << pItem->text();
	}
	return f;
};

// ---------------------------------------------------------------------

void ScanDialog::scanClicked(){
	done(QDialog::Accepted);
}

// ---------------------------------------------------------------------

void ScanDialog::checkedAll(){
	Qt::CheckState cs = m_pCheckedAll->checkState();
	for(int i = 0; i < m_pItemModel->rowCount(); i++){
		QStandardItem *pItem = m_pItemModel->item(i);
		pItem->setCheckState(cs);
	}
}
