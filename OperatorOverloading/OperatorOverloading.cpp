#include <iostream>

/**
 * @class MP
 * @brief Represents a 2D position or vector with overloaded arithmetic operators.
 *
 * MP (Manipulate Operators) is a lightweight 2D coordinate class designed to
 * demonstrate operator overloading in C++. It supports the four standard
 * arithmetic operations, equality comparisons, and stream output — allowing
 * positions and movements to be composed naturally using familiar math syntax.
 *
 * @example
 *   MP position(10.0f, 20.0f);
 *   MP move(0.5f, 0.5f);
 *   MP result = position + move; // X[10.5] Y[20.5]
 */
class MP //Stand for Manipulate Operators
{
public:
    float X, Y;
public:
    /**
     * @brief Default constructor. Initializes both X and Y to 0.0.
     *
     * Produces the origin point (0, 0), useful as a neutral starting
     * position before any movement is applied.
     *
     * @example
     *   MP origin;
     *   // origin.X == 0.0f, origin.Y == 0.0f
     */
	MP() :X(0.0), Y(0.0) {}

    /**
     * @brief Parameterized constructor. Initializes X and Y to given values.
     *
     * @param x  The horizontal coordinate.
     * @param y  The vertical coordinate.
     *
     * @example
     *   MP position(10.0f, 20.0f);
     *   // position.X == 10.0f, position.Y == 20.0f
     */
    MP(float x, float y) :X(x), Y(y) {}

    /**
     * @brief Prints the current X and Y coordinates with a movement label.
     *
     * Outputs a formatted line to stdout describing the current state
     * of this position, prefixed with "User {movement}:".
     *
     * @param movement  A descriptive label for the movement or state
     *                  (e.g., "starts at", "moved on to", "fall down at").
     *
     * @example
     *   MP pos(5.0f, 3.0f);
     *   pos.printPosition("starts at");
     *   // Output: User starts at: X[5] Y[3]
     */
    void printPosition(const std::string& movement)
    {
		std::cout << "\nUser " << movement << ": X[" << X << "] Y[" << Y << "]\n";
    }

    /**
     * @brief Adds two MP objects component-wise.
     *
     * Produces a new MP whose X is the sum of both X values, and
     * whose Y is the sum of both Y values. Neither operand is modified.
     *
     * @param anotherObject  The MP to add to this one.
     * @return A new MP representing the sum: (X + rhs.X, Y + rhs.Y).
     *
     * @example
     *   MP a(10.0f, 20.0f), b(0.5f, 0.5f);
     *   MP result = a + b; // X[10.5] Y[20.5]
     */
    MP operator+(const MP& anotherObject) const
    {
		return MP(X + anotherObject.X, Y + anotherObject.Y);
    }

    /**
     * @brief Multiplies two MP objects component-wise.
     *
     * Scales each component independently: the resulting X is X * rhs.X,
     * and the resulting Y is Y * rhs.Y. Useful for applying scalar
     * multipliers that differ per axis.
     *
     * @param anotherObject  The MP to multiply with this one.
     * @return A new MP representing the product: (X * rhs.X, Y * rhs.Y).
     *
     * @note This is NOT a dot product or cross product — it is a simple
     *       component-wise (Hadamard) multiplication.
     *
     * @example
     *   MP a(10.0f, 20.0f), scale(1.5f, 1.5f);
     *   MP result = a * scale; // X[15] Y[30]
     */
    MP operator* (const MP& anotherObject) const
    {
        return MP(X * anotherObject.X, Y * anotherObject.Y);
    }

    /**
     * @brief Subtracts one MP from another component-wise.
     *
     * Produces a new MP whose X is the difference of both X values,
     * and whose Y is the difference of both Y values. Useful for
     * computing displacement or reversing a movement.
     *
     * @param anotherObject  The MP to subtract from this one.
     * @return A new MP representing the difference: (X - rhs.X, Y - rhs.Y).
     *
     * @example
     *   MP a(10.0f, 20.0f), b(1.8f, 1.8f);
     *   MP result = a - b; // X[8.2] Y[18.2]
     */
    MP operator- (const MP& anotherObject) const
    {
        return MP(X - anotherObject.X, Y - anotherObject.Y);
    }

