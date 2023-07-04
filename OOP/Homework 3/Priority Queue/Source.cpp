#include "priorityQueue.hpp"

int main()
{
	try
	{
		KPriorityQueue<char> q(4); 

		q.push('A', 0);
		q.push('B', 3);
		q.push('C', 2);
		q.push('D', 2);
		q.push('E', 1);
		q.push('L', 3);
		q.push('M', 2);

		std::cout << q.peek(); 
		q.pop();

		std::cout << q.peek(); // L
		q.pop();

		std::cout << q.peek(); // C
		q.pop();

		std::cout << q.peek(); // D
		q.pop();

		std::cout << q.peek(); // M
		q.pop();

		std::cout << q.peek(); // E
		q.pop();

		std::cout << q.peek(); // A
		q.pop();

		std::cout << q.peek(); // A
		q.pop();
	}
	catch (const std::exception& e) 
	{
		std::cout << "An exception occurred: " << e.what() << std::endl;
	}
}