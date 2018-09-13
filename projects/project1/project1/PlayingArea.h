/**
 * \file PlayingArea.h
 *
 * \author Nic Wiggins
 *
 *  Area in which minions move around and so does Gru
 *  Surrounded by a green boarder
 */



#pragma once

/**
 * Area in which villians, Gru, and minions can move
 */
class CPlayingArea
{
public:
	CPlayingArea();
	virtual ~CPlayingArea();

	const static double GridSize;
	const static double GridRadius;
	const static double GridMargin;

	/** The grid radius
	* \returns grid radius in pixels */
	double GetGridRadius() const { return GridRadius; }

	/** The grid margin
	* \returns grid margin in pixels */
	double GetGridMargin() const { return GridMargin; }


	virtual void DrawBorder(Gdiplus::Graphics *graphics, Gdiplus::Pen *pen);

};

