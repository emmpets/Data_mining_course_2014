#include "DataMining.h"

#include <tuple>
#include <algorithm>
#include <map>

//Supporting functions
int sqrt(int x)
{
	return (int)sqrt((double)x);
}

bool CompareClassifiableData (const std::tuple<double, ClassifiableData>  &lhs, const std::tuple<double, ClassifiableData>  &rhs){
  return std::get<0>(lhs) < std::get<0>(rhs);
}

bool CompareFrequency(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) 
{
	return p1.second < p2.second; 
}

struct StringComparison
{
    public:
    bool operator()(const std::string x, const std::string y)
    {
         return x.compare(y)<0;
    }
};

int sumnonzeros(std::vector<int> &v)
{
	int result = 0;
	for(int i = v.size()-1; i >= 0; i--)
	{
		if(v[i] != 0 ) result ++;
	}
	return result;
}

//Cosine Similarity

double DataMining::CosineSimilarity(std::vector<double> &a, std::vector<double> &b)
{
	//inner product a.b
	double ab = inner_product(a,b);
	// |a|^2
	double aa = inner_product(a,a);
	// |b|^2
	double bb = inner_product(b,b);

	return ab/sqrt(aa*bb);
}



std::string DataMining::ClassifyKNN(std::vector< ClassifiableData > &points, ClassifiableData &input, int k, int classNumber)
{
	std::vector< std::tuple<double, ClassifiableData> > distances(points.size());
	for(int i = points.size()-1; i>=0; i--)
	{
		std::tuple<double, ClassifiableData> tp(input.Distance(points[i]),points[i]);
		distances[i] = tp;
	}
	std::sort(distances.begin(), distances.end(), CompareClassifiableData);
	std::map<std::string, int, StringComparison> frequencies;

	for(int i = 0; i < k; i++)
	{
		ClassifiableData p = std::get<1>(distances[i]);
		frequencies[classNumber == 2 ? p.class2 :p.class1] ++;
	}

	std::map<std::string, int, StringComparison>::iterator maxElement = std::max_element(frequencies.begin(), frequencies.end(),CompareFrequency);
	return maxElement->first;
}



std::vector<int> DataMining::ClassifyKMeans(std::vector<std::vector<double>> points, int k, std::vector<std::vector<double>> &centres)
{
	centres.resize(k);
	std::vector<int> result(points.size(),-1);
	int numberOfChanges, maxNumberOfLoops=1000;
	//Initial centres. Picking the k first points
	for(int i = 0; i < k; i++)
	{
		centres[i] = points[i];
	}
	do
	{
		int r;
		maxNumberOfLoops --;
		//Perform Classification
		std::vector<int> intermediateResult = ClassifySimple(points, centres);
		numberOfChanges = sumnonzeros(result - intermediateResult);
		result = intermediateResult;

			//Recomputing centres
		//a_setting to zero
		for(int i=0; i < k; i++)
		{
			for(int j = centres[i].size()-1; j >=0; j--)
				centres[i][j] = 0;
		}
		std::vector<int> teamCount(k);
		for(int i = result.size()-1; i >= 0; --i)
		{
			r = result[i];
			centres[r] = centres[r] + points[i];
			teamCount[r]++;
		}
		for(int i=0; i < k; i++)
		{
			for(int j = centres[i].size()-1; j >=0; j--)
				centres[i][j] /= 1.0*teamCount[i];
		}
	}while(numberOfChanges == 0 || maxNumberOfLoops <=0);

	return result;
}

int DataMining::ClassifyNearestNeihbour(std::vector< std::vector<double> > &points, double threshold, std::vector<std::vector<int>> &clusters)
{
	int totalPoints = points.size();
	std::vector<std::vector<double>> distances = ComputeAllDistances(points);
	clusters.clear();
	clusters.resize(1);
	clusters[0].push_back(0);
	for(int i = 1; i < totalPoints; i++)
	{
		bool hasBeenInserted = false;
		for(int cl =0; cl < clusters.size(); cl++)
		{
			for(int cp = 0; cp < clusters[cl].size(); cp++)
			{
				if(distances[i][clusters[cl][cp]] < threshold)
				{
					clusters[cl].push_back(i);
					hasBeenInserted = true;
					break;
				}
			}
			if(hasBeenInserted) break;
		}
		if(!hasBeenInserted)
		{
			std::vector<int> newCluster(1,i);
			clusters.push_back(newCluster);
		}
	}	
	return clusters.size();
}