    /**
     * @brief Divides two MP objects component-wise with zero-division guard.
     *
     * Produces a new MP whose X is X / rhs.X and Y is Y / rhs.Y.
     * If EITHER component of the divisor is zero, returns MP(0, 0)
     * to avoid undefined behavior from division by zero.
     *
     * @param anotherObject  The MP to divide this one by.
     * @return A new MP representing the quotient: (X / rhs.X, Y / rhs.Y),
     *         or MP(0, 0) if either divisor component is zero.
     *
     * @warning The zero guard triggers if EITHER X or Y is zero,
     *          meaning a valid component can be silently discarded.
     *          For example: MP(10, 5) / MP(2, 0) returns MP(0, 0),
     *          not MP(5, 0). Consider handling per-component if precision matters.
     *
     * @example
     *   MP a(10.0f, 20.0f), b(2.0f, 2.0f);
     *   MP result = a / b; // X[5] Y[10]
     *
     *   MP zero(0.0f, 2.0f);
     *   MP safe = a / zero; // X[0] Y[0]  <- zero guard triggered
     */
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

    /**
     * @brief Checks whether two MP objects are exactly equal.
     *
     * Returns true only if both X and Y components match exactly.
     * Used here to detect whether a player has reached a target position.
     *
     * @param anotherObject  The MP to compare against.
     * @return true  if X == rhs.X AND Y == rhs.Y.
     * @return false otherwise.
     *
     * @warning Compares float values with ==, which can fail for values
     *          computed through floating-point arithmetic due to rounding.
     *          For computed positions, prefer an epsilon-based comparison:
     *          std::abs(X - rhs.X) < 1e-5f.
     *
     * @example
     *   MP a(10.0f, 20.0f), b(10.0f, 20.0f);
     *   a == b; // true
     *
     *   MP c(10.0f, 19.9f);
     *   a == c; // false
     */
    bool operator==(const MP& anotherObject) const
    {
        return (X == anotherObject.X) && (Y == anotherObject.Y);
	}

    /**
     * @brief Checks whether two MP objects are not equal.
     *
     * Returns the logical negation of operator==. Two MP objects are
     * considered not equal if either X or Y (or both) differ.
     *
     * @param anotherObject  The MP to compare against.
     * @return true  if X != rhs.X OR Y != rhs.Y.
     * @return false if both components are exactly equal.
     *
     * @note Implemented by delegating to operator== via *this,
     *       ensuring both operators stay consistent with zero duplication.
     *
     * @example
     *   MP a(10.0f, 20.0f), b(9.0f, 20.0f);
     *   a != b; // true
     */
    bool operator!=(const MP& anotherObject) const
    {
        return !(*this == anotherObject);
	}
};

/**
 * @brief Stream insertion operator for MP — enables cout << mp syntax.
 *
 * A non-member overload of operator<< that writes an MP object's
 * coordinates to any std::ostream in the format: X[val] Y[val]
 *
 * Defined outside the class to allow the MP object to appear on the
 * RIGHT side of <<, while the stream appears on the left — matching
 * the natural direction of stream operators.
 *
 * @param stream         The output stream to write to (e.g., std::cout).
 * @param printedObject  The MP object whose coordinates will be written.
 * @return Reference to the same stream, enabling operator chaining
 *         (e.g., cout << a << b << endl).
 *
 * @example
 *   MP pos(3.0f, 7.5f);
 *   std::cout << pos;
 *   // Output: X[3] Y[7.5]
 *
 *   std::cout << "Position: " << pos << std::endl;
 *   // Output: Position: X[3] Y[7.5]
 */
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
