#ifndef TRAVELING_WILL_PLAYABLE_LEVEL_H
#define TRAVELING_WILL_PLAYABLE_LEVEL_H

#include "traveling_will_level.h"
#include "platform.h"
#include "will.h"
#include "button.h"

using std::string;
using std::shared_ptr;

using namespace ijengine;

class TravelingWillPlayableLevel : public TravelingWillLevel{
    public:
        TravelingWillPlayableLevel(const string& current_level, const string& next_level = "", const string audio_path = "", 
		int audio_duration = -1);
        ~TravelingWillPlayableLevel();

		bool done() const;
		string next() const;
		string audio() const;

		bool on_event(const GameEvent& event);

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
        static const int GAME_EVENT_JUMP =              1 << 4;
        static const int GAME_EVENT_SLIDE_PRESSED =     1 << 5;
        static const int GAME_EVENT_SLIDE_RELEASED =    1 << 6;
        static const int GAME_EVENT_MENU_SELECT =       1 << 7;
        static const int GAME_EVENT_PUNCH =             1 << 11;
        static const int NUMBER_OF_SECTIONS =           7;
        static const int WILL_HEIGHT =                  45;
        static const int WILL_WIDTH =                   57;
        static const int COLLECTABLE_DIMENSION =        30;
        static const int COLLECTABLE_SIZE =             WILL_HEIGHT + COLLECTABLE_DIMENSION;
        static const int ENEMY_DIMENSION =              45;
        static const int ENEMY_SIZE =                   WILL_HEIGHT + ENEMY_DIMENSION;
        static const int INVALID =                      -10000000;

        bool m_is_punching, level_started, level_finished;
        
        int m_audio_duration, m_audio_counter;
        int n_screens;
        int n_collectables, n_enemies;
        int collectable_it, enemy_it;
        int m_enemy_type;
        int m_punch_counter;
        
        deque<int> enemy_type, collectable, enemy;
        deque<double> collectable_height, enemy_height, platform_height;

        double m_x_speed, m_y_speed;
        double sprite_counter, m_sprite_speed;
        double m_camera_x, m_camera_y, m_reverse_camera_x, m_reverse_camera_y;
        double m_will_x, m_will_y;
        double m_collectable, m_enemy;
        double m_floor;

        Will * m_will;

        shared_ptr<Texture>  m_level[20], m_enemy_texture[4], m_collectable_texture;
        shared_ptr<Texture> m_progress_bar[3], m_will_progress_bar, m_number, m_collectable_icon;

        void do_collisions(unsigned now);
        void update_counters(unsigned now);
        void check_game_over();
        void update_platforms_position();

        Platform platforms[10];
};

#endif