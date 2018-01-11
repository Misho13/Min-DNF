#include "stdafx.h"
#include "Header.h"




bool Trash (const std::string &impl)
{
	char last;
	if (impl == "U")
	{
		return false;
	}
	else
	{
		for (int i= 0;i<impl.size();i++)
		{
			if (i == 0)
			{
				if (impl[i] != 'x' && impl[i] != '!')
					return true;
			}
			else
			{
				if (last == '!' && impl[i] != 'x')
				{
					return true;
				}
				else if ((((int)last >= 48) || ((int)last <= 57)) && (impl[i] != 'x') && (impl[i] != '!') && (((int)impl[i] < 48) || ((int)impl[i] > 57)))
					return true;
				else if (last == 'x' && (((int)impl[i] < 48) || ((int)impl[i] > 57)))
					return true;
			}
			last = impl[i];
		}
	}
	return false;
}

bool Test(char *F1, char *F2)
{
	std::ifstream f_ans(F1);
	std::ifstream f_test(F2);
	std::vector <std::string> ans;
	std::vector <std::string> test;
	std::string temp;
	while (!f_ans.eof())
	{
		f_ans >> temp;
		if (temp != "U" && !Trash(temp))
			ans.push_back(temp);
	}
	temp.clear();
	while (!f_test.eof())
	{
		f_test >> temp;
		if (temp != "U" && !Trash(temp))
			test.push_back(temp);
	}
	f_ans.close();
	f_test.close();
	if (test.size() != ans.size())
		return false;
	else
	{
		for (auto &x : ans)
		{
			if (std::find(test.begin(), test.end(), x) == test.end())
			{
				return false;
			}
		}
		return true;
	}
}

std::string Make_formula(std::vector<std::string> mdnf)
{
	std::stringstream result;
	if (mdnf.size() > 0)
	{
		int k = 0;
		for (auto &x : mdnf)
		{
			k++;
			int i = 0;
			for (auto &y : x)
			{
				if (y == '2')
				{
					i++;
					continue;
				}
				else if (y == '1')
				{
					
					result << "x" << i;
					i++;
				}
				else if (y == '0')
				{
					result << "!x" << i;
					i++;
				}
			}
			if (k != mdnf.size())
				result << " U ";
		}
	}
	return result.str();
}

std::string Gluing(const std::string &a, const std::string &b)
{
	std::string result;
	int found = -1;
	int kol = 0, i = 0;
	while ((kol<2) && (i<a.length()))
	{
		if ((a[i] != b[i]))
		{
			kol++;
			found = i;
		}
		i++;
	}
	if (kol == 1)
	{
		result = a;
		result[found] = '2';
	}
	return result;
}

std::string Absorption(const std::string &a, const std::string &b) 
{
	std::string result;
	int found = -1;
	int kol = 0, i = 0;
	while ((kol < 2) && (i < a.length()))
	{
		if (((a[i] == '2') && (b[i] != '2')) || ((b[i] == '2') && (a[i] != '2')))
		{
			kol++;
			found = i;
		}
		else
			if ((a[i] != '2') && (b[i] != '2') && (a[i] != b[i]))
				return result;
		i++;
	}
	if (kol == 1)
	{
		result = a;
		result[found] = '2';
	}
	return result;
}

std::string Bin(int x, int len) 
{
	std::string result;
	while (x > 0) 
	{
		int buf = x & 1;
		x = x >> 1;
		result.append(std::to_string(buf));
	}
	std::reverse(result.begin(), result.end());
	if (result.length() < len) 
	{
		int delta = len - result.length();
		std::string zeros;
		for (int i = 0; i < delta; ++i)
			zeros.append("0");
		result = zeros + result;
	}
	return result;
}

vector_t Make_sdnf(std::string & func_values) 
{

	vector_t sdnf;
	double len = log2(func_values.size());

	for (int i = 0; i < func_values.length(); ++i) {

		if (func_values[i] == '1') {
			std::string res = Bin(i, len);

			sdnf.push_back(std::pair<std::string, bool>(res,false));
		}
	}

	return sdnf;
}

vector_t Abbreviate(vector_t data,std::string (*function)(const std::string &, const std::string &))
{
	while (1)
	{
		vector_t h;
		bool flag = false;
		for (auto i = data.begin(); i != data.end(); i++)
		{
			for (auto j = i + 1; j != data.end(); ++j)
			{
				if (i != j)
				{
					std::string buf = function(i->first, j->first);
					if (!buf.empty())
					{
						i->second = true;
						j->second = true;
						flag = true;
						auto object = std::pair<std::string, bool>(buf, false);
						bool X3 = false;
						for (auto & x : h)
						{
							if (x.first == object.first)
							{
								X3 = true;
							}
						}
						if (!X3)
							h.push_back(object);
					}
				}
			}
			if (i->second == false)
			{
				bool X3 = false;
				for (auto & x : h)
				{
					if (x.first == i->first)
					{
						X3 = true;
					}
				}
				if (!X3)
					h.push_back(*i);
			}
		}
		if (flag != true)
			break;
		data = h;
	}
	return data;
}

vector_t Abbreviated_dnf(vector_t data)
{
	data = Abbreviate(data, Gluing);
	data = Abbreviate(data, Absorption);
	return data;
}

bool CheckParam(char *f1, char*f2, char*f3)
{
	std::ifstream F1(f1);
	std::ifstream F2(f2);
	std::ifstream F3(f3);
	if ((!F1.is_open()) || (!F2.is_open()) || (!F3.is_open()))
	{
		std::cout << "\n Check Args! \n";
		return false;
	}
	F1.close();
	F2.close();
	F3.close();
	return true;
}

bool Trash_in_function(const std::string & vect)
{
	for (auto &x : vect)
	{
		if (x != '0' && x != '1')
			return true;
	}
	return false;
}

bool Read_param (char* path,std::string &bin_vector)
{
	std::ifstream fr(path);
	fr >> bin_vector;
	fr.close();
	if (bin_vector.size() == 0)
	{
		std::cout << "\n Empty file";
		return false;
	}
	if (floor(log2(bin_vector.size())) != log2(bin_vector.size()))
	{
		std::cout << "\n Check function";
		return false;
	}
	if (Trash_in_function(bin_vector))
	{
		std::cout << "\n Unknown ";
		return false;
	}
	return true;
}

void Write_ans(char*path,const std::string & answer)
{
	std::ofstream wr(path);
	wr << answer;
	wr.close();
}

int main(int argc, char *argv[])
{
	if (CheckParam(argv[1], argv[2], argv[3]))
	{
		std::string bin_vector;
		if (Read_param(argv[1], bin_vector))
		{
			std::vector <std::string> cec;
			ImplMatrix M(Make_sdnf(bin_vector), Abbreviated_dnf(Make_sdnf(bin_vector)));
			cec = M.MDNF();
			Write_ans(argv[2], Make_formula(cec));
		}
		if (Test(argv[2], argv[3]))
			std::cout << "\n Correct work of main algorithm! \n";
		else
			std::cout << "\n Incorrect work of main algorithm! \n";
	}
	return 0;
}
