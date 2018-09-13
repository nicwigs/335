/**
* \file Counter.h
*
* \author Zoinul Choudhury
*
* Class to represent a Counter.
*/

#pragma once

#include <memory>
#include <string>

class CScoreboard;

/**
 * Class that discribes villian counter
 */
class CCounter
{
public:
	/// Default constructor (disabled)
	CCounter() = delete;

	/// Copy constructor (disabled)
	CCounter(const CCounter &) = delete;

	CCounter(CScoreboard *scoreboard, const std::wstring & filename, int pointMultiplier);
	
	virtual ~CCounter();

	/**
	* Adds points to the counter point total
	* \param points The amount of points to be added to the point count
	*/
	void AddPoints(int points) { mPointCount += points; }

	void Draw(Gdiplus::Graphics *graphics, Gdiplus::Brush *brush, Gdiplus::Font *font);

	/// Clear the counter's point count
	void Clear() { mPointCount = 0; };

	/**
	* Gets the counter image height
	* \return Image height
	*/
	int GetHeight() { return mImage->GetHeight(); }

	/**
	* Gets the X position for the counter
	* \return Integer X position
	*/
	int GetX() { return mX; }

	/**
	* Gets the Y position for the counter
	* \return Integer Y position
	*/
	int GetY() { return mY; }

	/**
	* Sets the x,y position for the counter
	* \param x The x position of the counter
	* \param y The y position of the counter
	*/
	void SetPosition(int x, int y) { mX = x; mY = y; }

	/**
	* Gets the total number of points for the counter
	* \return Counter point count multiplied by the point multiplier
	*/
	int GetPoints() { return (mPointCount * mPointMultiplier); }

private:
	/// Number of points for the counter
	int mPointCount = 0;

	/// Point multiplier for the counter
	int mPointMultiplier;

	/// X position for the counter
	int mX = 0;

	/// Y position for the counter
	int mY = 0;

	/// Counter image
	std::unique_ptr<Gdiplus::Bitmap> mImage;

	/// Scoreboard this counter is a part of
	CScoreboard *mScoreboard;
};

