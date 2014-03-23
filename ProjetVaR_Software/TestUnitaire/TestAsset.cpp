/**
 * Copyright (C) 2013 Benjamin Bouguet, Damien Carduner, Paul Chaignon,
 * Eric Chauty, Xavier Fraboulet, Clement Gautrais, Ulysse Goarant.

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "TestAsset.h"

/**
 * @brief Initializes an asset for the tests.
 */
TestAsset::TestAsset() {
	QDateTime firstDate(QDate(2014, 1, 2), QTime(0, 0, 0));
	QDateTime lastDate(QDate(2014, 1, 5), QTime(0, 0, 0));
	this->google = Asset("Google", "../../CSV_examples/asset1.txt", "YAHOO", firstDate, lastDate);
	this->missing = Asset("test", "../../CSV_examples/nonexistingfile.txt", "YAHOO", firstDate, lastDate);
}

/**
 * @brief Checks that the id can only be set once.
 */
void TestAsset::testId() {
	QCOMPARE(this->google.getId(), -1);
	this->google.setId(42);
	QCOMPARE(this->google.getId(), 42);
	try {
		this->google.setId(43);
	} catch(const IdAlreadyAttributedException e) {
		return;
	}
	QFAIL("No exception thrown when attributed an id to an asset twice.");
}

/**
 * @brief Checks that the name can actually be changed.
 */
void TestAsset::testName() {
	QVERIFY(this->google.getName() == "Google");
	this->google.changeName("Googl");
	QVERIFY(this->google.getName() == "Googl");
}

/**
 * @brief Tests the method getValues that retrieves all values of an asset.
 */
void TestAsset::testGetValues() {
	qDebug() << "Current dir: " << QDir::currentPath();

	QVector<double> result;

	// getValues() version with dates parameters
	try {
		result = this->google.getValues(this->google.getFirstDate(), this->google.getLastDate());
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
	QCOMPARE(result.at(2), 103.0);
	QCOMPARE(result.at(3), 104.0);

	// getValues() version without dates parameters
	try {
		result = this->google.getValues();
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	QCOMPARE(result.size(), 4);
	QCOMPARE(result.at(0), 101.0);
	QCOMPARE(result.at(1), 102.0);
	QCOMPARE(result.at(2), 103.0);
	QCOMPARE(result.at(3), 104.0);

	// NONEXISTING FILE CASE
	try {
		result = this->missing.getValues(this->missing.getFirstDate(), this->missing.getLastDate());
		QFAIL("getValues() was able to open the file that should not exist");
	} catch(CannotOpenFileException& e) {
		qDebug() << e.what();
	}

	// INCORRECT PARAMETERS CASE
	// firstDate is after endDate
	try {
		result = this->google.getValues(this->google.getLastDate(), this->google.getFirstDate());
		QFAIL("getValues was able to execute with incorrect date paramaeters");
	} catch(std::exception& e) {
		qDebug() << e.what();
	}
}
