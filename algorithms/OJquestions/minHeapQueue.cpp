#include <sstream>
#include <iostream>
#include <string.h>

class minHeapQueue{
    public:
        int _currentSize;
        int _maxSize;
        int *_array;

        minHeapQueue(const int capacity = 100) : _currentSize(0), _maxSize(capacity) 
        {
            _array = new int[capacity];
        }

        void insertQueue(const int &x);

        void find(const int &x);

        void doubleSpace();

        void findPositionForX(const int &_currPosition, const int x);

        void decrease(const int & nodeNum, const int &privilegeNum);

        long power(const int &powerNum);
};

void minHeapQueue::doubleSpace()
{
    int *newArray = new int[2 * _maxSize];
    strncpy((char *)newArray, (char *)_array, sizeof(int) * _maxSize);
    _array = newArray;
}

void minHeapQueue::findPositionForX(const int &_currPosition, const int x)
{
    int currPosition = _currPosition;
    for (; currPosition / 2 > 0;currPosition = currPosition / 2)
    {
        if (_array[currPosition] < _array[currPosition / 2])
        {
            _array[currPosition] = _array[currPosition / 2];
        }
        else { break; }
    }
    _array[currPosition] = x;
}

long minHeapQueue::power(const int &num)
{
    if (1 == num){return 2;}
    else {return 2 * power(num-1);}
}

void minHeapQueue::insertQueue(const int &x)
{
    if (_currentSize == _maxSize - 1){doubleSpace();}
    ++_currentSize;
    _array[_currentSize] = x;
    findPositionForX(_currentSize, x);
}

void minHeapQueue::find(const int &x)
{
   if (_array[1] > x) {std::cout << "1" << std::endl; return ;}
   else
   {
        for (int deep =1; ; ++deep)
        {
            int startPos = power(deep);
            int endPos = startPos + startPos - 1;
            for (int index = startPos; index <= endPos; index++)
            {
                if (index > _currentSize)
                {
                    std::cout << "none" << std::endl;
                    return ;
                }
                if (_array[index] > x)
                {
                    std::cout << index << std::endl;
                    return ;
                }
            }
        }
   }
}

void minHeapQueue::decrease(const int &nodeNum, const int &privilegeNum)
{
    if (nodeNum > _currentSize){return ;}
    _array[nodeNum] -= privilegeNum;
    if (_array[nodeNum] < 0){_array[nodeNum] = 0;}
    findPositionForX(nodeNum, _array[nodeNum]);
}

int main()
{
    minHeapQueue queue;

    int numOfArgs;
    std::cin >> numOfArgs;
    std::cin.ignore(1, '\n');
    if (!(numOfArgs <= 20000 && numOfArgs >=1)){return 0;}

    while (numOfArgs--)
    {
        std::string operation;
        std::getline(std::cin, operation);
        std::istringstream iss(operation);

        if (strncmp(operation.c_str(), "insert", 6) == 0)
        {
            int x;
            iss >> operation >> x;
            queue.insertQueue(x);
        }
        else if (strncmp(operation.c_str(), "find", 4) == 0)
        {
            int x;
            iss >> operation >> x;
            queue.find(x);
        }
        else if (strncmp(operation.c_str(), "decrease", 8) == 0)
        {
            int nodeNum, privilegeNum;
            iss >> operation >> nodeNum >> privilegeNum;
            queue.decrease(nodeNum, privilegeNum);
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
