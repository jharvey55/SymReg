#include <Point.h>

/**
 * @brief default constructor
 *
 * Produces point with value (0, 0)
 */
Point::Point()
{
	this->x = 0;
	this->y = 0;
}

/**
 * @brief Constructor for specified point
 *
 * @param x
 * @param y
 */
Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}
