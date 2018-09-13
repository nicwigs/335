/**
 * \file TileMinion.h
 *
 * \author Nic Wiggins
 *
 *  Class that implements a Minion Tile
 */

#pragma once

#include "Tile.h"


/**
 * A tile that has a minion on it
 */
class CTileMinion : public CTile
{
public:
	CTileMinion(CCity * city);

	///Default constructor (disabled)
	CTileMinion() = delete;

	///Copy constructor (disabled)
	CTileMinion(const CTileMinion &) = delete;

	~CTileMinion();

	void LoadImage(std::unique_ptr<Gdiplus::Bitmap> &image, std::wstring name);

	void Draw(Gdiplus::Graphics * graphics);
	void UpdateState();
	void FeedMinion();
	void TakePotion();
	void Update(double elapsed);
	/// The states of minions possbile 
	enum State {Normal, Banana, Mutant};

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitMinion(this); }

	/// if the minion is running
	bool mIsRunning = false;

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Sees if minion is a mutant minion 
	* \return True if is mutant**/
	bool IsMutant() { return mState == Mutant; }

private:
	/// The image of the normal minion
	std::unique_ptr<Gdiplus::Bitmap> mMinionImage;
	/// The image of the banana minion
	std::unique_ptr<Gdiplus::Bitmap> mBananaImage;
	/// The image of the mutant minion
	std::unique_ptr<Gdiplus::Bitmap> mMutantImage;

	///The state of the minion
	State mState = Normal;

	///Count of minions
	int mBananaCount = 0;

	/// X position minion moved since last update
	double mRunX = 0;

	/// Speed of minion while running
	double mSpeedX = 0;



};

