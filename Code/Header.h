
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using vector_t = std::vector<std::pair<std::string, bool>>;

bool Owns(const std::string &A,const std::string &B)
{
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] != B[i] && A[i] != '2' &&B[i] != '2')
		{
			return false;
		}
	}
	return true;
}

int Weight(std::string a)
{
	int k = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != '2')
			k++;
	}
	return k;
}

std::vector<std::vector<int>> Implmult(std::vector<std::vector<int>> a, std::vector<std::vector <int>> b)
{
	std::vector<std::vector<int>> result;
	for (auto & x: a)
		for (auto &y : b)
		{
			std::vector<int> buff;
			for (auto &xi:x)
				buff.push_back(xi);
				for (auto &yi : y)
				{
					if (std::find(buff.begin(), buff.end(), yi) == buff.end())
						buff.push_back(yi);
				}
			result.push_back(buff);
		}
	return result;
}

std::vector<std::string> Cover(bool **mat,std::vector<int>nepokr,std::vector<int>ignor,vector_t &ADNF)
{
	std::vector<std::string> a;
	std::vector<std::vector<std::vector<int>>> patrik;
	patrik.resize(nepokr.size());
	int i = 0;
	for (auto & x : nepokr)
	{
		int j = 0;
		for (auto & y : ignor)
		{
			std::vector <int> K;
			if (mat[y][x] == true)
			{
				K.push_back(y);
				patrik[i].push_back(K);
			}
			j++;
		}
		i++;
	}
	
	while (patrik.size() > 1)
	{
		std::vector <std::vector<int>> sets;
		sets = Implmult(patrik[0], patrik[1]);
		patrik.erase(patrik.begin(),patrik.begin()+2);
		if (sets.size())
			patrik.push_back(sets);
	}
	int wei = INT_MAX;
	int l = -1;
	int p = -1;
	for (int i = 0; i < patrik.size(); i++)
	{
		for (int j = 0; j < patrik[i].size(); j++)
		{
			int cur_w = 0;
			for (auto &x : patrik[i][j])
			{
				cur_w += Weight(ADNF[x].first);
			}
			if (cur_w < wei)
			{
				wei = cur_w;
				l = i;
				p = j;
			}
		}
	}
	for (auto &x : patrik[l][p])
	{
		a.push_back(ADNF[x].first);
	}
	return  a;
}


class ImplMatrix
{
private:
	bool ** mat;
	std::vector<std::vector<int>> pokr_stb;
	vector_t SDNF;
	vector_t ADNF;
	void fill()
	{
		for (int i = 0; i < ADNF.size(); i++)
		{
			for (int j = 0; j < SDNF.size(); j++)
			{
				if (Owns(ADNF[i].first, SDNF[j].first))
					mat[i][j] = true;

				else
					mat[i][j] = false;
			}
		}
	}
public:
	ImplMatrix(vector_t &A, vector_t &B)
	{
		SDNF = A;
		ADNF = B;
		mat = new bool*[ADNF.size()];
		for (int i = 0; i < ADNF.size(); i++)
		{
			mat[i] = new bool[SDNF.size()];
		}
		fill();
	}
	std::vector<std::string> MDNF()
	{
		std::vector<std::string> mdnf;
		std::vector<int> pokr;
		std::vector <int> consider;
		for (int i = 0; i < SDNF.size(); i++)
		{
			int kol = 0;
			int cec;
			for (int j = 0; j < ADNF.size(); j++)
			{
				if (mat[j][i] == true)
				{
					kol++;
					cec = j;
				}
			}
			if (kol == 1)
			{
				auto object = std::pair<std::string, bool>(ADNF[cec].first, false);
				bool X3 = false;
				for (auto & x : mdnf)
				{
					if (x == object.first)
					{
						X3 = true;
					}
				}
				if (!X3)
				{
					for (int k = 0; k < SDNF.size(); k++)
					{
						if (mat[cec][k] == true && std::find(pokr.begin(), pokr.end(), k) == pokr.end())
						{
							pokr.push_back(k);
						}
					}
					consider.push_back(cec);
					mdnf.push_back(object.first);
				}
			}
		}
		if (pokr.size() == SDNF.size())
			return mdnf;
		std::vector<int> nepokr;
		for (int i = 0; i < SDNF.size(); i++)
		{
			if (std::find(pokr.begin(), pokr.end(), i) == pokr.end())
				nepokr.push_back(i);
		}
		std::vector<int> ignor;
		for (int i = 0; i < ADNF.size(); i++)
		{
			if (std::find(consider.begin(), consider.end(), i) == consider.end())
				ignor.push_back(i);
		}
		std::vector <std::string> b = Cover(mat, nepokr, ignor, ADNF);
		for (auto &x : b)
		{
			mdnf.push_back(x);
		}
		return mdnf;
	}

	~ImplMatrix()
	{
		for (int i = 0; i < ADNF.size(); i++)
		{
			delete[]mat[i];
		}
		delete[]mat;
	}
};


