#include "pubghypetrain.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

class Moveable{
public:
  Moveable(int px, int py, int vx, int vy, char sym){
    this->px = px;
    this->py = py;
    this->vx = vx;
    this->vy = vy;
    this->sym = sym;
  };
  
  int px,py,vx,vy;
  char sym;
};

class BallGame{
  
public:
  BallGame( int width, 
            int height,
            char symForVacantPnt)
  {
    this->h = height;
    this->w = width;
    this->symForVacantPnt = symForVacantPnt;
  };
  
  vector<Moveable*> mvec;
  
  void addMoveable(Moveable* m){
    mvec.push_back(m);
  };
  
  void update(){
    int sz = mvec.size();
    for(int i = 0; i < sz;i++){
      this->update(mvec[i]);
    };
  };
  
  void update(Moveable* m){
    moveMoveable(m);
    collideMoveable(m);
  };
  
  void moveMoveable(Moveable* m){
    m->px += m->vx;
    m->py += m->vy;
  };
  
  void collideMoveable(Moveable* m){
    bool outX = (m->px <= 0 || m->px >= this->w-1);
    m->vx += -2 * m->vx * outX;
    bool outY = (m->py <= 0 || m->py >= this->h-1);
    m->vy += -2 * m->vy * outY;
  };
  
  char getSymOnPnt(int x, int y){
    int sz = mvec.size();
    for(int i = 0; i < sz;i++){
      if(mvec[i]->px == x && mvec[i]->py == y){return mvec[i]->sym;};
    };
    return this->symForVacantPnt;
  };
  
  int w;

  int h;
  
  char symForVacantPnt;
};

void draw(BallGame &b, int xmax, int ymax){
  ClearScreen();
  for(int y = 0; y < ymax; y++){
    for(int x = 0; x < xmax; x++){
     cout << b.getSymOnPnt(x,y);
    };
    cout << endl;
  };
};

int main(){
  int T_SLEEP_MILLIS = 50;
  int BALLPARK_WIDTH = 15;
  int BALLPARK_HEIGHT = 15; 
  BallGame bg(BALLPARK_WIDTH,BALLPARK_HEIGHT,'.');
  Moveable m1(1,5,2,-1,'O');
  Moveable m2(8,8,-1,-1,'X');
  bg.addMoveable(&m1);
  bg.addMoveable(&m2);
  for(int i = 0; i < 50; i++){
    bg.update();
    draw(bg,bg.w,bg.h);
    sleep(T_SLEEP_MILLIS);
  };
  return 0;
};