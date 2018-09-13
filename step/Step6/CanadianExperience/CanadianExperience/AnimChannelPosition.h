/**
 * \file AnimChannelPosition.h
 *
 * \author Nic Wiggins
 *
 * Animation channel for position.
 */

#pragma once

#include "AnimChannel.h"

 /**
 * Animation channel for positions. 
 */
class CAnimChannelPosition : public CAnimChannel
{
public:
	CAnimChannelPosition();
	virtual ~CAnimChannelPosition();

	/** \brief Copy constructor disabled */
	CAnimChannelPosition(const CAnimChannelPosition &) = delete;
	/** \brief Assignment operator disabled */
	void operator=(const CAnimChannelPosition &) = delete;

	/** Get the animation Channel position
	* \returns position of channel */
	Gdiplus::Point GetPosition() const { return mPosition; }

	void SetKeyframe(Gdiplus::Point pos);

	/** Class that represents a keyframe position */
	class KeyframePosition : public Keyframe
	{
	public:
		/** Get keyframe position
		* \returns position of keyframeposition */
		Gdiplus::Point GetPosition() const { return mPosition; }

		/** Use this keyframe as keyframe 1 */
		virtual void UseAs1() override { mChannel->mKeyframe1 = this; }
		/** Use this keyframe as keyfraem 2 */
		virtual void UseAs2() override { mChannel->mKeyframe2 = this; }
		/** Use this keyframe as the angle */
		virtual void UseOnly() override { mChannel->mPosition = mPosition; }

		/** Constructor
		* \param channel The channel we are for
		* \param point The position for the keyframe */
		KeyframePosition(CAnimChannelPosition *channel, Gdiplus::Point point) :
			Keyframe(channel), mChannel(channel), mPosition(point) {}

		/** \brief Default constructor disabled */
		KeyframePosition() = delete;
		/** \brief Copy constructor disabled */
		KeyframePosition(const KeyframePosition &) = delete;
		/** \brief Assignment operator disabled */
		void operator=(const KeyframePosition &) = delete;

	private:
		///position
		Gdiplus::Point mPosition;

		/// The channel this keyframe is associated with
		CAnimChannelPosition *mChannel;
	};

protected:
	void Tween(double t) override;

private:
	///position of channel
	Gdiplus::Point mPosition;

	/// The first angle keyframe
	KeyframePosition *mKeyframe1 = nullptr;

	/// The second angle keyframe
	KeyframePosition *mKeyframe2 = nullptr;
};

