#include <iostream>

class Point {
private:
   int x;
   int y;

public:
   Point(int xv, int yv) : x(xv), y(yv) { }

   int get_x() {
      return this->x;
   }

   int get_y() {
      return this->y;
   }
};

class Rectangle {
private:
   Point* top_left;
   Point* bottom_right;

public:
   Rectangle(int x1, int y1, int x2, int y2) {
      this->top_left = new Point(x1, y1);
      this->checkBound(*top_left);

      this->bottom_right = new Point(x2, y2);
      this->checkBound(*bottom_right);
   }

   ~Rectangle() {
      delete top_left;
      delete bottom_right;
   }

   void checkBound(Point& p) {
      if(!((p.get_x() > 0 && p.get_x() < 100) && (p.get_y() > 0 && p.get_y() < 100))) {
         std::cout << "out of bound" << std::endl;
         exit(0);
      }
   }

   void filledRect() {
      int width = (this->bottom_right->get_x() - this->top_left->get_x()) + 1;
      int height = (this->bottom_right->get_y() - this->top_left->get_y()) + 1;

      for(int i = 0; i < height; i++) {
         for(int j = 0; j < width; j++)
            std::cout << "*";
         std::cout << std::endl;
      }
   }

   void roundRect() {
      int width = (this->bottom_right->get_x() - this->top_left->get_x()) + 1;
      int height = (this->bottom_right->get_y() - this->top_left->get_y()) + 1;

      for(int i = 0; i < height; i++) {
         if(i == 0 || i == (height - 1)) {
            for(int j = 0; j < width; j++)
               std::cout << "*";
         } else {
            std::cout << "*";
            for(int j = 0; j < (width - 2); j++)
               std::cout << " ";
            std::cout << "*";
         }
         std::cout << std::endl;
      }
   }

   void pointRect() {
      int width = (this->bottom_right->get_x() - this->top_left->get_x()) + 1;
      int height = (this->bottom_right->get_y() - this->top_left->get_y()) + 1;

      std::cout << "*";
      
      for(int i = 0; i < height; i++)
         std::cout << std::endl;

      for(int j = 0; j < width; j++)
         std::cout << " ";

      std::cout << "*" << std::endl;
   }
};

int main() {
   int x1, y1, x2, y2;
   std::cin >> x1 >> y1 >> x2 >> y2;

   Rectangle r1(x1, y1, x2, y2);

   int menu;
   bool running = true;

   while(running) {
      std::cin >> menu;
      switch (menu)
      {
      case 0:
         running = false;
         break;

      case 1:
         r1.filledRect();
         break;
      
      case 2:
         r1.roundRect();
         break;

      case 3:
         r1.pointRect();
         break;
      
      default:
         break;
      }
   }
   return 0;
}