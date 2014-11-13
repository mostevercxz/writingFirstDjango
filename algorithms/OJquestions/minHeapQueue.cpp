#include <sstream>
#include <iostream>
#include <string.h>

class minHeapQueue{
		public:
				int _currentSize;
				int _maxSize;
				int *_array;

				minHeapQueue(const int capacity = 500) : _currentSize(0), _maxSize(capacity) 
		{
				_array = new int[capacity];
		}

				void insertQueue(const int x);

				int find(int rootIndex, const int x);

				bool doubleSpace();

				void findPositionForX(const int &_currPosition, const int x);

				void decrease(const int nodeNum, const int privilegeNum);

				void deleteRoot();

				long power(const int powerNum);

				~minHeapQueue(){delete []_array;}
};

bool minHeapQueue::doubleSpace()
{
		int *newArray = new int[2 * _maxSize];
		if (!newArray){return false;}
		for (int i = 1; i <= _currentSize; ++i)
		{
				newArray[i] = _array[i];
		}
		_maxSize = 2 * _maxSize;
		delete []_array;
		_array = newArray;
		return true;
}

void minHeapQueue::findPositionForX(const int &_currPosition, const int x)
{
		int currPosition = _currPosition;
		for (; currPosition / 2 > 0;currPosition = currPosition / 2)
		{
				if (_array[currPosition] < _array[currPosition / 2])
				{
						_array[currPosition] = _array[currPosition / 2];
						_array[currPosition / 2] = x;
				}
				else { break; }
		}
}

long minHeapQueue::power(const int num)
{
		if (1 == num){return 2;}
		else {return 2 * power(num-1);}
}

void minHeapQueue::insertQueue(const int x)
{
		if (x < 0){return ;}
		if ( 
			_currentSize < _maxSize-1 
			|| (_currentSize == _maxSize - 1 && doubleSpace())
			)
		{
				++_currentSize;
				_array[_currentSize] = x;
				findPositionForX(_currentSize, x);
		}
		else
		{
			return ;
		}
}

int minHeapQueue::find(int rootIndex, const int x)
{
		if (_currentSize == 0){return 0;}
		if (_array[rootIndex] > x) {return rootIndex;}
		else
		{
				int minLeftIndex = 0;
				int minRightIndex = 0;
				if (2 * rootIndex <= _currentSize) {minLeftIndex = find(2 * rootIndex, x);}
				if (2 * rootIndex + 1 <= _currentSize){minRightIndex = find(2 * rootIndex + 1, x);}

				if (0 == minRightIndex && minLeftIndex != 0){return minLeftIndex;}
				else if (0 == minLeftIndex && minRightIndex != 0){return minRightIndex;}
				else if (0 == minLeftIndex && 0 == minRightIndex){return 0;}
				else if (_array[minLeftIndex] > _array[minRightIndex])
				{
						return minRightIndex;
				}
				else if (_array[minLeftIndex] < _array[minRightIndex])
				{
					return minLeftIndex;
				}
				else if(_array[minLeftIndex] == _array[minRightIndex])
				{
						return minRightIndex < minLeftIndex ? minRightIndex : minLeftIndex;
				}
		}
}

void minHeapQueue::deleteRoot()
{
	if (_currentSize == 1){_currentSize = 0;}
	else if (_currentSize > 1)
	{
		_array[1] = _array[_currentSize--];
		int childIndex;
		int temp = _array[1];
		int beginIndex = 1;
		for (; beginIndex * 2 <= _currentSize; beginIndex = childIndex)
		{
			childIndex = beginIndex * 2;
			if (childIndex < _currentSize && _array[childIndex] > _array[childIndex + 1])
			{
				childIndex += 1;
			}
			if (_array[childIndex] < temp)
			{
				_array[beginIndex] = _array[childIndex];
			}
			else
			{
				break;
			}
		}
		_array[beginIndex] = temp;
	}
}

void minHeapQueue::decrease(const int nodeNum, const int privilegeNum)
{
		if (nodeNum > _currentSize || nodeNum <= 0){return ;}
		_array[nodeNum] -= privilegeNum;
		if (_array[nodeNum] < 0 && nodeNum == 1)
		{
				deleteRoot();
				return ;
		}
		else if (_array[nodeNum] >= 0)
		{
			findPositionForX(nodeNum, _array[nodeNum]);
		}
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
						int resultIndex = queue.find(1, x);
						if (resultIndex > 0)
						{
							std::cout << queue.find(1, x) << std::endl;
						}
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
