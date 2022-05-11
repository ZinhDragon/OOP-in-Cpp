#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

/**Point as a data class**/
class Point{
public:
    double x;
    double y;
    Point(){};
    Point(double x, double y){
        this->x=x;
        this->y=y;
    }
    ~Point(){};
    virtual void print(){
        cout<<left<<setfill('.')<<setw(30)<<"Center Point"<<"["<<this->x<<", "<<this->y<<"]"<<endl;
    }
};

class TwoDShape{
protected:
    string name;
    Point* point;   /**Composition: TwoDShape owns Point**/
public:
    TwoDShape(){};
    TwoDShape(double x, double y, string name){
        /**Exception[Try throw catch]: here we don't accept inappropriate name**/
        try{
            string inappropriateName = "Fuck";
            if(name != inappropriateName){
                this->name=name;
            } else {
                throw(name);
            }
        }
        catch(string name){
            cout<<"Inappropriate Name :)))"<<endl;
            exit(1);
        }
        /**Because point is a pointer, you need to allocate memory and value**/
        point = new Point(x,y);
    }
    ~TwoDShape(){
        /**Delete the point**/
        delete point;
    }
    string getName(){
        return this->name;
    }
    virtual void print(){
        point->print();
        cout<<left<<setfill('.')<<setw(30)<<"Name"<<this->name<<endl;
    }
    /** TwoDShape* obj instead of const TwoDShape& obj for more reliability **/
    double computeDistance(TwoDShape *obj){
        /**cmath header file**/
        return sqrt(pow(this->point->x - obj->point->x,2) + pow(this->point->y - obj->point->y,2));
    }
    /**Declare like below since you want TwoDShape to be an abstract class**/
    virtual double perimeter() = 0;
    virtual double area() = 0;
    virtual void printAreaAndPeri(){
        cout<<left<<setfill('.')<<setw(30)<<"Perimeter"<<this->perimeter()<<endl;
        cout<<left<<setfill('.')<<setw(30)<<"Area"<<this->area()<<endl;
    }

};

class Rectangle: public TwoDShape{
private:
    double width;
    double height;
public:
    Rectangle(){};
    Rectangle(double x, double y, string name, double width, double height):TwoDShape(x,y,name){
        this->width=width;
        this->height=height;
    }
    ~Rectangle(){};
    void print(){
        TwoDShape::print();
        cout<<left<<setfill('.')<<setw(30)<<"Width"<<this->width<<endl;
        cout<<left<<setfill('.')<<setw(30)<<"Height"<<this->height<<endl;
        TwoDShape::printAreaAndPeri();
    }
    double perimeter(){
        return 2*(this->width + this->height);
    }
    double area(){
        return this->width*this->height;
    }
};

class Square: public TwoDShape{
private:
    double side;
public:
    Square(){};
    Square(double x, double y, string name, double side):TwoDShape(x,y,name){
        this->side=side;
    }
    ~Square(){}
    void print(){
        TwoDShape::print();
        cout<<left<<setfill('.')<<setw(30)<<"Side"<<this->side<<endl;
        TwoDShape::printAreaAndPeri();
    }
    double perimeter(){
        return 4*this->side;
    }
    double area(){
        return pow(this->side,2);
    }
};

class Circle: public TwoDShape{
private:
    double radius;
public:
    Circle(){};
    Circle(double x, double y, string name, double radius):TwoDShape(x,y,name){
        this->radius=radius;
    }
    ~Circle(){}
    void print(){
        TwoDShape::print();
        cout<<left<<setfill('.')<<setw(30)<<"Side"<<this->radius<<endl;
        TwoDShape::printAreaAndPeri();
    }
    double perimeter(){
        /**M_PI to call pi number**/
        return M_PI*this->radius*2;
    }
    double area(){
        return M_PI*pow(this->radius,2);
    }
};

template <typename T>
void printData(vector<T*> vect){
    int i = 1;
    for(T* shapes: vect){
        cout<<"Shape #"<<i<<endl;
        shapes->print();
        i++;
        cout<<endl;
    }

}
template <typename T>
double computeTotalArea(vector<T*> vect){
    double sum = 0.0;
    for(T* shapes:vect){
        sum+=(shapes->area());
    }
    return sum;
}
template <typename T>
double computeTotalPerimeter(vector<T*> vect){
    double sum = 0.0;
    for(T* shapes: vect){
        sum+=(shapes->perimeter());
    }
    return sum;
}

