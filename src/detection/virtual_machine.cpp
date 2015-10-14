#include "virtual_machine.h"

DetectionVirtualMachine::DetectionVirtualMachine() {
	m_sType = "Virtual Machine";
}

void DetectionVirtualMachine::types(QStringList &list) {
	list << m_sType;
}

// --------------------------------------------------------------------

bool DetectionVirtualMachine::isType(const QFileInfo &fi, QString &type, QString &subtype) {
	QString sSuffix = fi.suffix().toUpper();
	QString sPath = fi.canonicalFilePath().toUpper();
	QString sName = fi.fileName().toUpper();
	// TODO: look inside file (search structure)
	bool bType = (sSuffix == "OVA");
	if (bType) {
		type = m_sType;
		subtype = "todo"; // version and another information
	}
	return bType;
}
