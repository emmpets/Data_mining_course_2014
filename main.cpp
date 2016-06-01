#include <iostream>
#include "DataMining.h"


template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T> v) {
    int last = v.size() - 1;
    out << "[";
    for(int i = 0; i < last; i++)
        out << v[i] << ", ";
    out << v[last] << "]";
    return out;
}

void ShowMenu(bool clear=true)
{
	std::cout <<"Choose" << std::endl;
	std::cout <<" 1. Cosine Similarity" << std::endl;
	std::cout <<" 2. Simple Classifier" << std::endl;
	std::cout <<" 3. k Nearest Neighbour Classifier" << std::endl;
	std::cout <<" 4. k means Classifier" << std::endl;
	std::cout <<" 5. Nearest Neighbour Classifier" << std::endl;
	
	std::cout <<std::endl<<"99. Clear Screen" << std::endl;
	std::cout <<std::endl<<" 0. Exit" << std::endl;
}

void ClearScreen()
{
#ifdef WIN32
	system("cls");
#else
	system("clear");
#endif
}


void ExecuteNearestNeighbourClassifier()
{
	DataMining mining;
	int numberOfPoints;
	std::cout << "Insert the number of points that will be randomly generated:";
	std::cin >> numberOfPoints;
	//Point Generation
	std::vector<std::vector<double>> points(numberOfPoints, std::vector<double>(2));
	for(int i = 0; i < numberOfPoints; i++)
	{
		points[i][0] = (1.+rand()%1000)/100;
		points[i][1] = (1.+rand()%1000)/100;
	}

	std::vector<std::vector<int>> clusters;
	std::cout << "Points :" << std::endl << points;
	int result = mining.ClassifyNearestNeihbour(points, 2, clusters);
	std::cout << "Total clusters: " << result << std::endl << "In Detail :" << std::endl << clusters;



}
void ExecuteSimpleClassifier()
{
	int numberOfPoints;
	std::cout << "Insert the number of points that will be randomly generated:";
	std::cin >> numberOfPoints;
	//Point Generation
	std::vector<std::vector<int>> points(numberOfPoints, std::vector<int>(2)), centres(4, std::vector<int>(2));
	for(int i = 0; i < numberOfPoints; i++)
	{
		points[i][0] = 1+rand()%100;
		points[i][1] = 1+rand()%100;
	}
	centres[0][0] = 4;		centres[0][1] = 25;
	centres[1][0] = 4;		centres[1][1] = 50;
	centres[2][0] = 4;		centres[2][1] = 75;
	centres[3][0] = 100;	centres[3][1] = 75;

	DataMining mining;
	std::vector<int> result = mining.ClassifySimple(points, centres);

	for(int i = 0; i < numberOfPoints; i++)
	{
		std::cout << "Point :"<< points[i] <<  " classified in team #"<< (result[i]+1) <<std::endl;
	} 
}

void ExecuteKnnClassifier()
{
	DataMining mining;
	std::vector<ClassifiableData> training;
	training.push_back(ClassifiableData("Kristina", "F", 1.6, "Short", "Medium"));
	training.push_back(ClassifiableData("Jim", "M", 2, "Tall", "Medium"));
	training.push_back(ClassifiableData("Maggie", "F", 1.9, "Medium", "Tall"));
	training.push_back(ClassifiableData("Martha", "F", 1.88, "Medium", "Tall"));
	training.push_back(ClassifiableData("Stephanie", "F", 1.7, "Short", "Medium"));
	training.push_back(ClassifiableData("Bob", "M", 1.85, "Medium", "Medium"));
	training.push_back(ClassifiableData("Kathy", "F", 1.6, "Short", "Medium"));
	training.push_back(ClassifiableData("Dave", "M", 1.7, "Short", "Medium"));
	training.push_back(ClassifiableData("Worth", "M", 2.2, "Tall", "Tall"));
	training.push_back(ClassifiableData("Steven", "M", 2.1, "Tall" , "Tall"));
	training.push_back(ClassifiableData("Debbie", "F", 1.8, "Medium", "Medium"));
	training.push_back(ClassifiableData("Todd", "M", 1.95, "Medium", "Medium"));
	training.push_back(ClassifiableData("Kim", "F", 1.9, "Medium", "Tall"));
	training.push_back(ClassifiableData("Amy", "F", 1.8, "Medium", "Medium"));
	training.push_back(ClassifiableData("Wynette", "F", 1.75, "Medium", "Medium"));

	std::string result = mining.ClassifyKNN(training, ClassifiableData("Pat", "F", 1.5,"",""),5,1);
	std::cout << "Class1: Pat 1.5m is " << result.c_str() << std::endl;
	result = mining.ClassifyKNN(training, ClassifiableData("Pat", "F", 1.5,"",""),5,2);
	std::cout << "Class2: Pat 1.5m is " << result.c_str() << std::endl;
}

void ExecuteCosineSimilarity()
{
	int k = 10, i;
	DataMining mining;
	std::vector<double> left(k), right(k);
	for(i = 0; i < k; i++)
	{
		left[i] = rand()*1./RAND_MAX;
		right[i] = rand()*1./RAND_MAX;
	}
	double distance = mining.CosineSimilarity(left, right);
	std::cout << "First :"<< left << std::endl << "Second:"<< right << std::endl << "Dist  :"<< distance << std::endl<<std::endl;
}

void ExecuteKMeansClassifier()
{
	int numberOfPoints;
	std::cout << "Insert the number of points that will be randomly generated:";
	std::cin >> numberOfPoints;
	//Point Generation
	std::vector<std::vector<double>> points(numberOfPoints, std::vector<double>(2)), centres;
	for(int i = 0; i < numberOfPoints; i++)
	{
		points[i][0] = 1.+rand()%10;
		points[i][1] = 1.+rand()%10;
	}
	DataMining mining;
	std::vector<int> result = mining.ClassifyKMeans(points,4, centres);

	std::cout << "Centres:"<< std::endl;

	
	for(int i = 0; i < 4; i++)
	{
		std::cout << "Centre :"<< (i+1) <<  " "<< centres[i] <<std::endl;
	} 
	
	for(int i = 0; i < numberOfPoints; i++)
	{
		std::cout << "Point :"<< points[i] <<  " classified in team #"<< (result[i]+1) <<std::endl;
	} 
}

void main()
{
	int selection;
	do
	{
		ShowMenu();
		std::cin >> selection;
		switch(selection)
		{
		case 99:
			ClearScreen();
			break;
		case 1:
			ExecuteCosineSimilarity();
			break;
		case 2:
			ExecuteSimpleClassifier();
			break;
		case 3:
			ExecuteKnnClassifier();
			break;
		case 4:
			ExecuteKMeansClassifier();
			break;
		case 5:
			ExecuteNearestNeighbourClassifier();
			break;
		}
	}while(selection!=0);
}