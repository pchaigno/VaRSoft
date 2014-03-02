#ifndef IMPORT_H
#define IMPORT_H

#include <QDialog>

namespace Ui {
class Import;
}

class Import : public QDialog
{
	Q_OBJECT

public:
	explicit Import(QWidget *parent = 0);
	~Import();

private:
	Ui::Import *ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();

signals:
		void dataEntered(const QString &text, const QDateTime &fDate ,const QDateTime &lDate);
		//void firstDateEntered(const QDateTime &date);
		//void lastDateEntered(const QDateTime &date);
};

#endif // IMPORT_H
