/**
 * \file ImageHelper.cpp
 *
 * \author Charles Owen
 * \cond
 */

#include "stdafx.h"
#include "ImageHelper.h"
#include <string>

using namespace std;
using namespace Gdiplus;

/**
 * Destructor (never actually used)
 */
CImageHelper::~CImageHelper()
{
}



/** 
 * Load an image into a bitmap pointer
 * \param name The filename to load 
 * \returns Reference to shared_ptr we load into
 */
std::shared_ptr<Gdiplus::Bitmap> CImageHelper::LoadImage(const wchar_t *name)
{
	auto bitmap = shared_ptr<Bitmap>(Bitmap::FromFile(name));
	if (bitmap->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open: ");
		msg += name;
		AfxMessageBox(msg.c_str());
		return nullptr;
	}

	return bitmap;
}

/// \endcond