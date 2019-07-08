#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void threadFunction(unsigned int start, unsigned int end, vector<unsigned int> * numVec );
int main()
{
    vector<unsigned int> numbers;
    vector<thread *> threadsVector;
    unsigned int min;
    unsigned int max;
    unsigned int n;
    cout << "Przedzial a: ";
    cin >> min;
    cout << "Przedzial b: ";
    cin >> max;
    cout << "N: ";
    cin >> n;
    if(max < min || n <= 0)
    {
        cout << "Wron input";
        return 1;
    }
    unsigned int jump = (max - min) / n;
    unsigned int maxToTh;
    for(unsigned int i = min; i < max; i += jump)
    {
        if(i > max)
            maxToTh = max;
        else
            maxToTh = i + jump;
        threadsVector.push_back(new thread(&threadFunction, i, maxToTh, &numbers));
    }
    for(auto & i : threadsVector)
    {
        i->join();
        delete i;
    }
    for(auto & i : numbers)
    {
        cout << i << " ";
    }
    return 0;
}

void threadFunction(unsigned int start, unsigned int end, vector<unsigned int> * numVec )
{
  bool flag = true;
  for(unsigned int i = start; i < end; i++)
  {
      flag = true;
      for(unsigned int j = 2; j < i && flag; j++)
      {
          if(i % j == 0)
          {
             flag = false;
          }
      }
      if(flag)
      {
          numVec->push_back(i);
      }

  }
}
