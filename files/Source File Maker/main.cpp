#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//TO DO: Input Checks, Add notes, Clean Up Code 

struct column {
	string name;
	char type;
	int value1 = 0;
	int value2 = 0;
	bool required = false;
};

int main() {

	//std::vector<string> code;
	vector<column> col;
	column temp;
	string str;
	string title;
	string id;
	string mrnumber = "mrnumber";
	char convert;
	fstream file;

	/**** INPUT ****/
	file.open("input.txt", ios::in);

	if (file) {
		file >> title;
		while (!file.eof()) {

			temp.name = "";
			temp.type = ' ';
			temp.value1 = 0;
			temp.value2 = 0;
			temp.required = false;

			file >> temp.name;

			if (temp.name.length() == 0) {
				break;
			}

			if (temp.name[temp.name.length() - 1] == '*') {
				temp.required = true;
				temp.name.erase(temp.name.length() - 1, 1);
			}

			file >> temp.type;

			if (temp.type == 'n' || temp.type == 's') {
				file >> temp.value1;
			}

			if (temp.type == 'n') {
				file >> temp.value2;
			}
			col.push_back(temp);
		}
	}

	id = title + "_id";

	cout << "Table Name: " << title << endl;
	cout << "Column Size: " << col.size() + 2 << endl;
	cout << "Column Names: " << endl;
	cout << "\t" << id << "\n\t" << mrnumber << endl;

	for (unsigned int i = 0; i < col.size(); ++i) {
		cout << "\t";
		cout << col[i].name << " ";
		cout << col[i].type << " ";
		cout << col[i].value1 << " ";
		cout << col[i].value2 << endl;
	}

	file.close();

	/**** SQL ****/
	file.open(title + ".sql", ios::out);

	file << "CREATE TABLE " << title << " (\n";
	file << "\t" << title << "_id TIMESTAMP NOT NULL DEFAULT(current_timestamp),\n";
	file << "\t" << mrnumber << " INT NOT NULL,\n";


	for (unsigned int i = 0; i < col.size(); ++i) {

		file << "\t" << col[i].name << " ";

		if (col[i].type == 'i') {
			file << "INT";
		}
		else if (col[i].type == 'n') {
			file << "NUMERIC (" << col[i].value1 << "," << col[i].value2 << ")";
		}
		else if (col[i].type == 'd') {
			file << "DATE";
		}
		else if (col[i].type == 't') {
			file << "TIME";
		}
		else if (col[i].type == 's') {
			file << "VARCHAR (" << col[i].value1 << ")";
		}

		if (col[i].required == true) {
			file << " NOT NULL";
		}

		file << ",\n";
	}

	file << "\tPRIMARY KEY(" << title << "_id),\n";
	file << "\tCONSTRAINT fk_MRN\n";
	file << "\t\tFOREIGN KEY(" << mrnumber << ")\n";
	file << "\t\t\tREFERENCES Patient_Info(" << mrnumber << ")\n";
	file << ");";

	file.close();

	cout << "SQL CREATED" << endl;
	/**** Python ****/
	file.open("results.txt", ios::out);

	file << "#### Classes ####" << endl;
	convert = toupper(title[0]);

	file << "class " << convert;

	for (unsigned int i = 1; i < title.length(); ++i) {

		file << title[i];

		if (title[i] == '_') {
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
	}
	file << "(db.Model):" << endl;
	file << "\t__tablename__ = '" << title << "'" << endl;
	file << "\t" << id << " = db.Column(db.DateTime, primary_key=True)" << endl;
	file << "\t" << mrnumber << " = db.Column(db.Integer)" << endl;

	for (unsigned int i = 0; i < col.size(); ++i) {
		file << "\t" << col[i].name << " = db.Column(db.";

		if (col[i].type == 'i') {
			file << "Integer";
		}
		else if (col[i].type == 'n') {
			file << "Numeric(" << col[i].value1 << "," << col[i].value2 << ")";
		}
		else if (col[i].type == 'd') {
			file << "Date()";
		}
		else if (col[i].type == 't') {
			file << "Time()";
		}
		else if (col[i].type == 's') {
			file << "String(" << col[i].value1 << ")";
		}

		file << ")" << endl;
	}

	file << endl;

	file << "    def __init__(self, " << id << ", " << mrnumber;
	for (unsigned int i = 0; i < col.size(); ++i) {
		file << ", " << col[i].name;
	}
	file << "):" << endl;

	file << "\t\tself." << id << " = " << id << endl;
	file << "\t\tself." << mrnumber << " = " << mrnumber << endl;

	for (unsigned int i = 0; i < col.size(); ++i) {

		if (col[i].required == true) {
			file << "\t\tself." << col[i].name << " = " << col[i].name << endl;
		}
		else {
			file << "\t\tself." << col[i].name << " = valid(" << col[i].name << ")" << endl;

		}
	}

	file << endl;

	file << "#### Form ####" << endl;

	file << "\t\tif source_file == '";
	convert = toupper(title[0]);
	file << convert;

	for (unsigned int i = 1; i < title.length(); ++i) {

		if (title[i] == '_') {
			file << " ";
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
		else {
			file << title[i];
		}
	}

	file << "':" << endl;
	file << "\t\t\treturn render_template('/forms/" << title << ".html', display_name=patient_selected, source=source_file)" << endl << endl;


	file << "#### Submit ####" << endl;

	file << "\t\tif table == '";
	convert = toupper(title[0]);
	file << convert;

	for (unsigned int i = 1; i < title.length(); ++i) {

		if (title[i] == '_') {
			file << " ";
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
		else {
			file << title[i];
		}
	}

	file << "':" << endl;

	file << "\t\t\t" << mrnumber << " = request.form['" << mrnumber << "']" << endl;

	for (unsigned int i = 0; i < col.size(); ++i) {
		file << "\t\t\t" << col[i].name << " = request.form['" << col[i].name << "']" << endl;
	}

	file << "\t\t\t" << id << " = datetime.datetime.now()" << endl;

	file << "\t\t\t" << "db.session.query(";
	convert = toupper(title[0]);

	file << convert;
	for (unsigned int i = 1; i < title.length(); ++i) {

		file << title[i];

		if (title[i] == '_') {
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
	}
	file << ")" << endl;
	file << "\t\t\t" << "data = ";

	convert = toupper(title[0]);

	file << convert;
	for (unsigned int i = 1; i < title.length(); ++i) {

		file << title[i];

		if (title[i] == '_') {
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
	}

	file << "(" << id;
	for (unsigned int i = 0; i < col.size(); ++i) {
		file << ", " << col[i].name;
	}
	file << ")" << endl;
	file << "\t\t\t" << "db.session.add(data)" << endl;
	file << "\t\t\t" << "db.session.commit()" << endl;
	file << "\t\t\t" << "return render_template('index.html', message='Data Was Successfully Saved')" << endl;

	file << endl;
	cout << "PYTHON CREATED" << endl;

	/**** HTML ****/
	file << "#### HTML ####" << endl;

	file << "<option value=\"";

	convert = toupper(title[0]);
	file << convert;

	for (unsigned int i = 1; i < title.length(); ++i) {

		if (title[i] == '_') {
			file << " ";
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
		else {
			file << title[i];
		}
	}

	file << "\">";
	convert = toupper(title[0]);
	file << convert;

	for (unsigned int i = 1; i < title.length(); ++i) {

		if (title[i] == '_') {
			file << " ";
			convert = toupper(title[i + 1]);
			file << convert;
			++i;
		}
		else {
			file << title[i];
		}
	}

	file << "</option>" << endl;
	cout << "SELECT HTML OPTION CREATED" << endl;


	/**** HTML ****/
	/*
	file << "\n" << title << ".html has been created. Place in templates/forms." << endl;

	for (unsigned int i = 0; i < col.size(); ++i) {

		file << "<h4>";
		convert = toupper(col[i].name[0]);
		file << convert;

		for (unsigned int j = 1; j < col[i].name.length(); ++j) {

			if (col[i].name[j] == '_') {
				file << " ";
				convert = toupper(col[i].name[j + 1]);
				file << convert;
				++j;
			}
			else {
				file << col[i].name[j];
			}
		}

		file << "</h4> ";
		string zeros = "";
		string nines = "";

		if (col[i].type == 'i') {
			file << "<input type=\"";
			file << "number\" name=\"" << col[i].name << "\" placeholder=\"0\"";
		}
		else if (col[i].type == 'n') {
			file << "<input type=\"";
			file << "number\" name=\"" << col[i].name << "\" placeholder=\"";
			for (unsigned int k = 0; k < col[i].value1 - col[i].value2; ++k) {
				zeros += "0";
				nines += +"9";
			}
			if (col[i].value2 != 0) {
				zeros += ".";
				nines += ".";
				for (int k = 0; k < col[i].value2; ++k) {
					zeros = zeros + "0";
					nines = nines + "9";
				}
			}

			file << zeros << "\" min=\"0\" max=\"" << nines << "\"";

			if (col[i].value2 != 0) {
				file << " step=\"0.";
				for (int k = 0; k < col[i].value2 - 1; ++k) {
					file << "0";
				}
				file << "1\"";
			}
		}
		else if (col[i].type == 'd') {
			file << "<input type=\"";
			file << "date\" name=\"" << col[i].name << "\"";
		}
		else if (col[i].type == 't') {
			file << "<input type=\"";
			file << "time\" name=\"" << col[i].name << "\"";
		}
		else if (col[i].type == 's') {

			//<h4>Comments< / h4> <textarea name = "comments", cols = "30", rows = "5", placeholder = "Comments", maxlength = 500>< / textarea>
			if (col[i].value1 < 40) {
				file << "<input type=\"";
				file << "text\" name=\"" << col[i].name << "\" placeholder=\"Text(";
				file << col[i].value1 << ")\" maxlength=" << col[i].value1;
			}
			else {
				file << "<textarea name=\"" << col[i].name << "\" placeholder=\"Text(";
				file << col[i].value1 << ")\" maxlength=" << col[i].value1;

				if (col[i].value1 > 40 && col[i].value1 <= 80) {
					file << " rows=2";
				}
				else if (col[i].value1 > 80 && col[i].value1 <= 120) {
					file << " rows=3";
				}
				else if (col[i].value1 > 120 && col[i].value1 <= 160) {
					file << " rows=4";
				}
				else {
					file << " rows=5";
				}

			}
		}

		if (col[i].required == true) {
			file << " required ";
		}

		if (col[i].type == 's' && col[i].value1 > 40) {
			file << "></textarea>";
		}
		else {
			file << "/>" << endl;
		}
	}
	*/

	file.close();

	/**** CREATE HTML ****/
	fstream inFile;
	fstream outFile;
	inFile.open("template.html", ios::in);
	outFile.open(title + ".html", ios::out);
	int count1 = col.size() / 3;
	int count2 = col.size() / 3;

	if (col.size() % 3 == 1) {
		count1++;
	}
	else if (col.size() % 3 == 2) {
		count1++;
		count2++;
	}

	count2 += count1;

	if (inFile.is_open()) {
		for (unsigned int i = 0; i < 47; ++i) {
			std::getline(inFile, str);
			outFile << str << endl;
		}
	}

	cout << "WHAT IS GOING ON?" << endl;

	for (unsigned int i = 0; i < col.size(); ++i) {

		if ((i == count1 || i == count2) && col.size() != 1) {
			outFile << "\t\t</div>\n\n\t\t<div class=\"select-two\">" << endl;
		}

		outFile << "\t\t\t<h4>";
		convert = toupper(col[i].name[0]);
		outFile << convert;

		for (unsigned int j = 1; j < col[i].name.length(); ++j) {

			if (col[i].name[j] == '_') {
				outFile << " ";
				convert = toupper(col[i].name[j + 1]);
				outFile << convert;
				++j;
			}
			else {
				outFile << col[i].name[j];
			}
		}

		outFile << "</h4> ";
		string zeros = "";
		string nines = "";

		if (col[i].type == 'i') {
			outFile << "<input type=\"";
			outFile << "number\" name=\"" << col[i].name << "\" placeholder=\"0\"";
		}
		else if (col[i].type == 'n') {
			outFile << "<input type=\"";
			outFile << "number\" name=\"" << col[i].name << "\" placeholder=\"";
			for (unsigned int k = 0; k < col[i].value1 - col[i].value2; ++k) {
				zeros += "0";
				nines += +"9";
			}
			if (col[i].value2 != 0) {
				zeros += ".";
				nines += ".";
				for (int k = 0; k < col[i].value2; ++k) {
					zeros = zeros + "0";
					nines = nines + "9";
				}
			}

			outFile << zeros << "\" min=\"0\" max=\"" << nines << "\"";

			if (col[i].value2 != 0) {
				outFile << " step=\"0.";
				for (int k = 0; k < col[i].value2 - 1; ++k) {
					outFile << "0";
				}
				outFile << "1\"";
			}
		}
		else if (col[i].type == 'd') {
			outFile << "<input type=\"";
			outFile << "date\" name=\"" << col[i].name << "\"";
		}
		else if (col[i].type == 't') {
			outFile << "<input type=\"";
			outFile << "time\" name=\"" << col[i].name << "\"";
		}
		else if (col[i].type == 's') {

			if (col[i].value1 < 40) {
				outFile << "<input type=\"";
				outFile << "text\" name=\"" << col[i].name << "\" placeholder=\"Text(";
				outFile << col[i].value1 << ")\" maxlength=" << col[i].value1;
			}
			else {
				outFile << "<textarea name=\"" << col[i].name << "\" placeholder=\"Text(";
				outFile << col[i].value1 << ")\" maxlength=" << col[i].value1;

				if (col[i].value1 > 40 && col[i].value1 <= 80) {
					outFile << " rows=2";
				}
				else if (col[i].value1 > 80 && col[i].value1 <= 120) {
					outFile << " rows=3";
				}
				else if (col[i].value1 > 120 && col[i].value1 <= 160) {
					outFile << " rows=4";
				}
				else {
					outFile << " rows=5";
				}

			}
		}

		if (col[i].required == true) {
			outFile << " required ";
		}

		if (col[i].type == 's' && col[i].value1 > 40) {
			outFile << "></textarea>\n";
		}
		else {
			outFile << "/>\n";
		}
	}

	if (col.size() == 2) {
		outFile << "\t\t</div>\n\n\t\t<div class=\"select-two\">" << endl;
	}
	else if (col.size() == 1) {
		outFile << "\t\t</div>\n\n\t\t<div class=\"select-two\">" << endl;
		outFile << "\t\t</div>\n\n\t\t<div class=\"select-two\">" << endl;
	}

	cout << "IS THIS OVER?" << endl;
	if (inFile.is_open()) {
		while (getline(inFile, str)) {
			outFile << str << endl;
		}
	}

	inFile.close();
	outFile.close();
	return 0;
}