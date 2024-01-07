#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <ostream>
#include <map>
#include <utility>
#include <set>
#include <tuple>
#include <ios>
#include <limits>
#include <cmath>
#include <stdlib.h>
using namespace std;
ifstream ifile;
ofstream outfile;

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		struct File

task:	    Declare struct variables of column number and row number indicated in file.
            Members are used in readTitle, readData and file operation
members:    column number and row number described in file
**************************************************************/
struct File
{
    int cols;
    int rows;
};

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		struct Dist_and_histogram

task:		Declare struct variables of vector of distinct value of data and
            its frequency. Members are used in histogram and distinct_frequency.
members:    vector of data for compute distinct frequency and histogram,
            frequency of the data
**************************************************************/
struct Dist_and_histogram
{
    vector<double>cal_distinct;
    vector<int>frequency;
};

//Function prototype
int main_menu_action();
int file_op_choice();
bool chk_format2(vector<string>, vector<vector<double>>);
void chk_format1(vector<string>, vector<vector<double>>, File&);
int file_operation(vector<string>&, vector<vector<double>>&, bool&, File&, int&);
void read_file(vector<string>&, vector<vector<double>>&, File&, int&);
void show_data(vector<string>, vector<vector<double>>);
vector<string> readTitles(vector<string>&, File&);
vector<vector<double>> readData(vector<vector<double>>&, File&);
int report_choice();
void html_txt(function<void()>, function<void()>);
void statistical_report_txt(function<void()>);
void statistical_report_html(function<void()>);
void compute_data_menu(vector<string>, vector<vector<double>>, bool&);
void switch_compute(vector<string>, vector<vector<double>>, bool&, int, bool&);
void sort_data_menu(vector<string>, vector<vector<double>>, bool&);
int sub_sort();
double calmean(vector<string>, vector<vector<double>>, int);
double maximum(vector<string>, vector<vector<double>>, int);
double minimum(vector<string>, vector<vector<double>>, int);
double median(vector<string>, vector<vector<double>>, int);
double variance(vector<string>, vector<vector<double>>, int);
double standardDeviation(vector<string>, vector<vector<double>>, int);
int column_stats(vector<string>, vector<vector<double>>, int&);
vector<double>push_cols_vector(vector<string>, vector<vector<double>>, int);
vector<vector<double>>dimensional(vector<string>, vector<vector<double>>, const int&, int);
void statistic_option(vector<string>, vector<vector<double>>, bool&);
void statistic_table(vector<string>&, int, double*);
void html_upper(vector<string>&, int);
void statistic_table_html(vector<string>&, int, double*);
void alltable(vector<string>, vector<vector<double>>, int, int);
void alltable_html(vector<string>, vector<vector<double>>, int, int);
void column_menu(vector<string>, int&);
int column_option(vector<string>, vector<vector<double>>, int&);
void table_above_below_mean(vector<string>, vector<vector<double>>, bool&);
void result_mean_table(vector<string>&, double&, int&, vector<double>&, vector<double>&, int&, int&, vector<double>&, vector<double>&);
void mean_table_html(vector<string>&, double&, int&, vector<double>&, vector<double>&, int&, int&, vector<double>&, vector<double>&);
void distinct_frequency(vector<string>, vector<vector<double>>, Dist_and_histogram& common, bool&);
void result_distinct_frequency(int, vector<string>, Dist_and_histogram& common);
void distinct_frequency_html(int, vector<string>, Dist_and_histogram& common);
void move_to_histogram(int, vector<string>, vector<vector<double>>, Dist_and_histogram& common);
void histogram(int, vector<string>, vector<vector<double>>, Dist_and_histogram& common);
void result_histogram(vector<int>, vector<string>, vector<vector<double>>, int);
void histogram_html(vector<int>, vector<string>, vector<vector<double>>, int);
bool ascending(const pair<double, double>&, const pair<double, double>&);
bool descending(const pair<double, double>&, const pair<double, double>&);
void sort_data_ascending(vector<string>, vector<vector<double>>, bool&);
void sort_data_descending(vector<string>, vector<vector<double>>, bool&);
void sort_data_result(vector<string>, vector<pair<int, int>>, int, string);
void sort_data_html(vector<string>, vector<pair<int, int>>, int, string);
void column_menu(vector<string>, int&);
int column_linearAndPearson(int&, int&, vector<string>, vector<vector<double>>);
void dependentVal(int&, int&, bool&, int&, int);
void linear_regression(vector<string>, vector<vector<double>>, bool&);
void result_linear_regression(vector<string>, vector<vector<double>>, int&, int&, vector<double>&, vector<double>&,
    vector<double>&, vector<double>&, double&, double&, double&, double&, double&, double&);
void linear_regression_html(vector<string>, vector<vector<double>>, int&, int&, vector<double>&, vector<double>&,
    vector<double>&, vector<double>&, double&, double&, double&, double&, double&, double&);
void pearson_steps(int&, int&, vector<double>&, vector<double>&, vector<double>&, vector<double>&,
    vector<double>&, vector<double>&, vector<double>&, double&, double&, double&, double&, double&);
void pearson_correlation(vector<string>, vector<vector<double>>, bool&);
void result_pearson_correlation(vector<string>, vector<vector<double>>, int&, int&, vector<double>&, vector<double>&, vector<double>&,
    vector<double>&, vector<double>&, vector<double>&, vector<double>&, double&, double&, double&, double&, double&, double&);
void pearson_th();
void pearson_correlation_html(vector<string>, vector<vector<double>>, int&, int&, vector<double>&, vector<double>&, vector<double>&,
    vector<double>&, vector<double>&, vector<double>&, vector<double>&, double&, double&, double&, double&, double&, double&);
void case2(vector<string>, vector<vector<double>>, const int&);
void case3(vector<string>, vector<vector<double>>, const int&);

/**************************************************************
Programmer:	    Adeline Fong Li Ling
Name: 		    main_menu_action

task:		    Get user input and check error for main menu
data returned:  User choice for main menu
Referred to: https://www.tutorialspoint.com/what-is-the-use-of-cin-ignore-in-cplusplus
**************************************************************/
int main_menu_action()
{
    int action;

    do {
            cout << "*********************" << endl;
            cout << "|     Main Menu     |" << endl;
            cout << "*********************" << endl;
            cout << "| 1. File operation |" << endl;
            cout << "| 2. Compute data   |" << endl;
            cout << "| 3. Sort data      |" << endl;
            cout << "| 4. Exit           |" << endl;
            cout << "*********************" << endl << endl;
            cout << "Please select an action: ";
            cin >> action;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Bad entry. Please enter a number to choose." << endl;
            }
            else if (action < 1 || action > 4)
                cout << endl << "Please choose either one from 1 to 4." << endl;
        } while (action < 1 || action > 4);

    return action;
}

/**************************************************************
Programmer:	    Adeline Fong Li Ling
Name: 		    file_op_choice

task:			Get user input and check error for menu of file operation
data returned:  User choice for file operation
Referred to: https://www.tutorialspoint.com/what-is-the-use-of-cin-ignore-in-cplusplus
**************************************************************/
int file_op_choice()
{
    int choice;
    do {
            cout << "**************************" << endl;
            cout << "|     File Operation     |" << endl;
            cout << "**************************" << endl;
            cout << "| 1. Read file           |" << endl;
            cout << "| 2. Show no. of columns |" << endl;
            cout << "| 3. Show no. of rows    |" << endl;
            cout << "| 4. Show column names   |" << endl;
            cout << "| 5. Show data           |" << endl;
            cout << "| 6. Back to main menu   |" << endl;
            cout << "**************************" << endl;
            cout << "Please select next step: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Bad entry. Please enter a number to choose." << endl;
            }
            else if (choice < 1 || choice > 6)
                cout << endl << "Please choose either one from 1 to 6." << endl;
        } while (choice < 1 || choice > 6);

    return choice;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		chk_format2

task:		Check file format. If the number of header(title) is
            not same as the number of data column, return true for error,
            indicates that format is not logical.
