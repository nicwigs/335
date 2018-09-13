/**
* \file PointHistory.cpp
*
* \author Charles Owen
*
* Class that maintains a collection of Point objects in order.
*/

#pragma once
#include <memory>

/**
 * Class that maintains a collection of Point objects in order.
 */
class CPointHistory
{
public:
	CPointHistory();
	virtual ~CPointHistory();

	void Add(Gdiplus::Point p);

protected:
	/**
	* Nested class that stores up to five points in a bin.
	*/
	class PointBin
	{
	public:
		/// Maximum number of points we can put into a bin
		const static int MaxPoints = 5;

		/// Constructor
		PointBin() {}

		/// Destructor
		virtual ~PointBin() {}

		/// Get the current count of items in this bin
		/// \return Count (zero to five)
		int GetCnt() { return mCnt; }

		bool Add(Gdiplus::Point point);

		/// Get a stored point
		/// \param i Index to the point (0 to mCnt-1)
		/// \return Stored point value
		Gdiplus::Point Get(int i) { return mPoints[i]; }

		/// Get the next bin in the list
		/// \return Pointer to next bin or null if none
		std::shared_ptr<PointBin> GetNext() { return mNext; }

		/// Set the next bin in the list
		/// \param next Next pointer to set
		void SetNext(std::shared_ptr<PointBin> next) { mNext = next; }

	private:
		/// Array to store the points
		Gdiplus::Point mPoints[MaxPoints];

		/// Number of elements currently stored in array
		int mCnt = 0;

		/// Next bin
		std::shared_ptr<PointBin> mNext;
	};
	public:
		/** Iterator that iterates over the city tiles */
		class Iter
		{
		public:
			/** Constructor
			* \param head The head of the linked list we are iterating over
			* \param bin The pointer to the current bin
			* \param point The point index in array with said bin */
			Iter(std::shared_ptr<PointBin> head, std::shared_ptr<PointBin> bin, int point )
				: mHead(head), mBin(bin),mPointIndex(point) {}

			/** Test for end of the iterator
			* \param other The other iterator we are comparing to
			* \returns True if we this position equals not equal to the other position */
			bool operator!=(const Iter &other) const
			{ return (mBin != other.mBin || mPointIndex != other.mPointIndex);}

			/** Get value at current position
			* \returns Value at mBin & mPointIndex in the collection */
			Gdiplus::Point operator *() const { return mBin->Get(mPointIndex);}

			/** Increment the iterator
			* \returns Reference to this iterator */
			const Iter& operator++()
			{
				mPointIndex++; //increase point index
				if (mPointIndex == mBin->GetCnt()) //Go beyond total amount of indexs in bin
				{
					mPointIndex = 0;
					mBin = mBin->GetNext();
				}
				return *this;
			}

		private:
			std::shared_ptr<PointBin> mHead;     ///< Head to list we are itterating over
			std::shared_ptr<PointBin> mBin;		///< Bin Position in collection
			int mPointIndex;					///< Point position in bin
		};

	/** Get an iterator for the beginning of the PointHistory Collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this->mHead,this->mHead,0); }

	/** Get an iterator for the end of the PointHistory collection
	* \returns Iter object at position past the end */
	Iter end() 
	{ return Iter(this->mHead,nullptr,0);}


	/// Pointer to the head of the linked list of bins
	std::shared_ptr<PointBin> mHead;

private:
	/// Pointer to the tail of the linked list of bins (last node)
	std::shared_ptr<PointBin> mTail;
};

