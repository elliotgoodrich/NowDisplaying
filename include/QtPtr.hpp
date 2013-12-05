#ifndef INCLUDE_GUARD_F120CACE_405C_4564_BF99_50B089C76A88
#define INCLUDE_GUARD_F120CACE_405C_4564_BF99_50B089C76A88

/**
\file   QtPtr.hpp
\author Elliot Goodrich

NowDisplaying - a program to display what music is currently playing.

Copyright (C) 2013 Elliot Goodrich

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QPointer>

#include <new>
#include <type_traits>
#include <utility>

namespace nd {

/**
	A smart pointer for QObjects that releases ownership when the object has an owner.

	\note This is not necessarily thread-safe.
*/
template <typename T>
class QtPtr {
public:
	/** Don't manage any pointer. */
	QtPtr()
	: m_ptr{nullptr} {
	}

	/** Construct a QtPtr object from T. */
	QtPtr(T* ptr)
	: m_ptr{ptr} {
	}

	/** If the pointer we are managing has a parent (i.e. it's lifetime is already managed) then
	    don't delete it. */
	~QtPtr() {
		if(m_ptr->parent()) {
			m_ptr = nullptr;
		}
	}

	/** Implicit conversion to T*. */
	operator T*() {
		return m_ptr;
	}

	/** Implicit conversion to T*. */
	operator T const*() const {
		return m_ptr;
	}

	/** Arrow operator. */
	T* operator->() {
		return m_ptr;
	}

	/** Arrow operator. */
	T const* operator->() const {
		return m_ptr;
	}

	/** Dereference operator. */
	T& operator*() {
		return *m_ptr;
	}

	/** Dereference operator. */
	T const& operator*() const {
		return *m_ptr;
	}

private:
	QPointer<T> m_ptr;
};

/** Create a QtPtr directly from the arguments to T's ctor. */
template <typename T, typename ...Args>
QtPtr<T> make_qt(Args&& ...args) {
	return QtPtr<T>(new T{std::forward<Args>(args)...});
}

}

#endif
