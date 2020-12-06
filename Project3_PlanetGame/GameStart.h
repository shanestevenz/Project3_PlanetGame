
#include "ViewObject.h"

class GameStart : public df::ViewObject {

private:
	void start();
	df::Music* p_music;
public:
	GameStart();
	void playMusic();
	int eventHandler(const df::Event* p_e);
	int draw();
};
