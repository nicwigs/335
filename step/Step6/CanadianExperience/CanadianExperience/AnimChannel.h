/**
 * \file AnimChannel.h
 *
 * \author Nic Wiggins
 *
 * Base class for animation channels
 */

#pragma once

#include <string>
#include <memory>
#include <vector>

class CTimeline;

 /**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class CAnimChannel
{
public:
	CAnimChannel();
	virtual ~CAnimChannel();

	/** \brief Copy constructor disabled */
	CAnimChannel(const CAnimChannel &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannel &) = delete;
	
	/** Get the animation Channel name
	* \returns channel name */
	std::wstring GetName() const { return mName; }
	/** Set channel name
	* \param name New name of channel */
	void SetName(const std::wstring &name) { mName = name; }

	/** Get a pointer to the Timeline object
	* \returns Pointer to the Timeline object
	*/
	CTimeline *GetTimeline() { return mTimeline; }
	/** Set timeline
	* \param timeline New name of channel */
	void SetTimeline(CTimeline *timeline) { mTimeline = timeline; }

	bool IsValid();
	void SetFrame(int currFrame);
	void DeleteKeyframe();

	/** Class that represents a keyframe */
	class Keyframe
	{
	public:
		/** Get the frame of keyframe
		* \returns the frame */
		int GetFrame() const { return mFrame; }
		/** Set Keyframe Frame
		* \param frame New frame */
		void SetFrame(const int frame) { mFrame = frame; }

		/** Use this keyframe as keyframe 1 */
		void virtual UseAs1() = 0;
		/** Use this keyframe as keyfraem 2 */
		void virtual UseAs2() = 0;
		/** Use this keyframe as the value (angle/position) */
		void virtual UseOnly() = 0;

		/** \brief Default constructor disabled */
		Keyframe() = delete;
		/** \brief Copy constructor disabled */
		Keyframe(const Keyframe &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const Keyframe &) = delete;

	protected:
		///Frame
		int mFrame;

		/** Constructor
		* \param channel Channel we are associated with */
		Keyframe(CAnimChannel *channel) : mChannel(channel) {}
	private:
		/// The channel this keyframe is associated with
		CAnimChannel *mChannel;
	};

protected:
	void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);
	void virtual Tween(double t);

private:
	///Name of Animation Channel  
	std::wstring mName;
	///First keyframe
	int mKeyframe1 = -1;
	///Second keyframe
	int mKeyframe2 = -1;

	/// The timeline object
	CTimeline *mTimeline = nullptr;

	/// The collection of keyframes for this channel
	std::vector<std::shared_ptr<Keyframe>> mKeyframes;
};

