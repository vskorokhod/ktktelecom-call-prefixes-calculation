#include <fstream>

using namespace std;

const int number_length = 11;

void to_array (long long num, int array_num[number_length])
{
	for (int i = number_length - 1; i >= 0; i--)
	{
		array_num[i] = num % 10;
		num = num / 10;
	}
	return;
}

int first_diff (int num1[number_length], int num2[number_length])
{
	int result = number_length;
	for (int i = 0; i < number_length; i++)
	{
		if (num1[i] != num2[i])
		{
			result = i;
			break;
		}
	}
	return result;
}

bool all_remaining_equals (int num[number_length], int pos, int value)
{
	bool result = true;
	for (int i = pos + 1; i < number_length; i++)
	{
		if (num[i] != value)
		{
			result = false;
			break;
		}
	}
	return result;
}

void simple_solution(int num[number_length], int diff_pos, string oper, ofstream &fout)
{
	for (int i = 0; i < diff_pos; i++)
	{
		fout << num[i];
	}
	fout << oper << endl;
	return;
}

void prefixes_1 (int num[number_length], int first_diff_pos, string oper, ofstream &fout)
{
	for (int i = first_diff_pos; i < number_length; i++)
	{
		if (all_remaining_equals(num, i, 0))
		{
			for (int j = 0; j <= i; j++)
			{
				fout << num[j];
			}
			fout << oper << endl;
			break;
		}
		else
		{
			for (int j = 9; j > num[i+1]; j--)
			{
				for (int l = 0; l <= i; l++)
				{
					fout << num[l];
				}
				fout << j << oper << endl;
			}
		}
	}
	return;
}

void prefixes_2 (int num1[number_length], int num2[number_length], int first_diff_pos, string oper, ofstream &fout)
{
	int temp[first_diff_pos+1];
	for (int i = 0; i < first_diff_pos; i++)
	{
		temp[i] = num1[i];
	}
	for (int i = num1[first_diff_pos] + 1; i < num2[first_diff_pos]; i++)
	{
		temp[first_diff_pos] = i;
		for (int j = 0; j <= first_diff_pos; j++)
		{
			fout << temp[j];
		}
		fout << oper << endl;
	}
	return;
}

void prefixes_3 (int num[number_length], int first_diff_pos, string oper, ofstream &fout)
{
	for (int i = first_diff_pos; i < number_length; i++)
	{
		if (all_remaining_equals(num, i, 9))
		{
			for (int j = 0; j <= i; j++)
			{
				fout << num[j];
			}
			fout << oper << endl;
			break;
		}
		else
		{
			for (int j = 0; j < num[i+1]; j++)
			{
				for (int l = 0; l <= i; l++)
				{
					fout << num[l];
				}
				fout << j << oper << endl;
			}
		}
	}
	return;
}

void prefixes_calculation(long long first_number, long long last_number, string oper, int aggr_rows, ofstream &fout)
{
	int first_diff_pos, first_num[number_length], last_num[number_length];
	if (first_number > last_number)
	{
		fout << "Wrong parameters - first number bigger than last number"<< endl << endl << endl;
		return;
	}
	if (aggr_rows > 1)
	{
		fout << "Aggregated " << aggr_rows << " rows" << endl;
	}
	to_array(first_number, first_num);
	to_array(last_number, last_num);
	first_diff_pos = first_diff(first_num, last_num);
	if (all_remaining_equals(first_num, first_diff_pos - 1, 0) and all_remaining_equals(last_num, first_diff_pos - 1, 9))
	{
		simple_solution (first_num, first_diff_pos, oper, fout);
		fout << endl << endl << endl;
		return;
	}
	prefixes_1(first_num, first_diff_pos, oper, fout);
	prefixes_2(first_num, last_num, first_diff_pos, oper, fout);
	prefixes_3(last_num, first_diff_pos, oper, fout);
	fout << endl << endl << endl;
	return;
}

int main() {
	long long first_number, last_number, next_first, next_last;
	string oper, next_oper;
	int aggr_rows;
	ofstream fout("result.txt");
	ifstream fin("data.txt");
	fin >> first_number >> last_number;
	getline(fin, oper);
	next_first = first_number;
	next_last = last_number;
	next_oper = oper;
	while (!fin.eof())
	{
		first_number = next_first;
		last_number = next_last;
		oper = next_oper;
		aggr_rows = 1;
		while (true)
		{
			fin >> next_first >> next_last;
			getline (fin, next_oper);
			if ((next_first != (last_number + 1)) or (oper != next_oper))
			{
				break;
			}
			last_number = next_last;
			aggr_rows++;
		}
		prefixes_calculation (first_number, last_number, oper, aggr_rows, fout);
	}
	if (aggr_rows == 1)
	{
		prefixes_calculation (next_first, next_last, next_oper, aggr_rows, fout);
	}
	fin.close();
	fout.close();
	return 0;
}
