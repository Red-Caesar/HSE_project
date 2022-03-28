#include "Map.h"
#include "Bullet.h"

Map::Map(const String &F) {
    File = F;
    map_image.loadFromFile("..\\images/" + File);
    map_texture.loadFromImage(map_image);//закидываем наше изображение в текстуру
    map_sprite.setTexture(map_texture);
}

void Map::SetNumberMap(int numb_m) {
    number_map = numb_m;
}

int Map::GetNumberMap() {
    return number_map;
}

std::vector<String> Map::GetDiagramMap() {
    switch (number_map) {
        case 0:
            return ZeroMap;
        case 1:
            return FirstMap;
        case 2:
            return SecondMap;
    }
}
void Map::SetDiagramMap(int i, int j, char texture) {
    switch (number_map) {
        case 0:
             ZeroMap[i][j] = texture;
        case 1:
             FirstMap[i][j] = texture;
        case 2:
             SecondMap[i][j] = texture;
    }

}

void Map::CreateMap(std:: vector<String> Diagram, int i, int j) {
    if (Diagram[i][j] == ' ') map_sprite.setTextureRect(IntRect(160,   0, 32, 32));
    if (Diagram[i][j] == 's') map_sprite.setTextureRect(IntRect( 32,   0, 32, 32));
    if (Diagram[i][j] == 'F') map_sprite.setTextureRect(IntRect(160,   0, 32, 32));
    if (Diagram[i][j] == '0') map_sprite.setTextureRect(IntRect(  0,  64, 32, 32));
    if (Diagram[i][j] == '1') map_sprite.setTextureRect(IntRect(  0, 128, 32, 32));
    if (Diagram[i][j] == '2') map_sprite.setTextureRect(IntRect(  0,  32, 32, 32));
    if (Diagram[i][j] == '3') map_sprite.setTextureRect(IntRect(  0,  96, 32, 32));
    if (Diagram[i][j] == '4') map_sprite.setTextureRect(IntRect(  0,   0, 32, 32));
    if (Diagram[i][j] == '8') map_sprite.setTextureRect(IntRect( 64,  96, 32, 32));
    if (Diagram[i][j] == '9') map_sprite.setTextureRect(IntRect( 64,  0, 32, 32));
    if (Diagram[i][j] == '?') map_sprite.setTextureRect(IntRect(160,   0, 32, 32));
    if (Diagram[i][j] == '@') map_sprite.setTextureRect(IntRect(160,   64, 32, 32));
    if (Diagram[i][j] == 'G') map_sprite.setTextureRect(IntRect(160,   32, 32, 32));
    map_sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

}

Sprite Map::GetMapSprite() {
    return map_sprite;
}
////////////////надо доделать
void Map::InteractionTankWithMap(std::vector<String> Diagram, Player &tank) {
    for (int i = tank.GetY() / 32; i < (tank.GetY() + tank.GetH()) /32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
        for (int j = tank.GetX() / 32; j < (tank.GetX() + tank.GetW()) /32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
        {
            if (tank.GetX() < 32) { tank.SetX(32); }
            if (tank.GetY() < 32) { tank.SetY(32); }
            if (tank.GetX() > 420) { tank.SetX(420); }
            if (tank.GetY() > 422) { tank.SetY(422); }

            if (Diagram[i][j] == '0' || Diagram[i][j] == '5' ){
                if (tank.GetX() > j * 32 - 12 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 + 16 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32 + tank.GetW() + 6); }
                }
            }
            if (Diagram[i][j] == '1' || Diagram[i][j] == '6' ){
                if (tank.GetY() > i * 32 - 12 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 + 16 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32 + tank.GetW() + 6); }
                }
            }
            if (Diagram[i][j] == '2' || Diagram[i][j] == '7' ){

                if (tank.GetX() < j * 32 + 16 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32 - 16 + tank.GetW() + 6); }
                }
            }
            if (Diagram[i][j] == '3' || Diagram[i][j] == '8'){
                if (tank.GetY() < i * 32 + 12 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 - 16 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32  + tank.GetW() + 6); }
                }
            }


                if (Diagram[i][j] == '4' || Diagram[i][j] == '9' || Diagram[i][j] == 'A' )//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
                {
                    if (tank.GetSpeedY() > 0) {//если мы шли вниз,
                        tank.SetY(i * 32 - tank.GetH() - 6);
                    }//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                    if (tank.GetSpeedY() < 0) {
                        tank.SetY(i * 32 + tank.GetH() + 6);
                    }//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                    if (tank.GetSpeedX() > 0) {
                        tank.SetX(j * 32 - tank.GetW() - 6);
                    }//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                    if (tank.GetSpeedX() < 0) {
                        tank.SetX(j * 32 + tank.GetW() + 6);
                    }//аналогично идем влево
                }
            }
    }