void sortPeri(vector<TwoDShape*> vect){
    vector<double> peri;
    for(TwoDShape* shapes: vect){
        peri.push_back(shapes->perimeter());
    }
    /**sort(*.begin(),*.end(), greater<type>()) to find the decreasing order**/
    sort(peri.begin(), peri.end(),greater<double>());
    for(double pe:peri){
        cout<<pe<<"; ";
    }
    cout<<endl;
}

template <typename T>
void printOnlyCircle(vector<T*> vect){
    int n = 0;
    /**To use the dynamic_cast use the one below**/
    for(T* shapes: vect){
        if(Circle* cir = dynamic_cast<Circle*>(vect.at(n))){
            cir->print(); cout<<endl;
        }
        n++;
    }
}

template <typename T>
void countShapes(vector<T*> vect){
    int n = 0;
    int i = 0, j = 0, k = 0;
    for(T* shapes: vect){
        if(Circle* cir = dynamic_cast<Circle*>(vect.at(n))){
            i++;
        }
        else if (Square* sqr = dynamic_cast<Square*>(vect.at(n))){
            j++;
        } else {
            k++;
        }
        n++;
    }
    cout<<"\nThere are "<<i<<" Circle(/s), "<<j<<" Square(/s), and "<<k<<" Rectangle(/s)"<<endl;
    i, j, k = 0;
}



int main(){
    freopen("shapeData.txt","w",stdout); //for file

    cout<<"Copyrighted Code by Nguyen Ngoc Vinh\n"<<endl;
    Circle circle1(3,4.5,"Circle 1", 8.3);
    Square square1(5.6,9.1,"Square 1", 7.3);
    Circle circle2(6.3,10,"Circle 2", 8.9);
    Rectangle rectangle1(5.2,8.7,"Rectangle 1", 5, 6.4);
    Rectangle rectangle2(8.3,13,"Rectangle 2",6,19);
    Circle circle3(5.3,19,"Circle 3",13.3);
    Square square2 (8.9,10.3,"Square 2", 23.3);
    //Circle fuck(4,5,"Fuck",8.9); //=> for exception
    Square square3(1.2,5.8,"Square 3",8);
    Square square4(9.9,5.6,"Square 4",10.5);
    Rectangle rectangle3(6.7,17.8,"Rectangle 3",10,14.2);

    vector<TwoDShape*> vect;
    vect.push_back(&circle1);
    vect.push_back(&square1);
    vect.push_back(&circle2);
    vect.push_back(&rectangle1);
    vect.push_back(&rectangle2);
    vect.push_back(&circle3);
    vect.push_back(&square2);
    vect.push_back(&square3);
    vect.push_back(&square4);
    vect.push_back(&rectangle3);

    /**Your own custom sort**/
    /**In this case, we want to sort in name alphabetical order**/
    sort(vect.begin(),vect.end(),[](TwoDShape* obj1, TwoDShape* obj2)
         {
             return (obj1->area() < obj2->area());
         }
         );
    printData(vect);

    cout<<left<<setfill('.')<<setw(30)<<"Distance between Circle 2 and Rectangle 1 is "<<circle2.computeDistance(&rectangle1)<<endl;
    cout<<left<<setfill('.')<<setw(30)<<"Distance between Square 1 and Circle 3 is "<<square1.computeDistance(&circle3)<<endl;
    cout<<endl;


    cout<<left<<setfill('.')<<setw(30)<<"Total area"<<computeTotalArea(vect)<<endl;
    cout<<left<<setfill('.')<<setw(30)<<"Total perimeter"<<computeTotalPerimeter(vect)<<endl;
    cout<<endl;

    cout<<"Perimeters sorted in descending order is: ";
    sortPeri(vect);
    cout<<endl;

    countShapes(vect);
    cout<<"\n\nPrint only Circles"<<endl;
    printOnlyCircle(vect);


    return 0;
}







