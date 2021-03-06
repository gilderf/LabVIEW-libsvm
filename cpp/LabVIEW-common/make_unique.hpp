// make_unique implementation -*- C++ -*-

// Copyright (C) 2008-2014 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

// Original implementation of the following code can be found in unique_ptr.h of GNU GCC 4.9.3
// The implementation of make_unique has not been modified, but the implementation of unique_ptr has been stripped

#pragma once

#include <memory>

namespace std {
	template<typename _Tp>
	struct _MakeUniq
	{ typedef unique_ptr<_Tp> __single_object; };

	template<typename _Tp>
	struct _MakeUniq<_Tp[]>
	{ typedef unique_ptr<_Tp[]> __array; };

	template<typename _Tp, size_t _Bound>
	struct _MakeUniq<_Tp[_Bound]>
	{ struct __invalid_type { }; };

	/// std::make_unique for single objects
	template<typename _Tp, typename... _Args>
	inline typename _MakeUniq<_Tp>::__single_object
	make_unique(_Args&&... __args)
	{ return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); }

	/// std::make_unique for arrays of unknown bound
	template<typename _Tp>
	inline typename _MakeUniq<_Tp>::__array
	make_unique(size_t __num)
	{ return unique_ptr<_Tp>(new typename remove_extent<_Tp>::type[__num]()); }

	/// Disable std::make_unique for arrays of known bound
	template<typename _Tp, typename... _Args>
	inline typename _MakeUniq<_Tp>::__invalid_type
	make_unique(_Args&&...) = delete;
}


