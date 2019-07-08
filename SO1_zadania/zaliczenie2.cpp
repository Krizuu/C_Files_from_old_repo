#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void threadFunction(unsigned int start, unsigned int end);
void killThreads(vector<thread *> * threadsVector);
vector<unsigned int> numbers;
bool volatile opFlag;	//ulotna zmienna bool

int main()
{
    opFlag = false;
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
    cout << "<" << min << "," << max << ">" << " N = " << n << endl;
    if(max < min || n <= 0)
    {
        cout << "Wrong input";
        return 1;
    }
    unsigned int jump = static_cast<unsigned int>((max - min) / n);	//zwraca wartosc typu int
    unsigned int maxToTh;
    unsigned int counter = 0;
    for(unsigned int i = min; i <= max - 1; i += jump)
    {
        counter++;
        if(i > max || counter == n)
            maxToTh = max;
        else
            maxToTh = i + jump;
        threadsVector.push_back(new thread(&threadFunction, i, maxToTh));
    }
    
    killThreads(&threadsVector);
    
    counter = 0;
    
    for(auto & i : numbers)
    {
    	counter++;
    	if(counter == n +1)
    	{
    		counter = 1;
    		cout << endl;
		}
        cout << i;
        cout << "  ";
    }
    return 0;
}


void killThreads(vector<thread *> * threadsVector)
{
    for(auto & i : *threadsVector)
    {
        i->join();
        delete i;
    }
}


void threadFunction(unsigned int start, unsigned int end)
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
          while(opFlag){}
          opFlag = true;
          numbers.push_back(i);
          opFlag = false;
      }

  }
}
