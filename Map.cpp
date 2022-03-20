#include "Map.h"

Map::Map(const String& F) {
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
    std::vector<String> ZeroMap = {
            "0000000000",
            "0         0",
            "0   s     0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "0         0",
            "00000000000",
    };
    std::vector<String> FirstMap = {
            "s000000000000000000000000000000000000000",
            "s                                      0",
            "s   s                                  0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "s                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0000000000000000000000000000000000000000",
    };
    std::vector<String> TileMap = {
            "FFFFFFFFFFFFF@",
            "F4F4F4F4F4F4F@",
            "F4F4F4F4F4F4F@",
            "F4F4F494F4F4F@",
            "F4F4F3F3F4F4F@",
            "F3F3F1F1F3F3F@",
            "1F11F3F3F11F1@",
            "8F33F1F1F33F8@",
            "F1F1F444F1F1F@",
            "F4F4F4F4F4F4F@",
            "F4F4F3F3F4F4F@",
            "F4F4F?1?F4F4F@",
            "FFFFF0F2FFFFF@",
    };
    switch (number_map) {
        case 0: return ZeroMap; break;
        case 1: return FirstMap; break;
        case 2: return TileMap; break;
    }
}

void Map::CreateMap(std::vector<String> Diagram,int i, int j) {

    if (Diagram[i][j] == ' ') map_sprite.setTextureRect(IntRect(160, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
    if (Diagram[i][j] == 's') map_sprite.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
//    if (Diagram[i][j] == '0') map_sprite.setTextureRect(IntRect(0, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
    if (Diagram[i][j] == 'F')  map_sprite.setTextureRect(IntRect(160, 0, 32, 32));
    if (Diagram[i][j] == '0')  map_sprite.setTextureRect(IntRect(0,64,32,32));
    if (Diagram[i][j] == '1')  map_sprite.setTextureRect(IntRect(0,128,32,32));
    if (Diagram[i][j] == '2')  map_sprite.setTextureRect(IntRect(0,32,32,32));
    if (Diagram[i][j] == '3')  map_sprite.setTextureRect(IntRect(0,96,32,32));
    if (Diagram[i][j] == '4')  map_sprite.setTextureRect(IntRect(0,0,32,32));
    if (Diagram[i][j] == '8')  map_sprite.setTextureRect(IntRect(64,96,32,32));
    if (Diagram[i][j] == '?')  map_sprite.setTextureRect(IntRect(160, 0, 32, 32));
    if (Diagram[i][j] == '@')  map_sprite.setTextureRect(IntRect(160, 0, 32, 32));
    map_sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат


}

Sprite Map::GetMapSprite() {
    return map_sprite;
}

void Map::InteractionWithMap(std::vector<String> Diagram, Player &tank) {
    for (int i = tank.GetY() / 32; i < (tank.GetY() + tank.GetH()) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
        for (int j = tank.GetX() / 32; j < (tank.GetX() + tank.GetW()) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
        {
            if (Diagram[i][j] == '4')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
            {
                if (tank.GetSpeedY()>0)//если мы шли вниз,
                {
                    tank.SetY(i * 32 - tank.GetH() - 6);//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                }
                if (tank.GetSpeedY()<0)
                {
                    tank.SetY(i * 32 + tank.GetH() + 6);//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                }
                if (tank.GetSpeedX()>0)
                {
                    tank.SetX(j * 32 - tank.GetW() - 6);//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                }
                if (tank.GetSpeedX() < 0)
                {
                    tank.SetX(j * 32 + tank.GetW() + 6);//аналогично идем влево
                }
            }

//            if (Diagram[i][j] == 's') { //если символ равен 's' (камень)
//                x = 300; y = 300;//какое то действие... например телепортация героя
//                TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
//            }
        }
}

