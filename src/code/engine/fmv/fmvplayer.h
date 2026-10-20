// The full-motion video player of the engine (code/engine/fmv/fmvplayer.cpp, unit 0x1082EC10 - 0x1082FA00; the file
// name and every name here are guesses, only the Lua names of the script calls are the engine's). Movies are asked
// for with PlayMovie, which queues a request; the per-frame UpdateMovies works on the request at the front of the
// queue and UpdateMovieState drives the request through its states. The decoder object lives in another unit
// (0x1059F000 - 0x105A1000).
#ifndef ENGINE_FMV_FMVPLAYER_H
#define ENGINE_FMV_FMVPLAYER_H

namespace engine
{
	// 0x1082F990: queues a movie. The unnamed arguments are copied into the request
	void PlayMovie(const char* path, bool unknown12, int id, int unused, bool unknown13, bool unknown11,
		int unknown18, bool unknown19);
	// 0x1082F300: draws and updates the movie of the request at the front of the queue
	void UpdateMovies();
	// 0x1082F7A0: moves the request at the front of the queue on through its states
	void UpdateMovieState();
	// 0x1082F6D0 / 0x1082F5D0
	void InitMovies();
	void ShutdownMovies();
	// 0x1082EE80: sets whether movies are skipped altogether, returns the old setting
	bool SetSkipMovies(bool skip);
	// 0x1082EE90 / 0x1082EEC0: the volume of the movies (the second is the product of three audio settings)
	void SetMovieVolume(float volume);
	void UpdateMovieVolume();
	// 0x1082EF20 / 0x1082EF50 / 0x1082EF80 / 0x1082EFC0: calls on the decoder under the lock
	void FadeMovieOut();
	void ResumeMovie();
	bool IsMovieUnknown();
	void ReleasePreloadedMovie();
	// 0x1082F020 / 0x1082F060 / 0x1082F070 / 0x1082F0A0 / 0x1082F0C0: the script calls and the like
	bool IsMovieLoaded();
	bool IsMovieDone();
	bool SkipMovie();
	void StopMovie();
	void SetMovieNoCanvas(bool value);
	// 0x1082F530 / 0x1082F570
	bool IsMoviePlaying();
	int GetQueuedMovieCount();
}

#endif
