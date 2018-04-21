#pragma once

#include <iostream>
#include <chrono>

/// <summary>
/// c++11で使用できる時間計測をラップして使いやすくしたもの
/// </summary>
class TimerChrono
{

public:
	using tick_type = __int64;

	TimerChrono () :
		_start(std::chrono::system_clock::time_point::min()){}

	/// <summary>
	/// 計測の初期化
	/// </summary>
	void Clear ()
	{
		_start = std::chrono::system_clock::time_point::min ();
	}

	/// <summary>
	/// 計測中か
	/// </summary>
	/// <returns>計測中か</returns>
	const bool IsStarted () const
	{
		return _start != std::chrono::system_clock::time_point::min ();
	}

	/// <summary>
	/// 計測開始
	/// </summary>
	void Start ()
	{
		_start = std::chrono::system_clock::now ();
	}

	/// <summary>
	/// 計測中の時間をmsで返す
	/// </summary>
	/// <returns>計測時間</returns>
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
/// 時間を計測
/// TimerChronoと分けているのは環境によって図り方を使い分けるため
/// デフォルトではstd::coutにログを書き出す
/// </summary>
template <typename T> class TimerBase : private T
{
public:

	using BaseTimer = T;
	using tick_type = typename T::tick_type;

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="start_now">初期化時に計測を開始するか</param>
	explicit TimerBase ( const bool start_now );

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="activity">どんなことを計測するか</param>
	/// <param name="start_now">計測時に初期化するか</param>
	explicit TimerBase (
		char const* activity = "Stopwatch",
		const bool start_now = true );

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="log">ログの出力先</param>
	/// <param name="activity">どんなことを計測するか</param>
	/// <param name="start_now">計測時に初期化するか</param>
	explicit TimerBase (
		std::ostream& log,
		char const* activity = "Stopwatch",
		const bool start_now = true );

	/// <summary>
	/// 終了処理
	/// 内部でStopを呼んでいる
	/// </summary>
	~TimerBase ();

	/// <summary>
	/// 計測を開始したか
	/// </summary>
	/// <returns>計測を開始したか</returns>
	const bool IsStarted () const;

	/// <summary>
	/// 現在計測中の時間を表示する
	/// </summary>
	/// <param name="event_name">計測意図</param>
	/// <returns>ラップタイムを返す</returns>
	const tick_type Show ( char const* event_name = "show" );

	/// <summary>
	/// 計測を開始する
	/// </summary>
	/// <param name="event_name">計測意図</param>
	/// <returns>ラップタイムを返す</returns>
	const tick_type Start ( char const* event_name = "start" );

	/// <summary>
	/// 計測を終了する
	/// </summary>
	/// <param name="event_name">計測意図</param>
	/// <returns>ラップタイムを返す</returns>
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



