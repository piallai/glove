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
#include "SlvMacros.h"
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
#include <QObject>
#endif

/*! Class managing the progress signal of a loop.
* Does not contain progress value. Only status.*/
class SlvProgressionQt :
#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	public QObject,
#endif
	public SlvName {

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
	Q_OBJECT
#endif

private:

	/*! Tracked index of progress.
	It is important to set a safe index because it can be set to Ncounter if cancel is triggered.
	ie: Use a different index for data manipulation.*/
	unsigned int* counter;
	/*! Expected maximum number of iterations. Set by emit_start method.*/
	unsigned int Ncounter;

	/*! Whether the progression has been canceled externally or not.*/
	bool l_was_canceled;

public:

	SlvProgressionQt(std::string _name = "");
	~SlvProgressionQt();

	/*! Assign name of progression.*/
	SlvProgressionQt& operator=(const SlvProgressionQt& _progression);

	/*! Whether the progression as reached its maximum or not: *counter >= Ncounter-1.
	* Return true if the progression was not started yet.*/
	bool is_over() const;
	/*! Whether the progression is managing a counter or not. Depends on emit_start strategy.*/
	bool has_counter() const;

	/*! Emit start signal. Watch without control on the loop (no cancel button). Use explicit emit_progress(int _value) to emit progress.*/
	void emit_start(std::string _info) const;
	/*! Emit start signal. Use emit_progress().
	* \p _info : Set progress message
	* \p _counter : pointer to the iteration value. Takes control of value by setting \p _Ncounter in case the progression is stopped.*/
	void emit_start(std::string _info, unsigned int* _counter, const unsigned int _Ncounter) const;

	/*! Emit progress by using counter pointer and counter number defined by emit_start.
	* Return false if counter pointer or counter number is null.
	* If counter reaches Ncounter, then end_signal() is emitted.*/
	bool emit_progress() const;
	/*! Emit progress by explicitly setting the progress value \p _value. Must be in the range [0, 100].
	* Does not assign value to counter pointer.*/
	void emit_progress(int _value) const;
	/*! Emits end_signal. Confirm manually the progression progress is over.
	* Apply counter finish.
	* Release counter pointer.
	* If a counter is provided, is automatically called at end of loop. No need to call it.*/
	void emit_end() const;
	/*! Emits final_signal. Implies that progress monitoring is completely over. Will remove Qt progression from GlvProgressMgr.
	* Doing so means the progression will need to be added again to a Qt GlvProgressMgr.
	* Apply counter finish.
	* Release counter pointer.
	* ie: Same as emit_end() with removal from GlvProgressMgr.*/
	void emit_final() const;

	void cancel();
	/*! Whether the progression has been canceled externally or not.
	* If so, it means the algorithm that was watched probably did not go through.*/
	bool was_canceled() const;

	/*! Designed to be called from outside the SlvProgressionQt instance.
	* Enforce finish by setting the counter to finish value Ncounter.
	* The loop will end if the iterator is properly related to the counter pointer.*/
	void counter_finish();

private:

	static bool is_over(unsigned int _counter, unsigned int _Ncounter);

#if OPTION_ENABLE_SLV_QT_PROGRESS==1
signals:

	void start_signal(std::string _message);
	void progress_signal(int _value);
	/*! If a counter is provided, is automatically emitted at end of loop.*/
	void end_signal();
	void final_signal();
#endif

};