void Map::InteractionEnemyTankWithMap(std::vector<String> Diagram, Enemy_tank &tank) {   // Та же функция, но для врагов
                                                                                         // В случае коллизии поднимаем флаг смены направления
    for (int i = tank.GetY() / 32; i < (tank.GetY() + tank.GetH()) /32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
        for (int j = tank.GetX() / 32; j < (tank.GetX() + tank.GetW()) /32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
        {
            if (tank.GetX() < 32) { tank.SetX(32);
                    tank.SetFlag_to_change(true);
            }
            if (tank.GetY() < 32) { tank.SetY(32);
                    tank.SetFlag_to_change(true);
            }
            if (tank.GetX() > 420) { tank.SetX(420);
                    tank.SetFlag_to_change(true);
            }
            if (tank.GetY() > 422) { tank.SetY(422);
                    tank.SetFlag_to_change(true);
            }

            if (Diagram[i][j] == '0' || Diagram[i][j] == '5' ){
                if (tank.GetX() > j * 32 - 16 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 + 16 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32 + tank.GetW() + 6); }
                    tank.SetFlag_to_change(true);
                }
            }
            if (Diagram[i][j] == '1'|| Diagram[i][j] == '6' ){
                if (tank.GetY() > i * 32 - 16 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 + 16 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32 + tank.GetW() + 6); }
                  //  if(!tank.GetIsPlayer()){
                        tank.SetFlag_to_change(true);
                   // }
                }
            }
            if (Diagram[i][j] == '2' || Diagram[i][j] == '7'){

                if (tank.GetX() < j * 32 + 16 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32 - 16 + tank.GetW() + 6); }
                   // if(!tank.GetIsPlayer()){
                        tank.SetFlag_to_change(true);
                   // }
                }
            }
            if (Diagram[i][j] == '3' || Diagram[i][j] == '8'){
                if (tank.GetY() < i * 32 + 16 ){
                    if (tank.GetSpeedY() > 0) { tank.SetY(i * 32 - tank.GetH() - 6);}
                    if (tank.GetSpeedY() < 0) { tank.SetY(i * 32 - 16 + tank.GetH() + 6); }
                    if (tank.GetSpeedX() > 0) { tank.SetX(j * 32 - tank.GetW() - 6);}
                    if (tank.GetSpeedX() < 0) { tank.SetX(j * 32  + tank.GetW() + 6); }
                  //  if(!tank.GetIsPlayer()){
                        tank.SetFlag_to_change(true);
                   // }
                }
            }

            if (Diagram[i][j] == '4' || Diagram[i][j] == '9' )//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
            {
                if (tank.GetSpeedY() > 0){//если мы шли вниз,
                    tank.SetY(i * 32 - tank.GetH() - 6);}//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                if (tank.GetSpeedY() < 0) {
                    tank.SetY(i * 32 + tank.GetH() + 6);}//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                if (tank.GetSpeedX() > 0) {
                    tank.SetX(j * 32 - tank.GetW() - 6);}//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                if (tank.GetSpeedX() < 0) {
                    tank.SetX(j * 32 + tank.GetW() + 6);}//аналогично идем влево
               // if(!tank.GetIsPlayer()){
                    tank.SetFlag_to_change(true);
                //}
            }
            //if(tank.GetX())
        }
}

bool Map::InteractionBulletWithMap(std::vector<String> Diagram, Bullet &bullet) {
    for (int i = bullet.GetY() / 32; i < bullet.GetY() /32; i++)
        for (int j = bullet.GetX() / 32; j < bullet.GetX()/32; j++){
            if (bullet.GetX() < 32 || bullet.GetY() < 32 || bullet.GetX() > 448|| bullet.GetY() > 448  ) { return false;}
            else {
                if (Diagram[i][j] == 'G'){
//                    game over
//                    who is the owner of bullet doesnt matter
//                }
                if ((Diagram[i][j] == '1' || Diagram[i][j] == '6') && bullet.GetY() > i * 32 + 16 )
                {
                    if (Diagram[i][j] == '1')
                         SetDiagramMap( i, j, 'F');
                    return false;}
                if ((Diagram[i][j] == '0' || Diagram[i][j] == '5')&& bullet.GetX() > j * 32 + 16 ) {
                    if (Diagram[i][j] == '0')
                        SetDiagramMap( i, j, 'F');
                    return false;}
                if ((Diagram[i][j] == '2' || Diagram[i][j] == '7') && bullet.GetX() < j * 32 + 16){
                    if (Diagram[i][j] == '2')
                        SetDiagramMap( i, j, 'F');
                    return false;}
                if ((Diagram[i][j] == '3' || Diagram[i][j] == '8') && bullet.GetY() < i * 32 + 16){
                    if (Diagram[i][j] == '3')
                        SetDiagramMap( i, j, 'F');
                    return false;}
                if (Diagram[i][j] == '4' || Diagram[i][j] == '9'){
                    if (Diagram[i][j] == '4'){
                        if (bullet.GetSpeedY() > 0){ SetDiagramMap( i, j, '1');}
                        if (bullet.GetSpeedY() < 0){ SetDiagramMap( i, j, '3');}
                        if (bullet.GetSpeedX() > 0){ SetDiagramMap( i, j, '0');}
                        if (bullet.GetSpeedX() < 0){ SetDiagramMap( i, j, '2');}
                    }
                    return false; }
                if (Diagram[i][j] == '9'){
                    return false;
                }
            return true; }
        }
}