data in:	title from file, data from file
data returned: error (true or false)
**************************************************************/
bool chk_format2(vector<string>title_found, vector<vector<double>>data_found)
{
    int data_col = data_found[0].size();
    int title_col = title_found.size();

    if (title_col != data_col)
        return true;
    else
        return false;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		chk_format1

task:		Check file description of number of rows and number of columns.
            If the number does not match the data, error is prompted.
data in:	title from file, data from file and struct of File
**************************************************************/
void chk_format1(vector<string>title_found, vector<vector<double>>data_found, File &f)
{
    int error = 0;
    int data_sz = data_found.size();
    int title_sz = title_found.size();

    if ((data_sz != f.rows) || (title_sz != f.cols))
    {
        cout << "######################## FILE ERROR ############################" << endl << endl;
        cout << "CAUTION: Error in description is detected." << endl;
        error += 1;
    }
    if (data_sz != f.rows)
        cout << "(Description of no. of rows does not match the actual row)" << endl;
    if (title_sz != f.cols)
        cout << "(Description of no. of columns does not match the actual column)" << endl;
    cout << endl;

    if (chk_format2(title_found, data_found))
    {
        if (error==0)
            cout << "######################## FILE ERROR ############################" << endl << endl;

        cout << "CAUTION: Format error is detected." << endl;
        cout << "(Header name does not comply with the existing data.)" << endl;
        error += 1;
    }

    if (error!=0)
        cout << "################################################################" << endl << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		file_operation

task:		Obtain choice from the menu and use if-else statement to proceed to next
            operation for file. User must first select 1 (read file) in order to proceed
            to 2,3,4 or 5. However, 6 can be selected anytime to back to main menu.
data in:	title from file, data from file, bool for repeating file operation, struct of File
            and number of file read
data returned: number of file read
**************************************************************/
int file_operation(vector<string>&title_found, vector<vector<double>>&data_found, bool& show_file_menu, File& f, int& read)
{
    int choice = file_op_choice();

    if (choice == 1)
        read_file(title_found, data_found, f, read);

    else if (choice == 2)
    {
        if (read == 0)
            cout << "Please read the file first." << endl;
        else
            cout << "Number of columns is: " << f.cols << endl;
    }
    else if (choice == 3)
    {
        if (read == 0)
            cout << "Please read the file first." << endl;
        else
            cout << "Number of rows is: " << f.rows << endl;
    }
    else if (choice == 4)
    {
        if (read == 0)
            cout << "Please read the file first." << endl;
        else
            cout << "Column names are as follow: " << endl;

        for (int i = 0; i < title_found.size(); i++)
            cout << i + 1 << ". " << title_found[i] << endl;
    }
    else if (choice == 5)
    {
        if (read == 0)
            cout << "Please read the file first." << endl;
        else
            show_data(title_found, data_found);
    }
    else if (choice == 6)
    {
        show_file_menu = false;
        system("cls");
    }

    return read;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		show_data

task:		Print the data content of the file in table form
data in:	title from file, data from file
**************************************************************/
void show_data(vector<string>title_found, vector<vector<double>>data_found)
{
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < title_found.size(); i++)
        cout << setw(10) << title_found[i] << " | ";

    cout << endl << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < data_found.size(); i++)
    {
        for (int j = 0; j < data_found[i].size(); j++)
        {
            cout << fixed << setprecision(0) << setw(10) << data_found[i][j] << " | ";
        }
        cout << endl;
    }

    cout << "----------------------------------------------------------------" << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		read_file

task:		Open file and read the file if the file is found. If the file has
            already being read, it will inform user to proceed with others. If file is not found,
            program exit.
data in:	title from file, data from file, struct of File and number of file read
**************************************************************/
void read_file(vector<string>&title_found, vector<vector<double>>&data_found, File& f, int& read)
{
    static string fname;

    if (read != 0)
    {
        cout << "The file \"" << fname << "\" is already loaded." << endl;
        cout << "Please proceed with other operations." << endl << endl;
    }
    else
    {
        cout << "Please type the file name to open (e.g. data.txt): ";
        getline(cin, fname);
        ifile.open(fname.c_str());

        if (!ifile)
        {
            cout << "File is not found..." << endl;
            exit(-1);
        }
        else
            cout << "File is loaded successfully..." << endl;

        vector<vector<double>> data;
        vector<string> titles;
        title_found = readTitles(titles, f);
        data_found = readData(data, f);

        chk_format1(title_found, data_found, f);
        read++;
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		readTitles

task:		Read the file line by line, using delimiter to get the value of title.
            For the last item of each line, it get title by finding the non-empty region.
data in:	vector for storing title and struct of File
data returned: title found in file
**************************************************************/
vector<string> readTitles(vector<string>& v, File& f)
{
    string line;

    ifile >> f.cols;
    ifile >> line;
    string delimiter = ",";
    char newline = '\n';
    size_t pos = 0;
    string token;
    while ((pos = line.find(delimiter)) != string::npos)
    {
        token = line.substr(0, pos);
        v.push_back(token);
        line.erase(0, pos + (delimiter.length()));
    }
    if (!line.empty())
        v.push_back(line);

    return v;
}
/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		readData

task:		Read the file line by line, using delimiter to get the value of data.
            For the last item of each line, it get by finding the non-empty region.
            Data read is converted into double. The data vector is stored into another
            vector to form 2D vector.
data in:	vector for storing data and struct of File
data returned: data found in file
**************************************************************/
vector<vector<double>> readData(vector<vector<double>>& v, File& f)
{
    string line;

    ifile >> f.rows;
    string delimiter = ",";

    while (ifile >> line)
    {
        vector<double> vec;
        string s(line);
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos)
        {
            token = s.substr(0, pos);
            stringstream converter(token);
            double xx;
            converter >> xx;
            vec.push_back(xx);
            s.erase(0, pos + delimiter.length());
        }
        if (!s.empty())
        {
            double xx = stof(s);
            vec.push_back(xx);
        }
        v.push_back(vec);
    }
    return v;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		report_choice

task:		Allow user to save result of computation to text file, html file, both or not save.
            Get input and check error.
data returned: user choice for generate report
**************************************************************/
int report_choice()
{
    int sv;
    cout << "Press ENTER key to continue..." << endl;
    cin.get();

    do {
            cout << "************************" << endl;
            cout << "|    Generate Report   |" << endl;
            cout << "************************" << endl;
            cout << "| 1. Save to text file |" << endl;
            cout << "| 2. Save to html file |" << endl;
            cout << "| 3. Save to both      |" << endl;
            cout << "| 4. Don't save        |" << endl;
            cout << "************************" << endl;
            cout << "Please select what to do with this result: ";
            cin >> sv;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Bad entry. Please enter a number to choose." << endl;
            }
            else if (sv < 1 || sv > 4)
                cout << endl << "Please choose either one from 1 to 4." << endl;
        } while (sv < 1 || sv > 4);

    return sv;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		html_txt

task:		Either save result of computation to text file, html file, both or not save
            according to user input. Execute functions to generate report chosen.
            If user choose 4, it will break without saving result.
data in:    function of text result and function of html result
Referred to:http://www.cplusplus.com/forum/beginner/195580/
**************************************************************/
void html_txt(function<void()>result1, function<void()>result2)
{
    int sv = report_choice();

    switch (sv)
    {
        case 1:
        {
            statistical_report_txt(result1);
            cout << "Result has been saved successfully." << endl;
            break;
        }
        case 2:
        {
            statistical_report_html(result2);
            cout << "Result has been saved successfully." << endl;
            break;
        }
        case 3:
        {
            statistical_report_txt(result1);
            statistical_report_html(result2);
            cout << "Result has been saved successfully." << endl;
            break;
        }
        case 4:
            break;
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		statistical_report_txt

task:		Open text file for append. If the file cannot be created, it will prompt error.
            If the file is ready, write the result table function into file by using streambuf to
            redirect output.
data in:    function of text result
Referred to:https://titanwolf.org/Network/Articles/Article?AID=07d04716-6ad9-46b7-8337-af74dc4c4af0#gsc.tab=0
**************************************************************/
void statistical_report_txt(function<void()>result1)
{
    outfile.open("txt_report.txt", ios_base::app);

    if (!outfile)
    {
        cout << "Text file cannot be created..." << endl;
        exit(-1);
    }
    else
    {
        streambuf* outbuf = cout.rdbuf(); // set cout to use the custom streambuf
        cout.rdbuf(outfile.rdbuf()); // redirect cout to the txt file
        result1();
        cout.rdbuf(outbuf); // restore the original output
    }

    outfile.close();
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		statistical_report_html

task:		Open html file for append. If the file cannot be created, it will prompt error.
            If the file is ready, write the result table function into file.
data in:    function of html result
**************************************************************/
void statistical_report_html(function<void()>result2)
{
    outfile.open("html_report.html", ios_base::app);

    if (!outfile)
    {
        cout << "HTML file cannot be created..." << endl;
        exit(-1);
    }
    else
        result2();

    outfile.close();
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		compute_data_menu

task:		Get user input and check error for the menu of compute data. Clear screen
            after each successful input. Function of switch_compute is called to proceed.
data in:    title from file, data from file, bool of repeating compute data menu
**************************************************************/
void compute_data_menu(vector<string>title_found, vector<vector<double>>data_found, bool& show_compute_menu)
{
    int comp;
    bool repeat = true;
    do {
            cout << "***************************" << endl;
            cout << "|      Compute Data       |" << endl;
            cout << "***************************" << endl;
            cout << "| 1. Statistics           |" << endl;
            cout << "| 2. Above and below mean |" << endl;
            cout << "| 3. Distinct frequency   |" << endl;
            cout << "| 4. Linear regression    |" << endl;
            cout << "| 5. Pearson correlation  |" << endl;
            cout << "| 6. Back to main menu    |" << endl;
            cout << "***************************" << endl;
            cout << "Please select a computation from above: ";
            cin >> comp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Bad entry. Please enter a number to choose." << endl;
            }
            else if (comp < 1 || comp > 6)
                cout << endl << "Please choose either one from 1 to 6." << endl;
        } while (comp < 1 || comp > 6);

    system("cls");

    switch_compute(title_found, data_found, show_compute_menu, comp, repeat);
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		switch_compute

task:		Switch-case is used to proceed to computation according to user's input.
            Each operation will repeat until the bool statement turn false (user choose
            to end operation). When case 6 is chosen, user can go back to main menu.
data in:    title from file, data from file, bool for repeating compute data menu,
            user choice and bool for repeating computations
**************************************************************/
void switch_compute(vector<string>title_found, vector<vector<double>>data_found, bool& show_compute_menu, int comp, bool& repeat)
{
    switch (comp){
        case 1:
        {
            while (repeat == true){
                cout << endl << "Current operation: Statistics" << endl;
                statistic_option(title_found, data_found, repeat);
            }
            break;
        }
        case 2:
        {
            while (repeat == true){
                cout << endl << "Current operation: Above and below mean" << endl;
                table_above_below_mean(title_found, data_found, repeat);
            }
            break;
        }
        case 3:
        {
            while (repeat == true){
                cout << endl << "Current operation: Distinct frequency" << endl;
                Dist_and_histogram common;
                distinct_frequency(title_found, data_found, common, repeat);
            }
            break;
        }
        case 4:
        {
            while (repeat == true){
                cout << endl << "Current operation: Linear regression" << endl;
                linear_regression(title_found, data_found, repeat);
            }
            break;
        }
        case 5:
        {
            while (repeat == true){
                cout << endl << "Current operation: Pearson correlation" << endl;
                pearson_correlation(title_found, data_found, repeat);
            }
            break;
        }
        case 6:{
            cout << "Back to main menu..." << endl;
            show_compute_menu = false;
            break;
        }
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		sort_data_menu

task:		Call function of sub_sort for user input. Switch-case is used to proceed
            to sorting according to user's input. Each operation will repeat until the
            bool statement turn false (user choose to end operation). When case 3 is
            chosen, user can go back to main menu.
data in:    title from file, data from file, bool of repeating sort data menu
**************************************************************/
void sort_data_menu(vector<string>title_found, vector<vector<double>>data_found, bool& show_sort_menu)
{
    bool repeat = true;
    int comp = sub_sort();

    switch (comp)
    {
        case 1:
        {
            while (repeat == true)
            {
                cout << endl << "Current operation: Sort data in ascending order" << endl;
                sort_data_ascending(title_found, data_found, repeat);
            }
            break;
        }
        case 2:
        {
            while (repeat == true)
            {
                cout << endl << "Current operation: Sort data in descending order" << endl;
                sort_data_descending(title_found, data_found, repeat);
            }
            break;
        }
        case 3:
        {
            cout << "Back to main menu..." << endl;
            show_sort_menu = false;
            break;
        }
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		sub_sort

task:		Get user input and check error for menu of sort data. Clear screen
            after successful input.
data returned:  user choice for sort data menu
**************************************************************/
int sub_sort()
{
    int comp;

    do {
        cout << "*******************************" << endl;
        cout << "|          Sort Data          |" << endl;
        cout << "*******************************" << endl;
        cout << "| 1. Sort in ascending order  |" << endl;
        cout << "| 2. Sort in descending order |" << endl;
        cout << "| 3. Back to main menu        |" << endl;
        cout << "*******************************" << endl;
        cout << "Please select a computation from above: ";
        cin >> comp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Bad entry. Please enter a number to choose." << endl;
        }
        else if (comp < 1 || comp > 3)
            cout << endl << "Please choose either one from 1 to 3." << endl;
    } while (comp < 1 || comp > 3);

    system("cls");

    return comp;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		calmean

task:		Calculate mean for statistics. Data obtained from the file is stored
            into a vector. Sum of data is calculated and it is divided by size of data.
data in:    title from file, data from file and column chosen to compute
data returned: mean
**************************************************************/
double calmean(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    vector<double>cal_mean;

    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);

    double datafound[data_found.size()];
    //Calculate mean
    double sum = 0, mean;
    for (auto x : cal_mean)
        sum = sum + x;
    mean = sum / cal_mean.size();

    return mean;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		maximum

task:		Calculate maximum. Data obtained from the file is stored into a vector
            and it is copied to an array. First element of the array is assigned to max.
            Iterate through each element after first to get the max of whole array.
data in:    title from file, data from file and column chosen to compute
data returned: max
**************************************************************/
double maximum(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    vector<double>cal_mean;
    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);

    double datafound[data_found.size()];
    std::copy(cal_mean.begin(), cal_mean.end(), datafound);
    double max = datafound[0];
    for (int i = 1; i < data_found.size(); i++)
    {
        if (datafound[i] > max)
            max = datafound[i];
    }

    return max;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		minimum

task:		Calculate minimum. Data obtained from the file is stored into a vector
            and it is copied to an array. First element of the array is assigned to min.
            Iterate through each element after first to get the min of whole array.
data in:    title from file, data from file and column chosen to compute
data returned: min
**************************************************************/
double minimum(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    vector<double>cal_mean;
    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);

    double datafound[data_found.size()];
    std::copy(cal_mean.begin(), cal_mean.end(), datafound);
    double min = datafound[0];
    for (auto i = 1; i < data_found.size(); i++)
    {
        if (datafound[i] < min)
            min = datafound[i];
    }

    return min;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		median

task:		Calculate median. Data obtained from the file is stored into a vector
            and it is copied to an array. Data of the array is sorted. Median is
            obtained by checking for the even number.
data in:    title from file, data from file and column chosen to compute
data returned: median
**************************************************************/
double median(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    vector<double>cal_mean;
    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);

    double datafound[data_found.size()];
    std::copy(cal_mean.begin(), cal_mean.end(), datafound);
    double med;
    std::sort(datafound, datafound + data_found.size());        //sort ascending order

    med = datafound[(data_found.size() / 2)];
    if (data_found.size() % 2 == 0)
        med = (med + datafound[data_found.size() / 2 - 1]) / 2;

    return med;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		variance

task:		Calculate variance. Data obtained from the file is stored into a vector
            and it is copied to an array. Mean is calculated and so on, according to
            the formula.
data in:    title from file, data from file and column chosen to compute
data returned: variance
Formula source:http://www.statisticslectures.com/topics/variancesample/
**************************************************************/
double variance(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    vector<double>cal_mean;
    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);
    double datafound[data_found.size()];
    std::copy(cal_mean.begin(), cal_mean.end(), datafound);

    //Calculate mean
    double sum = 0, mean;
    for (auto x : cal_mean)
        sum = sum + x;
    mean = sum / cal_mean.size();
    //variance
    sum = 0;
    for (int i = 0; i < data_found.size(); i++)
    {
        datafound[i] = pow((datafound[i] - mean), 2);
        sum += datafound[i];
    }
    double var = sum / (data_found.size() - 1);

    return var;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		standardDeviation

task:		Calculate standard deviation. Data obtained from the file is stored
            into a vector and it is copied to an array. Calculate the variance
            and obtain standard deviation by exponent of 0.5.
data in:    title from file, data from file and column chosen to compute
data returned: standard deviation
Formula source:http://www.statisticslectures.com/topics/variancesample/
**************************************************************/
double standardDeviation(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    vector<double>cal_mean;
    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);

    double datafound[data_found.size()];
    std::copy(cal_mean.begin(), cal_mean.end(), datafound);
    //Calculate mean
    double sum = 0, mean;
    for (auto x : cal_mean)
        sum = sum + x;
    mean = sum / cal_mean.size();
    //variance
    sum = 0;
    for (int i = 0; i < data_found.size(); i++)
    {
        datafound[i] = pow((datafound[i] - mean), 2);
        sum += datafound[i];
    }
    double var = sum / (data_found.size() - 1);
    //Standard Deviation
    double stad = pow(var, 0.5);
    return stad;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		column_stats

task:		Get user input and check error for menu of statistics
data in:    title from file, data from file and column chosen to compute
data returned: numbering of the menu options (last title)
**************************************************************/
int column_stats(vector<string>title_found, vector<vector<double>>data_found, int &column)
{
    int count;
    do {
            count = 0;
            cout << "***************************" << endl;
            for (int i = 1; i < title_found.size(); i++)
            {
                title_found[i][0] = toupper(title_found[i][0]);
                cout << "| " << i << ". " << setw(20) << left << title_found[i] << " |" << endl;
                count++;
            }
            cout << "| " << count+1 << ". " << setw(20) << left << "All choices" << " |" << endl;
            cout << "| " << count+2 << ". " << setw(20) << left << "End this computation" << " |" << endl;
            cout << "***************************" << endl;

            cout << "Please select column to compute: ";
            cin >> column;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Bad entry. Please enter a number to choose." << endl;
            }
            else if (column < 1 || column > count+2)
                cout << endl << "Please choose either one from 1 to " << count+2 << "." << endl;

        } while (column < 1 || column > count+2);

    return count;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		push_cols_vector

task:		Store all value of statistics calculation (all columns) into a
            new vector.
data in:    title from file, data from file and column chosen to compute
data returned: vector of statistics values
**************************************************************/
vector<double> push_cols_vector(vector<string>title_found, vector<vector<double>>data_found, int column)
{
    double mean = calmean(title_found, data_found, column);
    double max = maximum(title_found, data_found, column);
    double min = minimum(title_found, data_found, column);
    double med = median(title_found, data_found, column);
    double var = variance(title_found, data_found, column);
    double stad = standardDeviation(title_found, data_found, column);

    // insert to vector
    vector<double> stat;
    stat.push_back(max);
    stat.push_back(min);
    stat.push_back(mean);
    stat.push_back(med);
    stat.push_back(var);
    stat.push_back(stad);

    return stat;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		dimensional

task:		Use 2D vector to manage values of all statistics
data in:    title from file, data from file, numbering of last title
            of menu and column to compute
data returned: vector of statistics values
**************************************************************/
vector<vector<double>>dimensional(vector<string>title_found, vector<vector<double>>data_found, const int &count, int column)
{
    //create dimensional vector
    vector<vector<double>> vec;
    for (int i = 0; i < count; i++)
    {
        column = column + 1;
        vector<double>stat = push_cols_vector(title_found, data_found, column);

        //insert to dimensional vector
        for (int i = 0; i < 1; i++)
        {
            vector<double>v1;
            for (int j = 0; j < 1; j++)
            {
                for (double x : stat)
                    v1.push_back(x);
            }
            vec.push_back(v1);
        }
    }

    return vec;
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		statistic_option

task:		If-else statement used to compute statistics. If user input is 5 (compute all),
            2D vector is used to insert the statistics calculated. If user input is
            1, 2, 3 or 4, the statistics calculated is stored in an array. Print result of
            table and generate reports. If user input is 6, it will leave the function immediately
            to back to compute data menu.
data in:    title from file, data from file and bool for repeating statistics
**************************************************************/
void statistic_option(vector<string>title_found, vector<vector<double>>data_found, bool& repeat)
{
    int column;
    int count = column_stats(title_found, data_found, column);

    if (column == count+2)
    {
        cout << "Back to Compute Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    if (column == count+1)
    {
        column = 0;
        vector<vector<double>>vec = dimensional(title_found, data_found, count, column);

        alltable(title_found, vec, column, count);
        auto func1 = bind(alltable, title_found, vec, column, count);
        auto func2 = bind(alltable_html, title_found, vec, column, count);
        html_txt(func1, func2);
    }
    else
    {
        double mean = calmean(title_found, data_found, column);
        double max = maximum(title_found, data_found, column);
        double min = minimum(title_found, data_found, column);
        double med = median(title_found, data_found, column);
        double var = variance(title_found, data_found, column);
        double stad = standardDeviation(title_found, data_found, column);
        // insert to array
        double statistic[] = { max, min, mean, med, var,stad };

        statistic_table(title_found, column, statistic);
        auto func1 = bind(statistic_table, title_found, column, statistic);
        auto func2 = bind(statistic_table_html, title_found, column, statistic);
        html_txt(func1, func2);
    }
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		statistic_table

task:		Print formatted table result of statistics when user choose only
            1 column to compute
data in:    title from file, column, statistic results
**************************************************************/
void statistic_table(vector<string>& title_found, int column, double* statistic)
{
    string name[6] = { "maximum","minimum","mean","median","variance","standard deviation" };

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);
    cout << endl << "RESULT OF: " << title_found[column] << endl;
    cout << "STATISTICAL TABLE" << endl;
    cout << "--------------------------------" << endl;
    cout << setw(20) << "Statistic" << "|";

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);
    cout << setw(10) << title_found[column] << "|  " << endl;
    cout << "--------------------------------" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << setw(20);
        cout << name[i] << "|";
        cout << setw(10);
        cout << showpoint << fixed << setprecision(2) << statistic[i] << "|  " << endl;
    }
    cout << "--------------------------------" << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		html_upper

task:		Upper part of html which include title and name of result
data in:    title from file, column chosen
**************************************************************/
void html_upper(vector<string>& title_found, int column)
{
    outfile << "<!doctype html><html>"; //starting html
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);
    outfile << "<head>";
    outfile << "<link rel=\"stylesheet\" href=\"style_table.css\">";
    outfile << "<title>" << "Statistical report(HTML)" << "</title>";
    outfile << "</head>";
    outfile << "<body>";
    outfile << "<span style='font-weight: bold'>";
    outfile << "<p style='text-decoration: underline'>" << "RESULT OF: " << title_found[column] << "</p>";
    outfile << "</span>";
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		statistic_table_html

task:		Generate html report of statistics when user choose only 1 column to
            compute. The html file is opened for append. External css is used for styling.
data in:    title from file, column, statistic results
**************************************************************/
void statistic_table_html(vector<string>& title_found, int column, double* statistic)
{
    string name[6] = { "maximum","minimum","mean","median","variance","standard deviation" };

    html_upper(title_found, column);

    outfile << "<h4>" << "STATISTICS TABLE" << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>";
    outfile << "<th style='font-weight: bold'>" << "Statistic" << "</th>";

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);
    outfile << "<th style='font-weight: bold'>" << title_found[column] << "</th>";
    outfile << "</tr>";
    for (auto i = 0; i < 6; i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << name[i] << "</td>";
        outfile << "<td>" << showpoint << fixed << setprecision(2) << statistic[i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "</table><br>";
    outfile << "</body>";
    //ending html
    outfile << "</html>";
}

/**************************************************************
Programmer:	Kong Wan Er
Name: 		alltable

task:		Print formatted table result of statistics when user choose all column
            to compute
data in:    title from file, vector of statistics result, column, numbering of menu
            choice (last)
**************************************************************/
void alltable(vector<string>title_found, vector<vector<double>>vec, int column, int count)
{
    string name[6] = { "maximum","minimum","mean","median","variance","standard deviation" };
    cout << endl << "RESULT OF: " << "ALL CHOICES" << endl;
    cout << "STATISTICAL TABLE" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << setw(20) << "Statistic" << "|";
    column = 0;

    for (int i = 0; i < vec.size(); i++)
    {
        column = column + 1;
        title_found[column][0] = toupper(title_found[column][0]);
        cout << setw(10) << title_found[column] << "|  ";
    }
    cout << " " << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    for (int i = 0; i < 6; i++)
    {
        cout << setw(20);
        cout << name[i] << "|";
        for (int j = 0; j < count; j++)
            cout << showpoint << fixed << setprecision(2) << setw(10) << vec[j][i] << "|  ";
        cout << " " << endl;
    }
    cout << "-----------------------------------------------------------------------" << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		alltable_html

task:		Generate html report of statistics when user choose all column to
            compute. The html file is opened for append. External css is used for styling.
data in:    title from file, vector of statistics result, column, numbering of menu
            choice (last)
**************************************************************/
void alltable_html(vector<string>title_found, vector<vector<double>>vec, int column, int count)
{
    string name[6] = { "maximum","minimum","mean","median","variance","standard deviation" };

    outfile << "<!doctype html><html>"; //starting html
    column = 0;
    outfile << "<head>";
    outfile << "<link rel=\"stylesheet\" href=\"style_table.css\">";
    outfile << "<title>" << "Statistical report(HTML)" << "</title>";
    outfile << "</head>";
    outfile << "<body>";
    outfile << "<span style='font-weight: bold'>";
    outfile << "<p style='text-decoration: underline'>" << "RESULT OF: " << "ALL CHOICES" << "</p>";
    outfile << "</span>";

    outfile << "<h4>" << "STATISTICS TABLE" << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>";
    outfile << "<th style='font-weight: bold'>" << "Statistic" << "</th>";
    for (int i = 0; i < vec.size(); i++)
    {
        column = column + 1;
        title_found[column][0] = toupper(title_found[column][0]);
        outfile << "<th style='font-weight: bold'>" << title_found[column] << "</th>";
    }
    outfile << "</tr>";
    for (auto i = 0; i < 6; i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << name[i] << "</td>";
        for (int j = 0; j < count; j++)
            outfile << "<td style='font-weight: bold'>" << showpoint << fixed << setprecision(2) << vec[j][i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "</table><br>";
    outfile << "</body>";
    //ending html
    outfile << "</html>";
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		column_menu

task:		Display menu for user to choose a column that is from
            the titles in the file
data in:    title from file, numbering of menu element
**************************************************************/
void column_menu(vector<string>title_found, int& count)
{
    cout << "***************************" << endl;
    for (int i = 1; i < title_found.size(); i++)
    {
        title_found[i][0] = toupper(title_found[i][0]);
        cout << "| " << i << ". " << setw(20) << left << title_found[i] << " |" << endl;
        count++;
    }
    cout << "| " << count + 1 << ". " << setw(20) << left << "End this computation" << " |" << endl;
    cout << "***************************" << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		column_option

task:		Get user input and check error for the column choice menu (used by distinct frequency,
            table of above and below mean, and sorting)
data in:    title from file, data from file, column chosen
data returned: numbering of menu option (last)
**************************************************************/
int column_option(vector<string>title_found, vector<vector<double>>data_found, int &column)
{
    int count;
    do {
            count = 0;
            column_menu(title_found, count);

            cout << "Please select column to compute: ";
            cin >> column;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Bad entry. Please enter a number to choose." << endl;
            }
            else if (column < 1 || column > count+1)
                cout << endl << "Please choose either one from 1 to " << count+1 << "."<< endl;

        } while (column < 1 || column > count+1);

    return count;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		table_above_below_mean

task:		Obtain user input. If the user input is 5, go back to compute data menu
            without doing any computation. If not, calculate the mean for required column.
            According to the mean, iterate through the data to split to above and below mean.
            The number of data for each table is calculated. Print result of table and generate reports.
data in:    title from file, data from file, bool for repeating table above and below mean
**************************************************************/
void table_above_below_mean(vector<string>title_found, vector<vector<double>>data_found, bool& repeat)
{
    int column, no_above = 0, no_below = 0;
    vector<double>id, cal_mean, above_mean, below_mean, id_above, id_below;
    int count = column_option(title_found, data_found, column);

    if (column == count+1)
    {
        cout << "Back to Compute Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    for (auto i = 0; i < data_found.size(); i++)
        id.push_back(data_found[i][0]);

    for (auto i = 0; i < data_found.size(); i++)
        cal_mean.push_back(data_found[i][column]);

    //Calculate mean
    double sum = 0, mean;
    for (auto x : cal_mean)
        sum = sum + x;
    mean = sum / cal_mean.size();

    for (auto i = 0; i < cal_mean.size(); i++)
    {
        if (cal_mean[i] > mean)
        {
            if (!(find(id_above.begin(), id_above.end(), data_found[i][0]) != id_above.end()))
            {
                id_above.push_back(data_found[i][0]);
                above_mean.push_back(cal_mean[i]);
                no_above += 1;
            }
        }
        else if (cal_mean[i] < mean)
        {
            if (!(find(id_below.begin(), id_below.end(), data_found[i][0]) != id_below.end()))
            {
                id_below.push_back(data_found[i][0]);
                below_mean.push_back(cal_mean[i]);
                no_below += 1;
            }
        }
    }
    result_mean_table(title_found, mean, column, above_mean, below_mean, no_above, no_below, id_above, id_below);
    auto func1 = bind(result_mean_table, title_found, mean, column, above_mean, below_mean, no_above, no_below, id_above, id_below);
    auto func2 = bind(mean_table_html, title_found, mean, column, above_mean, below_mean, no_above, no_below, id_above, id_below);
    html_txt(func1, func2);
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		result_mean_table

task:		Print the formatted result of table of above mean and table of below mean.
            Table contains corresponding student ID of the data.
data in:    title from file, data from file, mean, column, data above mean, data below mean,
            no. above mean, no. below mean, id above mean and id below mean
**************************************************************/
void result_mean_table(vector<string>& title_found, double& mean, int& column, vector<double>& above_mean, vector<double>& below_mean,
    int& no_above, int& no_below, vector<double>& id_above, vector<double>& id_below)
{
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);
    cout << endl << "RESULT OF: " << title_found[column] << endl;
    cout << endl << "Mean value: " << showpoint << fixed << setprecision(2) << mean << endl << endl;

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);
    cout << noshowpoint << fixed << setprecision(0);

    cout << "Number of data above mean: " << no_above << endl;
    cout << "TABLE ABOVE MEAN" << endl;
    cout << "-----------------------" << endl;
    cout << setw(8) << "Student ID" << " | " << setw(8) << title_found[column] << " | " << endl;
    cout << "-----------------------" << endl;

    for (auto i = 0; i < id_above.size(); i++)
        cout << setw(8) << id_above[i] << " | " << setw(8) << above_mean[i] << " | " << endl;
    cout << "-----------------------" << endl << endl;

    cout << "Number of data below mean: " << no_below << endl;
    cout << "TABLE BELOW MEAN" << endl;
    cout << "-----------------------" << endl;
    cout << setw(8) << "Student ID" << " | " << setw(8) << title_found[column] << " | " << endl;
    cout << "-----------------------" << endl;

    for (auto i = 0; i < id_below.size(); i++)
        cout << setw(8) << id_below[i] << " | " << setw(8) << below_mean[i] << " | " << endl;
    cout << "-----------------------" << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		mean_table_html

task:		Generate html report of table results of above mean and below mean. The html file is
            opened for append. External css is used for styling. An outer table without border
            is used to align the two tables side by side.
data in:    title from file, mean, column, data above mean, data below mean,
            no. above mean, no. below mean, id above mean and id below mean
**************************************************************/
void mean_table_html(vector<string>& title_found, double& mean, int &column, vector<double>& above_mean, vector<double>& below_mean,
    int& no_above, int& no_below, vector<double>& id_above, vector<double>& id_below)
{
    html_upper(title_found, column);

    outfile << "<p>" << "Mean value: " << showpoint << fixed << setprecision(2) << mean << "</p>";
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);
    outfile << "<table border = 0 cellspacing = 10 style = 'vertical-align:top, border-spacing: 75px, margin-top:1.5px'>";
    outfile << "<tr>" << "<td style='vertical-align: top'>"; //outer table to align
    outfile << noshowpoint << fixed << setprecision(0);
    outfile << "<p>" << "Number of data above mean: " << no_above << "</p>";
    outfile << "</span>";

    outfile << "<h4>" << "TABLE ABOVE MEAN" << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>" << "<th style='font-weight: bold'>" << "Student ID" << "</th>";
    outfile << "<th style='font-weight: bold'>" << title_found[column] << "</th>" << "</tr>";
    for (auto i = 0; i < id_above.size(); i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << id_above[i] << "</td>";
        outfile << "<td>" << above_mean[i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "</table>";
    outfile << "</td>"; //outer table to align
    outfile << "<td style='vertical-align: top'>"; //outer table to align
    outfile << "<p>" << "Number of data below mean: " << no_below << "</p>";
    outfile << "<h4>" << "TABLE BELOW MEAN" << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>" << "<th style='font-weight: bold'>" << "Student ID" << "</th>";
    outfile << "<th style='font-weight: bold'>" << title_found[column] << "</th>" << "</tr>";
    for (auto i = 0; i < id_below.size(); i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << id_below[i] << "</td>";
        outfile << "<td>" << below_mean[i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "</table>";
    outfile << "</td>" << "</tr>" << "</table>"; //outer table to align
    outfile << "</body>";
    outfile << "</html>";
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		distinct_frequency

task:		Get user input and insert selected column data into vector of struct (Dist_and_histogram).
            Sort the data for better result. Use map to pair up data and each frequency. Frequency
            is obtained by appending number of distinct data exist (iterate). Remove duplicate pair of
            vectors so that only one pair exist for each distinct data. Result of distinct frequency
            is printed and report is generated.
data in:    title from file, data from file, struct of Dist_and_histogram, bool for repeating
Referred to: https://www.techiedelight.com/find-frequency-element-vector-cpp/
             https://stackoverflow.com/questions/34146182/c-remove-duplicate-elements-from-two-vectors/34147195#34147195
**************************************************************/
void distinct_frequency(vector<string>title_found, vector<vector<double>>data_found, Dist_and_histogram& common, bool& repeat)
{
    int column;
    int count = column_option(title_found, data_found, column);

    if (column == count+1)
    {
        cout << "Back to Compute Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    for (auto i = 0; i < data_found.size(); i++)
        common.cal_distinct.push_back(data_found[i][column]);

    sort(common.cal_distinct.begin(), common.cal_distinct.end());

    //map the data and frequency
    map<double, int>countFrequency;
    for (auto &x : common.cal_distinct)
        countFrequency[x]++;

    // append frequency by taking occurence of each key value in countFrequency
    for (auto i = 0; i < common.cal_distinct.size(); i++)
        common.frequency.push_back(countFrequency[common.cal_distinct[i]]);

    set<tuple<double, int>>freq_pair;
    for (size_t i = 0; i < common.cal_distinct.size();)
    {
        if (freq_pair.emplace(common.cal_distinct[i], common.frequency[i]).second) // If inserting data and frequency
            i++;                                                                   // into set of tuple is successful,
        else                                                                       // loop continue
        {
            common.cal_distinct.erase(common.cal_distinct.begin() + i);     // If not, the specific element which is
            common.frequency.erase(common.frequency.begin() + i);           // duplicate is erased
        }
    }

    result_distinct_frequency(column, title_found, common);
    auto func1 = bind(result_distinct_frequency, column, title_found, common);
    auto func2 = bind(distinct_frequency_html, column, title_found, common);
    html_txt(func1, func2);
    move_to_histogram(column, title_found, data_found, common);
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		result_distinct_frequency

task:		Print the formatted result of distinct frequency
data in:    title from file, struct of Dist_and_histogram, bool for repeating
**************************************************************/
void result_distinct_frequency(int column, vector<string>title_found, Dist_and_histogram& common)
{
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);

    cout << endl << "RESULT OF: " << title_found[column] << endl;
    cout << "DISTINCT FREQUENCY" << endl;
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);
    cout << "-----------------------" << endl;
    cout << setw(9) << title_found[column] << " | " << setw(9) << "Frequency" << " | " << endl;
    cout << "-----------------------" << endl;

    for (auto i = 0; i < common.cal_distinct.size(); i++)
        cout << setw(9) << fixed << setprecision(0) << common.cal_distinct[i] << " | " << setw(9) << common.frequency[i] << " | " << endl;
    cout << "-----------------------" << endl << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		distinct_frequency_html

task:		Generate html report of distinct frequency. The html file is opened for append.
            External css is used for styling.
data in:    title from file, struct of Dist_and_histogram, column chosen
**************************************************************/
void distinct_frequency_html(int column, vector<string>title_found, Dist_and_histogram& common)
{
    html_upper(title_found, column);

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);
    outfile << "<h4>" << "DISTINCT FREQUENCY" << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>";
    outfile << "<th style='font-weight: bold'>" << title_found[column] << "</th>";
    outfile << "<th style='font-weight: bold'>" << "Frequency" << "</th>";
    outfile << "</tr>";
    for (auto i = 0; i < common.cal_distinct.size(); i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << common.cal_distinct[i] << "</td>";
        outfile << "<td>" << common.frequency[i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "</table><br>";
    outfile << "</body>";
    //ending html
    outfile << "</html>";
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		move_to_histogram

task:		Ask user whether to display result of distinct frequency in histogram or not.
            If yes, histogram function is called. If no, nothing happen. If the input is
            incorrect, error is prompted and repeat for input again.
data in:    title from file, struct of Dist_and_histogram, column chosen
**************************************************************/
void move_to_histogram(int column, vector<string>title_found, vector<vector<double>>data_found, Dist_and_histogram& common)
{
    string option;
    bool show_option = true;

    while (show_option == true)
    {
        cout << endl << "Do you want a HISTOGRAM to display result?" << endl << "Please type y/n: ";
        getline(cin, option);
        transform(option.begin(), option.end(), option.begin(), ::toupper);

        if (option == "Y")
        {
            histogram(column, title_found, data_found, common);
            show_option = false;
        }
        else if (option == "N")
            show_option = false;
        else
        {
            cout << "Please type either y or n." << endl << endl;
            show_option = true;
        }
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		histogram

task:		Plot vertical histogram by using vector. By iterating through the distinct
            data, split data into range which is 0-20, 21-40,...until 80-100. Insert
            the splitted data into vector column by column (of histogram). Print histogram
            and generate reports.
data in:    title from file, struct of Dist_and_histogram, column chosen
**************************************************************/
void histogram(int column, vector<string>title_found, vector<vector<double>>data_found, Dist_and_histogram& common)
{
    int first_col = 0, second_col = 0, third_col = 0,
        forth_col = 0, fifth_col = 0;
    vector<int>plot;

    for (auto i = 0; i < common.cal_distinct.size(); i++)
    {
        if (common.cal_distinct[i] <= 20)
            first_col = first_col + common.frequency[i];
        else if (common.cal_distinct[i] >= 21 && common.cal_distinct[i] <= 40)
            second_col = second_col + common.frequency[i];
        else if (common.cal_distinct[i] >= 41 && common.cal_distinct[i] <= 60)
            third_col = third_col + common.frequency[i];
        else if (common.cal_distinct[i] >= 61 && common.cal_distinct[i] <= 80)
            forth_col = forth_col + common.frequency[i];
        else
            fifth_col = fifth_col + common.frequency[i];
    }

    plot.push_back(first_col);
    plot.push_back(second_col);
    plot.push_back(third_col);
    plot.push_back(forth_col);
    plot.push_back(fifth_col);

    result_histogram(plot, title_found, data_found, column);
    auto func1 = bind(result_histogram, plot, title_found, data_found, column);
    auto func2 = bind(histogram_html, plot, title_found, data_found, column);
    html_txt(func1, func2);
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		result_histogram

task:		Print formatted result of histogram by using nested for-loop. It starts
            printing from maximum data of each column, downwards until the end of histogram.
            "*" denotes there are element within the range, whereas " " denotes there are no.
data in:    vector of plotting column, title from file, column chosen
Referred to: https://www.javatpoint.com/cpp-algorithm-max_element-function
**************************************************************/
void result_histogram(vector<int>plot, vector<string>title_found, vector<vector<double>>data_found, int column)
{
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);
    cout << endl << setfill(' ') << setw(13) << "HISTOGRAM OF " << title_found[column] << " FOR " << data_found.size() <<
     " STUDENTS" << endl << endl;
    int max_data = *max_element(plot.begin(), plot.end());  // get max height of histogram

    for (int i = max_data; i > 0; i--)
    {
        for (int num : plot)
        {
            if (i <= num)
                cout << setw(8) << left << " * ";
            else
                cout << setw(8) << left << "   ";
        }
        cout << endl;
    }
    cout << "---------------------------------------> DATA" << endl;
    cout << setw(2.7) << "0-20" << "   " << setw(2.7) << "21-40" << "   " <<
        setw(2.7) << "41-60" << "   " << setw(2.7) << "61-80" << "   " << setw(2.7) << "81-100" << endl << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		histogram_html

task:		Generate html report of histogram. The html file is opened for append.
            Caption is used for the title of histogram.
data in:    vector of plotting column, title from file, column chosen
**************************************************************/
void histogram_html(vector<int>plot, vector<string>title_found, vector<vector<double>>data_found, int column)
{
    outfile << "<!doctype html><html>"; //starting html

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);
    outfile << "<head>";
    outfile << "<title>" << "Statistical report(HTML)" << "</title>";
    outfile << "</head>";
    outfile << "<body>";
    outfile << "<span style='font-weight: bold'>";
    outfile << "<caption style='text-decoration: underline'>" << "HISTOGRAM OF " << title_found[column] <<
    " FOR " << data_found.size() << " STUDENTS" << "</caption>";
    outfile << "</span>" << "<br>";

    int max_data = *max_element(plot.begin(), plot.end());
    outfile << "<table border = 0,cellpadding = 0, cellspacing = 0>";
    for (int i = max_data; i > 0; i--)
    {
        outfile << "<tr>";
        for (int num : plot)
        {
            outfile << "<td>" << "&nbsp;&ensp;&ensp;" << "</td>";
            if (i <= num)
                outfile << "<td>" << " * " << "&nbsp;&ensp;&ensp;" << "</td>";
            else
                outfile << "<td>" << "   " << "&nbsp;&ensp;&ensp;" << "</td>";
        }
        outfile << "</tr>";
    }
    outfile << "</table>";
    outfile << "<span style='font-weight: bold'>";
    outfile << "<p style='margin-top:1px'>" << "----------------------------------------------------> Data" << "</p>";
    outfile << "<p style='margin-top:1px'>" << "&nbsp;&ensp;" << "0-20" << "&nbsp;&ensp;&ensp;" << "21-40" <<
        "&nbsp;&ensp;&ensp;" << "41-60" << "&nbsp;&ensp;&ensp;" << "61-80" << "&nbsp;&ensp;&ensp;" << "81-100" << "</p>";
    outfile << "</span>";
    outfile << "</body>";
    //ending html
    outfile << "</html>";
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		ascending

task:		Return ascending order of pair vector according to the data (passed to sort function).
data in:    pair of id and pair of data
data returned: ascending order for the data
Referred to: https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-1-sort-by-first-and-second/
**************************************************************/
bool ascending(const pair<double, double>& id, const pair<double, double>& data)
{
    return (id.second < data.second);
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		descending

task:		Return descending order of pair vector according to the data (passed to sort function).
data in:    pair of id and pair of data
data returned: descending order for the data
Referred to: https://www.geeksforgeeks.org/sorting-vector-of-pairs-in-c-set-2-sort-in-descending-order-by-first-and-second/
**************************************************************/
bool descending(const pair<double, double>& id, const pair<double, double>& data)
{
    return (id.second > data.second);
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		sort_data_ascending

task:		Get user input. Pair up data and the id, sort them in ascending order (referring
            to data). Print result of sorted data and generate report. If the input is 5,
            user will back to sort data menu without doing any sorting.
data in:    title from file, data from file and bool for repeating sort data ascending
**************************************************************/
void sort_data_ascending(vector<string>title_found, vector<vector<double>>data_found, bool& repeat)
{
    vector<double>data;
    vector<double>id;
    int column;
    int count = column_option(title_found, data_found, column);

    if (column == count+1)
    {
        cout << "Back to Sort Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    // to pair up id and data
    vector<pair<int, int>>pair_vect;

    for (auto i = 0; i < data_found.size(); i++)
        id.push_back(data_found[i][0]);

    for (auto i = 0; i < data_found.size(); i++)
        data.push_back(data_found[i][column]);

    for (int i = 0; i < data.size(); i++)
        pair_vect.push_back(make_pair(id[i], data[i]));

    sort(pair_vect.begin(), pair_vect.end(), ascending);

    sort_data_result(title_found, pair_vect, column, "ASCENDING");
    auto func1 = bind(sort_data_result, title_found, pair_vect, column, "ASCENDING");
    auto func2 = bind(sort_data_html, title_found, pair_vect, column, "ASCENDING");
    html_txt(func1, func2);
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		sort_data_descending

task:		Get user input. Pair up data and the id, sort them in descending order (referring
            to data). Print result of sorted data and generate report.If the input is 5,
            user will back to sort data menu without doing any sorting.
data in:    title from file, data from file and bool for repeating sort data descending
**************************************************************/
void sort_data_descending(vector<string>title_found, vector<vector<double>>data_found, bool& repeat)
{
    vector<double>data;
    vector<double>id;
    int column;
    int count = column_option(title_found, data_found, column);

    if (column == count+1)
    {
        cout << "Back to Sort Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    // to pair up id and data
    vector<pair<int, int>>pair_vect;

    for (auto i = 0; i < data_found.size(); i++)
        id.push_back(data_found[i][0]);

    for (auto i = 0; i < data_found.size(); i++)
        data.push_back(data_found[i][column]);

    for (int i = 0; i < data.size(); i++)
        pair_vect.push_back(make_pair(id[i], data[i]));

    sort(pair_vect.begin(), pair_vect.end(), descending);

    sort_data_result(title_found, pair_vect, column, "DESCENDING");
    auto func1 = bind(sort_data_result, title_found, pair_vect, column, "DESCENDING");
    auto func2 = bind(sort_data_html, title_found, pair_vect, column, "DESCENDING");
    html_txt(func1, func2);
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		sort_data_result

task:		Print formatted result of sorted data. Used by sort_data_ascending and
            sort_data_descending.
data in:    title from file, pair of id and data, column chosen, and order of sort
**************************************************************/
void sort_data_result(vector<string>title_found, vector<pair<int, int>>pair_vect, int column, string order)
{
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::toupper);
    cout << endl << "RESULT OF: " << title_found[column] << endl;
    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);

    cout << "Data is sorted in " << order << " ORDER: " << endl;
    cout << "-----------------------" << endl;
    cout << setw(8) << "Student ID" << " | " << setw(8) << title_found[column] << " | " << endl;
    cout << "-----------------------" << endl;

    for (auto i = 0; i < pair_vect.size(); i++)
        cout << fixed << setprecision(0) << setw(8) << pair_vect[i].first << " | " << setw(8) << pair_vect[i].second << " | " << endl;
    cout << "-----------------------" << endl << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		sort_data_html

task:		Generate html report of sorted data. The html file is opened for append.
            External css is used for styling. Used by sort_data_ascending and
            sort_data_descending.
data in:    title from file, pair of id and data, column chosen, and order of sort
**************************************************************/
void sort_data_html(vector<string>title_found, vector<pair<int, int>>pair_vect, int column, string order)
{
    html_upper(title_found, column);

    transform(title_found[column].begin(), title_found[column].end(), title_found[column].begin(), ::tolower);
    title_found[column][0] = toupper(title_found[column][0]);

    outfile << "<h4>" << "Data is sorted in " << order << " ORDER: " << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>";
    outfile << "<th style='font-weight: bold'>" << "Student ID" << "</th>";
    outfile << "<th style='font-weight: bold'>" << title_found[column] << "</th>";
    outfile << "</tr>";
    for (auto i = 0; i < pair_vect.size(); i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << pair_vect[i].first << "</td>";
        outfile << "<td>" << pair_vect[i].second << "</td>";
        outfile << "</tr>";
    }
    outfile << "</table><br>";
    outfile << "</body>";
    //ending html
    outfile << "</html>";
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		column_linearAndPearson

task:		Get user input and check error for the column choice of linear regression
            and pearson correlation. 2 input are received. The independent variable cannot
            be same as dependent variable. Whenever input of 5 is received, the user will
            end the process immediately.
data in:    first column, second column, title from file, data from file
data returned: numbering of the menu option
**************************************************************/
int column_linearAndPearson(int& first, int& second, vector<string>title_found, vector<vector<double>>data_found)
{
    int count, c = 0;
    bool wrong_input;

    do {
            count = 0;
            column_menu(title_found, count);

            wrong_input = false;

            if (c == 0)
            {
                cout << "Please select a column to compute as independent variable: ";
                cin >> first;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << endl << "Bad entry. Please enter a number to choose." << endl;
                    wrong_input = true;
                }
                else if (first < 1 || first > count+1)
                {
                    cout << endl << "Please choose either one from 1 to " << count + 1 << "." << endl;
                    wrong_input = true;
                }
                else if (first == count+1)
                    break;  //end this computation
                else
                    c += 1;
            }
            else
            {
                dependentVal(first, second, wrong_input, c, count);
                if (second == count+1)
                    break;
                else
                    c += 1;
            }

        } while (wrong_input == true || c <= 1);

        return count;
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		dependentVal

task:		Get user input for dependent variable and check error. The independent variable
            cannot be same as dependent variable. Used by linear regression and pearson
            correlation.
data in:    first column, second column, bool for wrong input and numbering of the menu option
**************************************************************/
void dependentVal(int& first, int& second, bool& wrong_input, int& c, int count)
{
    cout << "Please select a column to compute as dependent variable: ";
    cin >> second;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Bad entry. Please enter a number to choose." << endl;
        wrong_input = true;
    }
    else if (second < 1 || second > count+1)
    {
        cout << endl << "Please choose either one from 1 to " << count+1 << "." << endl;
        wrong_input = true;
    }
    else if (second == first)
    {
        cout << endl << "Dependent variable cannot be same as independent variable." << endl <<
            "Please select another column." << endl;
        wrong_input = true;
    }
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		linear_regression

task:		Get user input for 2 columns and insert the data into vector x and y respectively.
            Linear regression is calculated according to the formula. Result of a and b is used to
            form y = ax + b. Print the result of linear regression and generate reports.
            If any of the input is 5, the user will back to compute data menu without going through
            computation.
data in:    title from file, data from file, bool for repeating linear regression
Formula source: https://www.youtube.com/watch?v=T7LauV6AnRg&t=24s
**************************************************************/
void linear_regression(vector<string>title_found, vector<vector<double>>data_found, bool& repeat)
{
    int first = 0, second = 0;
    double n = data_found.size();
    vector<double>x, y, sq_x, xy;
    double a, b, x_sum = 0, y_sum = 0, sq_x_sum = 0, xy_sum = 0;

    int count = column_linearAndPearson(first, second, title_found, data_found);

    if (first == count+1 || second == count+1)
    {
        cout << "Back to Compute Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    for (auto i = 0; i < data_found.size(); i++)
    {
        x.push_back(data_found[i][first]);
        y.push_back(data_found[i][second]);
    }

    for (auto i = 0; i < x.size(); i++)
    {
        sq_x.push_back(pow(x[i], 2));
        xy.push_back(x[i] * y[i]);
    }

    for (auto i = 0; i < x.size(); i++)
    {
        x_sum = x_sum + x[i];
        y_sum = y_sum + y[i];
        sq_x_sum = sq_x_sum + sq_x[i];
        xy_sum = xy_sum + xy[i];
    }

    b = (n * xy_sum - x_sum * y_sum) / ((n * sq_x_sum) - pow(x_sum, 2));
    a = (y_sum - (b * x_sum)) / n;

    result_linear_regression(title_found, data_found, first, second, x, y, sq_x, xy, x_sum, y_sum, sq_x_sum, xy_sum, a, b);
    auto func1 = bind(result_linear_regression, title_found, data_found, first, second, x, y, sq_x, xy, x_sum, y_sum, sq_x_sum, xy_sum, a, b);
    auto func2 = bind(linear_regression_html, title_found, data_found, first, second, x, y, sq_x, xy, x_sum, y_sum, sq_x_sum, xy_sum, a, b);
    html_txt(func1, func2);
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		result_linear_regression

task:		Print formatted table of computation and result of linear regression
data in:    title from file, data from file, first column, second column and all
            variables in table of computation
**************************************************************/
void result_linear_regression(vector<string>title_found, vector<vector<double>>data_found, int& first, int& second, vector<double>& x, vector<double>& y,
    vector<double>& sq_x, vector<double>& xy, double& x_sum, double& y_sum, double& sq_x_sum, double& xy_sum, double& a, double& b)
{
    transform(title_found[first].begin(), title_found[first].end(), title_found[first].begin(), ::toupper);
    transform(title_found[second].begin(), title_found[second].end(), title_found[second].begin(), ::toupper);

    cout << endl << "RESULT OF: " << title_found[first] << " and " << title_found[second] << endl;
    cout << "LINEAR REGRESSION" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << setw(10) << "x" << " | " << setw(10) << "y" << " | " << setw(10) << "x^2" << " | " << setw(10) << "xy" << " | " << endl;
    cout << "---------------------------------------------------" << endl;
    for (auto i = 0; i < data_found.size(); i++)
    {
        cout << noshowpoint << fixed << setprecision(0) << setw(10) << x[i] << " | " << setw(10) << y[i] << " | "
            << setw(10) << sq_x[i] << " | " << setw(10) << xy[i] << " | " << endl;
    }
    cout << "---------------------------------------------------" << endl;
    cout << setw(10) << x_sum << " | " << setw(10) << y_sum << " | " << setw(10) << sq_x_sum
        << " | " << setw(10) << xy_sum << " | " << endl;
    cout << "---------------------------------------------------" << endl << endl;
    cout << showpoint << fixed << setprecision(2) << "Value of a is " << a << " and b is " << b << endl;
    if (b > 0.00)
        cout << showpoint << fixed << setprecision(2) << "Equation of linear regression: y = " << a << "+" << b << "x" << endl;
    else if (b < 0.00)
        cout << showpoint << fixed << setprecision(2) << "Equation of linear regression: y = " << a << b << "x" << endl;
    else
        cout << showpoint << fixed << setprecision(2) << "Equation of linear regression: y = " << a << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		linear_regression_html

task:		Generate html report of linear regression. The html file is opened for append.
            External css is used for styling.
data in:    title from file, data from file, first column, second column and all
            variables in table of computation
**************************************************************/
void linear_regression_html(vector<string>title_found, vector<vector<double>>data_found, int& first, int& second, vector<double>& x, vector<double>& y,
    vector<double>& sq_x, vector<double>& xy, double& x_sum, double& y_sum, double& sq_x_sum, double& xy_sum, double& a, double& b)
{
    outfile << "<!doctype html><html>"; //starting html
    transform(title_found[first].begin(), title_found[first].end(), title_found[first].begin(), ::toupper);
    transform(title_found[second].begin(), title_found[second].end(), title_found[second].begin(), ::toupper);
    outfile << "<head>";
    outfile << "<link rel=\"stylesheet\" href=\"style_table.css\">";
    outfile << "<title>" << "Statistical report(HTML)" << "</title>";
    outfile << "</head>";
    outfile << "<body>";
    outfile << "<span style='font-weight: bold'>";
    outfile << "<p style='text-decoration: underline'>" << "RESULT OF: " << title_found[first] << " and " << title_found[second] << "</p>";
    outfile << "</span>";

    outfile << "<h4>" << "LINEAR REGRESSION" << "</h4>";
    outfile << "<table class=\"style\">";
    outfile << "<tr>";
    outfile << "<th style='font-weight: bold'>" << "x" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "y" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "x^2" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "xy" << "</th>";
    outfile << "</tr>";
    outfile << fixed << noshowpoint << setprecision(0);
    for (auto i = 0; i < data_found.size(); i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << x[i] << "</td>";
        outfile << "<td>" << y[i] << "</td>";
        outfile << "<td>" << sq_x[i] << "</td>";
        outfile << "<td>" << xy[i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "<tr><td>" << "Sum: " << x_sum << "</td>";
    outfile << "<td>" << "Sum: " << y_sum << "</td>";
    outfile << "<td>" << "Sum: " << sq_x_sum << "</td>";
    outfile << "<td>" << "Sum: " << xy_sum << "</td>";
    outfile << "</table>" << "<br>";
    outfile << "</body>";
    outfile << fixed << showpoint << setprecision(2);
    outfile << "Value of a is " << a << " and b is " << b << "<br>";
    if (b > 0.00)
        outfile << "Equation of linear regression: y = " << a << "+" << b << "x" << "<br>";
    else if (b < 0.00)
        outfile << "Equation of linear regression: y = " << a << b << "x" << "<br>";
    else
        outfile << "Equation of linear regression: y = " << a << "<br>";
    //ending html
    outfile << "</html>";
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		pearson_steps

task:		Calculation steps for pearson correlation takes place. All the required
            values are passed to the function by reference to change the actual value.
data in:    first column, second column and all variables in table of computation
**************************************************************/
void pearson_steps(int& first, int& second, vector<double>& x, vector<double>& y, vector<double>& X, vector<double>& Y,
    vector<double>& sq_X, vector<double>& sq_Y, vector<double>& XY, double& x_sum, double& y_sum, double& sq_X_sum, double& sq_Y_sum, double& XY_sum)
{
    for (auto i = 0; i < x.size(); i++)
    {
        x_sum = x_sum + x[i];
        y_sum = y_sum + y[i];
    }
    double mx = x_sum / x.size();
    double my = y_sum / y.size();

    for (auto i = 0; i < x.size(); i++)
    {
        double a = x[i] - mx;
        X.push_back(a);
        double b = y[i] - my;
        Y.push_back(b);
    }

    for (auto i = 0; i < x.size(); i++)
    {
        double a = X[i] * X[i];
        sq_X.push_back(a);
        double b = Y[i] * Y[i];
        sq_Y.push_back(b);
        double c = X[i] * Y[i];
        XY.push_back(c);
    }

    for (auto i = 0; i < x.size(); i++)
    {
        sq_X_sum = sq_X_sum + sq_X[i];
        sq_Y_sum = sq_Y_sum + sq_Y[i];
        XY_sum = XY_sum + XY[i];
    }
}

/**************************************************************
Programmer:	Ong Ai Li
Name: 		pearson_correlation

task:		Get 2 input from user and insert them into vectors x and y respectively.
            Function of pearson_steps is called to calculate. Result of r is then
            calculated. Print table of computation and the result, generate reports.
            If any of the input is 5, user will back to compute data menu without going
            through any computation.
data in:    title from file, data from file , bool for repeating pearson correlation
Formula source:  https://www.youtube.com/watch?v=2SCg8Kuh0tE
**************************************************************/
void pearson_correlation(vector<string>title_found, vector<vector<double>>data_found, bool& repeat)
{
    int first = 0, second = 0;
    vector<double>x, y, X, Y, sq_X, sq_Y, XY;
    double x_sum = 0, y_sum = 0, sq_X_sum = 0, sq_Y_sum = 0, XY_sum = 0, r;

    int count = column_linearAndPearson(first, second, title_found, data_found);

    if (first == count+1 || second == count+1)
    {
        cout << "Back to Compute Data menu..." << endl << endl;
        repeat = false;
        return;
    }

    for (auto i = 0; i < data_found.size(); i++)
    {
        x.push_back(data_found[i][first]);
        y.push_back(data_found[i][second]);
    }

    pearson_steps(first, second, x, y, X, Y, sq_X, sq_Y, XY, x_sum, y_sum, sq_X_sum, sq_Y_sum, XY_sum);

    r = XY_sum / sqrt(sq_X_sum * sq_Y_sum);

    result_pearson_correlation(title_found, data_found, first, second, x, y, X, Y, sq_X, sq_Y, XY, x_sum, y_sum, sq_X_sum, sq_Y_sum, XY_sum, r);
    auto func1 = bind(result_pearson_correlation, title_found, data_found, first, second, x, y, X, Y, sq_X, sq_Y, XY, x_sum, y_sum, sq_X_sum, sq_Y_sum, XY_sum, r);
    auto func2 = bind(pearson_correlation_html, title_found, data_found, first, second, x, y, X, Y, sq_X, sq_Y, XY, x_sum, y_sum, sq_X_sum, sq_Y_sum, XY_sum, r);
    html_txt(func1, func2);
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		result_pearson_correlation

task:		Print formatted table of computation and result of pearson corrrelation
data in:    title from file, data from file, first column, second column and
            all variables in table of computation
**************************************************************/
void result_pearson_correlation(vector<string>title_found, vector<vector<double>>data_found, int& first, int& second, vector<double>& x, vector<double>& y, vector<double>& X,
    vector<double>& Y, vector<double>& sq_X, vector<double>& sq_Y, vector<double>& XY, double& x_sum, double& y_sum, double& sq_X_sum, double& sq_Y_sum, double& XY_sum, double& r)
{
    transform(title_found[first].begin(), title_found[first].end(), title_found[first].begin(), ::toupper);
    transform(title_found[second].begin(), title_found[second].end(), title_found[second].begin(), ::toupper);
    cout << endl << "RESULT OF: " << title_found[first] << " and " << title_found[second] << endl;
    cout << "PEARSON CORRELATION" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    cout << setw(12) << "x" << " | " << setw(12) << "y" << " | " << setw(12) << "x-mx" << " | " << setw(12) << "y-my" <<
        " | " << setw(12) << "(x-mx)^2" << " | " << setw(12) << "(y-my)^2" << " | " << setw(12) << "(x-mx)(y-my)" << " | " << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

    for (auto i = 0; i < data_found.size(); i++)
    {
        cout << noshowpoint << fixed << setprecision(0) << setw(12) << x[i] << " | " << setw(12) << y[i] << " | " << setw(12) << fixed << setprecision(2)
            << X[i] << " | " << setw(12) << Y[i] << " | " << setw(12) << sq_X[i] << " | " << setw(12) << sq_Y[i] <<
            " | " << setw(12) << XY[i] << " | " << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    cout << noshowpoint << fixed << setprecision(0) << setw(12) << x_sum << " | " << setw(12) << y_sum << " | " << setw(12) << "-" << " | " << setw(12)
    << "-" << " | " << setw(12) << showpoint << fixed << setprecision(2) << sq_X_sum << " | " << setw(12) << sq_Y_sum << " | " << setw(12) << XY_sum << " | " << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl << endl;

    cout << "Pearson Correlation Coefficient: " << endl;
    cout << "r = " << r << endl;
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		pearson_th

task:		Print table header of pearson correlation
**************************************************************/
void pearson_th()
{
    outfile << "<tr>";
    outfile << "<th style='font-weight: bold'>" << "x" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "y" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "x-mx" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "y-my" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "(x-mx)^2" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "(y-my)^2" << "</th>";
    outfile << "<th style='font-weight: bold'>" << "(x-mx)(y-my)" << "</th>";
    outfile << "</tr>";
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		pearson_correlation_html

task:		Generate html report of pearson_correlation. The html file is opened for append.
            External css is used for styling.
data in:    title from file, data from file, first column, second column and all variables
            in table of computation
**************************************************************/
void pearson_correlation_html(vector<string>title_found, vector<vector<double>>data_found, int& first, int& second, vector<double>& x, vector<double>& y, vector<double>& X,
    vector<double>& Y, vector<double>& sq_X, vector<double>& sq_Y, vector<double>& XY, double& x_sum, double& y_sum, double& sq_X_sum, double& sq_Y_sum, double& XY_sum, double& r)
{
    outfile << "<!doctype html><html>";
    transform(title_found[first].begin(), title_found[first].end(), title_found[first].begin(), ::toupper);
    transform(title_found[second].begin(), title_found[second].end(), title_found[second].begin(), ::toupper);

    outfile << "<head>";
    outfile << "<link rel=\"stylesheet\" href=\"style_table.css\">";
    outfile << "<title>" << "Statistical report(HTML)" << "</title>";
    outfile << "</head>";
    outfile << "<body>";
    outfile << "<span style='font-weight: bold'>";
    outfile << "<p style='text-decoration: underline'>" << "RESULT OF: " << title_found[first] << " and " << title_found[second] << "</p>";
    outfile << "</span>";
    outfile << "<h4>" << "PEARSON CORRELATION" << "</h4>";
    outfile << "<table class=\"style\">";
    pearson_th();

    for (auto i = 0; i < data_found.size(); i++)
    {
        outfile << "<tr>";
        outfile << "<td>" << noshowpoint << fixed << setprecision(0) << x[i] << "</td>";
        outfile << "<td>" << y[i] << "</td>";
        outfile << "<td>" << showpoint << fixed << setprecision(2) << X[i] << "</td>";
        outfile << "<td>" << Y[i] << "</td>";
        outfile << "<td>" << sq_X[i] << "</td>";
        outfile << "<td>" << sq_Y[i] << "</td>";
        outfile << "<td>" << XY[i] << "</td>";
        outfile << "</tr>";
    }
    outfile << "<tr><td>" << "Sum: " << noshowpoint << fixed << setprecision(0) << x_sum << "</td>";
    outfile << "<td>" << "Sum: " << y_sum << "</td>";
    outfile << "<td>" << "     " << "</td>";
    outfile << "<td>" << "     " << "</td>";
    outfile << "<td>" << "Sum: " << showpoint << fixed << setprecision(2) << sq_X_sum << "</td>";
    outfile << "<td>" << "Sum: " << sq_Y_sum << "</td>";
    outfile << "<td>" << "Sum: " << XY_sum << "</td>";
    outfile << "</table>" << "<br>";
    outfile << "Pearson Correlation Coefficient: " << "<br>";
    outfile << "r = " << r << "<br>";
    outfile << "</body>";
    outfile << "</html>";
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		case2

task:		Print and proceed with compute data menu if the file is read.
data in:    title from file, data from file, number of file read
**************************************************************/
void case2(vector<string>title_found, vector<vector<double>>data_found, const int &read)
{
    if (read == 0)
        cout << "Please read the file first. (File operation>>Read file)" << endl;
    else
    {
        bool show_compute_menu = true;
        while (show_compute_menu == true)
        {
            system("cls");
            compute_data_menu(title_found, data_found, show_compute_menu);
        }
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling
Name: 		case3

task:		Print and proceed with sort data menu if the file is read.
data in:    title from file, data from file, number of file read
**************************************************************/
void case3(vector<string>title_found, vector<vector<double>>data_found, const int& read)
{
    if (read == 0)
        cout << "Please read the file first. (File operation>>Read file)" << endl;
    else
    {
        bool show_sort_menu = true;
        while (show_sort_menu == true)
        {
            system("cls");
            sort_data_menu(title_found, data_found, show_sort_menu);
        }
    }
}

/**************************************************************
Programmer:	Adeline Fong Li Ling, Kong Wan Er
Name: 		main

task:		Use a do-while loop to repeat the main menu. show_main_menu will become
            false when user choose to quit the program. It get input from user to
            proceed with the menu. For each cases in switch-case, the screen is cleared
            and there is a while loop to repeat the sub menu, which is file_operation,
            compute_data_menu and sort_data_menu. When input is 4 (Exit), program ends
            and the file closes.
**************************************************************/
int main()
{
    int read = 0;
    vector<string>title_found;
    vector<vector<double>>data_found;
    File f;
    bool show_main_menu = true;
    cout << "Welcome to our Basic Data Analysis Program!" << endl;
    cout << "To begin with, please go to File Operation to read file." << endl << endl;

    do {
            int action = main_menu_action();

            switch (action)
            {
                case 1:
                {
                    system("cls");
                    bool show_file_menu = true;
                    while (show_file_menu == true)
                        read = file_operation(title_found, data_found, show_file_menu, f, read);
                    break;
                }
                case 2:
                {
                    case2(title_found, data_found, read);
                    break;
                }
                case 3:
                {
                    case3(title_found, data_found, read);
                    break;
                }
                case 4:
                {
                    system("cls");
                    cout << "End program..." << endl;
                    ifile.close();
                    show_main_menu = false;
                    exit(0);
                    break;
                }
            }

       } while (show_main_menu == true);
}
