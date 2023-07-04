#include <iostream>
#include "StringCreaterPieceByPiece.h"
#include "MyString.h"

int main()
{
	StringCreaterPieceByPiece sc(2);
	sc.addPiece("tt");
	sc.addPiece("");
	sc.addPiece(" ball ");
	sc.addPiece("meow");
	sc.addPiece(" bla");
	sc[1] << " fri ";
	sc[2] << " Hi ";
	sc[2] << 10;
	sc[0] >> " my";
	sc[0] >> 10;
	MyString result1 = sc.toString(); // “test Hello friends 10football”
	std::cout << result1 << std::endl;
	sc.swapPices(1, 2);

	MyString result2 = sc.toString(); // “test10football Hello friends”
	std::cout << result2 << std::endl;
	sc.remove(1);

	MyString result3 = sc.toString(); // “test10 Hello friends
	std::cout << result3 << std::endl;

	/*StringPiece piece("kjfcw");
	piece.print();
	
	piece >> 5;
	piece.print();

	piece >> "jc"; 
	piece.print();

	piece << 10;
	piece.print();

	piece << "fejl";
	piece.print();*/
}