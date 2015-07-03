/*
This file is part of Telegram Desktop,
the official desktop version of Telegram messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014 John Preston, https://desktop.telegram.org
*/
#pragma once

#include "audio.h"

class PlayerWidget : public TWidget {
	Q_OBJECT

public:

	PlayerWidget(QWidget *parent);

	void paintEvent(QPaintEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void leaveEvent(QEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void resizeEvent(QResizeEvent *e);

	bool progressStep(float64 ms);
	bool stateStep(float64 ms);

	void updateState(SongMsgId playing, AudioPlayerState playingState, int64 playingPosition, int64 playingDuration, int32 playingFrequency);
	void updateState();
	void clearSelection();

	void mediaOverviewUpdated(PeerData *peer, MediaOverviewType type);

	bool seekingSong(const SongMsgId &song) const;

signals:

	void playerSongChanged(MsgId msgId);

private:

	enum OverState {
		OverNone = 0,
		OverPrev,
		OverPlay,
		OverNext,
		OverClose,
		OverVolume,
		OverFull,
		OverPlayback,

		OverStateCount
	};
	void updateDownTime();
	void updateOverState(OverState newState);
	void updateOverRect(OverState state);

	void updateControls();
	void findCurrent();

	void startPlay(MsgId msgId);

	QPoint _lastMousePos;
	void updateSelected();

	bool _prevAvailable, _nextAvailable, _fullAvailable;
	OverState _over, _down;
	int32 _downCoord;
	int64 _downDuration;
	int32 _downFrequency;
	float64 _downProgress;

	float64 _stateHovers[OverStateCount];
	typedef QMap<int32, uint64> StateAnimations;
	StateAnimations _stateAnimations;
	Animation _stateAnim;

	SongMsgId _song;
	int32 _index;
	History *_history;
	QRect _playRect, _prevRect, _nextRect, _playbackRect;
	QRect _closeRect, _volumeRect, _fullRect, _infoRect;
	int32 _timeWidth;
	QString _time;
	Text _name;
	bool _showPause;
	int64 _position, _duration;
	int32 _loaded;

	anim::fvalue a_progress, a_loadProgress;
	Animation _progressAnim;

};
