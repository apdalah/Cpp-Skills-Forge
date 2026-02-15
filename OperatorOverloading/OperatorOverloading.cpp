#include <iostream>

class MP //Stand for Manipulate Operators
{
public:
    float X, Y;
public:

	MP() :X(0.0), Y(0.0) {}

    MP(float x, float y) :X(x), Y(y) {}

    void printPosition(const std::string& movement)
    {
		std::cout << "\nUser " << movement << ": X[" << X << "] Y[" << Y << "]\n";
    }

    MP operator+(const MP& anotherObject) const
    {
		return MP(X + anotherObject.X, Y + anotherObject.Y);
    }

    MP operator* (const MP& anotherObject) const
    {
        return MP(X * anotherObject.X, Y * anotherObject.Y);
    }

    MP operator- (const MP& anotherObject) const
    {
        return MP(X - anotherObject.X, Y - anotherObject.Y);
    }

    MP operator/ (const MP& anotherObject) const
    {
        if (anotherObject.X != 0 && anotherObject.Y != 0)
        {
            return MP(X / anotherObject.X, Y / anotherObject.Y);
        }
        else
        {
            return MP(0.0f, 0.0f);
        }
    }

    bool operator==(const MP& anotherObject) const
    {
        return (X == anotherObject.X) && (Y == anotherObject.Y);
	}

    bool operator!=(const MP& anotherObject) const
    {
        return !(*this == anotherObject);
	}
};


std::ostream& operator<<(std::ostream& stream, const MP& printedObject)
{
    stream << "X[" << printedObject.X << "] Y[" << printedObject.Y << "]";
    return stream;
}

int main()
{
    MP position0;
	std::cout << "Default position is:" << position0 << " => [Printed through overloade '<<' operator!]" << std::endl;


	MP position1(10.0f, 20.0f);
    position1.printPosition("starts at");

    MP moveUp(0.5f, 0.5f);
	MP movedPosition = position1 + moveUp;
	movedPosition.printPosition("moved on to");

    MP powerUP(1.5f, 1.5f);
	MP poweredPosition = position1 * powerUP;
    poweredPosition.printPosition("power up to");

    MP stepBack(1.8f, 1.8f);
	MP steppedBackPosition = position1 - stepBack;
    steppedBackPosition.printPosition("stepped back to");

	MP fallDown(2.0f, 2.0f);
	MP fallenPosition = position1 / fallDown;
    fallenPosition.printPosition("fall down at");

	MP finalPosition = position1 + moveUp - stepBack * powerUP / fallDown;
	finalPosition.printPosition("final position is");

	MP winingPosition(10.0f, 20.0f);

    if (finalPosition == winingPosition)
    {
        std::cout << "\nPlayer reached the winning position!" << std::endl;
    }
    else
    {
        std::cout << "\nPlayer is still away from the winning position." << std::endl;
	}


	return 0;
}
