/*
* This file is part of the Glove distribution (https://github.com/piallai/glove).
* Copyright (C) 2024 Pierre Allain.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "GloveOptions.h"

#include "SlvName.h"
#include "SlvLblName.h"
#include "SlvMacrosDeclarations.h"
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
#include <QObject>
#endif

/*! Class managing the progress signals of a loop.*/
class SlvProgressionQt :
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	public QObject,
#endif
	public SlvLblName {

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	Q_OBJECT
#endif

private:

	/*! Tracked index of progress.
	It is important to set a safe index because it can be set to Niterations if cancel is triggered.
	ie: Use a different index for data manipulation.*/
	void* iterator_ptr;
	enum IteratorType { Int, UnsignedInt, Size_t };
	/*! Type of the iterator defined at start.*/
	IteratorType iterator_type;

	/*! Expected maximum number of iterations. Set by emit_start method.*/
	unsigned int Niterations;

	/*! Whether progression instance is used directly as an iterator
	* true : instance is an iterator. See operator= method.
	* false : instance may control an external iterator using a pointer.*/
	bool l_iterating;
	/*! Iteration value when l_iterating is true.*/
	std::size_t iterator;

	bool l_started;
	/*! If Niterations was not provided, then there is no feedback on progress.
	* This variable checks if progress has ended or not.*/
	bool l_no_feedback_ended;

	/*! Optional message.*/
	glvm_GetSetVariable(std::string, message);

	/*! Whether the progression has been canceled externally or not.*/
	bool l_was_canceled;

	/*! Whether this progress is being called multiple times.
	* If true, default hiding policy on ending will avoid glitches.
	* In this case, hiding must be managed using finish().*/
	bool l_recurrent;

public:

	SlvProgressionQt(std::string _name = "", bool _l_recurrent = false);
	SlvProgressionQt(const SlvProgressionQt& _progression);
	~SlvProgressionQt();

private:
	/*! Reset progress status.*/
	void clear_progress();

public:
	/*! Reset progress status.*/
	void clear();

	/*! Does nothing. Disable assigment to ensure progress variables are not mixed.*/
	SlvProgressionQt& operator=(const SlvProgressionQt& _progression);

	/*! Whether this progress is being called multiple times.
	* If true, default hiding policy on ending will avoid glitches.
	* In this case, hiding must be managed using finish().*/
	void set_recurrent(bool _l_recurrent);
	/*! Whether this progress is being called multiple times.
	* If true, default hiding policy on ending will avoid glitches.
	* In this case, hiding must be managed using finish().*/
	bool is_recurrent() const;

	/*! Whether the progression as reached its maximum or not: *iterator_ptr >= Niterations-1.
	* Return true if the progression was not started yet.*/
	bool is_over() const;
	/*! Whether the progression is managing a iterator_ptr or not. Depends on start() strategy.*/
	bool has_iterator_ptr() const;
	/*! Whether progression instance is used as an iterator. See operator= method.*/
	bool is_iterating() const;
	/*! Whether control on progress is possible or not.*/
	bool is_cancelable() const;

	/*! Emit start signal. Progress without bar nor control on the loop (no cancel button).*/
	void start();
	/*! Emit start signal. Progress without control on the loop (no cancel button).
	* Use explicit update(int _value) at the end of the loop to update progress.*/
	void start(const unsigned int _Niterations);
	/*! Emit start signal.
	* Use update() at the end of the loop to update progress.
	* \p _iterator_ptr : pointer to the iteration value. Takes control of value by setting it to \p _Niterations in case the progression is stopped.*/
	template <class Titerator>
	void start(Titerator* _iterator_ptr, const unsigned int _Niterations);
private :
	void start_pv(const unsigned int _Niterations);
public :

	/*! Emit progress by using _iterator_ptr pointer and Niterations number defined by emit_start.
	* Return false if _iterator_ptr pointer or Niterations number is null.
	* If _iterator_ptr reaches Niterations, then ended() is emitted.*/
	bool update();
	/*! Update progress by explicitly setting the progress value \p _value.
	* To be used with start(const unsigned int _Niterations).
	* Does not assign value to _iterator_ptr pointer.
	* Return false if _iterator_ptr number is null.*/
	bool update(int _value);
	/*! Confirm manually the progress is over.
	* To be used if started with start(), ie no progress bar nor cancel control.
	* If the progress is already monitored by a _iterator_ptr or an iterator, is automatically called at end of loop. No need to call it explicitly.
	* Apply iterator finish.
	* Release iterator_ptr pointer (set to NULL).*/
	void end();
	/*! Implies that progress monitoring is completely over. Will remove Qt progression from GlvProgressMgr.
	* Doing so means the progression will need to be added again to a Qt GlvProgressMgr.
	* Apply iterator finish.
	* Release _terator_ptr pointer (set to NULL).
	* ie: Same as end() with removal from GlvProgressMgr.*/
	void finish();

	/*! Apply cancel to tracked iterator/iterator_ptr.
	* Ends the loop.
	* Does not emit signals. Use end() method instead.*/
	void cancel();
	/*! Whether the progression has been canceled externally or not.
	* If so, it means the algorithm that was watched probably did not go through.*/
	bool was_canceled() const;

	/*! Cast to iterator.*/
	operator std::size_t() const;
	/*! Initialize iterator and start progress.*/
	SlvProgressionQt& operator=(const std::size_t _iterator);

	/*! Control of maximum. Compare iterator < _Niterations and updates Niterations. Comparison in for-loop used to set Niterations.
	* Leaves < operator possible on iterator index, without impacting progression.
	* On the other hand, bitwise operation is not possible of iterator index.
	* Use init() or start() methods as an alternative to manage Niterations with classical int iterator index.*/
	bool operator<<(std::size_t _Niterations);
	/*! Overload to avoid call to built-in operator and std::size_t casting.*/
	bool operator<<(int _Niterations);
	/*! Overload to avoid call to built-in operator and std::size_t casting.*/
	bool operator<<(unsigned int _Niterations);

	/*! Control of maximum. Compare iterator < _Niterations and updates Niterations. Comparison in for-loop used to set Niterations.
	* Leaves < operator possible on iterator index, without impacting progression.
	* On the other hand, bitwise operation is not possible of iterator index.
	* Use init() or start() methods as an alternative to manage Niterations with classical int iterator index.*/
	bool operator<<=(std::size_t _Niterations);
	/*! Overload to avoid call to built-in operator and std::size_t casting.*/
	bool operator<<=(int _Niterations);
	/*! Overload to avoid call to built-in operator and std::size_t casting.*/
	bool operator<<=(unsigned int _Niterations);

	/*! Increase iterator and update progress.*/
	SlvProgressionQt& operator++();
	/*! Increase iterator and update progress.*/
	SlvProgressionQt operator++(int);

private:

	/*! Enforce finish by setting the iterator_ptr to finish value Niterations.
	* The loop will end if the iterator is properly related to the iterator_ptr pointer.*/
	void iterator_finish();

	/*! iterator_ptr pointer is being checked at end of loop content.*/
	static bool is_iterator_ptr_over(unsigned int _iterator_value, unsigned int _Niterations);
	/*! Iterator is being checked at beginning of loop content.*/
	static bool is_iterator_over(std::size_t _iterator, unsigned int _Niterations);

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
signals:

	/*! Emitted when progress starts.*/
	void started();
	/*! Emit progress value in a range [0, 100] when progress is updated.*/
	void updated(int _value);
	/*! If an iterator or iterator_ptr is provided, is automatically emitted at end of loop.*/
	void ended();
	/*! Emitted when progress is completely over.*/
	void finished();
#endif

};
