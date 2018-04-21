#pragma once

#include <iostream>
#include <chrono>

/// <summary>
/// c++11�Ŏg�p�ł��鎞�Ԍv�������b�v���Ďg���₷����������
/// </summary>
class TimerChrono
{

public:
	using tick_type = __int64;

	TimerChrono () :
		_start(std::chrono::system_clock::time_point::min()){}

	/// <summary>
	/// �v���̏�����
	/// </summary>
	void Clear ()
	{
		_start = std::chrono::system_clock::time_point::min ();
	}

	/// <summary>
	/// �v������
	/// </summary>
	/// <returns>�v������</returns>
	const bool IsStarted () const
	{
		return _start != std::chrono::system_clock::time_point::min ();
	}

	/// <summary>
	/// �v���J�n
	/// </summary>
	void Start ()
	{
		_start = std::chrono::system_clock::now ();
	}

	/// <summary>
	/// �v�����̎��Ԃ�ms�ŕԂ�
	/// </summary>
	/// <returns>�v������</returns>
	__int64 GetMs ()
	{
		if ( IsStarted() )
		{
			std::chrono::system_clock::duration diff;
			diff = std::chrono::system_clock::now () - _start;
			return std::chrono::duration_cast< std::chrono::milliseconds >( diff ).count ();
		}

		return 0;
	}

private:
	std::chrono::system_clock::time_point _start;
};


/// <summary>
/// ���Ԃ��v��
/// TimerChrono�ƕ����Ă���̂͊��ɂ���Đ}������g�������邽��
/// �f�t�H���g�ł�std::cout�Ƀ��O�������o��
/// </summary>
template <typename T> class TimerBase : private T
{
public:

	using BaseTimer = T;
	using tick_type = typename T::tick_type;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="start_now">���������Ɍv�����J�n���邩</param>
	explicit TimerBase ( const bool start_now );

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="activity">�ǂ�Ȃ��Ƃ��v�����邩</param>
	/// <param name="start_now">�v�����ɏ��������邩</param>
	explicit TimerBase (
		char const* activity = "Stopwatch",
		const bool start_now = true );

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="log">���O�̏o�͐�</param>
	/// <param name="activity">�ǂ�Ȃ��Ƃ��v�����邩</param>
	/// <param name="start_now">�v�����ɏ��������邩</param>
	explicit TimerBase (
		std::ostream& log,
		char const* activity = "Stopwatch",
		const bool start_now = true );

	/// <summary>
	/// �I������
	/// ������Stop���Ă�ł���
	/// </summary>
	~TimerBase ();

	/// <summary>
	/// �v�����J�n������
	/// </summary>
	/// <returns>�v�����J�n������</returns>
	const bool IsStarted () const;

	/// <summary>
	/// ���݌v�����̎��Ԃ�\������
	/// </summary>
	/// <param name="event_name">�v���Ӑ}</param>
	/// <returns>���b�v�^�C����Ԃ�</returns>
	const tick_type Show ( char const* event_name = "show" );

	/// <summary>
	/// �v�����J�n����
	/// </summary>
	/// <param name="event_name">�v���Ӑ}</param>
	/// <returns>���b�v�^�C����Ԃ�</returns>
	const tick_type Start ( char const* event_name = "start" );

	/// <summary>
	/// �v�����I������
	/// </summary>
	/// <param name="event_name">�v���Ӑ}</param>
	/// <returns>���b�v�^�C����Ԃ�</returns>
	const tick_type Stop ( char const* event_name = "stop" );

private:

	tick_type GetLapTime ();

	char const* _activity;
	tick_type _lap_time;
	std::ostream& _log;
};

template <typename T> inline TimerBase<T>::TimerBase ( const bool start_now ) :
	_activity { "Stopwatch" },
	_lap_time { 0 },
	_log { std::cout }
{
	if ( start_now )
	{
		Start ();
	}
}

template <typename T> inline TimerBase<T>::TimerBase (
	char const* activity,
	const bool start_now ) :
	_activity { activity },
	_lap_time { 0 },
	_log { std::cout }
{
	if ( start_now )
	{
		if ( _activity )
		{
			Start ();
		}
		else
		{
			Start ( nullptr );
		}
	}
}

template <typename T> inline TimerBase<T>::TimerBase (
	std::ostream& log,
	char const* activity,
	const bool start_now ) :
	_activity { activity },
	_lap_time { 0 },
	_log { log }
{
	if ( start_now )
	{
		if ( _activity )
		{
			Start ();
		}
		else
		{
			Start ( nullptr );
		}
	}
}

template <typename T> inline TimerBase<T>::~TimerBase ()
{
	if ( IsStarted () )
	{
		if ( _activity )
		{
			Stop ();
		}
		else
		{
			Stop ( nullptr );
		}
	}
}

template <typename T> inline typename TimerBase<T>::tick_type TimerBase<T>::GetLapTime ()
{
	return BaseTimer::GetMs();
}

template <typename T> inline const bool TimerBase<T>::IsStarted () const
{
	return BaseTimer::IsStarted ();
}

template <typename T> inline const typename TimerBase<T>::tick_type TimerBase<T>::Show ( char const* event_name )
{
	if ( IsStarted () )
	{
		_lap_time = GetLapTime ();

		if ( event_name && event_name [ 0 ] )
		{
			if ( _activity )
			{
				_log << _activity << ": ";
			}

			_log << event_name << "at " << _lap_time << "ms" << std::endl << std::flush;
		}
	}
	else
	{
		if ( _activity )
		{
			_log << _activity << ": not started" << std::endl << std::flush;
		}
	}

	return _lap_time;
}

template <typename T> inline const typename TimerBase<T>::tick_type TimerBase<T>::Start ( char const* event_name )
{
	if ( IsStarted () )
	{
		Stop ( event_name );
	}
	else
	{
		if ( event_name && event_name [ 0 ] )
		{
			if ( _activity )
			{
				_log << _activity << ": ";
			}

			_log << event_name << std::endl << std::flush;
		}
	}

	BaseTimer::Start ();

	return _lap_time;
}

template <typename T> inline const typename TimerBase<T>::tick_type TimerBase<T>::Stop ( char const* event_name )
{
	if ( IsStarted () )
	{
		_lap_time = GetLapTime ();

		if ( _activity )
		{
			_log << _activity << ": ";
		}

		_log << event_name << " " << _lap_time << "ms" << std::endl << std::flush;
	}

	BaseTimer::Clear ();

	return _lap_time;
}

using Stopwatch = TimerBase<TimerChrono>;



