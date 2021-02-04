#ifndef source
#define source
using namespace std;
enum class shape{rectangle,circle};
struct rect{int weight,height;};
struct cir{int rad;};
struct container{
    shape main_shape,small_shape;
    rect rect1,rect2;
    cir circ1,circ2;
};
int TakeNumberFromUser(int flag);
char TakeCharacterFromUser(int flag);
bool CheckValidtyOfCharacter(const char input);
bool CheckValidtyOfNumber(const int input);
container checkshape(int flag,char shape);
container cont();
void makefile(container a_cont);
#endif
