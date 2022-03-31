#include "Player.h"
#include "Types.h"

using namespace sf;


void Player::Init(int x, int y) {
    m_sprite.setPosition(x, y);
    m_x = x;
    m_y = y;
    m_dir = DIR_UP;
}


void Player::setRect(float CurrentFrame) {
    if (m_name == "main_tank") {

        switch (m_level) {
            case TANK_SLOW:
                switch (m_dir) {
                    case DIR_RIGHT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 1, 35, 26, 26));
                        break;
                    case DIR_LEFT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 5, 99, 26, 26));
                        break;
                    case DIR_DOWN:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 65, 26, 26));
                        break;
                    case DIR_UP:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 5, 26, 26));
                        break;
                }
                break;
            case TANK_MEDIUM:
                switch (m_dir) {
                    case DIR_RIGHT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 64, 35, 32, 26));
                        break;
                    case DIR_LEFT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 64, 99, 32, 26));
                        break;
                    case DIR_DOWN:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 67, 64, 26, 32));
                        break;
                    case DIR_UP:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 67, 0, 26, 32));
                        break;
                }
                break;
        }
    }
    if (m_name == "friend_tank") {
        switch (m_level) {
            case TANK_SLOW:
                switch (m_dir) {
                    case DIR_RIGHT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 1, 163, 26, 26));
                        break;
                    case DIR_LEFT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 5, 227, 26, 26));
                        break;
                    case DIR_DOWN:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 193, 26, 26));
                        break;
                    case DIR_UP:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 3, 133, 26, 26));
                        break;
                }
                break;
            case TANK_MEDIUM:
                switch (m_dir) {
                    case DIR_RIGHT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 64, 163, 32, 26));
                        break;
                    case DIR_LEFT:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 64, 227, 32, 26));
                        break;
                    case DIR_DOWN:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 67, 192, 26, 32));
                        break;
                    case DIR_UP:
                        m_sprite.setTextureRect(IntRect(32 * int(CurrentFrame) + 67, 128, 26, 32));
                        break;
                }
                break;
        }

    }

}


void Player::update(float time) {
    switch (m_dir) {
        case 0:
            m_vx = m_speed;
            m_vy = 0;
            break;
        case 1:
            m_vx = -m_speed;
            m_vy = 0;
            break;
        case 2:
            m_vx = 0;
            m_vy = m_speed;
            break;
        case 3:
            m_vx = 0;
            m_vy = -m_speed;
            break;
    }

    m_x += m_vx * time;
    m_y += m_vy * time;

    m_speed = 0;
    m_sprite.setPosition(m_x, m_y);
    if (m_player_lives == 0) { is_alive = false; }
}

int Player::GetPlayerLives() const {
    return m_player_lives;
}

void Player::SetPlayerLives(int lives) {
    m_player_lives = lives;
}

void Player::DecreaseLives() {
    m_player_lives--;
}

void Player::Respawn() {
    if (m_name == "main_tank") {
        m_x = 164;
        m_y = 420;
    }
    if (m_name == "friend_tank") {
        m_x = 290;
        m_y = 420;
    }
}

void Player::SpawnInit(int x, int y) {
    spawn_image.loadFromFile("..\\images/sprite.bmp");
    spawn_texture.loadFromImage(spawn_image);
    spawn_sprite.setTexture(spawn_texture);
    spawn_sprite.setPosition(x, y);
    Spawn = true;
}

Sprite Player::GetSpriteSpawn() {
    return spawn_sprite;
}

void Player::DrawSpawnStars(Game_time time) {
    int i = time.GetTimeSpawn() / 100;
    switch (i) {
        case 1:
            spawn_sprite.setTextureRect(IntRect(256, 32, 32, 32));
            break;
        case 2:
            spawn_sprite.setTextureRect(IntRect(290, 32, 32, 32));
            break;
        case 3:
            spawn_sprite.setTextureRect(IntRect(320, 32, 32, 32));
            break;
        case 4:
            spawn_sprite.setTextureRect(IntRect(352, 32, 32, 32));
            break;
        case 5:
            spawn_sprite.setTextureRect(IntRect(386, 32, 32, 32));
            break;
        case 6:
            spawn_sprite.setTextureRect(IntRect(420, 32, 32, 32));
            break;
    }

}

void Player::DrawSpawn(Game_time time) {
    int i = time.GetTimeSpawn() / 100;
    i = i % 2;
    switch (i) {
        case 0:
            spawn_sprite.setTextureRect(IntRect(256, 0, 32, 32));
            break;
        case 1:
            spawn_sprite.setTextureRect(IntRect(288, 0, 32, 32));
            break;
    }

}

void Player::SetFlagSpawn(bool value) {
    Spawn = value;
}

bool Player::GetFlagSpawn() {
    return Spawn;
}

void Player::SetPlayerLevel(int level) {
    m_player_lives = level;
}

void Player::Control(float CurrentFrame) {
    if (m_name == "main_tank") {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            m_dir = DIR_LEFT;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            m_dir = DIR_RIGHT;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            m_dir = DIR_UP;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            m_dir = DIR_DOWN;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
    }
    if (m_name == "friend_tank") {
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            m_dir = DIR_LEFT;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            m_dir = DIR_RIGHT;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            m_dir = DIR_UP;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            m_dir = DIR_DOWN;
            m_speed = 0.1;
            setRect(CurrentFrame);
        }
    }
}
