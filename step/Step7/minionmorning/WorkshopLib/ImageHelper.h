/**
 * \file ImageHelper.h
 *
 * \author Charles Owen
 *
 * Simple image loader helper class.
 * \cond
 */

#pragma once
#include <memory>

/**
 * Simple image loader helper class.
 */
class CImageHelper
{
public:
	CImageHelper() = delete;
	~CImageHelper();
	static std::shared_ptr<Gdiplus::Bitmap> LoadImage(const wchar_t * name);
};

/// \endcond
