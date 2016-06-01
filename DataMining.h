#pragma once
#include "Utilities.h"


class ClassifiableData
{
public:
	std::string name, gender, class1, class2;
	ClassifiableData(){}
	ClassifiableData(std::string name, std::string gender, double height, std::string class1, std::string class2) 
	{
		this->name = name;
		this->gender = gender;
		this->height = height;
		this->class1 = class1;
		this->class2 = class2;
	}
	
	double height;
	double Distance(ClassifiableData &other)
	{
		return abs(height - other.height);
	}
};


int sqrt(int x);


class DataMining
{

private:
	template <class T>
	T distance(std::vector<T> &a, std::vector<T> &b)
	{
		std::vector<T> dif = a-b;
		return sqrt(inner_product(dif, dif));	
	}

	template <class T>
	std::vector<std::vector<T> > ComputeAllDistances(std::vector<std::vector<T> > &points)
	{
		std::vector<std::vector<T> > result (points.size(), std::vector<T>(points.size()));
		for(int i = points.size()-1; i >=0; i--)
		{
			for(int j = i-1; j >=0; j--)
			{
				result[i][j] = result[j][i] = distance(points[i], points[j]);
			}
		}
		return result;
	}
public:
	DataMining(void){}
	~DataMining(void){}

	double CosineSimilarity(std::vector<double> &left, std::vector<double> &right);
	template <class T>
	std::vector<int> ClassifySimple(std::vector< std::vector<T> > &points, std::vector< std::vector<T> > &teamCenters)
	{
		std::vector<int> result(points.size(),-1);
		for(int i = points.size()-1; i >=0; i--)
		{
			int minDistance = 99999999;
			for(int j = teamCenters.size()-1; j>=0; j--)
			{
				int dist = distance(points[i], teamCenters[j]);
				if(dist< minDistance)
				{
					result[i]=j;
					minDistance = dist;
				}
			}
		}
		return result;
	}

	std::string ClassifyKNN(std::vector< ClassifiableData > &points, ClassifiableData &input, int k, int classNumber = 1);
	std::vector<int> ClassifyKMeans(std::vector<std::vector<double>> points, int k, std::vector<std::vector<double>> &centres);
	int ClassifyNearestNeihbour(std::vector< std::vector<double> > &points, double threshold, std::vector<std::vector<int>> &clusters);

};

