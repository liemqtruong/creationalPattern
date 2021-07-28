#include <iostream>
#include <functional>
#include <tuple>
#include <memory>
#include <unordered_map>

using namespace std;

class Shape {
    public:
    virtual tuple<string> draw(tuple<string>){ 
        cout<<"Shape::draw()" << endl;
        return make_tuple("1111");
    }
};

class Triangle : public Shape {
    public:
    static shared_ptr<Triangle> getInstance(){
        return make_shared<Triangle>(Triangle());
    }
    
    virtual tuple<string> draw(tuple<string> str) override{
        cout << "Triangle::draw " << get<0>(str) << endl;
        return str;
    }
    Triangle(){}
};

class Circle : public Shape {
    public:
    static shared_ptr<Circle> getInstance(){
        return make_shared<Circle>(Circle());
    }
    
    virtual tuple<string> draw(tuple<string> str) override{
        cout << "Circle::draw " << get<0>(str) << endl;
        return str;
    }

    Circle(){}
};

int inc (int i){
    return i+1;
}

class ShapeManager {
	public:
	ShapeManager(){
		map["Triangle"] = Triangle::getInstance;
		map["Circle"] = Circle::getInstance;
	}
	
	shared_ptr<Shape> getShape(string key){
	    try{
		    return map[key]();
	    }catch( exception& e){
	        cout << "Caught exeption: " << e.what() << endl;
			return 0;
	    }
	}
	private:
    unordered_map<string, function<shared_ptr<Shape>()>> map;
	
		
};



int main() {
    ShapeManager sm;
    string key = "Circle";
	auto f = sm.getShape(key);
	if ( f == 0 ){
	    cout << "Return is 0" << endl;
	}else {
	    f->draw(make_tuple("1234"));	    
	}

    //auto func = map[key];
    //func()->draw(make_tuple("Hello"));
    
    //map[key]()->draw(make_tuple("Hi"));
    
    
    //shared_ptr<Shape> s = Triangle::getInstance();
    //tuple<string> str = make_tuple("Hello");
    //s->draw(str);
    
    
    //function<int(int)> increment = inc;
    //cout << increment(3) << endl;
    
}
